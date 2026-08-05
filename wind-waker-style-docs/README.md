# Wind Waker-style Rendering (this fork)

This is a fork of Ship of Harkinian that adds a **Wind Waker-style rendering mod** to *Ocarina of
Time*. It is not upstream SoH — the root `CLAUDE.md` describes the vanilla codebase; this folder
describes what the fork adds.

The mod is four feature families, each with a detail doc:

| Feature | What it does | Default | Doc |
|---|---|---|---|
| **Cel Shading** | toon-relights the **objects** (Link, NPCs, enemies, items): per-pixel single-key-light ramp | on | [`wind-waker-style-cel-shading.md`](./wind-waker-style-cel-shading.md) |
| **Light Casting** | point lights cast **pools on the world** (stencil light volumes) + WW flame flicker | off | [`wind-waker-light-casting.md`](./wind-waker-light-casting.md) |
| **Actor Shadows** | each object casts its **own silhouette on the ground** (stencil slab volumes) | off | [`wind-waker-actor-shadows.md`](./wind-waker-actor-shadows.md) |
| **Sky** | gradient dome, drifting clouds + horizon band, twinkling stars, wind wisps — weather-reactive | off | [`wind-waker-sky.md`](./wind-waker-sky.md) |

Supporting docs:

- [`wind-waker-bonbori-light.md`](./wind-waker-bonbori-light.md) — the reverse-engineered reference
  for WW's real torch-light pool (from the noclip.website reproduction). Light Casting's
  flicker/tumble constants come from here.
- [`cloud-texture-replacement-guide.md`](./cloud-texture-replacement-guide.md) — artist-facing: how
  to replace the five cloud textures with a mods-folder o2r.

All user-facing controls live in one GUI menu: **Wind Waker Style** (pages: Cel Shading, Lights,
Actor Shadows, Sky), defined in `soh/soh/SohGui/SohMenuWindWakerStyle.cpp`.

## How the features fit together

**1. The same two-layer split.** Each lighting feature is split so the cross-platform renderer never
learns anything OoT-specific:

- **Policy** lives game-side in `soh/soh/Enhancements/Graphics/` — *decides* (which light is the
  key, which actors are excluded, the look tuning) and pushes the result down.
- **Transport** lives in `libultraship/` Fast3D — *executes* a generic primitive (relight a draw,
  set a stencil mode, build a shadow volume) and reads no SoH config.

The handoff is a new GBI opcode (`gSPToon`, `gSPToonKey`, `gSPStencil`, `gSPToonShadow`) emitted by
policy and consumed by a `gfx_set_*_handler_custom` in the interpreter, applied across all three
backends (OpenGL / Metal / D3D11). The sky needs none of this — it is pure game-side geometry
emitted through existing hooks.

**2. A shared key light.** Cel Shading picks one dominant light per actor (closest in-range point
light, else the sun/moon), eased between sources. Actor Shadows casts along that same key, so an
actor's shading and its shadow always agree. Both are driven from `HandleActorDraw` in
`ToonLighting.cpp`.

**3. A shared stencil pipeline.** Light Casting introduced the renderer's `StencilMode` API and the
world-only-depth `POLY_OPA` insertion point (draw after the room, before actors). Actor Shadows
renders its slab volumes through the same modes at the same point. The receiver pre-pass (walkable
floor actors drawn early) feeds both, so shadows *and* light pools land on the drawbridge and its
kin.

**4. A shared actor scope.** The `gSPToon` bracket around the actor draw loop scopes the relight to
objects only, and the same blacklist (`ToonActorExcluded`: doors, Deku Tree, water boxes, scenery)
opts an actor out of both relight and shadows.

**5. Shared light sources.** All lighting features read the engine's point-light list
(`play->lightCtx`), so one new light feeds everything at once. The held **Deku stick light**
(`DekuStickLight.cpp`) does exactly that: a lit stick's flame becomes a real torch-equivalent point
light — it can be a cel key, casts a pool, and pulls shadows. Details in the light-casting doc.

**6. Shared environment sampling.** The sky layers share `WWSkyEnv.cpp`: WW's real sea-stage
palette, sun-elevation time of day, a smoothed weather signal, wind, and the common horizon line.

## Naming convention

GUI labels and internal identifiers differ on purpose — internal names were frozen so existing
configs survive GUI renames.

| GUI | Internal prefix (code / CVars / GBI) |
|---|---|
| Cel Shading | `Toon` / `ToonLighting` |
| Light Casting (Lights page) | `WorldLighting` / `Stencil` |
| Actor Shadows | `WorldShadows` / `ToonShadow` |
| Sky | `WWSky`, `WWSkyGradient`, `WWClouds`, `WWNightSky`, `WWWindWisps` |

All CVars sit under `gEnhancements.Graphics.*` (debug toggles under `gDeveloperTools.*`).

## Branch & base

Built on SoH's stable release, tag **`9.2.3`** (not `develop`), to avoid develop-era regressions.
Everything lives on the **`wind-waker-style-cel-shading`** branch in both repos (soh + the
`libultraship` submodule). Consequence: this build uses the 9.2.3 save format (develop-build saves
won't load). Releases are tagged `9.2.3-celshade*`.

## Build & test (macOS)

Configure once (Debug; brew prefix + Xcode SDK + the `FMT_CONSTEVAL` workaround this machine needs):

```sh
cmake -H. -Bbuild-cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH="$(brew --prefix)" \
  -DCMAKE_OSX_SYSROOT="$(xcrun --sdk macosx --show-sdk-path)" \
  -DCMAKE_CXX_FLAGS=-DFMT_CONSTEVAL=constexpr
```

Then rebuild only what changed:

```sh
make -C build-cmake libultraship -j10   # renderer changes (gbi.h / interpreter / backends)
make -C build-cmake soh -j10            # game-side / GUI changes
make -C build-cmake GenerateSohOtr      # ONLY if shaders changed (cel-shading shader edits)
```

A new source file needs a re-configure so the CMake `GLOB` picks it up.

Run from an interactive Terminal (`build-cmake/soh/soh-macos`); launching detached crashes in
`CAMetalLayer nextDrawable` (an environment quirk, not the code). Per-feature visual checks are in
each detail doc.
