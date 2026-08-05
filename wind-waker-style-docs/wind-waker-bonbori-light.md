# Wind Waker "Bonbori" Torch Light — Reference

Reverse-engineered from the noclip.website reproduction of *The Wind Waker*: the faceted, rotating,
flickering torch light pool seen on walls and floors (e.g. Forsaken Fortress torches). This is the
reference the **Light Casting** feature's constants are matched against — the port itself lives in
`soh/soh/Enhancements/Graphics/WorldLighting.cpp`.

> **Key insight:** the visible pool is **not** a soft point light. It is a low-poly sphere mesh
> ("Bonbori") rendered as a depth-tested volume mask, then used to additively tint the scene with a
> warm colour. The faceting comes from the low poly count; the motion from spinning + scaling the
> mesh; the flicker from randomized alpha/scale targets eased over time.

There is also a separate, conventional point light at the same torch (soft warm lighting on nearby
surfaces) — documented at the end as the "companion light". The two are independent systems.

## Source map (noclip.website)

| Concern | File | Notes |
|---|---|---|
| Torch actor / driver | `src/ZeldaWindWaker/d_a.ts` — class `d_a_ep` | spins, scales, sets alpha, queues the Bonbori each frame |
| Alpha-model system | `src/ZeldaWindWaker/d_drawlist.ts` — `dDlst_alphaModel_c` | geometry, materials, volume + composite passes |
| Easing helpers | `src/ZeldaWindWaker/SComponent.ts` — `cLib_addCalc*`, `cM_rndF`, `cM_s2rad` | math primitives |
| Point-light flicker | `src/ZeldaWindWaker/d_kankyo.ts` — `settingTevStruct_plightcol_plus` | companion soft light |
| Pipeline wiring | `src/ZeldaWindWaker/Main.ts` | runs in the main pass against populated depth |

## Time & angle base

- Logic runs at **30 Hz**: `deltaTimeFrames = 1.0` ⇒ 1/30 s. All "per frame" values below are per
  1/30 s.
- Angles are 16-bit: a full turn = `0x10000` units, so 1 unit = 360/65536°.

## The easing function

All smoothing is first-order exponential smoothing with a per-frame slew cap (a low-pass filter —
not a spring; it never overshoots):

```ts
// The workhorse — eases in asymptotically:
function cLib_addCalc2(src, target, speed, maxVel) {
    return src + clampAbs(speed * (target - src), 0.0, maxVel);
}
```

Each tick it moves fraction `speed` of the remaining gap, capped at `maxVel`. With `speed = 0.4` the
gap shrinks to ~60% per tick. Random source is `cM_rndF(max)` — uniform `[0, max)`; no noise
function anywhere.

## Size flicker (the dominant visible pulse)

The orb's uniform scale wobbles: re-roll a random target on a random interval, ease toward it.

| Parameter | Value | In seconds |
|---|---|---|
| Re-roll interval | `3 + rnd(6)` frames | [0.10, 0.30) s |
| Size target | `0.75 + rnd(0.075)` → [0.75, 0.825) | — |
| Ease | speed 0.4/frame, maxVel 0.04/frame | — |
| Final scale | `alphaModelScale * lightPower` (≈1 warmed up) | — |

The orb radius oscillates roughly ±5% around ~0.79× base, re-rolled ~5×/s, softly eased.

## Light-level flicker (pool brightness — the fine grain)

The alpha the volume stamps. Re-rolls faster but over a much smaller band, slew-capped — a subtle
shimmer, never a strobe.

| Parameter | Value | In seconds |
|---|---|---|
| Re-roll interval | `rnd(5)` frames | [0, 0.167) s |
| Alpha target | `32 + rnd(4)` of 255 → ≈ 0.13 | — |
| Ease | speed 1.0/frame, maxVel 1.0 alpha-unit/frame | — |

> **Perceptual weighting:** the **size** pulse is the dominant visible flicker; the brightness pulse
> is fine grain on top. Do not make the brightness flicker hard.

## Rotation (the spin)

```ts
this.alphaModelRotY += 0xD0  * deltaTimeFrames;  // 208 units/frame
this.alphaModelRotX += 0x100 * deltaTimeFrames;  // 256 units/frame
// matrix: translate(posTop) → rotY → rotX → scale(uniform)
```

| Axis | units/frame | °/sec | seconds per turn |
|------|------------:|------:|-----------------:|
| Y | 208 | 34.28 | 10.50 |
| X | 256 | 42.19 | 8.53 |

No Z rotation. Both spin continuously. The 256:208 = 16:13 ratio is deliberately non-harmonic, so
the orientation tumbles without a visible loop (~110 s true period).

## The 3-pass volume → composite

Implemented in `dDlst_alphaModel_c.draw()`. The orb is never drawn as visible colour — it is drawn
as a depth-tested volume into the destination **alpha** channel, then a fullscreen quad adds the
warm colour through that alpha mask (same intersection logic as a stencil light volume, accumulated
in alpha instead of stencil):

- **Pass A** — back faces, ADD into dst alpha, depth-tested vs the scene.
- **Pass B** — front faces, SUBTRACT from dst alpha, depth-tested.
  Net alpha ≠ 0 only where solid scene geometry lies inside the orb — that's why the pool conforms
  to the wall/floor instead of being a flat disc.
- **Pass C** — fullscreen ortho quad, no depth test, blend `tint * DSTALPHA + scene * 1`. Tint is
  `0xEB7D00` (R 235, G 125, B 0 — warm orange); the stamped alpha carries the flicker.

The original game used three materials (two add, one sub); noclip reduces it to two mesh draws + one
composite. Enum variants `BonboriTwice`/`Thrice` stamp multiple times for stronger pools.

## The mesh

- Loaded from `l_bonboriPos` + `l_bonboriDL` in `d_drawlist.o`.
- Position-only F32 vertices, INDEX8 (≤256 verts) — deliberately low-poly, purely a volume hull.
- Exact triangle count wasn't decoded; any low-poly sphere (icosphere subdivision 0–1) reproduces
  the look.

## Companion environment point light (separate system)

`d_a_ep` also registers a conventional soft point light at the torch:

```ts
this.light.color = { r: 600/255, g: 400/255, b: 120/255 };  // warm orange (>1 intentional)
this.light.power = this.lightPower * 150.0;  // RADIUS — constant once warmed up, NEVER flickers
this.light.fluctuation = 250.0;              // brightness flicker strength
```

`lightPower` ramps once at spawn, then holds. Only the **brightness** flickers (in `d_kankyo.ts`):
with `fluctuation = 250`, near the torch brightness re-rolls each frame between ~0.67 and 1.0;
the flicker amplitude fades to zero at the radius. **Distance gates the flicker; the radius itself
is constant.**

## Quick-reference cheat sheet

| Thing | Value |
|---|---|
| Logic rate | 30 Hz |
| Rot Y / X / Z | 34.28°/s / 42.19°/s / none |
| Size re-roll | every [0.10, 0.30) s |
| Size target | [0.75, 0.825), ease 0.4/f cap 0.04/f |
| Alpha re-roll | every [0, 0.167) s |
| Alpha target | ≈ 0.13, ease 1.0/f cap 1/255/f |
| Tint colour | RGB (235, 125, 0) |
| Composite blend | `tint * DSTALPHA + scene` |
| Volume passes | back ADD + front SUB into dst alpha, depth-tested |
| Mesh | low-poly sphere, POS-only F32, INDEX8 |
| Companion light | radius constant; brightness-only flicker, distance-gated |
| Random | uniform — no noise function |
