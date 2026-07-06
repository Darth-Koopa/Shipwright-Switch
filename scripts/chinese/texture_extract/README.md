# Chinese Texture Extraction

Extracts Chinese-language texture PNGs from the iQue (CN) version ROM.

## Directory Layout

```
scripts/chinese/texture_extract/
├── extract.py            ← extraction script
├── xml/                  ← texture XML definitions (one <File> per ROM file)
│   ├── boss_title_cards.xml
│   ├── do_action_static.xml
│   ├── item_name_static.xml
│   ├── map_name_static.xml
│   └── place_title_cards.xml
└── raw/                  ← decompressed binary files dumped from ROM (*.bin)
```

Output goes to `soh/assets/custom/textures/` — one folder per `<File>`, one PNG per `<Texture>`.

## Prerequisites: Dumping Binary Files from ROM

This script does **not** read the ROM directly. You must first dump the required files from an iQue ROM using [Z64Utils](https://github.com/zeldaret/Z64Utils).

### Steps

1. Download or build **Z64Utils** from https://github.com/zeldaret/Z64Utils

2. Open Z64Utils and load the iQue ROM (`oot_ique.z64`)

3. ROM -> ExportFS to get required .bin files, copy the following files (matching the `<File Name="...">` attributes in each XML) to `raw/` directory.

   | XML | ROM Files Needed |
   |---|---|
   | `boss_title_cards.xml` | `object_bv`, `object_fd`, `object_fhg`, `object_ganon`, `object_ganon2`, `object_goma`, `object_kingdodongo`, `object_mo`, `object_sst`, `object_tw` |
   | `do_action_static.xml` | `do_action_static` |
   | `item_name_static.xml` | `item_name_static` |
   | `map_name_static.xml` | `map_name_static` |
   | `place_title_cards.xml` | `g_pn_01` through `g_pn_57` |

## Running the Extraction

```bash
# From the project root
uv run texture_extract/extract.py
```

The script will:
1. Parse all texture definitions from `xml/`
2. Match each `<File>` to `raw/<File>.bin` and read the raw data
3. Decode N64 texture formats (`i8` / `ia4` / `ia8` etc.) to RGBA
4. Write PNGs to `soh/assets/custom/textures/<File>/<TextureName>.<Format>.png`

## Supported Texture Formats

| Format | Bits/pixel | Channel layout | Bytes/pixel |
|--------|-----------|----------------|-------------|
| `i4` | 4 | 4-bit intensity | 0.5 |
| `i8` | 8 | 8-bit intensity | 1 |
| `ia4` | 4 | 3-bit I + 1-bit A | 0.5 |
| `ia8` | 8 | 4-bit I + 4-bit A | 1 |
| `ia16` | 16 | 8-bit I + 8-bit A | 2 |
| `rgba16` | 16 | RGBA5551 | 2 |
| `rgba32` | 32 | RGBA8888 | 4 |

Format names follow ZAPD convention (total bits per pixel, not per channel).
