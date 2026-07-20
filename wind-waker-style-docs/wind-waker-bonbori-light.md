# Wind Waker "Bonbori" Torch Light — Implementation Reference

Reverse-engineered from the noclip.website reproduction of *The Legend of Zelda: The Wind Waker*.
This documents the **faceted, rotating, growing/flickering torch light pool** that appears on
walls and floors (e.g. Forsaken Fortress Exterior torches).

> **Key insight:** the visible "light pool" is **not** a soft point light. It is a **low-poly sphere
> mesh ("Bonbori") rendered as a depth-tested volume into the framebuffer's alpha channel**, then
> used as a mask to additively tint the scene with a warm color. The faceting comes from the low
> poly count; the motion comes from spinning + scaling that mesh; the flicker comes from randomized
> alpha and scale targets that are eased over time.

There is **also** a separate, conventional environment point light (`LIGHT_INFLUENCE`) at the same
torch — that one handles soft warm lighting on nearby surfaces and is documented at the end as the
"companion light." The two are independent systems.

---

## Source map (noclip.website)

| Concern | File | Notes |
|---|---|---|
| Torch actor / driver | `src/ZeldaWindWaker/d_a.ts` — class `d_a_ep` (~L212–398) | spins, scales, sets alpha, queues the Bonbori each frame |
| Alpha-model system | `src/ZeldaWindWaker/d_drawlist.ts` — `dDlst_alphaModel_c` (~L79–219) | geometry, materials, 3-pass volume + composite |
| Easing helpers | `src/ZeldaWindWaker/SComponent.ts` — `cLib_addCalc*`, `cM_rndF`, `cM_s2rad` | math primitives |
| Point-light flicker | `src/ZeldaWindWaker/d_kankyo.ts` — `settingTevStruct_plightcol_plus` (~L447) | companion soft light |
| Pipeline wiring | `src/ZeldaWindWaker/Main.ts` (~L458, ~L575) | runs in Main pass against populated depth |

---

## Time & angle base (needed for every conversion)

- **Logic runs at 30 Hz.** `Main.ts`: `frameCount = time/1000 * 30`. So `deltaTimeFrames = 1.0` ⇒ **1/30 s**.
  All "per frame" values below are **per 1/30 second**.
- **Angles are 16-bit.** `cM_s2rad(v) = v * (π / 0x8000)`. A full turn = `0x10000` = 65536 units = 360°.
  So **1 unit = 360/65536° = 0.00549316°**.

---

## 1. The easing function (used everywhere)

All smoothing in this system is **first-order exponential smoothing with a per-frame slew cap**
(a low-pass filter — *not* a second-order critically-damped spring, despite the visual similarity:
it never overshoots and never oscillates because there is no velocity/momentum term).

```ts
// SComponent.ts
function clampAbs(v, min, max) { /* clamps |v| into [min,max], keeps sign */ }

// The workhorse — no minimum velocity, eases in asymptotically:
function cLib_addCalc2(src, target, speed, maxVel) {
    return src + clampAbs(speed * (target - src), 0.0, maxVel);
}

// The richer variant — adds a minimum velocity + snap-to-target so it actually arrives:
function cLib_addCalc(src, target, speed, maxVel, minVel) {
    const delta = target - src;
    const vel = clampAbs(speed * delta, minVel, maxVel);
    if (Math.abs(vel) > Math.abs(delta)) return target; // would overshoot → snap exactly
    return src + vel;
}
```

Behavior of `cLib_addCalc2(src, target, speed, maxVel)` each tick:
1. Compute the gap `delta = target - src`.
2. Move a fraction `speed` of that gap: `speed * delta` (geometric decay of the error).
3. Clamp that step's magnitude to `maxVel` (slew-rate limit; prevents large jumps).

With `speed = 0.4`, the remaining gap shrinks to ~60% every tick (half-life ≈ 1.4 ticks).

**Random source:** `cM_rndF(max) = Math.random() * max` — uniform `[0, max)`. **No noise function is used.**

---

## 2. Bonbori SIZE flicker (the dominant visible pulse)

Driven by `timers[1]` in `d_a_ep.execute()`. The orb's uniform scale wobbles, re-rolling a fresh
random target on a random interval and easing toward it.

```ts
// timers count down in frames (1/30 s)
this.timers[1] -= deltaTimeFrames;

if (this.timers[1] === 0) {
    this.timers[1] = 3.0 + cM_rndF(6.0);              // next re-roll interval
    this.alphaModelScaleTarget = 0.75 + cM_rndF(0.075); // new size target
}

// ease toward the target (speed 0.4/frame, capped at 0.04/frame)
this.alphaModelScale = cLib_addCalc2(this.alphaModelScale, this.alphaModelScaleTarget, 0.4 * deltaTimeFrames, 0.04);

// final mesh scale also multiplies the torch's overall light power
const scale = this.alphaModelScale * this.lightPower;
```

| Parameter | Value | In seconds (30 Hz) |
|---|---|---|
| Re-roll interval | `3 + cM_rndF(6.0)` ⇒ **[3, 9) frames** | **[0.10, 0.30) s** (avg ~6 frames ≈ 0.20 s) |
| Size target | `0.75 + cM_rndF(0.075)` ⇒ **[0.75, 0.825)** | — |
| Ease speed | `0.4` per frame (40% of remaining gap) | — |
| Ease max velocity | `0.04` per frame | 1.2 / s |
| Final scale | `alphaModelScale * lightPower` | `lightPower ≈ placement scale.x`, ~1 once warmed up |

So the orb radius oscillates roughly **±5% around ~0.79× base**, re-rolled ~5×/s, softly eased.

---

## 3. Light LEVEL flicker (pool brightness — the fine grain)

Driven by `timers[0]` in `d_a_ep.execute()`. This is the alpha (opacity/intensity) of the projected
pool. It re-rolls faster but moves over a much smaller band and is slew-capped, so it reads as a
subtle shimmer rather than a hard strobe.

```ts
this.timers[0] -= deltaTimeFrames;

if (this.timers[0] === 0) {
    this.timers[0] = cM_rndF(5.0);                 // next re-roll interval
    this.alphaModelAlphaTarget = 32.0 + cM_rndF(4.0); // new alpha target (0–255 range)
}

// ease toward the target (speed 1.0/frame, capped at 1.0 alpha-unit/frame)
this.alphaModelAlpha = cLib_addCalc2(this.alphaModelAlpha, this.alphaModelAlphaTarget, 1.0 * deltaTimeFrames, 1.0);
```

| Parameter | Value | In seconds (30 Hz) |
|---|---|---|
| Re-roll interval | `cM_rndF(5.0)` ⇒ **[0, 5) frames** | **[0, 0.167) s** (avg ~2.5 frames ≈ 0.08 s) |
| Alpha target | `32 + cM_rndF(4.0)` ⇒ **[32, 36)** of 255 | normalized **[0.125, 0.141]** |
| Ease speed | `1.0` per frame | — |
| Ease max velocity | `1.0` alpha-unit/frame | 30 / s |

This `alphaModelAlpha` becomes `MAT0.a = data.alpha / 255` when the mesh is drawn (see §5), i.e. it
controls **how much alpha the volume stamps** into the framebuffer ⇒ pool brightness ≈ **0.13**.

> **Perceptual weighting (important for matching the look):** the **size** pulse (§2) is the dominant
> visible flicker; the **brightness** pulse (§3) is a fine grain on top (only a 32→36 band, slew-capped).
> Do **not** make the brightness flicker hard — keep it subtle.

> Notes: `timers[2]` is decremented but never read. There is a disabled alternate branch
> (`field_0x7d4`, always 0 here) that would have used `timers[1] = cM_rndF(5.0)` and
> `scaleTarget = 0.55 + cM_rndF(0.2)` — ignore it.

---

## 4. Rotation rates (the spin)

```ts
this.alphaModelRotY += 0xD0  * deltaTimeFrames;  // 0xD0  = 208 units/frame
this.alphaModelRotX += 0x100 * deltaTimeFrames;  // 0x100 = 256 units/frame
// matrix built as: translate(posTop) → rotY → rotX → scale(uniform)
```

| Axis | units/frame | °/frame | °/sec | rad/sec | seconds per full turn |
|------|------------:|--------:|------:|--------:|----------------------:|
| **Y** | 208 | 1.1426 | **34.28** | 0.598 | **10.50 s** (65536/208 ≈ 315 frames) |
| **X** | 256 | 1.4063 | **42.19** | 0.736 | **8.53 s** (256 frames) |

- Both spin continuously and never reset. There is **no Z rotation**.
- The ratio is `256:208 = 16:13` — deliberately **non-harmonic**, so the orientation tumbles without an
  obvious loop (only truly repeats every ~110 s). This is a big reason the pool never looks like it's
  just spinning in place.

---

## 5. How the scene is tinted (the 3-pass volume → composite)

Implemented in `dDlst_alphaModel_c.draw()`. The orb is **never drawn as visible color** — it is drawn
as a **depth-tested volume into the destination alpha channel**, then a fullscreen quad adds the warm
color through that alpha mask. This is a shadow-volume / stencil-volume style intersection (z-fail
counting), accumulated in alpha instead of stencil.

The actor sets the tint color and queues the orb each frame:

```ts
// d_a.ts, in d_a_ep.draw()
const alphaModel0 = globals.dlst.alphaModel0;
colorFromRGBA8(alphaModel0.color, 0xEB7D0000);  // warm orange: R=235, G=125, B=0 (A unused here)
alphaModel0.set(dDlst_alphaModel__Type.Bonbori, this.alphaModelMtx, this.alphaModelAlpha);
```

Then per queued orb, two volume passes write alpha, followed by one fullscreen composite:

**Pass A — back faces, ADD into alpha** (`materialHelperBackRevZ`, material `l_backRevZMat`)
**Pass B — front faces, SUBTRACT from alpha** (`materialHelperFrontZ`, material `l_frontZMat`)

```ts
// d_drawlist.ts (material setup)
frontZ.ropInfo.blendMode = GX.BlendMode.SUBTRACT;
frontZ.ropInfo.depthFunc  = GX.CompareType.GREATER;
// MAT0.a = data.alpha / 0xFF;  // the flickering stamp alpha from §3
```

Both passes are **depth-tested against the already-rendered scene depth buffer**. The net alpha at a
pixel = (back faces behind the wall) − (front faces behind the wall) = nonzero **only where solid
scene geometry lies inside the orb volume**. That is what makes the pool *conform* to the wall/floor
instead of being a flat disc, and the low poly count is what makes its boundary faceted.

**Pass C — fullscreen composite** (`materialHelperDrawAlpha`, an ortho quad):

```ts
// d_drawlist.ts (composite material) — "the magic is the DSTALPHA"
mb.setZMode(false, GX.CompareType.ALWAYS, false);                       // no depth test/write
mb.setBlendMode(GX.BlendMode.BLEND, GX.BlendFactor.DSTALPHA, GX.BlendFactor.ONE);
// TEV outputs the rasterized MAT0 color (= alphaModel0.color, the warm tint)
colorCopy(materialParams.u_Color[ColorKind.MAT0], this.color);
```

Blend math: `result = tintColor * DSTALPHA + scene * 1` — i.e. **additively add the warm tint, scaled
by the accumulated destination alpha**. Where the orb stamped alpha (wall inside the orb), the warm
color is added; elsewhere nothing.

> The original game used **three** materials (two add, one sub); this reproduction reduces it to **two**
> mesh draws + one composite (comment in `d_drawlist.ts`). The enum also has `BonboriTwice`,
> `Bonbori2`, `BonboriThrice`, `Cube`, `BeamCheck` — variants that stamp multiple times for stronger
> pools or use different shapes.

---

## 6. The mesh ("Bonbori")

- Loaded from compiled symbol data: `l_bonboriPos` + `l_bonboriDL` in `d_drawlist.o`.
- **Position-only** vertex format: `POS_XYZ`, **F32**, stride `0x0C` (12 bytes). No normals, no UVs —
  it exists purely as a volume hull (never shaded).
- **INDEX8** indices ⇒ at most 256 vertices. Deliberately **low-poly** → faceted silhouette.
- Exact triangle count = `bonboriShape.indexCount` (decoded from `l_bonboriDL` at load). The precise
  count was **not decoded** for this doc — it's simply "low-poly sphere-like." Any low-poly sphere
  (e.g. an icosphere at subdivision 0–1) reproduces the look; decode `l_bonboriDL` if you need the
  exact hull.

---

## 7. Render-pipeline integration

```ts
// Main.ts
renderInstManager.setCurrentList(dlst.alphaModel);
dlst.alphaModel0.draw(globals, renderInstManager, viewerInput); // queue (~L458)
...
this.executeList(passRenderer, dlst.alphaModel, 'AlphaModel');   // execute in Main pass (~L575)
// → renders into mainColor + mainDepth, AFTER opaque scene depth is populated
```

The critical requirement when porting: run this **after** your opaque geometry/depth prepass, reading
that depth, so the volume intersection is correct.

---

## 8. Companion environment point light (separate system)

At the same torch, `d_a_ep` also registers a conventional soft point light (`LIGHT_INFLUENCE`). This
lights nearby surfaces warmly; it is **not** the faceted pool. Included here for completeness.

```ts
// d_a.ts, d_a_ep.ep_move() — set every frame
vec3.copy(this.light.pos, this.posTop);
this.light.color.r = 600 / 0xFF;   // warm orange (values >1 are intentional)
this.light.color.g = 400 / 0xFF;
this.light.color.b = 120 / 0xFF;
this.light.power = this.lightPower * 150.0;  // RADIUS / range — constant once warmed up, NEVER flickers
this.light.fluctuation = 250.0;              // how hard the brightness flickers
```

`lightPower` ramps **once** at spawn (`cLib_addCalc2(lightPower, scale.x, 0.5·dt, 0.2)`) then holds.
The **radius does not flicker** — only brightness does. The brightness flicker lives in
`d_kankyo.ts` (`settingTevStruct_plightcol_plus`):

```ts
atten     = clamp(dist / power, 0, 1);
influence = 1 - atten*atten;                 // quadratic falloff, =0 at the radius
if (fluctuation >= 1000) {
    target = fluctuation - 1000;             // steady, no flicker
} else {
    base   = 255 - (fluctuation / 3) * influence;
    target = lerp(base, 255, cM_rndF(1.0));  // per-frame uniform-random brightness
}
// dynamic-light channel additionally smooths: cLib_addCalc2(color.r, target/255, 0.4, 20.0)
// warm tint add on surfaces: colorC0 += lightColor * (influence * 0.2)
```

With `fluctuation = 250`, near the torch (`influence ≈ 1`) brightness re-rolls each frame between
~0.67 and 1.0; at the radius (`influence = 0`) the flicker vanishes. **Distance gates the flicker
amplitude; the radius itself is constant.**

---

## 9. Porting recipe (modern engine)

The Bonbori pool maps cleanly onto a **deferred light-volume / stencil-decal** pass:

1. **Mesh:** a deliberately low-poly sphere (icosphere subdivision 0–1). Flat-shaded, no soft falloff —
   you want hard volume edges and visible facets.
2. **Per torch, per tick (30 Hz):**
   - `rotY += 1.1426°` (34.28°/s), `rotX += 1.4063°` (42.19°/s). No Z.
   - update SIZE timer/ease (§2) → `meshScale = scale * lightPower`
   - update ALPHA timer/ease (§3) → pool intensity ≈ 0.13
3. **Mark the volume:** render the sphere with a **z-fail stencil pass** (incr back / decr front against
   the scene depth buffer), exactly like a deferred point-light stencil pass. Stencil ≠ 0 ⇒ "wall is
   inside the orb."
4. **Tint pass:** additively blend the warm color (≈ RGB 235,125,0) onto the scene where stencil is set,
   scaled by the flicker alpha. (WW equivalent: `tint * DSTALPHA + scene`.)
5. Optional: stamp 2–3× (`BonboriTwice`/`Thrice`) for stronger pools.

### Drop-in pseudocode (at 30 Hz ticks)

```text
// rotation
rotY += radians(1.1426)   // 34.28°/s
rotX += radians(1.4063)   // 42.19°/s

// SIZE flicker
sizeTimer -= 1
if sizeTimer <= 0:
    sizeTimer  = 3 + rand(0, 6)              // frames
    sizeTarget = 0.75 + rand(0, 0.075)
scale += clamp(0.4*(sizeTarget - scale), -0.04, 0.04)
meshScale = scale * lightPower

// LIGHT-LEVEL flicker
alphaTimer -= 1
if alphaTimer <= 0:
    alphaTimer  = rand(0, 5)                 // frames
    alphaTarget = (32 + rand(0,4)) / 255     // ≈ 0.13
alpha += clamp(1.0*(alphaTarget - alpha), -1/255, 1/255)
```

### Framerate independence (if not locked to 30 fps)

- Multiply rotation increments and timer decrements by `dt_seconds * 30`.
- Replace each ease with `x += (target - x) * (1 - pow(1 - speed, dt*30))`, clamped to the per-tick
  max-velocity scaled by `dt*30` (`0.04*dt*30` for scale, `(1/255)*dt*30` for alpha).
- Re-roll thresholds stay in seconds: size `(3 + rand(0,6))/30` s, alpha `rand(0,5)/30` s.

---

## Quick-reference cheat sheet

| Thing | Value |
|---|---|
| Logic rate | 30 Hz (1 frame = 1/30 s) |
| Angle unit | 360/65536° per unit |
| Rot Y | 0xD0 = 208 u/f = 34.28°/s (10.50 s/turn) |
| Rot X | 0x100 = 256 u/f = 42.19°/s (8.53 s/turn) |
| Rot Z | none |
| Size re-roll | every [3, 9) frames = [0.10, 0.30) s |
| Size target | 0.75 + rand(0, 0.075) → [0.75, 0.825) |
| Size ease | speed 0.4/f, maxVel 0.04/f |
| Alpha re-roll | every [0, 5) frames = [0, 0.167) s |
| Alpha target | 32 + rand(0, 4) of 255 → ≈ 0.13 |
| Alpha ease | speed 1.0/f, maxVel 1.0(/255)/f |
| Tint color | 0xEB7D0000 → RGB (235, 125, 0), warm orange |
| Composite blend | `tint * DSTALPHA + scene` (additive, alpha-masked) |
| Volume passes | back ADD + front SUBTRACT into dst alpha, depth-tested vs scene |
| Mesh | low-poly sphere, POS-only F32, INDEX8 (≤256 verts) |
| Companion light radius | `lightPower * 150`, constant (does NOT flicker) |
| Companion light fluctuation | 250 (brightness-only flicker, distance-gated) |
| Random | `Math.random()` (uniform) — no noise function |
