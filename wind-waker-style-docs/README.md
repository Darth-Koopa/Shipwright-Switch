# Wind Waker-style Rendering (this fork)

This is a **fork of Ship of Harkinian** that exists to add a **Wind Waker-style rendering mod** to
*Ocarina of Time*. It is not upstream SoH — the root `CLAUDE.md` describes the vanilla codebase; this
folder describes what we built on top of it.

The mod is **three independent features** that together produce the cel-shaded, toon-lit look:

| Feature | Lights the… | Core technique | Default | Detail doc |
|---|---|---|---|---|
| **Cel Shading** | **objects** (Link, NPCs, enemies, items) | per-pixel single-key-light half-Lambert ramp in the fragment shader | **on** | [`wind-waker-style-cel-shading.md`](./wind-waker-style-cel-shading.md) |
| **Light Casting** | **world** (floors, walls) | stencil light-volume (icosphere ∩ world) tinted into pools | off (experimental) | [`wind-waker-light-casting.md`](./wind-waker-light-casting.md) |
| **Actor Shadows** | **ground under objects** | captured silhouette projected onto the floor plane, soft multi-tap stencil edge | **on** | [`wind-waker-actor-shadows.md`](./wind-waker-actor-shadows.md) |

Supporting reference: [`wind-waker-bonbori-light.md`](./wind-waker-bonbori-light.md) — the reverse-engineered
breakdown of WW's real torch-light pool (from the noclip.website reproduction) that Light Casting's
flicker/tumble model is matched against. Read it only if you need to re-derive those constants.

**The Sky** (newer, fourth feature family, behind the "Use Sky" toggle): a WW-style gradient sky dome,
drifting vrkumo clouds + horizon cloud band, twinkling starfield — all weather-reactive. Docs:
[`wind-waker-clouds-investigation.md`](./wind-waker-clouds-investigation.md) (clouds architecture, debugging
history, and the texture override contract), [`wind-waker-sky-scene-profiles-plan.md`](./wind-waker-sky-scene-profiles-plan.md)
(weather signals + the per-scene profile plan), and
[`cloud-texture-replacement-guide.md`](./cloud-texture-replacement-guide.md) (**artist-facing**: how to
replace the five cloud textures, with previews).

---

## How the three features fit together

All three share one design and reuse each other's machinery — that's what keeps them coherent rather
than three bolt-ons.

**1. The same two-layer split.** Each feature is split so the cross-platform renderer never learns
anything OoT-specific:

- **Policy** lives game-side in `soh/` — *decides* (which light is the key, which actors are excluded,
  the look tuning) and pushes the result down via a custom GBI command.
- **Transport** lives in `libultraship/` Fast3D — *executes* a generic primitive (relight a draw / set a
  stencil mode / project a silhouette) and reads no SoH config.

The handoff is always a **new GBI opcode** (`gSPToon`, `gSPStencil`, `gSPToonShadow`) emitted by Policy
and consumed by a `gfx_set_*_handler_custom` in the interpreter, applied across all three backends
(OpenGL / Metal / D3D11).

**2. A shared "key light."** Cel Shading picks one dominant light per actor (closest in-range point
light, else the sun/moon), eased smoothly between sources. **Actor Shadows reuses that exact key** as
its cast direction — so an actor's shading and its shadow always agree. Both are driven from
`HandleActorDraw` in `soh/soh/Enhancements/Graphics/ToonLighting.cpp`.

**3. A shared stencil pipeline.** Light Casting introduced the renderer's `StencilMode` API and the
world-only-depth `POLY_OPA` insertion point (draw after the room, before actors). Actor Shadows builds
directly on both (`StencilMode::ShadowMask`, same insertion point). The two never run in the same part
of a frame, so they don't collide.

**4. A shared actor scope + blacklist.** The `gSPToon` bracket around the actor draw loop scopes both
relight and shadows to objects only (never the static world). The same data-driven blacklist
(`ToonActorExcluded`: doors, Deku Tree, water boxes) opts an actor out of both.

```
        ┌── Cel Shading ──────────────► relight objects (shader ramp)
key light┤
        └── Actor Shadows ────────────► project silhouette onto floor (stencil decal)

Light Casting ──────────────────────► tint world pools (stencil volume)   [independent]
```

**5. Shared light sources.** Because all three read the engine's point-light list (`play->lightCtx`),
adding a light there feeds every feature at once. The **held Deku stick light** does exactly that: when
Link holds a *lit* Deku stick, `DekuStickLight.cpp` registers a point light at the burning tip
(`meleeWeaponInfo[0].tip`) so the flame — which emits no light in vanilla — becomes a real source. It is
torch-equivalent by construction (radius matched to `obj_syokudai`; the same per-frame white-noise
brightness so the flame-flicker hook smooths it identically; obeys the cel `PointLightRange` for free). It
casts a pool with its own size — `WorldLighting.cpp` identifies the stick light by address (via
`DekuStickLight_GetActiveLightInfo()`) and applies `DekuStickSphereSize` (default 0.5) instead of the
global `SphereSize`. Its **color is asset-driven,
not hardcoded**: it looks up an optional texture (`textures/wind-waker/deku_stick_light_color`) absent
from vanilla archives and averages it; with nothing there it falls back to OoT's canonical fire color
`{255,200,0}`. A texture pack can add/alt-swap that one asset to recolor the light. CVars:
`gEnhancements.Graphics.WorldLighting.{DekuStickLight, DekuStickSphereSize}` (toggle default **on**); GUI
under **Wind Waker Style → Lights → "Deku Stick"** (its own right-column section): the toggle is always
visible (it controls all three effects — cel/shadows apply even with Light Casting off), while "Deku Stick
Cast Size" (a pool-only control) hides when Light Casting is off. Driven from the `OnPlayerUpdate` hook, with an `OnSceneInit` reset (the new scene
rebuilds `lightCtx`). *(No renderer/shader changes — pure game-side point-light registration.)*

---

## Per-feature technique in one paragraph each

**Cel Shading.** The actor draw loop is bracketed with `gSPToon(true/false)`. Per actor, Policy picks +
eases the key light and emits `gSPToonKey(dir, color)`. The renderer forwards the world-space vertex
normal + that one key into a `TOON` shader variant, which computes `t = N·L*0.5+0.5` and blends a
two-tone `albedo * mix(shadow, lit, smoothstep(ramp))`. Single key per object is the WW rule — multiple
lights break the toon look. *(Shader changes → needs `make GenerateSohOtr`.)*

**Light Casting.** Per in-range point light, Policy emits a low-poly **icosphere** as a 3-pass stencil
light-volume (z-fail: back faces incr, front faces decr → stencil set exactly where world geometry lies
inside the sphere; then a composite pass additively tints those pixels with the light's color). Drawn
into `POLY_OPA` after the room but before actors, so the depth buffer is world-only — pools conform to
walls/floors and are occluded by (never tint) actors. The sphere slowly tumbles and pulses on a
WW-matched flicker model; a companion **flame flicker** replaces OoT's white-noise torch jitter with an
eased random-walk at the light source. *(No shader changes — fixed-function stencil + flat combiner.)*

**Actor Shadows.** As each actor's triangles stream through Fast3D, the renderer captures their
world-space positions, then projects each onto the actor's floor plane along the (elevation-remapped)
cel key direction, drawing the silhouette as a translucent decal. A **multi-tap stencil edge** (each tap
offset around a ring, accumulated via increasing stencil refs) feathers a soft penumbra. Replaces the
vanilla feet/circle/horse shadows (suppressed while on). Planar projection conforms to slopes but floats
flat past hard cliff edges (accepted; true cliff conformance needs shadow mapping). *(No shader
changes.)*

---

## Naming convention (applies to all three)

The user-facing GUI label and the internal identifiers differ on purpose — internal names were frozen so
old saves/configs keep working through GUI renames.

| GUI label | Internal prefix (code / CVars / GBI) |
|---|---|
| Cel Shading | `Toon` / `ToonLighting` (`gEnhancements.Graphics.ToonLighting.*`) |
| Light Casting | `WorldLighting` / `Stencil` (`gEnhancements.Graphics.WorldLighting.*`) |
| Actor Shadows | `WorldShadows` / `ToonShadow` (`gEnhancements.Graphics.WorldShadows.*`) |

Each feature's GUI page is under **Settings → <label>** in `soh/soh/SohGui/SohMenuSettings.cpp`.

---

## Branch & base

Built on SoH's **last stable release, tag `9.2.3`** (not `develop`), to shed develop-era regressions the
earlier prototype hit. All three features now live on the **`wind-waker-style-cel-shading`** branch in
both repos (soh + the `libultraship` submodule). Consequence: this build uses the **9.2.3 save format**
(develop-build saves won't load). See the cel-shading doc's "Branch & base" section for the specific
stable-vs-develop adaptations.

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
make -C build-cmake GenerateSohOtr      # ONLY if shaders changed — i.e. Cel Shading shader edits
```

(A new source file needs a re-configure so the CMake `GLOB` picks it up.)

Run from an **interactive Terminal** (`build-cmake/soh/soh-macos`); launching detached crashes in
`CAMetalLayer nextDrawable` (a pre-existing environment quirk, not the code). Per-feature visual checks
are in each detail doc.
