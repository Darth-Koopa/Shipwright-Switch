# Wind Waker-style Actor Shadows

Developer notes for the actor-shadow feature on the `wind-waker-style-cel-shading` branch.
References are by file + symbol (line numbers drift). Start with [`README.md`](./README.md) for how
this fits the other features.

Cel shading relights the objects; light casting lights the world; actor shadows casts each object's
own silhouette onto the ground, from the same key light cel shading picks for that actor.

> **Naming:** the GUI says **"Actor Shadows"** (page: **Wind Waker Style → Actor Shadows**); CVars
> use **`Graphics.WorldShadows.*`**; the renderer transport uses **`gSPToonShadow*` /
> `G_SETTOONSHADOW` / `toon_shadow_*`** (mirrors `gSPToon`/`gSPToonKey`).

## What it does

Each actor casts a shape-based drop shadow: its own captured silhouette, cast along the eased cel
key light, wrapped onto the real ground so it follows slopes and bumps. It replaces the vanilla
actor shadows (Link's feet, the NPC/enemy circles, the horse shadow, the sign/cobra texture
shadows), which are suppressed while it is on. Off by default. It is decoupled from cel shading —
shadows work with the relight off (they only reuse the key *selection*).

## The technique: silhouette slab volumes

The shadow is a stencil shadow volume, but not an extrusion to infinity — it is a thin **slab** at
the actor's feet, so the shadow conforms to nearby ground without leaking down cliffs:

1. **Capture.** While an actor is armed, the renderer records each drawn triangle's world-space
   positions (`GfxSpVertex` stores `wx/wy/wz`, `GfxSpTri1` appends to `mShadowVerts`). Capture is
   gated on `G_LIGHTING` — unlit geometry (glow effects, most transparents) doesn't cast.
2. **Build** (`Interpreter::FlushToonShadow`, at each object boundary). Feet level = the lowest
   captured vertex. The captured triangles are projected along the key direction onto the feet
   level and rasterized **conservatively** at twice the output resolution
   (`kShadowRasterSize` = 2 × `kShadowGridSize` = 256; a sub-cell is marked when its centre lies
   within half a sub-cell-diagonal of a triangle — the margin closes float cracks between adjacent
   triangles). Each output cell's 2×2 sub-cells give it a 0–4 coverage count. The volume is one box
   per run of occupied cells, extruded from `feet + SlabRise` down to `feet − SlabDepth`. Abutting
   boxes share exactly-coincident, oppositely-wound walls, so their z-fail counts cancel and the
   union is seamless with stencil overlap 1.

   The grid is what makes the stencil math safe: with one closed prism per projected triangle
   (the naive alternative), every prism overlapping a ground pixel z-fail-increments the same
   8-bit stencil — and at low camera pitch the view ray's underground segment crosses hundreds of
   prism walls — so anything denser than a vanilla N64 mesh (~2k triangles is already far past it)
   saturates the counter and the shadow shows angle-dependent holes. The grid boxes emit walls only
   along each band region's outline (interior walls between abutting boxes are skipped — what
   remains is the closed boundary surface of the union), so stencil increments scale with the
   silhouette's boundary crossings: a handful, at any resolution and any camera angle.

   The key's elevation is remapped first (`Length` slider → `minElevation`) so a low light still
   casts a short shadow tucked under the actor. The footprint also scales toward its centroid by an
   eased 0..1 size the game passes, so shadows grow in and shrink out instead of popping. Volumes
   accumulate in `mShadowVolumeAccum` — nothing draws yet. A per-frame accumulator budget guards
   the pathological case: once exceeded, later objects skip their shadow (the newest is dropped;
   everything already built keeps rendering).
3. **Anti-aliased edge (opacity bands).** With `EdgeSoftness` above 0, the coverage counts split
   the footprint into disjoint bands: fully-covered cells form the core, and the partially-covered
   cells — exactly the silhouette's staircase — render lighter. Softness 1 uses one lighter step
   (partial → ½); softness 2 grades finer (2–3 sub-cells → ⅔, 1 sub-cell → ⅓) and adds a one-cell
   halo outside the footprint at ⅓. Each band becomes its own box volumes; because the bands come
   from the bitmap, this costs a few hundred extra boxes and one or two extra composite quads —
   nothing is rendered twice (unlike the abandoned multi-tap approach, which re-rendered the full
   volume per sample and blotched where taps overlapped).

4. **Render** (`Interpreter::RenderShadowVolumes`, once per frame). Per band: the band's volumes
   are transformed to clip space once and drawn as ONE batched two-sided z-fail stencil pass
   (`StencilMode::VolumeIncrDecr` — the GPU's facing picks wrap-increment or wrap-decrement per
   triangle, so no cull passes and each face is submitted once; wrap ops plus the composite's
   nonzero test make primitive order and facing polarity irrelevant), then a fullscreen composite
   quad blends flat black × the band's alpha where stencil is nonzero, self-clearing as it goes. Band alphas step down from `Opacity`: softness 1
   → core, ½; softness 2 → core, ⅔, ⅓.

The render is triggered by a `gSPToonShadowFlush` sentinel emitted in the actor draw loop
(`func_800315AC`) after the room and the receiver pre-pass but before the actors — so at that point
the depth buffer is world-only: shadows land on the environment, never on actors (no self-shadow,
no cross-actor shadowing). Because an actor's triangles stream *after* that point in the display
list, the volumes rendered each frame are the previous frame's captures — the shadow lags one frame
(imperceptible for a ground shadow).

**Batched submission:** the volume is thousands of identical-state triangles, and routing each
through `GfxSpTri1` repays full combiner/shader resolution per triangle (the measured CPU
bottleneck). Instead the render state is resolved once via a discarded setup triangle, the
per-vertex VBO layout is learned from what it wrote, and the vertex buffer is filled directly —
with the same software backface cull per pass. Backend-agnostic (it writes `mBufVbo`).

## Which actors cast

An actor casts when all of:

1. Not blacklisted — `ToonActorExcluded` (shared with cel shading: doors, Deku Tree, water boxes,
   `En_Wood02`, `Bg_Spot*`) and `ToonShadowExcluded` (adds `En_Kusa` — a blob under every grass tuft
   reads wrong — and the shadow receivers below).
2. Has a floor: `actor->floorPoly`, or a downward raycast fallback for actors that never run a bg
   check (e.g. the courtyard guards), with `distToFloor ∈ (−50, 1500)`.
3. Within the render-distance cull (`actor->projectedPos.z < MaxDistance`).
4. Link is not on a wall (climbing a ladder/vine, hanging from a ledge) — a ground slab would cut
   into the wall. The gate eases the shadow's size over ~0.15 s rather than popping.

**Deep-rooted models** (`ToonShadowDeepRooted`: signposts) bury geometry below the floor, which
would sink the whole slab underground; for those the arm command carries the floor Y and the
renderer lifts the feet up to it (the clamp only ever lifts).

**Vanilla shadow suppression** (`SuppressVanillaShadows`): `ActorShadow_Draw` (circle/white/horse)
and `ActorShadow_DrawFeet` (Link) early-return via `ActorShadow_Suppressed()` (`z_actor.c`). A few
actors draw a bespoke shadow in their own `draw()` and are gated individually: `En_Kanban`,
`Bg_Jya_Cobra`, `En_Dekubaba`, `En_Karebaba`, `En_Heishi1`. The rest of the bespoke-shadow actors
(Wallmaster drop telegraph — gameplay-critical, bosses, horse, …) intentionally keep theirs. To
suppress another, gate its shadow draw behind the same two CVars (grep `gCircleShadowDL` under
`soh/src/overlays/actors/`).

## Shadow & light receivers (walkable floor actors)

Some surfaces the player walks on are actors, not room geometry — the Castle-Town drawbridge
(`Bg_Spot00_Hanebasi`), the Gerudo Valley bridge (`Bg_Spot09_Obj`), several dungeon platforms
(`Bg_Mori_Bigst`, `Bg_Haka_Meganebg`, `Bg_Menkuri_Kaiten`, the Shadow-Temple `Bg_Haka_Gate` floor
and statue variants). Actors draw after the shadow/light flushes, so these floors would catch
neither shadows nor light pools.

Fix: a **receiver pre-pass**. `func_800315AC` draws a curated whitelist of these floor actors first
— before the light-pool and shadow flushes — so their geometry is in the depth buffer and both
effects land on them; the main loop then skips them so each draws once. The per-actor loop body is
factored into `Actor_DrawListEntry` so the pre-pass and the main loop share one cull/lens/draw path.

- Whitelist: `ToonShadowReceiver` in `ToonLighting.cpp`, exposed to C as
  `ToonLighting_IsShadowReceiver` (`ToonLighting.h`). `Bg_Haka_Gate` is additionally gated by its
  params low byte (only the walkable floor/statue variants).
- Receivers are also in `ToonShadowExcluded`, so a floor never casts its own silhouette.
- Always on with the feature (the old `ReceiverActors` toggle is gone — its CVar is ignored).
- Watch moving platforms: the capture lags one frame, so a fast-moving receiver shows the shadow
  trailing during motion (`Bg_Menkuri_Kaiten` is the test case).

## Data flow (one frame)

1. **Arm.** `HandleActorDraw` (`ToonLighting.cpp`, `OnActorDraw` hook) emits `gSPToonKey` (cel
   behaviour, deduped), then — if shadows are on and the actor qualifies — emits
   `gSPToonShadowArm(feetClamp, easedSize)` into `POLY_OPA` only. A disqualified actor emits
   `gSPToonShadow(0,0,0,0)` instead, which disarms capture but still marks the object boundary so
   the previous actor's capture can't leak.
2. **Renderer captures + defers.** `gfx_set_toon_shadow_handler_custom` flushes the previous
   object's volume (`FlushToonShadow`), snapshots `toon_shadow_dir` from `toon_key_dir` (the next
   object overwrites the live key before this object's deferred flush), stores the size/feet-clamp,
   and sets `mRdp->toon_shadow`. The actor's geometry then streams through capture.
3. **Flush sentinel.** The `gSPToonShadowFlush` command in the actor loop triggers
   `RenderShadowVolumes` — the batched stencil passes + composite above.
4. **Per frame,** `OnToonFrameUpdate` pushes the look tuning via
   `SetToonShadowParams(opacity, minElevation, slabDepth, slabRise, showVolume)`.

## Where the code lives

### SoH (game-side policy)

- `soh/soh/Enhancements/Graphics/ToonLighting.cpp` — shared with cel shading: the shadow arm block
  in `HandleActorDraw`, `ToonShadowExcluded` / `ToonShadowReceiver` / `ToonShadowDeepRooted`, the
  eased `shadowScale` in `ToonKeyState`, the params push in `OnToonFrameUpdate`.
  `RegisterToonLighting` runs the hooks while cel shading OR shadows is enabled.
- `soh/src/code/z_actor.c` — `ActorShadow_Suppressed()` + the early-return guards; the receiver
  pre-pass, `Actor_DrawListEntry`, and the `gSPToonShadowFlush` emit in `func_800315AC`.
- Bespoke-shadow overlays (gated on `Enabled && SuppressVanillaShadows`):
  `ovl_En_Kanban`, `ovl_Bg_Jya_Cobra`, `ovl_En_Dekubaba`, `ovl_En_Karebaba`, `ovl_En_Heishi1`.
- GUI: `soh/soh/SohGui/SohMenuWindWakerStyle.cpp`, page **Wind Waker Style → Actor Shadows**.

### libultraship (renderer transport)

- GBI: `include/libultraship/libultra/gbi.h` — `G_SETTOONSHADOW 0x4b`, the
  `gSPToonShadow`/`gSPToonShadowArm`/`gSPToonShadowFlush` macros. `include/fast/lus_gbi.h` —
  `OTR_G_SETTOONSHADOW`.
- `src/fast/interpreter.cpp` — `gfx_set_toon_shadow_handler_custom`, the capture in
  `GfxSpVertex`/`GfxSpTri1`, `FlushToonShadow` (build + accumulate), `RenderShadowVolumes`
  (batched render), the bracket-edge flush in `gfx_set_toon_handler_custom`.
- `include/fast/interpreter.h` — `LoadedVertex.wx/wy/wz`, `RSP.toon_shadow_*`, `RDP.toon_shadow`,
  `mShadowVerts` / `mShadowVolumeAccum` / `mShadowXform`, `SetToonShadowParams`.
- Stencil: `StencilMode::VolumeIncrDecr` (two-sided single pass, all three backends) plus light
  casting's `Composite`; plus the per-frame stencil clear in `gfx_opengl.cpp` / `gfx_direct3d11.cpp`
  `ClearFramebuffer` (Metal clears via `LoadActionClear`).

No shader/asset changes — no `soh.o2r` regen.

## CVars

`gEnhancements.Graphics.WorldShadows.*`. Slider defaults live in the GUI AND as `kDefault*` in
`ToonLighting.cpp` — keep in sync.

| CVar | Default | Meaning |
|---|---|---|
| `Enabled` | **0** | Master toggle (also un-gates the shared `OnActorDraw` hook). |
| `SuppressVanillaShadows` | 1 | Hide the vanilla feet/circle/horse/sign/cobra shadows. |
| `Opacity` | 0.2 | Shadow darkness. |
| `EdgeSoftness` | 0 | Penumbra rings around the silhouette (0 = hard edge, max 2). New key on purpose — the removed multi-tap `Softness` float must not leak stale values into it. |
| `Length` | 0.2 | → `minElevation = 0.95 − Length·0.85`; higher lets a low light stretch the shadow. |
| `SlabDepth` | 8 | How far below the feet the slab reaches (downhill ground, cliff spill). |
| `SlabRise` | 8 | How far above the feet the slab reaches (uphill ground; too high catches the actor's legs). |
| `MaxDistance` | 550 | Camera-forward distance past which an actor's shadow is culled. |
| `gDeveloperTools.WorldShadows.ShowVolume` | 0 | Draw the volumes translucently (black caps, blue walls). |

## Invariants & gotchas

- **Emit `gSPToonShadowArm` after `gSPToonKey`, into `POLY_OPA` only.** The handler snapshots the
  key at arm time; POLY_OPA keeps translucent effects from casting.
- **The direction is a snapshot, not the live `toon_key_dir`** — the next object overwrites the live
  key before this object's deferred flush.
- **Every non-excluded actor emits an arm or a disarm** so the object boundary is always marked;
  otherwise one actor's captured geometry leaks into the next actor's volume.
- **Capture is gated on `toon_shadow`, not `toon`** — the decoupling that lets shadows run with cel
  shading off. The world-pos capture in `GfxSpVertex` is gated on `toon || toon_shadow`.
- **The volume geometry must not be re-captured**: `RenderShadowVolumes` clears
  `mRdp->toon_shadow` while it replays the volumes through the draw path.
- **The per-frame stencil clear is required** — the z-fail masks assume stencil starts at 0, and
  the composite only self-clears pixels it actually draws.
- **Keep the clamping stencil ops** (`GL_INCR`, Metal `IncrementClamp`, D3D11 `INCR_SAT`). Wrap ops
  look tempting for dense overlap, but clamp-at-0 is what absorbs stray rim pixels where a front
  face rasterizes a pixel its back face missed — with wrap those underflow to 255 and sparkle. The
  grid path keeps overlap counts small so clamping never saturates.
- **Feet level comes from the captured geometry** (lowest vertex), not the collision floor — the
  collision floor is unreliable for this (`floorHeight` can belong to a different surface than the
  visible feet). The deep-rooted clamp only ever lifts it.
- **One frame of lag is by design.** Rendering the volumes mid-frame (no lag) would put actors in
  the depth buffer → self-shadowing.
- Stencil shadow volumes extruded from the *unprojected* mesh (classic Carmack volumes) were tried
  and abandoned for OoT actors — non-watertight meshes leak, self-shadow, and double-shadow at
  ledges. The slab-of-projected-silhouette approach is what works; don't retry the classic form.

## Build & test (macOS)

Build per [`README.md`](./README.md#build--test-macos) (renderer + soh; no `GenerateSohOtr`).
Enable **Wind Waker Style → Actor Shadows**. Checks:

- Link casts a shape shadow that wraps onto slopes and steps.
- Orbit a torch / change time of day → the shadow direction swings with the cel key.
- Walk off a ledge → the shadow fades out (floor gate) instead of smearing; climb a ladder → fades.
- Deep-rooted check: signposts still cast (feet clamp).
- The drawbridge / Gerudo bridge catch shadows (receivers), and cast none themselves.
- Doors, trees, grass tufts cast none (blacklist); Wallmaster telegraph unchanged.
- Show Shadow Volume (dev tools) to inspect the slabs; Slab Depth/Rise visibly change their extent.
- Disable Cel Shading but keep Actor Shadows → shadows still render (decoupling).
