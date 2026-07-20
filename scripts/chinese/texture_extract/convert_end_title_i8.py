#!/usr/bin/env python3
"""
Convert the ovl_End_Title Chinese title-card PNGs to I8 format.

Background
----------
The CHI end-title textures (sTheEndCHITex / sTheLegendOfZeldaCHITex /
sOcarinaOfTimeCHITex) are grayscale WHITE glyphs with an alpha coverage mask
(RGB = grayscale brightness, A = coverage). A bare ".png" with no N64 format
suffix is NOT treated as a texture by ZAPD -- it is packed as a raw blob, so
loading it with gDPLoadTextureTile as IA8 produces garbage. Switching to
".i8.png" makes ZAPD recognise it as a proper I8 texture.

I8 rule: G_IM_FMT_I packs a single intensity channel that the RDP uses for
BOTH color and alpha. So white texel (I=255) -> opaque, black texel (I=0) ->
transparent. To get orange glyphs we drive the color through ENV via the
combine (TEXEL0 * ENVIRONMENT) in z_end_title.c.

Encoding choice
---------------
The source is white glyph + alpha. For a tinted (single-hue orange) glyph the
only thing that should vary is COVERAGE, so we encode the intensity from the
original alpha:  I = A.
  * core (A=255) -> I=255 -> orange, opaque
  * edge (A=128) -> I=128 -> orange, semi-transparent (AA preserved)
  * bg  (A=0)    -> I=0   -> transparent
The PNG alpha is set to the SAME intensity so the file displays as white glyph
on transparent in any image viewer (matching the original look). Note: the I8
texture ignores the PNG alpha at runtime -- only the R channel (intensity) is
used -- so this is purely cosmetic for the editor.

The source plain ".png" was already removed from the assets tree (it would
collide with the I8 texture name). Re-runs read the original from BACKUP_DIR.

Usage:
  py scripts/chinese/texture_extract/convert_end_title_i8.py
"""
import os
import shutil
from PIL import Image

SRC_DIR = "soh/assets/custom/textures/overlays/ovl_End_Title"
BACKUP_DIR = "scripts/chinese/texture_extract/end_title_src"
NAMES = [
    "sTheEndCHITex",
    "sTheLegendOfZeldaCHITex",
    "sOcarinaOfTimeCHITex",
]


def main():
    os.makedirs(BACKUP_DIR, exist_ok=True)
    for name in NAMES:
        plain = os.path.join(SRC_DIR, name + ".png")
        i8 = os.path.join(SRC_DIR, name + ".i8.png")

        # Source: prefer the plain .png in the assets tree; fall back to backup.
        src = plain if os.path.exists(plain) else os.path.join(BACKUP_DIR, name + ".png")
        if not os.path.exists(src):
            print(f"[skip] {src} not found")
            continue

        im = Image.open(src).convert("RGBA")
        px = im.load()
        w, h = im.size
        out = Image.new("RGBA", (w, h))
        opx = out.load()
        for y in range(h):
            for x in range(w):
                r, g, b, a = px[x, y]
                # Intensity = original coverage (alpha). Glyph core -> 255,
                # edges -> partial (AA), background -> 0.
                i = a
                # RGBA mode required by ZAPD's I8 reader (avoids the grayscale
                # crash); R is the intensity, A mirrors it for editor preview.
                opx[x, y] = (i, i, i, i)

        # Back up the original (raw blob) before replacing it, if present.
        if os.path.exists(plain):
            shutil.copy2(plain, os.path.join(BACKUP_DIR, name + ".png"))
            os.remove(plain)

        out.save(i8)
        print(f"[ok] wrote {i8} ({w}x{h})")


if __name__ == "__main__":
    main()
