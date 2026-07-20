# Wind Waker-style Cel Shading

A developer/agent orientation for the cel-shading feature on the `wind-waker-style-cel-shading`
branch. Read this instead of the diffs to get caught up. References are by **file + symbol** (not line
numbers, which drift). Start with [`README.md`](./README.md) for how this fits the other two features.

> **Naming note:** the user-facing GUI says **"Cel Shading"**, but every internal identifier — code,
> CVars, GBI commands — uses **`Toon`/`ToonLighting`**. They are the same feature. The CVar keys
> (`gEnhancements.Graphics.ToonLighting.*`) were intentionally kept so existing settings/saves survive
> the rename; only labels and tooltips say "Cel Shading".

---

## What it does

Per-pixel, **single-dominant-light** cel shading, applied **only to actors/objects** (Link, NPCs,
enemies, items, pots, …) — never the static world/rooms. Each lit object is re-lit by one key light
through a soft half-Lambert ramp (`smoothstep(N·L)`), giving the Wind Waker two-tone look. The single
key per object is the WW rule (multiple lights break the toon look). Enabled by default on this modded
build.

## Architecture: two layers

The feature is split so the cross-platform framework never needs to know anything OoT-specific.

| Layer | Repo | Responsibility |
|-------|------|----------------|
| **Policy** (game-side) | `soh/` | *Which* light is the key, *how* it eases between sources, the look tuning. Pushes everything the renderer needs. |
| **Transport** (renderer) | `libultraship/` (Fast3D) | The per-pixel relight: marks which draws to relight, forwards the normal + one key light, ramps `N·L` in the fragment shader. Reads no SoH config. |

## Data flow (one frame)

1. **Bracket the actor loop.** `func_800315AC` in `soh/src/code/z_actor.c` wraps the actor draw loop
   with `gSPToon(POLY_OPA/XLU_DISP++, true)` … `gSPToon(..., false)` (CVar-gated). This is what scopes
   the effect to objects only.
2. **Per actor, choose + emit the key.** After `Lights_Draw` in `Actor_Draw` (same file), a CVar-gated
   `GameInteractor_ExecuteOnActorDraw(actor)` fires the `OnActorDraw` hook. `HandleActorDraw` in
   `soh/soh/Enhancements/Graphics/ToonLighting.cpp` picks the key light (closest in-range point light,
   else the day/night sun/moon), eases it (per-actor persistent state), and emits
   `gSPToonKey(dir, color)`.
3. **Renderer consumes it.** In `libultraship/src/fast/interpreter.cpp`:
   `gfx_set_toon_handler_custom` sets `mRdp->toon`; `gfx_set_toon_key_handler_custom` stores the world
   key + **flushes the previous object's batch** (so batched objects each get their own key);
   `SelectToonLight` caches the key into the RSP; `GfxSpVertex` forwards the **world-space** vertex
   normal and forces vertex shade to white; `GfxSpTri1` selects the `TOON` shader variant and packs the
   normal into the VBO; `Interpreter::Flush` pushes the key as a per-draw uniform via `SetToonLighting`.
4. **Shader ramps it.** The toon variant of each backend's fragment shader computes
   `t = N·L*0.5+0.5`, `ramp = smoothstep(center-soft, center+soft, t)`, and blends a two-tone
   `albedo * mix(shadow, lit, ramp)`.

Once per frame, `OnToonFrameUpdate` (ToonLighting.cpp) pushes the ramp tuning (center/softness/
highlight/shadow + the debug-view flag) to the renderer via `SetToonRamp`.

---

## Where the code lives

### SoH (game-side policy)

- **`soh/soh/Enhancements/Graphics/ToonLighting.cpp`** — the brain. Key symbols:
  - `HandleActorDraw` — choose key, ease, emit `gSPToonKey` (registered on the `OnActorDraw` hook).
  - `ToonClosestPointLight` / `ToonEnvKey` — key selection (proximity wins; brightness ignored).
  - `ToonSlerp` / `ToonSmoothDamp` — antipode-safe direction + critically-damped colour easing.
  - `OnToonFrameUpdate` — pushes ramp params via `SetToonRamp` once/frame.
  - `RegisterToonLighting` + `RegisterShipInitFunc initFunc(...)` — `COND_HOOK`s the hooks only while
    enabled. Reads `Enabled` defaulting to **1** (on by default).
  - `GetRenderingApi()` — `Ship::Context::GetInstance()->GetWindow()` → `Fast3dWindow` → interpreter →
    `GetCurrentRenderingAPI()`.
- **`soh/src/code/z_actor.c`** — `// SOH [Enhancement] Toon lighting` markers: the `gSPToon` bracket in
  `func_800315AC` and the `OnActorDraw` call in `Actor_Draw`. All CVar-gated (default 1).
- **GameInteractor hook `OnActorDraw`** — declared/dispatched in
  `soh/soh/Enhancements/game-interactor/GameInteractor_{HookTable.h,Hooks.h,Hooks.cpp}`.
- **`soh/soh/SohGui/SohMenuSettings.cpp`** — the **Settings → Cel Shading** page (sidebar entry, the
  6 sliders, the "Reset All to Defaults" button, the "Options"/"Debug" titles, the two debug toggles).

### libultraship (renderer transport)

- **GBI commands / macros**
  - `include/libultraship/libultra/gbi.h` — `G_SETTOON 0x41`, `G_SETTOONKEY 0x4a`; the `gSPToon` /
    `gsSPToon` / `gSPToonKey` macros (mirror `gSPGrayscale`).
  - `include/fast/lus_gbi.h` — `OTR_G_SETTOON` / `OTR_G_SETTOONKEY` opcode constants.
- **`src/fast/interpreter.cpp` + `include/fast/interpreter.h`**
  - Handlers `gfx_set_toon_handler_custom`, `gfx_set_toon_key_handler_custom` (+ entries in the
    `otrHandlers` dispatch table).
  - `Interpreter::SelectToonLight`, `GfxSpVertex` (normal forward), `GfxSpTri1` (`use_toon`, VBO
    packing), `Interpreter::Flush` (`SetToonLighting`).
  - `ShaderOpts::TOON` opt bit; `CCFeatures::opt_toon`; `RDP::toon`; `RSP::toon_*`;
    `LoadedVertex::nx/ny/nz`; `VBO_MAX_FLOATS_PER_VERTEX`.
- **`include/fast/backends/gfx_rendering_api.h`** — base-class `SetToonLighting` / `SetToonRamp` and the
  `mToon*` members the backends read.
- **Per-backend uniform plumbing** — `src/fast/backends/gfx_opengl.cpp` (+`.h`),
  `gfx_metal.cpp` (+`gfx_metal.h`, `gfx_metal_shader.cpp`), `gfx_direct3d11.cpp`
  (+`gfx_direct3d_common.h` `PerToonCB`).
- **Shaders** (packed into `soh.o2r`) — `src/fast/shaders/opengl/default.shader.vs` + `.fs`,
  `metal/default.shader.metal`, `directx/default.shader.hlsl`. The `@if(o_toon)` blocks add the
  `aNormal`/`vNormal` attribute and the ramp math.
- **`include/fast/toon_shading.h`** — shared `TOON_SHADING_DEFAULT_*` fallbacks.

---

## CVars

Internal prefix is `ToonLighting`; the GUI shows "Cel Shading".

| CVar (`gEnhancements.Graphics.ToonLighting.*` unless noted) | Default | Meaning |
|---|---|---|
| `Enabled` | **1** | Master toggle (on by default; respected if explicitly turned off). |
| `RampCenter` | 0.5 | Where dark→light sits on the ramp. |
| `RampSoftness` | 0.02 | Width of the transition band (UI shows 2 decimals, steps 0.01). |
| `HighlightIntensity` | 0.6 | Brightness of the lit band. |
| `ShadowIntensity` | 0.6 | How dark the shadow band gets (1 = down to ambient). |
| `PointLightRange` | 1.5 | × a point light's radius, for **key selection only** (never the game's real lighting). |
| `TransitionTime` | 1.0 | Seconds for the eased key travel between sources. |
| `gDeveloperTools.ToonLighting.ShowDebug` | 0 | "Light Source Viewer": rays per candidate light + range rings + the chosen-key needle. |
| `gDeveloperTools.ToonLighting.HighlightBands` | 0 | "Highlight Lit Objects": every relit object drawn flat white(lit)/black(shadow), albedo discarded. |

Selection defaults live in `ToonLighting.cpp` (`kDefault*`); ramp/shader defaults in the slider
`Options` AND `toon_shading.h` — keep them in sync.

---

## Invariants & gotchas (don't break these)

- **VBO stride lockstep.** `VBO_MAX_FLOATS_PER_VERTEX` (= 40, was 32) drives the CPU `mBufVbo`
  allocation AND every backend's GPU vertex buffer (D3D11 `vertex_buffer` ByteWidth, Metal
  `kInitialVertexBufferLength`). Change it in one place only or buffers overrun.
- **Shader-id bit packing.** `TOON` is opt bit **17**; the loaded-shader id packs **above** it
  (`shader.id << 18` in `interpreter.cpp` — encode in `GfxSpTri1`, decode in `gfx_cc_get_features`).
  Adding another opt bit means bumping that shift again.
- **World-space normal, not object space.** A skeletal actor batches every limb (each under its own
  modelview) into one draw with a single key uniform; only world-space normals are all in the same
  frame as the world-space key. `GfxSpVertex` does the object→world transform.
- **Per-object flush.** `gfx_set_toon_key_handler_custom` calls `Flush()` first, so Fast3D's batching
  can't apply one object's key to another's geometry.
- **Attribute order must match** across: VBO packing in `GfxSpTri1`, the 3 shader templates, the OGL
  attrib binding, and the D3D11 input layout — it's `… grayscale, TOON normal, inputs`.
- **D3D11 toon constant buffer is at register `b2`** (the first free slot at this LUS base).
- **Shader edits need an o2r regen.** Shaders are packed into `soh.o2r`; after editing any
  `default.shader.*`, run `make GenerateSohOtr`. Pure C++/GUI changes do not.

---

## Branch & base (why it looks like this)

Built on SoH's **last stable release, tag `9.2.3`** (submodule LUS at `fdcaf633`), NOT develop. The
prior `toon-lighting` branch was based on develop and players hit develop-era regressions; basing on
9.2.3 sheds them. Consequence: this build uses the **9.2.3 save format** (develop-build saves won't
load).

Deliberately **excluded**: the develop-era fix commits (PR #1121 tile-size rounding, the
degenerate-`G_VTX_OTR_HASH` desync guard, the `gGfxDesyncTrace` trace) — they patch regressions that
only exist on develop. If a bug reproduces on the stable base, add the relevant fix back; otherwise
leave it out.

Stable-vs-develop adaptations already made (in case you re-derive): shader-id shift `17→18` (stable has
no `SHADER_ID_SHIFT` constant), D3D11 toon CB `b3→b2`, the OpenGL shader is split `.vs`/`.fs`, Metal
`DrawUniforms.textureFiltering` sized to `[6]`, and `GetRawInstance()→GetInstance()` in ToonLighting.cpp.

## Build & test (macOS)

Build per [`README.md`](./README.md#build--test-macos). Cel shading is the **one feature that touches
shaders**, so after editing any `default.shader.*` you **must** run `make GenerateSohOtr` (pure C++/GUI
changes don't). Good visual checks: the toon look on actors with the sliders, the Light Source Viewer,
and **Lake Hylia water at high FPS** (should be clean without #1121 — the proof the stable rebase shed
the develop-era regressions).
