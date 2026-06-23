#!/usr/bin/env python3
"""Generate chinese_font_hd.o2r — HD texture mod for Chinese font glyphs.

Creates an .o2r mod file with 128×128 RGBA32 HD versions of every
CharChn glyph, using the same binary format as OoT Reloaded HD pack.

All-CharChn design: every CJK glyph gets its own HD texture.
No Kanji reuse — the HD pack is self-contained.

Usage:
    uv run message/generate_hd_font_o2r.py

The generated .o2r file should be placed in the mods directory:
    mods/chinese_font_hd.o2r
"""

from __future__ import annotations

import re
import struct
import sys
import zipfile
from pathlib import Path

try:
    from PIL import Image, ImageDraw, ImageFont
    HAS_PIL = True
except ImportError:
    HAS_PIL = False

# Paths
HERE = Path(__file__).resolve().parent           # scripts/chinese/message/
REPO = HERE.parent.parent.parent                 # Shipwright-CN/
TBL_PATH = REPO / "soh" / "src" / "code" / "z_kanfont_chinese_tbl.inc"
FONT_PATH = HERE / "charmap" / "SourceHanSansSC-Regular.otf"
OUT_O2R = REPO / "chinese_font_hd.o2r"

# OTR binary format constants
OTR_HEADER_SIZE = 0x40
RESOURCE_TYPE_TEXTURE = 0x4F544558   # "OTEX" little-endian
TEXTURE_TYPE_GRAYSCALE_4BPP = 5      # I4 original format identifier
TEX_FLAG_LOAD_AS_RAW = 1

# HD texture parameters (same as sxunix's original)
HD_SIZE = 128
RENDER_SIZE = 256                    # 2× supersampling for sharper strokes
FONT_SIZE = 216                      # ~108pt × 2 for the 2× canvas
GLYPH_COLOR = (210, 210, 210, 255)  # gray210, matches OoT Reloaded kanji style

# Scale factors: original 16×16 I4 → HD 128×128 RGBA32
H_BYTE_SCALE = 64.0
V_PIXEL_SCALE = 8.0

def parse_char_entries(tbl_path: Path) -> list[tuple[str, str]]:
    """Parse z_kanfont_chinese_tbl.inc → [(tex_name, char), ...] for all
    gMsgCharChn*Tex entries that are NOT EmptyTex placeholders."""
    content = tbl_path.read_text(encoding="utf-8")
    entries: list[tuple[str, str]] = []

    # Match: gMsgCharChnXXXXTex, // ...  U+XXXX '字'
    # Exclude gMsgCharChnEmptyTex
    for m in re.finditer(
        r"^\s+(gMsgCharChn[0-9A-Fa-f]+Tex),\s*//\s*\[\d+\]\s+0x[0-9A-Fa-f]+\s+"
        r"U\+[0-9A-Fa-f]+\s+'(.+?)'",
        content,
        re.MULTILINE,
    ):
        tex_name = m.group(1)
        char = m.group(2)
        if tex_name != "gMsgCharChnEmptyTex" and len(char) == 1:
            entries.append((tex_name, char))

    return entries


# Same offsets as generate_assets.py, scaled 16× (256px render ÷ 16px I4)
_HD_Y_OFFSET: dict[str, int] = {
    "一": 32,  "，": 48,  "。": 48,  "…": 32,  "．": 48,  "、": 48,
}


def generate_rgba_image(char: str, font, size: int) -> bytes:
    """Render char at 2× resolution, LANCZOS downscale to target size.

    Returns raw RGBA bytes (size × size × 4).
    """
    img = Image.new("RGBA", (RENDER_SIZE, RENDER_SIZE), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)

    bbox = font.getbbox(char)
    char_w = bbox[2] - bbox[0]
    char_h = bbox[3] - bbox[1]
    x = (RENDER_SIZE - char_w) // 2 - bbox[0]
    y = (RENDER_SIZE - char_h) // 2 - bbox[1]
    y += _HD_Y_OFFSET.get(char, 0)

    draw.text((x, y), char, fill=GLYPH_COLOR, font=font)
    img = img.resize((size, size), Image.LANCZOS)
    return img.tobytes("raw", "RGBA")


def build_otr_resource(rgba_data: bytes) -> bytes:
    """Build a complete OTR binary resource (64-byte header + V1 texture)."""
    buf = bytearray()

    buf += struct.pack("<B", 0)       # Endianness = Little
    buf += struct.pack("<B", 0)       # IsCustom
    buf += struct.pack("<BB", 0, 0)   # unused
    buf += struct.pack("<I", RESOURCE_TYPE_TEXTURE)
    buf += struct.pack("<I", 1)       # ResourceVersion = 1 (V1)
    buf += struct.pack("<Q", 0xDEADBEEFDEADBEEF)
    while len(buf) < OTR_HEADER_SIZE:
        buf += struct.pack("<I", 0)

    buf += struct.pack("<I", TEXTURE_TYPE_GRAYSCALE_4BPP)
    buf += struct.pack("<I", HD_SIZE)
    buf += struct.pack("<I", HD_SIZE)
    buf += struct.pack("<I", TEX_FLAG_LOAD_AS_RAW)
    buf += struct.pack("<f", H_BYTE_SCALE)
    buf += struct.pack("<f", V_PIXEL_SCALE)
    buf += struct.pack("<I", len(rgba_data))
    buf += rgba_data

    return bytes(buf)


def main():
    if not HAS_PIL:
        print("Pillow not installed. Run: uv sync")
        sys.exit(1)

    if not TBL_PATH.exists():
        print(f"Table not found: {TBL_PATH}")
        sys.exit(1)
    if not FONT_PATH.exists():
        print(f"Font not found: {FONT_PATH}")
        print("  Download: https://github.com/adobe-fonts/source-han-sans/releases")
        sys.exit(1)

    entries = parse_char_entries(TBL_PATH)
    print(f"Found {len(entries)} CharChn glyph entries")

    font = ImageFont.truetype(str(FONT_PATH), FONT_SIZE)
    print(f"Generating {HD_SIZE}×{HD_SIZE} RGBA32 HD textures...")

    with zipfile.ZipFile(str(OUT_O2R), "w", zipfile.ZIP_DEFLATED) as zf:
        zf.writestr("portVersion", "9.2.3")

        for i, (tex_name, char) in enumerate(entries):
            rgba_data = generate_rgba_image(char, font, HD_SIZE)
            otr_data = build_otr_resource(rgba_data)
            zf.writestr(f"alt/textures/chinese_font/{tex_name}", otr_data)

            if (i + 1) % 200 == 0 or i == len(entries) - 1:
                print(f"  {i + 1}/{len(entries)}")

    size_mb = OUT_O2R.stat().st_size / 1024 / 1024
    print(f"Done: {OUT_O2R} ({size_mb:.1f} MB, {len(entries)} textures)")
    print(f"Place in: mods/chinese_font_hd.o2r")


if __name__ == "__main__":
    main()
