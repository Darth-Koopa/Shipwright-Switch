# Wind Waker-style Light Casting

A developer/agent orientation for the **light-casting** feature on the `wind-waker-style-cel-shading`
branch. Read this instead of the diffs to get caught up. References are by **file + symbol** (not line
numbers, which drift). Start with [`README.md`](./README.md) for how this fits the other two features.

This is the companion to [`wind-waker-style-cel-shading.md`](./wind-waker-style-cel-shading.md):
**cel shading lights the _objects_** (Link, NPCs, items) via a forward per-object relight; **light
casting lights the _world_** (floors, walls) via point-light pools. The two are independent and scoped
to opposite halves of the scene.

> **Naming note:** the user-facing GUI says **"Light Casting"**, but every internal identifier — code,
> CVars, the GBI command — uses **`WorldLighting`** / **`Stencil`**. CVar keys are
> `gEnhancements.Graphics.WorldLighting.*`.

---

## What it does

Each in-range **point light** (torch, fairy, bomb flash, …) casts a **pool of light onto the static
world geometry** around it, the way Wind Waker's "Bonbori" torch lights do: a **faceted, slowly
tumbling, gently pulsing polygon of light** that **conforms to and is occluded by** the surfaces inside
the light's reach. It is scoped to the **world only** — placed objects/actors keep their own cel
shading (and are *not* tinted by the pools). Off by default (experimental).

It also includes a **Wind Waker flame flicker** that replaces OoT's jagged per-frame torch flicker
(white noise) with a slow, eased random-walk — applied at the light *source*, so it calms the scene
lighting, the vanilla glow, and the cast pools together.

The look and timing are matched to the **noclip.website** reproduction of WW; see
[`wind-waker-bonbori-light.md`](./wind-waker-bonbori-light.md) for the
reverse-engineered reference this feature targets.

## The technique: stencil light volumes

The pool is **not** a soft point light. It is the **screen-space intersection of a low-poly icosphere
with the world**, found with a classic **stencil light-volume (shadow-volume-style z-fail) pass**, then
tinted additively. Per light, three passes:

1. **Mask A** — render the icosphere **back** faces, depth-tested vs the scene, **stencil += 1 on
   depth-fail** (z-fail). Color/depth writes off.
2. **Mask B** — render the icosphere **front** faces, same, **stencil −= 1 on depth-fail**.
   → stencil = 1 **exactly where a world surface lies inside the icosphere volume** (the faceted
   polygon cross-section, correctly self-occluded).
3. **Composite** — render the icosphere **back** faces with **no depth test**, **stencil test == ref(0)
   → draw, zero-on-pass** (self-clearing), additively-ish blending the light color × intensity. Back
   faces avoid near-plane clipping when the camera is inside the volume; the stencil mask alone confines
   the fill to the right pixels.

Emitted into **`POLY_OPA`** *after the room is drawn but before the bulk of the actor loop*, so at draw time
the depth buffer holds **world-only** depth — pools clip to the world, are occluded by (and never tint)
opaque actors, and our passes write no depth so actor depth-testing is unaffected.

> **Note (receiver pre-pass):** the `OnPlayDrawWorldLights` flush now fires from inside the actor loop
> (`func_800315AC`), just after the actor-shadow **walkable-floor receiver pre-pass** rather than from
> `Play_Draw`. This lets pools also fall on the few floors that are actors (drawbridge, trap floor, …) while
> still preceding every other actor. See `wind-waker-actor-shadows.md` → "Shadow & light receivers."

---

## Architecture: two layers (same split as cel shading)

| Layer | Repo | Responsibility |
|-------|------|----------------|
| **Policy** (game-side) | `soh/` | Which lights cast, where (world-space), the icosphere geometry, the 3-pass sequence, the WW tumble/flicker model, Navi handling, the GUI. |
| **Transport** (renderer) | `libultraship/` (Fast3D) | A generic **stencil-mode** the interpreter can set per draw, applied across all three backends. Knows nothing OoT-specific. |

## Data flow (one frame)

1. **Source flame flicker (during actor Updates).** Flame actors set their light color every update
   (`Obj_Syokudai` etc. → `Lights_PointSetColorAndRadius`). That function is intercepted in
   `soh/src/code/z_lights.c` (CVar-gated): `WorldLighting_ApplyFlameFlicker` replaces the white-noise
   brightness with a slow random-walk **for lights it detects as flickering** (large per-frame jump),
   leaving steady/smooth lights (e.g. the mirror-shield beam) alone.
2. **Cast pools (during the actor loop).** From `func_800315AC`, after the room + actor-shadow receiver
   pre-pass and before the rest of the actors, the `OnPlayDrawWorldLights` GameInteractor hook fires
   (CVar-gated). `DrawWorldLights`
   (`WorldLighting.cpp`) walks `play->lightCtx.listHead` and, per point light, emits the 3-pass stencil
   volume into `POLY_OPA`, tinted by the light's live color, sized/spun by the WW model.
3. **Stencil state crosses to the renderer.** Each pass emits `gSPStencil(mode)`; the interpreter's
   `gfx_set_stencil_handler_custom` **flushes the pending batch then `SetStencilMode(mode)`**; each
   backend applies the matching stencil + color-write state in `DrawTriangles`. A final
   `gSPStencil(OFF)` resets before the actors draw.

---

## Where the code lives

### SoH (game-side policy)

- **`soh/soh/Enhancements/Graphics/WorldLighting.cpp`** — the brain. Key symbols:
  - `BuildIcosphere` / `EmitIcosphere` — generates a **level-2 icosphere** (42 unique verts, 80 faces)
    expanded to **240 per-face verts** (so each `gSPVertex` load ≤ the 32-vertex cache) and emits it in
    **8 chunks of 30** live during draw.
  - `WorldLighting_ApplyFlameFlicker` (`extern "C"`, called from `z_lights.c`) — the **source** flame
    flicker: per-light slow random-walk, jump-based flame detection, hue-preserving brightness replace.
  - `WWEase` — Wind Waker's `cLib_addCalc2` easing (first-order exp + per-tick slew cap), frame-rate
    corrected from WW's 30 Hz to our 20 Hz.
  - `WorldLightGetState` — get-or-create per-light animation state (tumble angles + size/alpha
    random-walks), keyed by the frame-stable `LightInfo*`, pruned each frame by generation.
  - `WorldLightLoadMatrix` — centers on the light, applies the **two-axis tumble** (Y then X), scales.
  - `WorldLightMaskPass` / `WorldLightCompositePass` / `DrawLightPool` — the 3-pass stencil sequence.
  - `DrawWorldLights` — the per-frame light walk; advances tumble + size/alpha flicker; selects Navi.
  - `RegisterWorldLighting` + `RegisterShipInitFunc initFunc(...)` — `COND_HOOK`s `OnPlayDrawWorldLights`
    only while `Enabled` (default 0).
- **`soh/src/code/z_actor.c`** — `func_800315AC` fires `GameInteractor_ExecuteOnPlayDrawWorldLights(play)`
  just after the actor-shadow receiver pre-pass (moved here from `z_play.c` so pools also reach the walkable
  floor actors; see `wind-waker-actor-shadows.md`). The old `z_play.c` call site now only carries a breadcrumb.
- **`soh/src/code/z_lights.c`** — two `// SOH [Enhancement]` edits:
  - `Lights_PointSetColorAndRadius` — the flame-flicker interception (calls `WorldLighting_ApplyFlameFlicker`).
  - `Lights_DrawGlow` — early-returns to **hide the vanilla billboarded glow circles** while light
    casting is on (unless `ShowVanillaGlow`).
- **GameInteractor hook `OnPlayDrawWorldLights`** — `GameInteractor_{HookTable.h,Hooks.h,Hooks.cpp}`.
- **`soh/soh/SohGui/SohMenuSettings.cpp`** — the **Settings → Light Casting** page (sliders + Reset).

### libultraship (renderer transport)

- **GBI command** — `include/libultraship/libultra/gbi.h`: `G_SETSTENCIL 0x46` + the `gSPStencil(pkt,
  mode)` macro (mirrors `gSPToon`). `include/fast/lus_gbi.h`: `OTR_G_SETSTENCIL = OPCODE(0x46)`.
- **`src/fast/interpreter.cpp`** — `gfx_set_stencil_handler_custom` (flush-then-`SetStencilMode`) +
  its entry in the `otrHandlers` table.
- **`include/fast/backends/gfx_rendering_api.h`** — `enum class StencilMode { Off, VolumeIncr,
  VolumeDecr, Composite }`, the base `SetStencilMode(int)` + `mStencilMode` member.
- **Per-backend stencil application** (read `mStencilMode` in `DrawTriangles`):
  - `gfx_opengl.cpp` — already had `GL_DEPTH24_STENCIL8`; just adds `glStencilFunc`/`glStencilOp`.
  - `gfx_metal.cpp` (+`gfx_metal.h`) — a **separate `Stencil8` texture** as the render pass's
    `stencilAttachment` (the depth texture and `GetPixelDepth` are left untouched), + stencil ops on the
    per-draw `DepthStencilDescriptor`.
  - `gfx_direct3d11.cpp` (+`gfx_direct3d_common.h`) — unified all feature levels to combined
    **`R24G8` / `D24_UNORM_S8_UINT`** (so a stencil plane always exists; `GetPixelDepth` reads the
    `R24_UNORM_X8` SRV), + stencil ops in the depth-stencil state.

No shader/asset changes — the pool uses the existing flat-color combiner + render modes, so **no
`soh.o2r` regen is needed** (unlike cel shading).

---

## CVars

Internal prefix is `WorldLighting`; the GUI shows "Light Casting".

| CVar (`gEnhancements.Graphics.WorldLighting.*`) | Default | Meaning |
|---|---|---|
| `Enabled` | **0** | Master toggle (also gates the always-on flame flicker). |
| `SphereSize` | 1.0 | Pool size, × the light's radius. |
| `RotationSpeed` | 1.0 | × the Wind Waker two-axis tumble rate (1 = authentic). |
| `Intensity` | 1.0 | Pool brightness (→ composite blend alpha). |
| `SizeFlicker` | 1.0 | Depth of the WW size pulse (1 = authentic ±5%; 0 = steady). The dominant flicker. |
| `UseNaviLight` | 0 | Also cast a pool from Navi (off: her fast movement pops). |
| `NaviSphereSize` | 0.6 | Navi pool size (× radius), separate from torches. Shown when Navi is on. |
| `NaviIntensity` | 0.6 | Navi pool brightness (white reads brighter than torch yellow). Shown when Navi is on. |
| `NaviRotationSpeed` | 0.5 | Navi tumble rate (× WW rate). Shown when Navi is on. |
| `ShowVanillaGlow` | 0 | Off hides the vanilla billboarded torch glow circles (they clash with the pools). |
| `FlickerSpeed` | 1.0 | Rate of the WW flame flicker (× authentic). |
| `DekuStickLight` | **1** | Register a point light at a lit held Deku stick's burning tip, so it lights objects (cel), casts shadows, and (with casting on) casts a pool — like a torch. Works even when casting is off (feeds cel/shadows). See README → "Shared light sources" and `DekuStickLight.cpp`. |
| `DekuStickSphereSize` | 0.5 | The Deku stick pool's size (× radius), separate from `SphereSize`. `DrawWorldLights` identifies the stick light by address (`DekuStickLight_GetActiveLightInfo()`) and substitutes this for the global size. |

Slider defaults live in the GUI `Options` AND as `kDefault*` constants in `WorldLighting.cpp` — keep
them in sync. (Orphaned keys from removed controls — `FlickerSmoothing`, `WindWakerFlicker`,
`SizeBrightness` — may linger in old configs; harmless.)

## The Wind Waker flicker model (matched to noclip)

All "per-frame" values below are converted from WW's **30 Hz** to our **20 Hz** by running in *seconds*
+ `WWEase`'s `dt*30` correction. Random source is uniform `Rand_ZeroOne()`.

- **Two-axis tumble** (`WorldLightLoadMatrix`): Y `kWWRotYRate ≈ 0.598 rad/s`, X `kWWRotXRate ≈ 0.736
  rad/s` (non-harmonic 16:13 → never visibly loops), no Z; scaled by `RotationSpeed`.
- **Size flicker** (dominant pulse): re-roll a target every **0.10–0.30 s** to **1.0 ± 5%·`SizeFlicker`**,
  ease with `WWEase(0.4, 0.05)`. Drives the icosphere scale. *Decoupled from the brightness noise* —
  this is the fix that made it read "slow/organic" instead of jagged.
- **Brightness flicker** (subtle fine grain): re-roll the pool alpha every **0–0.167 s** to **[0.90,
  1.0]**, ease with `WWEase(1.0, 0.08)`.
- **Source flame flicker** (`WorldLighting_ApplyFlameFlicker`): slow random-walk in **[0.60, 1.0]** of
  full bright, new target every `0.25 s / FlickerSpeed`; **flame detection** = per-frame brightness jump
  `> 12` (with an 8-update sticky hold) so only white-noise flames are transformed; hue preserved by
  scaling channels.
- **Navi** is excluded from the size/alpha flicker (her light is constant white — confirmed in
  `En_Elf`); any jitter is her movement.

---

## Invariants & gotchas (don't break these)

- **Emit into `POLY_OPA`, not `POLY_XLU`.** That's what makes the depth buffer world-only at our pass
  (actors not yet drawn) → pools don't tint actors and actors correctly occlude pools. Moving it to XLU
  reintroduces actor-tinting.
- **`StencilMode` values must match** the `WL_STENCIL_*` defines in `WorldLighting.cpp`
  (Off=0, VolumeIncr=1, VolumeDecr=2, Composite=3).
- **Reset stencil to OFF** at the end of `DrawWorldLights` (before actors), every frame.
- **Mask passes are invisible via prim alpha 0 + no alpha-compare** (`G_RM_AA_ZB_XLU_SURF`), *not* a
  color-write mask — Fast3D's Metal/D3D11 bake color-write/blend into the pipeline, so they can't be
  toggled per-draw. Same reason there's **no true additive blend**: overlapping pools alpha-blend (they
  don't super-brighten). Adding additive would need a per-backend pipeline variant (deferred).
- **Face culling is CPU-side** in Fast3D (GPU cull is `None`), so the mask passes select back/front
  faces with `G_CULL_FRONT` / `G_CULL_BACK` geometry-mode and Fast3D's CPU culler honors it.
- **Metal:** the stencil plane is a **separate `Stencil8` texture** (depth + `GetPixelDepth`
  untouched). `MTL::TextureDescriptor::texture2DDescriptor(...)` returns an **autoreleased** object —
  **do not `->release()` it** (doing so double-frees → SIGBUS at startup; this bit us once).
- **D3D11:** combined `D24S8` on all feature levels; the depth SRV for `GetPixelDepth` is
  `R24_UNORM_X8_TYPELESS`. (Compiles on macOS but only runs on Windows — Metal is the macOS runtime.)
- **Icosphere stride:** emit via `gSPVertex(POLY_OPA_DISP++, (uintptr_t)&sIcoVtx[...], 30, 0)` — the
  game-side `gSPVertex` is a wrapper taking a `uintptr_t` (cast required) that also runs an OTR
  resource-sig check, so emit it **live during draw** (never bake it into a DL at init).
- **Per-light state** is keyed by `LightInfo*` (actor-owned, frame-stable), pruned each frame by a
  generation counter; the flicker map is cap-cleared at 256 entries.

---

## Build & test (macOS)

Build per [`README.md`](./README.md#build--test-macos) — **no `GenerateSohOtr`** (no shader changes;
fixed-function stencil + the existing flat-color combiner). Enable **Settings → Light Casting**, go
to a torch/fairy/bomb flash; the pool should be a faceted polygon conforming to the floor/wall, slowly
tumbling and pulsing, occluded by (and not tinting) actors, with the vanilla glow circle hidden. Good
checks: a lit torch (size pulse + tumble), two nearby torches (overlap), Lake Hylia/dungeon torches.

## Status & next

- **Done:** the full stencil light-volume pipeline across all 3 backends; the WW flicker model matched
  to noclip; Navi controls; vanilla-glow suppression.
- **Known/deferred:** overlapping pools alpha-blend rather than additively brighten (needs a per-backend
  additive pipeline variant); the pool tint uses each light's color rather than WW's fixed warm orange
  (kept general on purpose); the torch *flame sprite* still animates on its own (only the *light* is
  re-flickered).
- **Next phase — shadows:** the stencil buffer + per-light-volume machinery here (the `StencilMode`
  API, the `gSPStencil` opcode, the icosphere/volume emission, the world-only-depth `POLY_OPA`
  insertion point) is the foundation for casting **shadows** on the environment.
