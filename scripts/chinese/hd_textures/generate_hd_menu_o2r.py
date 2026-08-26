#!/usr/bin/env python3
"""Generate chinese_menu_hd.o2r — HD texture mod for Chinese UI textures.

Reads HD PNGs from scripts/chinese/hd_textures/:
  - textures/      → 菜单字体 (CHI 后缀，支持 ia4/ia8/i8/ia16/rgba32/i4)
  - objects/       → 对象纹理 (如标题 logo，同上)
  - overlays/      → 覆盖层纹理 (新增，支持全部格式)

Each HD PNG must have a corresponding custom (non-HD) texture in
soh/assets/custom/<textures|objects|overlays>/<folder>/ to determine origin size.

Usage:
    uv run hd_textures/generate_hd_menu_o2r.py
"""

from __future__ import annotations

import struct
import sys
import zipfile
from pathlib import Path

try:
    from PIL import Image
    HAS_PIL = True
except ImportError:
    HAS_PIL = False

# Paths
HERE = Path(__file__).resolve().parent                 # scripts/chinese/hd_textures/
REPO = HERE.parent.parent.parent                       # Shipwright-CN/
CUSTOM_DIR = REPO / "soh" / "assets" / "custom" / "textures"
CUSTOM_OBJ_DIR = REPO / "soh" / "assets" / "custom" / "objects"
CUSTOM_OVERLAY_DIR = REPO / "soh" / "assets" / "custom" / "overlays"

HD_DIR = HERE / "textures"                            # HD PNGs for menu fonts
HD_OBJ_DIR = HERE / "objects"                         # HD PNGs for object textures
HD_OVERLAY_DIR = HERE / "overlays"                    # HD PNGs for overlay textures

OUT_O2R = REPO / "chinese_menu_hd.o2r"

# OTR binary format constants
OTR_HEADER_SIZE = 0x40
RESOURCE_TYPE_TEXTURE = 0x4F544558
TEX_FLAG_LOAD_AS_RAW = 1

# Texture type constants (Safe values: any number except 3 or 4 works)
RGBA32 = 1
I4     = 10   # 4-bit intensity (grayscale) – non-CI, safe
I8     = 5    # 8-bit intensity
IA4    = 6    # 4-bit intensity+alpha
IA8    = 7    # 8-bit intensity+alpha
IA16   = 9    # 16-bit intensity+alpha

def tex_type_from_png_name(png_name: str) -> int:
    """Return the texture type based on the PNG format suffix."""
    if ".rgba32." in png_name:
        return RGBA32
    if ".ia16." in png_name:
        return IA16
    if ".ia8." in png_name:
        return IA8
    if ".ia4." in png_name:
        return IA4
    if ".i8." in png_name:
        return I8
    if ".i4." in png_name:
        return I4
    return IA4   # fallback

def orig_bytes_per_row(orig_w: int, tex_type: int) -> float:
    """Original bytes per row for the given N64 texture type."""
    if tex_type == RGBA32:
        return orig_w * 4.0
    if tex_type == IA16:
        return orig_w * 2.0
    if tex_type in (IA8, I8):
        return orig_w * 1.0
    else:                       # IA4, I4 → 4bpp
        return orig_w * 0.5

# Allowed formats for each category (now includes .i4)
MENU_FORMATS = {".ia4", ".ia8", ".i8", ".ia16", ".rgba32", ".i4"}
OBJECT_FORMATS = {".ia4", ".ia8", ".i8", ".ia16", ".rgba32", ".i4"}
OVERLAY_FORMATS = {".ia4", ".ia8", ".i8", ".ia16", ".rgba32", ".i4"}

def _find_hd_png(hd_dir: Path, tex_name: str, preferred_fmt: str = "") -> Path | None:
    """Find the HD PNG for a texture. Prefers the same format suffix as the
    custom base (``<tex>.<fmt>.png``), then the bare ``<tex>.png``, then any
    ``<tex>.*.png`` present in the HD folder."""
    if preferred_fmt:
        pref = hd_dir / f"{tex_name}{preferred_fmt}.png"
        if pref.exists():
            return pref
    bare = hd_dir / f"{tex_name}.png"
    if bare.exists():
        return bare
    cands = sorted(hd_dir.glob(f"{tex_name}.*.png"))
    return cands[0] if cands else None

def _collect(custom_root: Path, hd_root: Path, prefix: str,
             formats: set[str], require_chi: bool, report_missing: bool,
             result: dict[str, list[tuple[str, Path, Path]]],
             missing: list[str], unsupported: list[str]) -> None:
    """Scan one (custom_root, hd_root) tree and append packable entries.

    ``prefix`` becomes the alt path prefix (e.g. "textures", "objects", "overlays"),
    so an entry is later packed at ``alt/<prefix>/<folder>/<tex>``.
    """
    if not custom_root.exists():
        return

    for custom_dir in sorted(custom_root.iterdir()):
        if not custom_dir.is_dir():
            continue
        folder = custom_dir.name
        hd_dir = hd_root / folder

        entries: list[tuple[str, Path, Path]] = []
        for png in sorted(custom_dir.iterdir()):
            if not png.name.endswith(".png"):
                continue
            if require_chi and "CHI" not in png.name:
                continue
            tex_name = png.name.split(".")[0]
            parts = png.name.split(".")
            fmt = "." + parts[-2].lower() if len(parts) >= 3 else ""
            if fmt not in formats:
                unsupported.append(f"  {prefix}/{folder}/{png.name} (format {fmt or '?'})")
                continue
            hd_png = _find_hd_png(hd_dir, tex_name, fmt)
            if hd_png is None:
                if report_missing:
                    missing.append(f"  {prefix}/{folder}/{tex_name}")
                continue
            entries.append((tex_name, png, hd_png))

        if entries:
            result[f"{prefix}/{folder}"] = entries

def _warn_orphan_hd(hd_root: Path, custom_root: Path, prefix: str) -> None:
    """Warn about HD PNGs that have no matching custom base (they cannot
    override anything and are silently ignored)."""
    if not hd_root.exists():
        return
    orphans: list[str] = []
    for hd_dir in sorted(hd_root.iterdir()):
        if not hd_dir.is_dir():
            continue
        custom_dir = custom_root / hd_dir.name
        for png in sorted(hd_dir.glob("*.png")):
            tex_name = png.name.split(".")[0]
            has_base = custom_dir.is_dir() and any(
                p.name.split(".")[0] == tex_name for p in custom_dir.glob("*.png")
            )
            if not has_base:
                orphans.append(f"  {prefix}/{hd_dir.name}/{png.name}")
    if orphans:
        print(f"WARNING: {len(orphans)} HD PNG(s) have no custom base texture "
              f"(cannot override — ignored):")
        for o in orphans:
            print(o)

def verify_coverage() -> dict[str, list[tuple[str, Path, Path]]]:
    """Collect every custom PNG that can be packed into the O2R.

    Scans three trees:
      * custom/textures + hd_textures/textures  → alt/textures/... (menu fonts,
        CHI-only, now supports all formats)
      * custom/objects  + hd_textures/objects   → alt/objects/...  (object
        textures, all formats allowed)
      * custom/overlays + hd_textures/overlays  → alt/overlays/... (overlay
        textures, all formats allowed)
    """
    result: dict[str, list[tuple[str, Path, Path]]] = {}
    missing: list[str] = []
    unsupported: list[str] = []

    # Menu font textures (CHI-only, report missing)
    _collect(CUSTOM_DIR, HD_DIR, "textures", MENU_FORMATS,
             require_chi=True, report_missing=True,
             result=result, missing=missing, unsupported=unsupported)

    # Object textures (no CHI requirement, optional)
    _collect(CUSTOM_OBJ_DIR, HD_OBJ_DIR, "objects", OBJECT_FORMATS,
             require_chi=False, report_missing=False,
             result=result, missing=missing, unsupported=unsupported)
    _warn_orphan_hd(HD_OBJ_DIR, CUSTOM_OBJ_DIR, "objects")

    # Overlay textures (no CHI requirement, optional)
    _collect(CUSTOM_OVERLAY_DIR, HD_OVERLAY_DIR, "overlays", OVERLAY_FORMATS,
             require_chi=False, report_missing=False,
             result=result, missing=missing, unsupported=unsupported)
    _warn_orphan_hd(HD_OVERLAY_DIR, CUSTOM_OVERLAY_DIR, "overlays")

    if missing:
        print(f"WARNING: Skipping {len(missing)} custom CHI textures with no HD PNG (art missing):")
        for m in missing:
            print(m)
    if unsupported:
        print(f"WARNING: Skipping {len(unsupported)} textures with unsupported HD format:")
        for u in unsupported:
            print(u)

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

    # Scale factors
    obpr = orig_bytes_per_row(orig_w, tex_type)
    h_byte_scale = (hd_w * 4.0) / obpr
    v_pixel_scale = float(hd_h) / orig_h

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
    print(f"  Packing {total} HD textures (others skipped — see warnings above).\n")

    print(f"Packing O2R → {OUT_O2R} ...")
    with zipfile.ZipFile(str(OUT_O2R), "w", zipfile.ZIP_DEFLATED) as zf:
        zf.writestr("portVersion", "9.2.3")

        count = 0
        for subpath, entries in entries_by_folder.items():
            for tex_name, custom_png, hd_png in entries:
                with Image.open(custom_png) as orig:
                    orig_w, orig_h = orig.size

                tex_type = tex_type_from_png_name(custom_png.name)

                with Image.open(hd_png) as hd_img:
                    hd_img = hd_img.convert("RGBA")
                    hd_w, hd_h = hd_img.size
                    rgba_data = hd_img.tobytes("raw", "RGBA")

                otr_data = build_otr_resource(rgba_data, orig_w, orig_h,
                                              hd_w, hd_h, tex_type)
                zf.writestr(f"alt/{subpath}/{tex_name}", otr_data)
                count += 1

    size_mb = OUT_O2R.stat().st_size / 1024 / 1024
    print(f"Done: {OUT_O2R} ({size_mb:.1f} MB, {count} textures)")
    print(f"Place in: mods/chinese_menu_hd.o2r")

if __name__ == "__main__":
    main()