# Wind Waker-style Actor Shadows

A developer/agent orientation for the **actor-shadow** feature on the `wind-waker-style-cel-shading`
branch. Read this instead of the diffs to get caught up. References are by **file + symbol** (not line
numbers, which drift). Start with [`README.md`](./README.md) for how this fits the other two features.

This is the third feature in the Wind Waker line, after
[`wind-waker-style-cel-shading.md`](./wind-waker-style-cel-shading.md) (relights the _objects_) and
[`wind-waker-light-casting.md`](./wind-waker-light-casting.md) (lights the _world_). **Actor shadows**
casts each object's own silhouette onto the ground from the same key light cel shading uses.

> **Naming note:** the GUI says **"Actor Shadows"**, CVars use **`Graphics.WorldShadows.*`**, and the
> renderer transport reuses **`gSPToonShadow` / `G_SETTOONSHADOW` / `FlushToonShadow` / `toon_shadow_*`**
> (mirrors `gSPToon` / `gSPToonKey`). Same split-naming convention as the other two features.

---

## What it does

Each actor (Link, NPCs, enemies, items, pots, signs, …) casts a **shape-based drop shadow** that is its
own **captured silhouette**, projected onto the actor's **floor polygon** (so it follows slopes) **along
the same eased key light** cel shading chose for that actor, drawn as a translucent decal with a **soft
edge**. It **replaces** the vanilla actor shadows (Link's multi-light feet, the NPC/enemy circles, the
horse shadow, the sign/cobra texture shadows), which are suppressed while it's on. On by default on this
build. The same data-driven blacklist as cel shading (doors, the Deku Tree, water boxes) opts those
actors out of both relight and shadow.

It is **decoupled from cel shading**: actor shadows work whether or not the cel relight is enabled (it
only reuses the per-actor key *selection*). The shadow is the heir of the abandoned `shadow-development`
planar shadow — same projection, now with (a) the **soft edge** that attempt lacked and (b) **all three
backends** (that attempt was Metal-only).

**Accepted limitation (same as vanilla):** planar projection onto the floor *polygon* — it conforms to
slopes but projects flat past a hard cliff edge. True cliff conformance needs **shadow mapping** (a large
separate system). Stencil shadow **volumes** were tried and abandoned for OoT actors — **do not retry**
(non-watertight meshes leak, self-shadow, double-shadow at ledges).

## Which actors cast a shadow (and which keep a vanilla one)

An actor gets the new **shape shadow** when all of: (1) it isn't blacklisted (`ToonActorExcluded`:
doors, Deku Tree, water boxes); (2) it has a floor within range (`distToFloor ∈ [-50,1500]`); (3) it's
within the **render-distance cull** (`actor->projectedPos.z < MaxDistance`); and (4) its geometry is
drawn with **`G_LIGHTING`** (the capture gate — unlit geometry isn't captured, so a fully unlit actor
gets no shape shadow).

**Vanilla shadow suppression** is global for the **standard path** — `ActorShadow_Draw`
(circle/white/horse) and `ActorShadow_DrawFeet` (Link), which is the vast majority of actors including
Link's feet — all early-return via `ActorShadow_Suppressed()`.

But ~17 actors draw a **bespoke** shadow directly in their own `draw()` (their own
`gSPDisplayList(gCircleShadowDL/…)`), bypassing that path. Only a few are suppressed
(`ovl_En_Kanban`, `ovl_Bg_Jya_Cobra`, `ovl_En_Dekubaba`, `ovl_En_Karebaba` — the last two because their
lit body is captured, so their bespoke circle would *double up*). The rest **intentionally keep** their
vanilla shadow: `ovl_En_Wallmas` (the drop **telegraph** — gameplay-critical), the bosses
(`Boss_Ganon/Ganon2/Mo/Sst/Tw`), `ovl_En_Horse_Normal`, `ovl_En_Clear_Tag` (Arwing, airborne),
`ovl_En_Nwc` (cucco chicks), `ovl_En_Vb_Ball`, `ovl_Door_Shutter` (a door — already blacklisted). To
suppress another, gate its bespoke shadow draw behind the same two CVars (grep `gCircleShadowDL` /
`ShadowDL` under `soh/src/overlays/actors/`).

## Shadow & light receivers (walkable floor actors)

A handful of surfaces the player walks on are spawned as **actors**, not baked into the room mesh — the
Castle-Town drawbridge (`Bg_Spot00_Hanebasi`), the Gerudo Valley bridge (`Bg_Spot09_Obj`), and some dungeon
platforms (`Bg_Mori_Bigst`, `Bg_Haka_Meganebg`, `Bg_Menkuri_Kaiten`, the Shadow-Temple `Bg_Haka_Gate` trap
floor/statue). Because actors draw *after* the shadow/light flushes, those floors caught neither shadows nor
light pools — the effect stopped at the floor's edge.

**Fix — a receiver pre-pass.** `func_800315AC` (the actor draw loop) now draws a small **whitelist** of these
floor actors *first*, before the light-pool and shadow flushes, so their geometry is in the depth buffer and
both world effects fall on them. They are then **skipped** in the main actor loop so each still draws once.
This is purely a draw-order change — the flushes are unchanged.

- **Whitelist:** `ToonShadowReceiver` in `ToonLighting.cpp`, exposed to the C game code as
  `ToonLighting_IsShadowReceiver` (declared in the new `ToonLighting.h`). Curated by actor id; the reused
  `Bg_Haka_Gate` overlay is additionally gated by its params low byte (only the walkable FLOOR/STATUE variants,
  not the gate/skull). Receivers are also added to `ToonShadowExcluded` so a floor never casts its **own**
  silhouette (which would self-shadow now that it sits in the depth buffer).
- **Draw path:** the per-actor loop body was factored into `Actor_DrawListEntry` (byte-for-byte vanilla) so the
  pre-pass and the main loop share one cull/lens/draw path.
- **Light pools too:** the `OnPlayDrawWorldLights` flush was moved from `Play_Draw` (pre-actor) into
  `func_800315AC`, right after the pre-pass — so torch/fairy pools also land on these floors. Safe because the
  pools clear `G_LIGHTING` (the open cel bracket can't shade them). Side effect: pools now flush slightly later
  in the frame (after skybox/rain/screen-fill); identical in normal play, only differs during rain/fades.
- **Gating:** the pre-pass runs while Actor Shadows + the **Walkable Actors** toggle are on, so light-on-floors
  currently rides on the shadow feature being enabled.

Adding a floor is one `case` in `ToonShadowReceiver`. Watch moving platforms: the capture lags one frame, so a
fast-rotating/rising receiver shows the shadow trailing during motion.

## The technique: planar silhouette projection + multi-tap soft edge

Per object, the renderer captures the actor's drawn **world-space triangles**, then at the object boundary
projects each onto the floor plane along the cast direction and draws them as flat translucent geometry:

1. **Capture** — as the actor's verts/tris stream through Fast3D, `GfxSpVertex` stores each vertex's
   world position (`LoadedVertex.wx/wy/wz`) and `GfxSpTri1` appends the triangle's 3 world positions to
   `mShadowVerts` (while `mRdp->toon_shadow` is armed).
2. **Project** — `FlushToonShadow` first **remaps the key's elevation**: the key's height above the floor
   plane (`L·N`) is remapped into `[minElevation, 1]` with the azimuth preserved, so a low light is raised
   toward straight-overhead before projecting. This keeps the shadow **short and under the actor** (like
   the vanilla shadow) and **bounds the projected length** so it eases smoothly with the key instead of
   popping when the light is near-horizontal (length is hypersensitive to the key's vertical component at
   low angles — the s8-quantized key would otherwise snap visibly even while the cel ramp looks smooth).
   `minElevation` comes from the Length slider. Then it intersects each captured vertex's cast ray with the
   floor plane (`t = -(N·V + planeD)/(N·castDir)`), skipping whole-triangle-below-floor cases (hanging off
   a ledge).
3. **Soft edge (multi-tap)** — the projected silhouette is drawn over **N taps**, each offset slightly
   around a ring in the floor's tangent plane (radius = Softness). Each tap uses a fresh, increasing
   **stencil ref** in **`StencilMode::ShadowMask`** (compare GREATER, op REPLACE): within a tap each
   ground pixel paints exactly once (overlapping limbs don't blotch); across taps each higher ref
   re-passes and adds one accumulation layer → the core (all taps overlap) is darkest, the fringe
   feathers into a soft penumbra. Per-tap alpha solves `1-(1-A)^(1/N) = A` so N taps reach core opacity
   `A`. N=1 degrades to a single hard-edged shadow.

The shadow draws in **`POLY_OPA`** with **`G_RM_AA_ZB_XLU_DECAL`** (decal zmode → slope-scaled depth bias
+ LEQUAL, depth-tested vs the scene but **no depth write**), flat `SHADE` combiner (black × per-tap
alpha). World→clip uses `mRsp->P_matrix` (the camera is baked into the projection matrix).

---

## Architecture: two layers (same split as the other two features)

| Layer | Repo | Responsibility |
|-------|------|----------------|
| **Policy** (game) | `soh/` | Pick the key (reused from cel shading), compute the per-actor floor plane, choose which actors cast (blacklist), suppress vanilla shadows, push the look tuning. |
| **Transport** (renderer) | `libultraship/` (Fast3D) | Capture each object's world geometry, project it onto the floor plane, draw it as a multi-tap stencil-masked translucent decal. Knows nothing OoT-specific. |

## Data flow (one frame)

1. **Per actor, choose key + arm the floor plane.** `HandleActorDraw` in
   `soh/soh/Enhancements/Graphics/ToonLighting.cpp` (on the `OnActorDraw` hook) picks + eases the key and
   emits `gSPToonKey` (unchanged cel behaviour), then — if `WorldShadows.Enabled` and the actor isn't
   blacklisted — computes the floor plane from `actor->floorPoly`/`actor->floorHeight` and emits
   **`gSPToonShadow(nx,ny,nz,planeD)` into `POLY_OPA` only**. A zero normal (no floor in range) disarms
   the shadow but still marks the per-object boundary.
2. **Renderer captures + defers.** `gfx_set_toon_shadow_handler_custom` flushes the **previous** object's
   shadow, decodes the floor plane into `mRsp->toon_shadow_plane[4]`, sets `mRdp->toon_shadow`, and
   **snapshots `toon_shadow_dir` from `toon_key_dir`** (critical: the next object overwrites
   `toon_key_dir` before this object's deferred flush). `GfxSpVertex`/`GfxSpTri1` then capture the actor's
   world geometry.
3. **Renderer draws.** At the next object boundary (next `gSPToonShadow`, or the `gSPToon` bracket edge),
   `FlushToonShadow` runs the project + multi-tap sequence above, then resets the stencil to `Off`.
4. **Per frame**, `OnToonFrameUpdate` pushes the look tuning via
   `interp->SetToonShadowParams(opacity, minGraze, taps, softness)`.

---

## Where the code lives

### SoH (game-side policy)
- **`soh/soh/Enhancements/Graphics/ToonLighting.cpp`** — `ToonActorExcluded` (blacklist), `sToonEnabled`
  (bracket tracking), `GetInterpreter`, the shadow emit + floor-plane block in `HandleActorDraw`,
  `OnToonFrameUpdate` (`SetToonShadowParams` push), and `RegisterToonLighting` (now gates the hooks on
  **cel OR shadows** enabled, watches both CVars). Defaults: `kDefaultShadowOpacity = 0.5`,
  `kDefaultShadowSoftness = 0.4`, `kDefaultShadowTaps = 4`, `kDefaultShadowLength = 0.66`.
- **`soh/src/code/z_actor.c`** — `ActorShadow_Suppressed()` predicate; early-return guards in
  `ActorShadow_Draw` (circle/white/horse) and `ActorShadow_DrawFeet` (Link's feet). The `OnActorDraw`
  hook callout now fires when `ToonLighting.Enabled || WorldShadows.Enabled`. The `gSPToon` relight
  bracket in `func_800315AC` stays gated on `ToonLighting.Enabled` only.
- **Bespoke-shadow overlays** gated behind `WorldShadows.Enabled && SuppressVanillaShadows`:
  `ovl_En_Kanban/z_en_kanban.c`, `ovl_Bg_Jya_Cobra/z_bg_jya_cobra.c`, `ovl_En_Dekubaba/z_en_dekubaba.c`,
  `ovl_En_Karebaba/z_en_karebaba.c` (see "Which actors cast a shadow").
- **`soh/soh/SohGui/SohMenuSettings.cpp`** — the **Settings → Actor Shadows** page (Enable, Suppress
  Vanilla Shadows, Opacity, Softness, Tap Count, Length + Reset).

### libultraship (renderer transport)
- **GBI:** `include/libultraship/libultra/gbi.h` — `G_SETTOONSHADOW 0x4b` + `gSPToonShadow(pkt,nx,ny,nz,planeD)`
  (normals as 3× s8 in w0, `planeD` as raw float32 bits in w1). `include/fast/lus_gbi.h` —
  `OTR_G_SETTOONSHADOW`.
- **`src/fast/interpreter.cpp`** — `gfx_set_toon_shadow_handler_custom` (+ dispatch entry),
  `GfxSpVertex` (world-pos capture, gated `toon || toon_shadow`), `GfxSpTri1` (triangle capture, gated on
  `toon_shadow` — decoupled from `toon`), `Interpreter::FlushToonShadow` (project + multi-tap loop),
  `gfx_set_toon_handler_custom` (bracket-boundary flush).
- **`include/fast/interpreter.h`** — `LoadedVertex.wx/wy/wz`; `RSP.toon_shadow_plane[4]/toon_shadow_dir[3]`;
  `RDP.toon_shadow`; `Interpreter` members `mShadowVerts`, `mToonShadowAlpha/MinGraze/Softness`,
  `mShadowTaps`, `mStencilRefCounter`; `SetToonShadowParams`, `FlushToonShadow`.
- **`include/fast/backends/gfx_rendering_api.h`** — `StencilMode::ShadowMask = 4`;
  `SetStencilMode(int mode, int ref = 0)` + `mStencilRef`.
- **Per-backend `DrawTriangles`** — the `ShadowMask` branch (GREATER / REPLACE / KEEP, ref applied every
  draw) in `gfx_metal.cpp` (`setStencilReferenceValue`), `gfx_opengl.cpp` (`glStencilFunc/Op`),
  `gfx_direct3d11.cpp` (`OMSetDepthStencilState` ref). Plus the **per-frame stencil clear** added to
  `gfx_opengl.cpp` (`GL_STENCIL_BUFFER_BIT`) and `gfx_direct3d11.cpp` (`D3D11_CLEAR_STENCIL`)
  `ClearFramebuffer` (Metal already clears via `LoadActionClear`).

No shader/asset changes — fixed-function stencil + the existing flat-color combiner, so **no `soh.o2r`
regen** is needed (unlike cel shading).

---

## CVars

Internal prefix `WorldShadows`; the GUI shows "Actor Shadows".

| CVar (`gEnhancements.Graphics.WorldShadows.*`) | Default | Meaning |
|---|---|---|
| `Enabled` | **1** | Master toggle (also un-gates the shared `OnActorDraw` hook). |
| `SuppressVanillaShadows` | 1 | Hide the vanilla feet/circle/horse/sign/cobra shadows. |
| `Opacity` | 0.5 | Core target darkness `A`. |
| `Softness` | 0.4 | Penumbra width (tap ring radius = softness × 8 world units); 0 = hard edge. |
| `Taps` | 4 | Accumulation taps (1–8); 1 = hard shadow. |
| `Length` | 0.3 | Shadow length → `minElevation = 0.95 - Length*0.85` (lower = light forced steeper = shorter). |
| `MaxDistance` | 1500 | Camera-forward distance (`actor->projectedPos.z`) past which an actor's shadow is culled. |
| `ReceiverActors` | 1 | Draw the walkable-floor whitelist before the flushes so shadows + light pools land on them (GUI: "Shadows on Walkable Actors"). |

Slider defaults live in the GUI **and** as `kDefault*` in `ToonLighting.cpp` — keep in sync.

---

## Invariants & gotchas (don't break these)

- **Emit `gSPToonShadow` AFTER `gSPToonKey`, into `POLY_OPA` only.** The handler snapshots the key
  direction at arm time; POLY_OPA means the floor/world depth is present and translucent effects don't
  cast.
- **The dir is a snapshot, not the live `toon_key_dir`.** The next object overwrites `toon_key_dir`
  before this object's deferred flush, so `gfx_set_toon_shadow_handler_custom` copies it into
  `toon_shadow_dir`.
- **Deferred, per-object flush.** Each object's shadow is drawn at the *next* object's `gSPToonShadow`
  (or the bracket edge in `gfx_set_toon_handler_custom`). Both run `FlushToonShadow` first, so an object's
  captured geometry can't leak into another's shadow.
- **Capture is gated on `toon_shadow`, not `toon`** — that's the decoupling that lets shadows run with
  cel shading off. The world-pos capture in `GfxSpVertex` is gated on `toon || toon_shadow`.
- **Multi-tap stencil:** fresh **increasing** ref per tap + GREATER/REPLACE gives single-layer-per-tap
  AND cross-tap accumulation. The ref is applied **every draw** in Metal/D3D11 (their state-rebuild guard
  only fires on mode change, not ref change). The per-frame stencil clear is mandatory (the mask assumes
  stencil starts at 0; the volume `Composite` mode self-zeroes but the shadow mask does not).
- **Ref wrap (8-bit, 1–255):** with N taps/actor, a shadow whose taps straddle the 255→1 wrap loses a
  little penumbra/overlap for that one frame — benign, self-corrects. Don't reset the stencil per-actor.
- **Decal zmode** (`G_RM_AA_ZB_XLU_DECAL`) is what keeps the coplanar shadow off the floor's z-fight and
  off the actor's body (no depth write).
- **`StencilMode` ↔ `WL_STENCIL_*`:** light casting uses Off/VolumeIncr/VolumeDecr/Composite (0–3);
  ShadowMask is the new value **4**. The two features never overlap in a frame (light casting resets to
  Off before the actor loop).
- **No `GenerateSohOtr`.** No shader changes.

---

## Build & test (macOS)

Build per [`README.md`](./README.md#build--test-macos) (renderer + soh; **no `GenerateSohOtr`** — no
shader changes). Enable **Settings → Actor Shadows**. Checks:
- Link casts a **shape** shadow with a **soft** edge and an even core (no dark limb seams → per-tap mask).
- Orbit the fairy / change time of day → the shadow direction swings with the key.
- Stand on a slope → the shadow follows the floor polygon; hang off a ledge → no smear onto Link (it
  floats flat past the edge, accepted).
- Toggle Suppress Vanilla Shadows; doors / Deku Tree / water cast none (blacklist).
- Softness/Taps widen+feather; Opacity darkens; Taps=1 → hard shadow.
- Disable Cel Shading but keep Actor Shadows → shadows still render, actors not relit (decoupling).

## Status & next

Functional and merged into `wind-waker-style-cel-shading` (both repos). The full capture → project →
multi-tap pipeline works across all 3 backends, reusing the cel key, the blacklist, vanilla suppression,
and the GUI; decoupled from cel shading; builds clean. Two rounds of tuning are already in:
**(1)** the **elevation remap** (§technique step 2) — raises a low key toward overhead before projecting
to bound shadow length and stop it popping as the cel key eases (Length default 0.3); **(2)** the
**render-distance cull** (`MaxDistance`) plus deku-baba double-shadow fix (see "Which actors cast a
shadow"). What remains is polishing intermittent visual glitches.

### Known glitches / where we left off (TODO — next session)
- **Intermittent visual glitches** reported by the user, **not yet diagnosed** — investigate next. No
  repro captured yet; likely candidates to check first: the deferred per-object flush boundary (does every
  actor's geometry drain under the right plane?), the 8-bit stencil-ref wrap in crowded scenes (overlapping
  actor shadows dropping a layer for a frame), and the decal depth bias vs the floor at glancing angles.
- A scene felt laggy (cause unconfirmed) — the render-distance cull + Tap Count are the perf levers; A/B
  with the Actor Shadows master toggle to confirm whether shadows are implicated.
- **Standing limitations (by design):** floats flat past hard cliff edges (planar projection; full fix =
  shadow mapping, out of scope); unlit actors get no shape shadow (capture needs `G_LIGHTING`); the soft
  edge is a jittered-ring approximation, not a true blurred projected texture; bespoke-shadow actors
  (Wallmaster telegraph, bosses, horse, …) keep their vanilla shadow on purpose.
- Tuning knobs if the look needs nudging: `kShadowSoftnessScale` (=8.0) and the `0.95 - Length*0.85`
  elevation curve in `OnToonFrameUpdate`, plus the slider defaults.
