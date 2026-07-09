# Chinese Message Tools

Tools for extracting, calibrating, and fixing Chinese (iQue) message data for
Ship of Harkinian.

## File Structure

```
scripts/chinese/message/
├── README.md
├── calibrate_messages.py      # Compare NTSC / iQue / OOT dump → Excel
├── dump_ique_messages.py      # Split iQue ROM binary → message_raw_cn.txt
├── dump_nes_messages.py       # Split OTR binary → message_raw_ntsc.txt
├── pyproject.toml
├── charmap/
│   ├── charmap_chn.txt        # iQue CN: char → 2-byte code (2196 entries)
│   └── charmap_ntsc.txt       # NES: extended Latin + button icons (44 entries)
└── txt/
    ├── message_raw_ntsc.txt   # 2116 English messages (OTR-extracted)
    └── message_raw_cn_from_ique.txt  # 2115 Chinese messages (iQue ROM, corrected)
```

---

## Character Encoding Ranges

### NES / NTSC (English)

Every byte in a raw message is either a control code, a regular character,
or a button icon. No multi-byte encoding.

| Range | Content |
|-------|---------|
| `0x00` | Padding (inter-message null) |
| `0x01`–`0x1F` | Control codes (see table below) |
| `0x20`–`0x7E` | ASCII printable |
| `0x7F` | Blank glyph |
| `0x80`–`0x9E` | Extended Latin (`À`, `î`, `Â`, `Ä`, `Ç`, …) |
| `0x9F`–`0xAB` | Button icons (`(A)`, `(B)`, `(C)`, `(L)`, `(R)`, `(Z)`, `(↑)`, `(↓)`, `(←)`, `(→)`, `(▼)`, `(+)`, `(P)`) |

### iQue Chinese

Bytes `>= 0xA0` form **2-byte CJK sequences** (`high << 8 | low`).
Bytes `< 0xA0` use the same NES rules above (control codes, ASCII, buttons).

| Range | Content | Count |
|-------|---------|-------|
| `0x01`–`0x9E` | Same as NES (control codes, ASCII, extended Latin) | — |
| `0xA0`–`0xAC` prefix + any low byte | 2-byte CJK character | — |
| `0xA08C`–`0xA775` | Main iQue character set | ~1770 |
| `0xAA9F`–`0xAAAB` | Button icons (same semantics as NES `0x9F`–`0xAB`) | 13 |
| `0xAAAC`–`0xAC48` | Extended custom characters (v8) | ~411 |

---

## Control Codes

All control codes are in range `0x01`–`0x1F`. `0x03` is unused/invalid.

| Code | Name | Params | Behaviour |
|------|------|--------|-----------|
| `0x01` | NEWLINE | 0 | Line break |
| `0x02` | END | 0 | End of message; decode loop exits |
| `0x04` | BOX_BREAK | 0 | Text box page break; decode loop exits |
| `0x05` | COLOR | 1 | Next byte = color index (0–7) |
| `0x06` | SHIFT | 1 | Horizontal pixel offset |
| `0x07` | TEXTID | 2 | Chain to next message `(hi << 8) \| lo`; decode loop exits |
| `0x08` | QUICKTEXT_ENABLE | 0 | Fast-text region start |
| `0x09` | QUICKTEXT_DISABLE | 0 | Fast-text region end |
| `0x0A` | PERSISTENT | 0 | Text stays on screen |
| `0x0B` | EVENT | 0 | Trigger event; decode loop exits |
| `0x0C` | BOX_BREAK_DELAYED | 1 | Auto-advance after N frames; decode loop exits |
| `0x0D` | AWAIT_BUTTON_PRESS | 0 | Pause until player presses button |
| `0x0E` | FADE | 1 | Fade out over N frames (8-bit timer) |
| `0x0F` | NAME | 0 | Replaced with player name at runtime |
| `0x10` | OCARINA | 0 | Ocarina staff display |
| `0x11` | FADE2 | 2 | Fade out (16-bit timer) |
| `0x12` | SFX | 2 | Play sound effect `(hi << 8) \| lo` |
| `0x13` | ITEM_ICON | 1 | Draw item icon for given item ID |
| `0x14` | TEXT_SPEED | 1 | Set text display speed |
| `0x15` | BACKGROUND | 3 | Set text box background (idx, fg, bg) |
| `0x16` | MARATHON_TIME | 0 | Replaced with marathon timer value |
| `0x17` | RACE_TIME | 0 | Replaced with race timer value |
| `0x18` | POINTS | 0 | Replaced with minigame score |
| `0x19` | TOKENS | 0 | Replaced with Gold Skulltula count |
| `0x1A` | UNSKIPPABLE | 0 | Prevent player from skipping text |
| `0x1B` | TWO_CHOICE | 0 | Present 2-option choice |
| `0x1C` | THREE_CHOICE | 0 | Present 3-option choice |
| `0x1D` | FISH_INFO | 0 | Replaced with fishing record |
| `0x1E` | HIGHSCORE | 1 | Replaced with high score (indexed by param) |
| `0x1F` | TIME | 0 | Replaced with current in-game time |

> **Tip**: When comparing NTSC and CN control sequences, codes `0x01`, `0x04`, `0x05`,
> `0x06`, `0x0C`, `0x13`, and `0x1A` are intentionally ignored — they represent
> formatting/layout choices that differ between English and Chinese localizations.

---

## Scripts

### `dump_nes_messages.py`

Extracts English messages from an OTR binary resource file.

**Input:** OTR resource at `text/nes_message_data_static/ntsc_nes_message_data_static`
(from `.otr` archive).

**Binary format:**

```
OTR Resource Header (0x40 bytes):
  [0x00-0x03]  version marker
  [0x04-0x07]  "TXTO" magic
  [0x08-0x3F]  resource metadata

Factory Data:
  [4 bytes LE]  uint32 msgCount
  For each message:
    [2 bytes LE]  uint16 textId
    [1 byte]      uint8  textboxType
    [1 byte]      uint8  textboxYPos
    [4 bytes LE]  int32  msgLength   (ReadString length prefix)
    [msgLength]   message body bytes
```

**Output:** `txt/message_raw_ntsc.txt` — one message per line:
```
0x0001 = { 0x1A, 0x13, 0x2D, 0x08, 0x59, 0x6F, 0x75, ... };
```

**Relevant SoH source:** `OTRExporter/OTRExporter/TextFactory.cpp:8-31`,
`libultraship/src/ship/utils/binarytools/BinaryReader.cpp:178-185`.

---

### `dump_ique_messages.py`

Extracts Chinese messages from an iQue ROM data segment.

**Input:** Raw binary extracted from iQue ROM (`cn_message_data_static.bin`).

**Binary format:** Pure message body bytes concatenated, separated by `0x02`
(MESSAGE_END) + null padding. No headers, no table — messages are split by
parsing CJK 2-byte sequences and control codes to correctly identify MESSAGE_END
markers (avoiding false matches where `0x02` is a CJK low byte).

**Output:** `txt/message_raw_cn_from_ique.txt` — same format as the NES dump,
with textIds aligned by position to the NTSC reference.

**Features:**
- CJK-aware byte parsing (handles `0x02` inside 2-byte sequences)
- Built-in typo correction dictionary (`CORRECTIONS`) for known iQue ROM errata
- NTSC textId alignment (position-based mapping)

**Usage:**
```bash
uv run python dump_ique_messages.py [input.bin] [output.txt] [ntsc_ref.txt]
```

---

### `calibrate_messages.py`

Generates an Excel workbook comparing NTSC and CN message data side-by-side.

**Inputs:**

| File | Description |
|------|-------------|
| `txt/message_raw_ntsc.txt` | English messages |
| `txt/message_raw_cn_from_ique.txt` | Chinese messages (iQue, corrected) |
| OOT CN text dump (HTML) | Reference Chinese text |
| `charmap/charmap_ntsc.txt` | NES character mapping |
| `charmap/charmap_chn.txt` | iQue CN character mapping |

**Excel columns:**

| Col | Content |
|-----|---------|
| A: textId | Message identifier |
| B: NTSC Raw Hex | English raw bytes |
| C: NTSC Readable | English with decoded text + `[0x##]` control markers |
| D: CN Raw Hex | Chinese raw bytes |
| E: CN Readable | Chinese with decoded text + `[0x##]` control markers |
| F: N64 CN Text Dump | Reference Chinese text |
| G: Ctrl Match | Control code comparison (✓ / ✗) |
| H: Char Match | Chinese character comparison (✓ / ✗) |

**Highlighting:**
- 🔴 Red background — control code mismatch (more critical)
- 🟡 Yellow background — Chinese character mismatch
- ⬜ Gray alternating — fully matching

**Fuzzy matching:** The character comparison normalises known
word-choice differences before comparing, for example:
- `或` ↔ `和` (or / and)
- `他` ↔ `她` (he / she)

**Usage:**
```bash
uv run python calibrate_messages.py
# Output: message_calibration.xlsx
```

---

## Typical Workflow

1. Extract English messages from OTR:
   ```bash
   uv run python dump_nes_messages.py <otr_extracted_binary> txt/message_raw_ntsc.txt
   ```

2. Extract Chinese messages from iQue ROM:
   ```bash
   uv run python dump_ique_messages.py cn_message_data_static.bin \
       txt/message_raw_cn_from_ique.txt txt/message_raw_ntsc.txt
   ```

3. Run calibration:
   ```bash
   uv run python calibrate_messages.py
   ```

4. Open `message_calibration.xlsx`, review red (control code) and yellow
   (character) mismatches. For systematic iQue typos, add entries to the
   `CORRECTIONS` dictionary in `dump_ique_messages.py` and re-run steps 2–3.

## Dependencies

```toml
[project]
dependencies = [
    "openpyxl>=3.1.0",
]
```
