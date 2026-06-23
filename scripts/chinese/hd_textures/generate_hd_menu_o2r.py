#!/usr/bin/env python3
"""Generate chinese_menu_hd.o2r — HD texture mod for Chinese UI textures.

Reads HD PNGs from scripts/chinese/hd_textures/ (do_action_static,
item_name_static, map_name_static) and packs them into an O2R mod file.

Each HD PNG must have a corresponding custom (non-HD) CHI texture in
soh/assets/custom/textures/<folder>/ to determine origin size.

Usage:
    uv run hd_textures/generate_hd_menu_o2r.py
"""

from __future__ import annotations

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
HERE = Path(__file__).resolve().parent             # scripts/chinese/hd_textures/
REPO = HERE.parent.parent.parent                   # Shipwright-CN/
CUSTOM_DIR = REPO / "soh" / "assets" / "custom" / "textures"
HD_DIR = HERE                                       # HD PNGs in the same directory
OUT_O2R = REPO / "chinese_menu_hd.o2r"

# OTR binary format constants
OTR_HEADER_SIZE = 0x40
RESOURCE_TYPE_TEXTURE = 0x4F544558
TEX_FLAG_LOAD_AS_RAW = 1

FOLDERS = ["do_action_static", "item_name_static", "map_name_static"]

# N64 texture types derived from the custom PNG suffix
IA4 = 6   # .ia4.png → G_IM_FMT_IA | G_IM_SIZ_4b  (4bpp)
IA8 = 7   # .ia8.png → G_IM_FMT_IA | G_IM_SIZ_8b  (8bpp)


def tex_type_from_png_name(png_name: str) -> int:
    """Return the N64 texture type based on the PNG format suffix."""
    return IA8 if ".ia8." in png_name else IA4


def orig_bytes_per_row(orig_w: int, tex_type: int) -> float:
    """Original bytes per row for the given N64 texture type."""
    if tex_type == IA8:     # 8bpp: 1 byte/pixel
        return orig_w * 1.0
    else:                   # IA4 / I4: 4bpp: 0.5 byte/pixel
        return orig_w * 0.5


def verify_coverage() -> dict[str, list[tuple[str, Path, Path]]]:
    """Check every custom CHI PNG has a matching HD PNG.  Returns per-folder
    list of (tex_name, custom_path, hd_path)."""
    result: dict[str, list[tuple[str, Path, Path]]] = {}
    missing: list[str] = []

    for folder in FOLDERS:
        custom_dir = CUSTOM_DIR / folder
        hd_dir = HD_DIR / folder
        entries: list[tuple[str, Path, Path]] = []

        if not custom_dir.exists():
            continue
        for png in sorted(custom_dir.iterdir()):
            if not png.name.endswith(".png") or "CHI" not in png.name:
                continue
            # custom: gFooCHITex.ia4.png → name: gFooCHITex
            tex_name = png.name.split(".")[0]
            hd_png = hd_dir / f"{tex_name}.png"
            if not hd_png.exists():
                missing.append(f"  {folder}/{tex_name}: HD PNG not found at {hd_png}")
            entries.append((tex_name, png, hd_png))

        if entries:
            result[folder] = entries

    if missing:
        print("ERROR: Missing HD textures:")
        for m in missing:
            print(m)
        sys.exit(1)

    return result


def build_otr_resource(rgba_data: bytes, orig_w: int, orig_h: int,
                       hd_w: int, hd_h: int, tex_type: int) -> bytes:
    """Build a complete OTR binary resource for one HD texture."""
    buf = bytearray()

    # OTR Header (64 bytes)
    buf += struct.pack("<B", 0)
    buf += struct.pack("<B", 0)
    buf += struct.pack("<BB", 0, 0)
    buf += struct.pack("<I", RESOURCE_TYPE_TEXTURE)
    buf += struct.pack("<I", 1)
    buf += struct.pack("<Q", 0xDEADBEEFDEADBEEF)
    while len(buf) < OTR_HEADER_SIZE:
        buf += struct.pack("<I", 0)

    # Scale factors — correct for the original texture format
    obpr = orig_bytes_per_row(orig_w, tex_type)
    h_byte_scale = (hd_w * 4.0) / obpr      # HD RGBA32 bytes-per-row ÷ orig bytes-per-row
    v_pixel_scale = float(hd_h) / orig_h    # HD height ÷ orig height

    # V1 Texture Data
    buf += struct.pack("<I", tex_type)
    buf += struct.pack("<I", hd_w)
    buf += struct.pack("<I", hd_h)
    buf += struct.pack("<I", TEX_FLAG_LOAD_AS_RAW)
    buf += struct.pack("<f", h_byte_scale)
    buf += struct.pack("<f", v_pixel_scale)
    buf += struct.pack("<I", len(rgba_data))
    buf += rgba_data

    return bytes(buf)


def main():
    if not HAS_PIL:
        print("Pillow not installed. Run: uv sync")
        sys.exit(1)

    print("Verifying HD texture coverage...")
    entries_by_folder = verify_coverage()
    total = sum(len(v) for v in entries_by_folder.values())
    print(f"  All {total} custom CHI textures have matching HD PNGs.\n")

    print(f"Packing O2R → {OUT_O2R} ...")
    with zipfile.ZipFile(str(OUT_O2R), "w", zipfile.ZIP_DEFLATED) as zf:
        zf.writestr("portVersion", "9.2.3")

        count = 0
        for folder, entries in entries_by_folder.items():
            for tex_name, custom_png, hd_png in entries:
                # Read original dimensions from the custom PNG
                with Image.open(custom_png) as orig:
                    orig_w, orig_h = orig.size

                # Derive texture type from the custom PNG suffix
                tex_type = tex_type_from_png_name(custom_png.name)

                # Read HD RGBA data
                with Image.open(hd_png) as hd_img:
                    hd_img = hd_img.convert("RGBA")
                    hd_w, hd_h = hd_img.size
                    rgba_data = hd_img.tobytes("raw", "RGBA")

                otr_data = build_otr_resource(rgba_data, orig_w, orig_h,
                                              hd_w, hd_h, tex_type)
                zf.writestr(f"alt/textures/{folder}/{tex_name}", otr_data)
                count += 1

    size_mb = OUT_O2R.stat().st_size / 1024 / 1024
    print(f"Done: {OUT_O2R} ({size_mb:.1f} MB, {count} textures)")
    print(f"Place in: mods/chinese_menu_hd.o2r")


if __name__ == "__main__":
    main()
