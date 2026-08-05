# Wind Waker-style Cel Shading

Developer notes for the cel-shading feature on the `wind-waker-style-cel-shading` branch. References
are by file + symbol (line numbers drift). Start with [`README.md`](./README.md) for how this fits
the other features.

> **Naming:** the GUI says **"Cel Shading"**; every internal identifier — code, CVars, GBI commands —
> uses **`Toon`/`ToonLighting`**. The CVar keys were kept through the rename so existing settings
> survive; only labels and tooltips say "Cel Shading".

## What it does

Per-pixel, single-dominant-light cel shading, applied only to actors/objects (Link, NPCs, enemies,
items, pots, …) — never the static world. Each lit object is re-lit by one key light through a soft
half-Lambert ramp (`smoothstep(N·L)`), giving the Wind Waker two-tone look. One key per object is
the WW rule — multiple lights break the toon look. On by default.

## Architecture: two layers

| Layer | Repo | Responsibility |
|-------|------|----------------|
| **Policy** (game) | `soh/` | Which light is the key, how it eases between sources, the look tuning. Pushes everything the renderer needs. |
| **Transport** (renderer) | `libultraship/` Fast3D | The per-pixel relight: marks which draws to relight, forwards the normal + one key light, ramps `N·L` in the fragment shader. Reads no SoH config. |

## Data flow (one frame)

1. **Bracket the actor loop.** `func_800315AC` in `soh/src/code/z_actor.c` wraps the actor draw loop
   with `gSPToon(true/false)` on both `POLY_OPA` and `POLY_XLU` (CVar-gated). This scopes the effect
   to objects only.
2. **Per actor, choose + emit the key.** `Actor_Draw` fires the `OnActorDraw` hook after
   `Lights_Draw`. `HandleActorDraw` in `soh/soh/Enhancements/Graphics/ToonLighting.cpp` picks the
   key (closest in-range point light, else the brighter of sun/moon), eases it with per-actor
   persistent state, and emits `gSPToonKey(dir, color)` to both display lists. Emits are deduped:
   if the quantized key matches the last one emitted this pass (e.g. everything lit by the sun),
   nothing is emitted and the objects batch together in one draw.
3. **Renderer consumes it.** In `libultraship/src/fast/interpreter.cpp`:
   `gfx_set_toon_handler_custom` sets `mRdp->toon`; `gfx_set_toon_key_handler_custom` stores the
   world-space key and flushes the previous object's batch (so each object gets its own key);
   `GfxSpVertex` forwards the world-space vertex normal and forces vertex shade to white;
   `GfxSpTri1` selects the `TOON` shader variant and packs the normal into the VBO;
   `Interpreter::Flush` pushes the key as a per-draw uniform via `SetToonLighting`.
4. **Shader ramps it.** The toon variant of each backend's fragment shader computes
   `t = N·L*0.5+0.5`, `ramp = smoothstep(center−soft, center+soft, t)`, and blends a two-tone
   `albedo * mix(shadow, lit, ramp)`.

Once per frame, `OnToonFrameUpdate` (ToonLighting.cpp) pushes the ramp tuning to the renderer via
`SetToonRamp`.

## Key selection

- `ToonClosestPointLight` — the closest in-range point light (torch, fairy, bomb, Deku stick) wins
  outright; brightness is ignored, so flickering torches give a stable key. "In range" is the
  light's radius × `PointLightRange`.
- With Navi opted out (`UseNaviLight` off), her two emitted lights are skipped by address — she
  orbits Link and blinks, so she otherwise steals the key constantly.
- `ToonEnvKey` — fallback to the sun or moon, whichever is currently brighter.
- Easing: `ToonSlerp` (antipode-safe direction slerp) + `ToonSmoothDamp` (critically-damped colour),
  state keyed by actor pointer, evicted on `OnActorDestroy`.

## Excluded actors

`ToonActorExcluded` (ToonLighting.cpp) opts an actor out of both the relight and the actor shadow:
all doors (`ACTORCAT_DOOR`), the Great Deku Tree, water-box surfaces, trees/bushes (`En_Wood02`),
and everything whose ActorDB name starts with `Bg_Spot` (overworld scenery: bridges, fences, rocks —
they read as environment, not objects). Around an excluded actor the bracket flips OFF and back ON,
deduped by `sToonEnabled`.

## Where the code lives

### SoH (game-side policy)

- `soh/soh/Enhancements/Graphics/ToonLighting.cpp` — the brain (shared with Actor Shadows; see that
  doc for the shadow half). `HandleActorDraw`, key selection/easing, `OnToonFrameUpdate`,
  `RegisterToonLighting` (hooks run while cel shading OR actor shadows is enabled).
- `soh/src/code/z_actor.c` — `// SOH [Enhancement]`-marked: the `gSPToon` bracket in
  `func_800315AC`, the `OnActorDraw` callout in `Actor_Draw`.
- Hook declarations: `soh/soh/Enhancements/game-interactor/GameInteractor_{HookTable.h,Hooks.h,Hooks.cpp}`.
- GUI: `soh/soh/SohGui/SohMenuWindWakerStyle.cpp`, page **Wind Waker Style → Cel Shading**.

### libultraship (renderer transport)

- GBI: `include/libultraship/libultra/gbi.h` — `G_SETTOON 0x41`, `G_SETTOONKEY 0x4a`, the
  `gSPToon`/`gSPToonKey` macros. `include/fast/lus_gbi.h` — `OTR_G_SETTOON`/`OTR_G_SETTOONKEY`.
- `src/fast/interpreter.cpp` + `include/fast/interpreter.h` — the handlers, `SelectToonLight`,
  normal forwarding in `GfxSpVertex`, `TOON` variant selection + VBO packing in `GfxSpTri1`,
  `SetToonLighting` push in `Flush`. `ShaderOpts::TOON`, `RDP::toon`, `RSP::toon_*`,
  `LoadedVertex::nx/ny/nz`, `VBO_MAX_FLOATS_PER_VERTEX`.
- `include/fast/backends/gfx_rendering_api.h` — `SetToonLighting`/`SetToonRamp` + the `mToon*`
  members backends read.
- Per-backend uniform plumbing: `gfx_opengl.cpp/.h`, `gfx_metal.cpp/.h` + `gfx_metal_shader.cpp`,
  `gfx_direct3d11.cpp` + `gfx_direct3d_common.h` (`PerToonCB`).
- Shaders (packed into `soh.o2r`): `src/fast/shaders/{opengl/default.shader.vs,.fs,
  metal/default.shader.metal, directx/default.shader.hlsl}` — the `@if(o_toon)` blocks.
- `include/fast/toon_shading.h` — shared `TOON_SHADING_DEFAULT_*` fallbacks.

## CVars

`gEnhancements.Graphics.ToonLighting.*` unless noted. Slider defaults live in the GUI `Options` AND
as `kDefault*` constants (ToonLighting.cpp / toon_shading.h) — keep them in sync.

| CVar | Default | Meaning |
|---|---|---|
| `Enabled` | **1** | Master toggle. |
| `RampCenter` | 0.5 | Where dark→light sits on the ramp. |
| `RampSoftness` | 0.02 | Width of the transition band. |
| `HighlightIntensity` | 0.6 | Brightness of the lit band. |
| `ShadowIntensity` | 0.6 | How dark the shadow band gets. |
| `PointLightRange` | 1.5 | × a point light's radius, for key selection only. |
| `UseNaviLight` | 1 | Off = Navi's light never becomes a key. |
| `TransitionTime` | 1.0 | Seconds for the eased key travel between sources. |
| `gDeveloperTools.ToonLighting.ShowDebug` | 0 | "Light Source Viewer": rays per candidate light, range rings, chosen-key needle. |
| `gDeveloperTools.ToonLighting.HighlightBands` | 0 | "Highlight Lit Objects": relit objects drawn flat white/black. |

## Invariants & gotchas

- **VBO stride lockstep.** `VBO_MAX_FLOATS_PER_VERTEX` drives the CPU `mBufVbo` allocation AND every
  backend's GPU vertex buffer size (D3D11 `vertex_buffer` ByteWidth, Metal
  `kInitialVertexBufferLength`). Change it in one place only, or buffers overrun.
- **Shader-id bit packing.** The loaded-shader id packs above the shader-opt bits
  (`shader.id << N` in `interpreter.cpp` — encode in `GfxSpTri1`, decode in `gfx_cc_get_features`).
  Adding an opt bit means bumping that shift.
- **World-space normal, not object space.** A skeletal actor batches every limb (each under its own
  modelview) into one draw with a single key uniform; only world-space normals share a frame with
  the world-space key. `GfxSpVertex` does the object→world transform.
- **Per-object flush.** `gfx_set_toon_key_handler_custom` calls `Flush()` first, so Fast3D's
  batching can't apply one object's key to another's geometry. Game-side, every `gSPToon` edge
  clears the key-dedup state (the renderer expects a fresh key per toon-on).
- **Attribute order must match** across the VBO packing in `GfxSpTri1`, the 3 shader templates, the
  OGL attrib binding, and the D3D11 input layout — `… grayscale, TOON normal, inputs`.
- **D3D11 toon constant buffer is at register `b2`.**
- **Shader edits need an o2r regen.** After editing any `default.shader.*`, run
  `make GenerateSohOtr`. Pure C++/GUI changes don't.

## Branch & base

Built on SoH's stable release tag `9.2.3` (not `develop`), with `libultraship` on the matching fork
branch. Consequence: this build uses the 9.2.3 save format. The develop-only regression fixes
(PR #1121 tile-size rounding, the `G_VTX_OTR_HASH` desync guard) are intentionally absent — they
patch bugs that don't exist on the stable base. If a rendering bug reproduces here, check whether it
also exists on stable before reaching for those patches.

## Build & test (macOS)

Build per [`README.md`](./README.md#build--test-macos). This is the one feature that touches
shaders, so shader edits need `make GenerateSohOtr`. Good visual checks: the toon look on actors
with the sliders, the Light Source Viewer near a torch, and Lake Hylia water at high FPS (should be
clean — the proof the stable base sheds the develop-era regressions).
