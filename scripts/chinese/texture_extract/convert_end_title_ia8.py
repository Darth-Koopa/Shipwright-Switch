#!/usr/bin/env python3
# Convert the ovl_End_Title Chinese glyph PNGs to IA8 for use in the end-title screen.
#
# Source images (in soh/assets/custom/textures/overlays/ovl_End_Title/) are grayscale WHITE
# glyphs on transparent background: RGB = white (luminance), A = coverage/antialias mask.
#
# The end-title draw combine is (PRIMITIVE-ENVIRONMENT)*TEXEL0 + ENVIRONMENT with
# PRIM=(0,0,0) black and ENV=(255,120,30) orange. For an IA texture, TEXEL0's intensity I
# drives the color and its alpha A drives coverage. To render the glyph ORANGE (like the
# English title) the glyph intensity must be 0 (black) and the alpha must be the coverage.
# So we emit IA8 with I=0 (RGB=0) and A = source alpha. The viewer shows a black silhouette
# on transparent; in-game it is tinted orange with antialiased edges.
#
# Output: <Name>.ia8.png (RGBA PNG; ZAPD reads .ia8.png -> I=R, A=A). The original .png is
# kept as the editable source (a copy is also in end_title_src/).
import os
from PIL import Image

SRC_DIR = "soh/assets/custom/textures/overlays/ovl_End_Title"
BACKUP_DIR = "scripts/chinese/texture_extract/end_title_src"
NAMES = [
    "sTheLegendOfZeldaCHITex",
    "sOcarinaOfTimeCHITex",
    "sTheEndCHITex",
]


def main():
    for name in NAMES:
        src_path = os.path.join(SRC_DIR, name + ".png")
        if not os.path.exists(src_path):
            raise SystemExit(f"missing source: {src_path}")
        im = Image.open(src_path).convert("RGBA")
        px = im.load()
        w, h = im.size
        out = Image.new("RGBA", (w, h))
        opx = out.load()
        for y in range(h):
            for x in range(w):
                r, g, b, a = px[x, y]
                # IA8: intensity (color) = 0 (black -> orange under the combine),
                # alpha = source coverage. Preserve antialiasing via alpha.
                opx[x, y] = (0, 0, 0, a)
        out_path = os.path.join(SRC_DIR, name + ".ia8.png")
        out.save(out_path)
        # keep an editable backup of the latest source
        os.makedirs(BACKUP_DIR, exist_ok=True)
        Image.open(src_path).convert("RGBA").save(os.path.join(BACKUP_DIR, name + ".png"))
        print(f"wrote {out_path} ({w}x{h})")


if __name__ == "__main__":
    main()
