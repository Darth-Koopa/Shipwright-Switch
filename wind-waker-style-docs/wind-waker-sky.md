# Wind Waker-style Sky

Developer notes for the sky feature family on the `wind-waker-style-cel-shading` branch.
References are by file + symbol (line numbers drift). Start with [`README.md`](./README.md) for how
this fits the other features.

The sky is drawn over OoT's textured skybox as four independent layers, all behind one **"Use Sky"**
master toggle (`gEnhancements.Graphics.WWSky.Enabled`):

| Layer | File | What it draws |
|---|---|---|
| Gradient | `WWSkyGradient.cpp` | WW's vrbox sky: a vertex-coloured dome (sky / horizon haze / fake sea) |
| Clouds | `WWClouds.cpp` | Drifting puffy-cloud billboards + the horizon cloud band |
| Stars | `WWNightSky.cpp` | WW's twinkling starfield (pure geometry, night only) |
| Wind wisps | `WWWindWisps.cpp` | The white streaks that curl through the sky on the wind |

`WWSkyEnv.cpp/.h` is the shared plumbing: the WW palette, the sun-driven time of day, the weather
sampler, wind, the shared horizon line, and the split-screen debug. All of it runs game-side in
`soh/soh/Enhancements/Graphics/` — no renderer or shader changes, no `GenerateSohOtr`.

Everything is a port of Wind Waker's own systems, as reverse-engineered by noclip.website
(`src/ZeldaWindWaker/d_kankyo_wether.ts` and friends). WW runs its sim at 30 fps and this hook at
20 fps, so every ported per-frame constant is scaled by 30/20 (`kFrameScale = 1.5`).

## Hooks and draw order

All layers draw from GameInteractor hooks fired in `Play_Draw` (`soh/src/code/z_play.c`), layered
back to front:

1. Vanilla skybox draws (kept — it backs the split-screen debug and non-sky scenes).
2. `OnPlayDrawSkyGradient` → the gradient dome paints over it (no z-test/z-write).
3. `OnPlayDrawSky` → stars.
4. `OnPlayDrawSkyClouds` → clouds, horizon band, then wisps.
5. Sun, moon, and the world draw after, on top.

Each layer checks `play->skyboxId == SKYBOX_NORMAL_SKY`, so the sky only replaces the real outdoor
sky. The file-select screen (vanilla night sky) is also covered: `z_file_choose.c` calls
`WWSky_DrawFileSelect` after its `SkyboxDraw_Draw`, which draws the dome with a fixed night palette
(`WWSkyEnv_NightColors`) plus the starfield — file select has no `PlayState`, so those paths take a
bare `(gfxCtx, view)`.

## Shared environment sampling (`WWSkyEnv.cpp`)

**Palette.** `kSeaPalette` holds WW's real sea-stage sky colours — six time slots (dawn, morning,
noon, evening, dusk, night) × two weather sets (clear, rain), five colours each: `sky` (upper dome),
`kasumi` (horizon haze), `usoUmi` (below the horizon), `kumo`/`kumoCenter` (cloud edge/centre).
Extracted from WW's `sea/Stage.arc` `stage.dzs` (EnvR → Colo → Pale → Virt chunks). Only colour
values ship — no Nintendo assets.

**Time of day is the sun's elevation, not the clock.** `WWSkyEnv_SunHeight()` returns
`cos(dayTime - 0x8000)` — the same formula OoT uses to place the sun (+1 noon, 0 at the 06:00/18:00
horizon, −1 midnight). `SunSlots` maps that height to a pair of palette slots and a blend factor,
with separate AM/PM stop tables (dawn/morning going up, evening/dusk coming down). Keying off the
visible sun keeps the warm dusk peaking exactly as the sun touches the horizon. (OoT's own lighting
table turns the world to sunset ~2h before the sun geometry sets, so a clock schedule reads early.)

**Weather.** `WWSkyEnv_Sample` derives from `envCtx`:

- `cloudiness` 0..1 from the fine↔cloud skybox rows (`unk_17`/`unk_18` + `skyboxBlend` while a
  transition is in flight), forced to 1 by rain (`unk_EE[1]`) or pending lightning
  (`LIGHTNING_MODE_ON`/`LAST` — `LAST` means one more bolt is coming, so the sky stays stormy for
  it). Eased asymmetrically: ~1 s to cloud over, ~10 s to clear.
- `storm` 0..1 from the rain ramp / lightning.
- `fogColor` — the scene's current blended fog colour.

`WWSkyEnv_SampleColors` then blends: two palette slots by sun height, then clear→rain by
cloudiness. Consumers react on top: clouds raise coverage with cloudiness and speed up drift with
storm; stars fade out by cloudiness.

**Wind.** `WWSkyEnv_Wind` maps OoT's `envCtx.windDirection/windSpeed` into WW's form: a unit XZ
direction (with a steady fallback breeze so the sky always drifts) and a power in WW's 0.3–0.9
bracket. Shared by cloud drift, band scroll, and wisp flight.

**Horizon line.** WW translates its whole vrbox (sky dome, fake sea, cloud band) as one unit.
`WWSkyEnv_HorizonY` is that shared Y: camera height × (1 − parallax) + height offset, from the
Horizon Height / Horizon Parallax sliders. The gradient's haze/sea line and the cloud band both sit
on it.

**Split-screen debug.** `WWSky.SplitDebug` scissors every WW sky draw to the left half of the
screen, leaving the vanilla skybox visible on the right for a live A/B. Each layer wraps its
geometry in `WWSkyEnv_SplitDebugBegin/End`.

## The layers

### Gradient (`WWSkyGradient.cpp`)

WW's sky is not a texture — it is vertex-coloured meshes tinted by scheduled colours. This file
mirrors that: a camera-centred dome (static geometry, built once) whose vertex colours are rewritten
every frame with the sampled palette. Three fixed zones, measured from WW's `vr_sky.bdl` /
`vr_uso_umi.bdl` meshes: `usoUmi` below the horizon, `kasumi` haze fading linearly into `sky` by
+6.6° elevation. The zone shape never animates — only the colours do, exactly like WW. Dome rows are
placed non-uniformly (`kDomeElevations`) so the thin haze band gets enough vertices.

Drawn with no z-test/z-write straight over the skybox; everything later paints on top. Uses the
camera-epoch frame-interpolation child (like the vanilla skybox) so camera cuts snap instead of
smearing.

### Clouds (`WWClouds.cpp`)

Two systems in one file:

- **Drifting clouds** — WW's `dKankyo_vrkumo_Packet`: up to 100 cloud sprites on a camera-following
  dome (no parallax), drifting on the wind, respawning at the edge, faded/sized by a distance
  falloff. Each cloud is three overlapping textured billboards (`cloudtx_01/02/03`, offset per cloud
  by WW's `cloudRep` table). Tinted by the palette's `kumo`/`kumoCenter`.
- **Horizon cloud band** — WW's `vr_back_cloud.bdl` (drawn by `d_a_vrbox2`), rebuilt procedurally:
  three full-circle rings sitting on the shared horizon line. Each ring samples its 256×64 strip
  twice — a static copy and a wind-scrolled copy, combined as `screen(static, scrolled)` — which
  makes the band slowly evolve instead of just sliding. Ring order/wraps/scroll rates are measured
  from the model.

Hand-built textured display lists must set **cycle type and alpha compare** explicitly
(`gDPSetCycleType(G_CYC_1CYCLE)` + `gDPSetAlphaCompare(G_AC_NONE)`) — both are inherited RDP state,
and the skybox draws immediately before in `G_CYC_2CYCLE`, which silently breaks the combiner's
texture slot mapping. Vanilla draws get this from their `Gfx_SetupDL_*` call; ours does it inline.

### Stars (`WWNightSky.cpp`)

WW's `dKankyo_star_Packet`: up to 1000 stars, each two overlapping triangles (a six-pointed
billboard), vertex-coloured, no textures. The first 16 are WW's fixed bright constellation
(`hokuto_pos`); the rest spiral outward around the camera. Every star follows the camera exactly, so
there's no parallax and the field reads as infinitely far. Twinkle is WW's mechanism: one shared
sine wave modulates star size, staggered per star. Star count fades with the sun height
(`StarAmountForSun`) and with cloudiness.

Two scale adaptations, both invisible on screen because a camera-following star's angular size is
offset/distance (scale cancels): constellation stars are scaled down 0.25× to fit OoT's 12800 far
plane; the small spiral stars are scaled up 25× so their sub-unit geometry survives s16 integer
vertices. Star vertices live in a static buffer — the per-frame graphics arena is the same buffer
the display list grows into, and ~96 KB of vertex data there corrupts it.

### Wind wisps (`WWWindWisps.cpp`)

WW's wind lines (`dKankyo__Windline` / `WIND_EFF`): each wisp is a point flying along the wind,
swerving on a sine wave, with a 20% chance of a full loop-de-loop; it fades in, cruises, fades out,
and respawns ahead of the camera. WW renders the streak as a particle trail (JPA effect); we have no
JPA, so the streak is a tapered translucent ribbon through the point's recent position history.

Ribbon details that matter:

- Trail samples are **frozen at emission** (position, cross-section direction, alpha) — recomputing
  them per frame makes the streak squirm.
- Each wisp has its **own vertex region** (`sWispVtx[wisp]`). `gSPVertex` records a pointer that
  Fast3D dereferences only when the XLU list executes at end of frame — a shared scratch buffer
  would render every ribbon with the last wisp's geometry.
- Cross-section holds full alpha across a core and ramps to zero at the edge (a plain 3-vert
  gradient ribbon is smudgy — bright only along an infinitely thin centreline).
- Emitted into `POLY_XLU` with z-test on, so terrain occludes the streaks.

Spawns scatter across the real screen (aspect-corrected), with a pitch-clamped base and an altitude
floor so flyovers stay high overhead.

## CVars

All `gEnhancements.Graphics.*`. GUI page: **Wind Waker Style → Sky** in
`soh/soh/SohGui/SohMenuWindWakerStyle.cpp` (sections: Horizon, Sky Gradient, Clouds, Stars, Wind
Wisps, Debug). Slider defaults are mirrored as `kDefault*` constants in each file — keep them in
sync.

| CVar | Default | Meaning |
|---|---|---|
| `WWSky.Enabled` | 0 | "Use Sky" master toggle for all four layers. |
| `WWSky.SplitDebug` | 0 | Left half WW sky, right half vanilla skybox. |
| `WWSkyGradient.Enabled` | 1 | Gradient dome. |
| `WWSkyGradient.Brightness` | 1.0 | Multiplier on the palette colours. |
| `WWClouds.Enabled` | 1 | Drifting clouds + horizon band. |
| `WWClouds.Opacity` | 0.85 | Cloud alpha. |
| `WWClouds.Coverage` | 0.3 | Cloud count floor (weather raises it; WW: 50 + 50·strength). |
| `WWClouds.DriftSpeed` | 1.0 | × WW's wind-driven drift (storm raises it). |
| `WWClouds.HorizonBandHeight` | −408 | World-space horizon offset (shared with the gradient). |
| `WWClouds.HorizonBandParallax` | 0.75 | 0 = follows camera height, 1 = pinned to world height. |
| `WWNightSky.Enabled` | 1 | Starfield. |
| `WWNightSky.StarCount` | 1000 | Cap (WW's own count); time of day scales it down. |
| `WWNightSky.Brightness` | 1.0 | Star alpha multiplier. |
| `WWNightSky.TwinkleSpeed` | 1.0 | × WW's twinkle rate. |
| `WWWindWisps.Enabled` | 1 | Wind wisps. |
| `WWWindWisps.Amount` | 1.0 | × WW's wind-driven wisp count (10 × windPower). |
| `WWWindWisps.Speed` | 1.0 | × flight-sim timestep (path keeps its shape; fades stay GameCube-rate). |

Per-layer toggles are sub-toggles: a layer runs only when `WWSky.Enabled` and its own `Enabled` are
both on (`COND_HOOK` on both CVars).

## Cloud textures: built-ins and the override contract

The mod ships no Nintendo art. The built-in cloud textures are original WW-*style* look-alikes
generated by `scripts/gen-ww-cloud-textures.py` into
`soh/assets/custom/textures/wind-waker/clouds/`, packed into `soh.o2r` by the build. Any mods-folder
o2r providing the same resource paths overrides them at runtime — that is the delivery mechanism for
WW-themed texture packs:

| Resource path | Used for | Built-in size |
|---|---|---|
| `textures/wind-waker/clouds/cloudtx_01..03` | drifting cloud sprite layers | 64×64 |
| `textures/wind-waker/clouds/cloud_mae` | horizon band, front strip (gappy clusters) | 256×64 |
| `textures/wind-waker/clouds/cloud_naka` | horizon band, back strip (continuous mass) | 256×64 |

Rules: RGBA32, power-of-two, max 512×512 (band strips max 256 wide — the band wraps them several
times and wider strips overflow S10.5 texel coords). The cloud shape lives in the alpha channel; RGB
stays near-white (it is tinted by time of day and weather). Band strips tile horizontally; their
bottom edge is the horizon. The artist-facing walkthrough is
[`cloud-texture-replacement-guide.md`](./cloud-texture-replacement-guide.md).

## Build & test

Build per [`README.md`](./README.md#build--test-macos); soh-side only, no `GenerateSohOtr`. Turn on
**Wind Waker Style → Sky → Use Sky** in an outdoor scene. Good checks: the dusk/dawn colour peaks as
the sun touches the horizon; clouds grey out and multiply as rain rolls in; stars fade under
overcast; wisps follow the wind direction; split-screen debug against the vanilla sky; the
file-select screen shows the night dome + stars.
