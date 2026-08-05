# Wind Waker-style Light Casting

Developer notes for the light-casting feature on the `wind-waker-style-cel-shading` branch.
References are by file + symbol (line numbers drift). Start with [`README.md`](./README.md) for how
this fits the other features.

Cel shading lights the *objects*; light casting lights the *world*: each point light casts a pool
onto floors and walls. The two are independent and scoped to opposite halves of the scene.

> **Naming:** the GUI says **"Light Casting"** (page: **Wind Waker Style → Lights**); internal
> identifiers use **`WorldLighting`** / **`Stencil`**. CVar keys are
> `gEnhancements.Graphics.WorldLighting.*`.

## What it does

Each in-range point light (torch, fairy, bomb flash, held Deku stick, …) casts a pool of light onto
the world geometry around it, the way Wind Waker's "Bonbori" torch lights do: a faceted, slowly
tumbling, gently pulsing polygon of light that conforms to — and is occluded by — the surfaces
inside its reach. World only: actors keep their cel shading and are never tinted by the pools. Off
by default.

The page also carries two effects that work even with casting off:

- **Improve Flame Flicker** — replaces OoT's per-frame white-noise torch flicker with Wind Waker's
  slow eased random-walk, applied at the light *source*, so the scene lighting, the vanilla glow,
  and the cast pools all calm down together.
- **Navi's Light Tint** — tints Navi's emitted light toward her targeting colour at the source
  (`EnElf_UpdateLights`), so cel shading, her cast pool, and vanilla scene lighting share one colour.

The flicker/tumble model is matched to the noclip.website reproduction of WW; the measured constants
are in [`wind-waker-bonbori-light.md`](./wind-waker-bonbori-light.md).

## The technique: stencil light volumes

The pool is not a soft point light. It is the screen-space intersection of a low-poly icosphere with
the world, found with a stencil light-volume (z-fail) pass, then tinted. Per light, three passes:

1. **Mask A** — icosphere **back** faces, depth-tested vs the scene, stencil += 1 on depth-fail.
   Colour/depth writes off.
2. **Mask B** — icosphere **front** faces, stencil −= 1 on depth-fail. Stencil is now nonzero
   exactly where a world surface lies inside the volume (the faceted cross-section, correctly
   self-occluded).
3. **Composite** — icosphere back faces, no depth test, draw where stencil != 0 and zero it on pass
   (self-clearing), blending the light's colour × intensity. Back faces avoid near-plane clipping
   when the camera is inside the volume.

Emitted into `POLY_OPA` after the room but before the actors, so the depth buffer holds world-only
depth: pools conform to walls/floors, are occluded by actors, and never tint them.

## Data flow (one frame)

1. **Source flame flicker (actor updates).** Flame actors set their light colour every update via
   `Lights_PointSetColorAndRadius` (`soh/src/code/z_lights.c`), which calls
   `WorldLighting_ApplyFlameFlicker` when "Improve Flame Flicker" is on. It replaces the white-noise
   brightness with a slow random-walk for lights it detects as flickering (large per-frame jump),
   leaving steady lights (e.g. the mirror-shield beam) alone.
2. **Cast pools (actor draw loop).** `func_800315AC` (`z_actor.c`) fires `OnPlayDrawWorldLights`
   after the room and the actor-shadow receiver pre-pass, before the rest of the actors — so pools
   also land on the few walkable floors that are actors (drawbridge, trap floor; see the actor-
   shadows doc, "Shadow & light receivers"). `DrawWorldLights` (`WorldLighting.cpp`) walks
   `play->lightCtx.listHead` and emits the 3-pass volume per point light, tinted by the light's live
   colour, sized/spun by the WW model.
3. **Stencil state crosses to the renderer.** Each pass emits `gSPStencil(mode)`; the interpreter's
   `gfx_set_stencil_handler_custom` flushes the pending batch then calls `SetStencilMode(mode)`;
   each backend applies the matching stencil + colour-write state in `DrawTriangles`. A final
   `gSPStencil(OFF)` resets before the actors draw.

## Per-source treatment

`DrawWorldLights` identifies special sources by `LightInfo*` address and gives each its own size,
intensity, and enable:

| Source | Enable | Size / intensity CVars |
|---|---|---|
| Torches & other point lights | `Enabled` | `SphereSize`, `Intensity` |
| Navi | `UseNaviLight` | `NaviSphereSize`, `NaviIntensity` |
| Wild fairies (Kokiri ambient, healing fairies) | `OtherFairyLights` | `WildFairySphereSize`, `WildFairyIntensity` |
| Held lit Deku stick | `DekuStickLight` | `DekuStickSphereSize` (see below) |

## The held Deku stick light (`DekuStickLight.cpp`)

Vanilla OoT draws a flame on a lit Deku stick but emits no light. `DekuStickLight.cpp` registers a
point light at the burning tip (`meleeWeaponInfo[0].tip`) from the `OnPlayerUpdate` hook (reset on
`OnSceneInit` — a new scene rebuilds `lightCtx`). Because all three WW features read the engine's
point-light list, the one light feeds them all: it can become a cel key, it casts a pool, and
shadows follow it.

It is torch-equivalent by construction: radius matched to the wall torch (`obj_syokudai`), and the
same per-frame white-noise brightness a torch has, so the flame-flicker hook smooths it identically.
Its colour is asset-driven: an optional texture (`textures/wind-waker/deku_stick_light_color`,
absent from vanilla archives) is averaged into the light's RGB; without it the light falls back to
OoT's canonical fire colour `{255, 200, 0}`. A texture pack can add that one asset to recolor the
light.

## Where the code lives

### SoH (game-side policy)

- `soh/soh/Enhancements/Graphics/WorldLighting.cpp` — the brain:
  - `BuildIcosphere` / `EmitIcosphere` — a level-2 icosphere (42 verts, 80 faces) expanded to 240
    per-face verts so each `gSPVertex` load fits the 32-vertex cache; emitted in chunks of 30, live
    during draw.
  - `WorldLighting_ApplyFlameFlicker` (`extern "C"`, called from `z_lights.c`) — the source flame
    flicker: slow random-walk, jump-based flame detection, hue-preserving brightness replace.
  - `WWEase` — WW's `cLib_addCalc2` easing (first-order exp + slew cap), frame-rate corrected from
    WW's 30 Hz to our 20 Hz.
  - `WorldLightGetState` — per-light animation state (tumble angles + size/alpha random-walks),
    keyed by the frame-stable `LightInfo*`, pruned each frame by generation.
  - `WorldLightLoadMatrix` — centres on the light, applies the two-axis tumble, scales.
  - `WorldLightMaskPass` / `WorldLightCompositePass` / `DrawLightPool` — the 3-pass sequence.
  - `DrawWorldLights` — the per-frame light walk + per-source dispatch.
- `soh/soh/Enhancements/Graphics/DekuStickLight.cpp/.h` — the stick light (above).
- `soh/src/code/z_lights.c` — `Lights_PointSetColorAndRadius` (flame-flicker call) and
  `Lights_DrawGlow` (early-return that hides the vanilla billboarded glow circles when
  `HideVanillaGlow` is on).
- `soh/src/code/z_actor.c` — the `OnPlayDrawWorldLights` callout in `func_800315AC`.
- `soh/src/overlays/actors/ovl_En_Elf/z_en_elf.c` — the Navi light tint (`NaviSaturation`).
- GUI: `soh/soh/SohGui/SohMenuWindWakerStyle.cpp`, page **Wind Waker Style → Lights**.

### libultraship (renderer transport)

- GBI: `include/libultraship/libultra/gbi.h` — `G_SETSTENCIL 0x46` + `gSPStencil(pkt, mode)`.
  `include/fast/lus_gbi.h` — `OTR_G_SETSTENCIL`.
- `src/fast/interpreter.cpp` — `gfx_set_stencil_handler_custom` (flush, then `SetStencilMode`).
- `include/fast/backends/gfx_rendering_api.h` — `enum class StencilMode`, the base
  `SetStencilMode` + `mStencilMode`.
- Per-backend stencil application (`DrawTriangles`):
  - `gfx_opengl.cpp` — `glStencilFunc`/`glStencilOp` (GL already had `GL_DEPTH24_STENCIL8`).
  - `gfx_metal.cpp/.h` — a separate `Stencil8` texture as the render pass's `stencilAttachment`
    (the depth texture and `GetPixelDepth` are untouched) + stencil ops on the per-draw
    `DepthStencilDescriptor`.
  - `gfx_direct3d11.cpp` + `gfx_direct3d_common.h` — combined `R24G8`/`D24_UNORM_S8_UINT` on all
    feature levels so a stencil plane always exists (`GetPixelDepth` reads the `R24_UNORM_X8` SRV).

No shader/asset changes — the pool uses the existing flat-colour combiner, so no `soh.o2r` regen.

## CVars

`gEnhancements.Graphics.WorldLighting.*`. Slider defaults live in the GUI AND as `kDefault*`
constants in `WorldLighting.cpp` — keep them in sync.

| CVar | Default | Meaning |
|---|---|---|
| `Enabled` | **0** | Light casting master toggle. |
| `WWDefaultMovement` | 1 | Use WW's authentic tumble/pulse rates; off reveals the two sliders below. |
| `RotationSpeed` | 1.0 | × the WW two-axis tumble rate. |
| `SizeFlicker` | 1.0 | Depth of the WW size pulse (1 = authentic ±5%). |
| `SphereSize` | 0.5 | Pool size, × the light's radius. |
| `Intensity` | 0.2 | Pool brightness. |
| `UseNaviLight` | 1 | Also cast a pool from Navi. |
| `NaviSphereSize` | 0.75 | Navi pool size. |
| `NaviIntensity` | 0.2 | Navi pool brightness. |
| `OtherFairyLights` | 0 | Cast pools from wild fairies too. |
| `WildFairySphereSize` | 0.75 | Wild-fairy pool size. |
| `WildFairyIntensity` | 0.2 | Wild-fairy pool brightness. |
| `DekuStickLight` | 1 | Register the held-Deku-stick light (feeds cel/shadows even with casting off). |
| `DekuStickSphereSize` | 0.5 | The stick's pool size. |
| `HideVanillaGlow` | 1 | Hide the vanilla billboarded glow circles while casting is on. |
| `ImproveFlameFlicker` | 1 | The WW flame flicker at the source (independent of casting). |
| `FlickerSpeed` | 1.0 | Rate of the WW flame flicker. |
| `gDeveloperTools.WorldLighting.ShowLightSpheres` | 0 | Draw the icosphere volumes visibly. |

## The Wind Waker flicker model

All per-frame values are converted from WW's 30 Hz to our 20 Hz by running in seconds with
`WWEase`'s `dt*30` correction. Random source is uniform `Rand_ZeroOne()`. Measured values and their
derivation: [`wind-waker-bonbori-light.md`](./wind-waker-bonbori-light.md).

- **Two-axis tumble**: Y ≈ 0.598 rad/s, X ≈ 0.736 rad/s (non-harmonic 16:13, never visibly loops),
  no Z.
- **Size flicker** (the dominant pulse): re-roll a target every 0.10–0.30 s to 1.0 ± 5% ×
  `SizeFlicker`, ease with `WWEase(0.4, 0.05)`. Decoupled from the brightness noise — that
  decoupling is what makes it read slow and organic instead of jagged.
- **Brightness flicker** (fine grain): re-roll the pool alpha every 0–0.167 s to [0.90, 1.0], ease
  with `WWEase(1.0, 0.08)`.
- **Source flame flicker** (`WorldLighting_ApplyFlameFlicker`): slow random-walk in [0.60, 1.0] of
  full bright, new target every `0.25 s / FlickerSpeed`; flame detection = per-frame brightness jump
  > 12 with a sticky hold, so only white-noise flames are transformed; hue preserved by scaling
  channels.
- **Navi** is excluded from the size/alpha flicker (her light is constant; any jitter is her
  movement).

## Invariants & gotchas

- **Emit into `POLY_OPA`, not `POLY_XLU`.** That is what makes the depth buffer world-only at our
  pass — pools don't tint actors, and actors occlude pools. Moving it to XLU reintroduces
  actor-tinting.
- **`StencilMode` values must match** the `WL_STENCIL_*` defines in `WorldLighting.cpp`
  (Off=0, VolumeIncr=1, VolumeDecr=2, Composite=3).
- **Reset stencil to OFF** at the end of `DrawWorldLights`, every frame, before the actors draw.
- **Mask passes are invisible via prim alpha 0 + no alpha-compare** (`G_RM_AA_ZB_XLU_SURF`), not a
  colour-write mask — Fast3D's Metal/D3D11 bake colour-write/blend into the pipeline, so they can't
  be toggled per draw. Same reason there is no true additive blend: overlapping pools alpha-blend
  (they don't super-brighten); adding additive would need a per-backend pipeline variant.
- **Face culling is CPU-side** in Fast3D, so the mask passes select back/front faces with
  `G_CULL_FRONT`/`G_CULL_BACK` geometry mode and Fast3D's CPU culler honours it.
- **Metal:** `MTL::TextureDescriptor::texture2DDescriptor(...)` returns an **autoreleased** object —
  do not `->release()` it (double-free → SIGBUS at startup).
- **Icosphere emission:** the game-side `gSPVertex` is a `uintptr_t` wrapper that runs an OTR
  resource-sig check — emit the sphere live during draw, never bake it into a DL at init.
- **Per-light state** is keyed by `LightInfo*` (actor-owned, frame-stable), pruned each frame by a
  generation counter; the flicker map is cap-cleared at 256 entries.

## Build & test (macOS)

Build per [`README.md`](./README.md#build--test-macos) — no `GenerateSohOtr`. Enable **Wind Waker
Style → Lights → Enable Light Casting**, visit a torch: the pool should be a faceted polygon
conforming to the floor/wall, slowly tumbling and pulsing, occluded by (and not tinting) actors,
with the vanilla glow circle hidden. Good checks: two nearby torches (overlap), a lit Deku stick,
Navi against a wall, the Castle-Town drawbridge at night (pool on a walkable actor).
