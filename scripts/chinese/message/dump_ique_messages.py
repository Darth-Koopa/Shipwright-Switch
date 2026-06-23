#!/usr/bin/env python3
"""
Dump iQue ROM message data from a raw binary segment.

Unlike the OTR-packed NTSC format (which has a 0x40-byte header + msgCount +
per-message {id, type, ypos, len, data}), the iQue extracted binary is just
the raw message body bytes concatenated together, separated by 0x02 (MESSAGE_END)
and null-padding.

The tricky part: 0x02 can also appear as the low byte of a 2-byte Chinese
character (e.g. 0xA1 0x02).  We must parse the data byte-by-byte, correctly
skipping 2-byte CJK sequences, to identify the true MESSAGE_END markers.

Usage:
    uv run message/dump_ique_messages.py
"""

import re
import struct
from pathlib import Path

# ---------------------------------------------------------------------------
# Control code parameter counts (same as NES message format)
# ---------------------------------------------------------------------------
CTRL_PARAMS = {
    0x01: 0, 0x02: 0, 0x04: 0, 0x05: 1, 0x06: 1,
    0x07: 2, 0x08: 0, 0x09: 0, 0x0A: 0, 0x0B: 0,
    0x0C: 1, 0x0D: 0, 0x0E: 1, 0x0F: 0, 0x10: 0,
    0x11: 2, 0x12: 2, 0x13: 1, 0x14: 1, 0x15: 3,
    0x16: 0, 0x17: 0, 0x18: 0, 0x19: 0, 0x1A: 0,
    0x1B: 0, 0x1C: 0, 0x1D: 0, 0x1E: 1, 0x1F: 0,
}

# Any byte >= 0xA0 in iQue encoding is the high byte of a 2-byte CJK character
def _is_cjk_high(b: int) -> bool:
    return b >= 0xA0


def split_ique_messages(data: bytes) -> list[bytes]:
    """Split raw iQue message data into individual message byte arrays.

    Walks through bytes, correctly handling:
    - 2-byte CJK sequences (>= 0xA0 prefix)
    - Control codes with their parameters
    - 0x02 as MESSAGE_END marker (only when standalone, not inside CJK)
    - Null bytes (0x00) as inter-message padding

    Returns a list of bytearrays, one per message, excluding the trailing
    0x02 and inter-message null padding.
    """
    messages = []
    current = bytearray()
    i = 0
    n = len(data)

    while i < n:
        b = data[i]

        # Null bytes between messages (padding) — skip
        if b == 0x00 and len(current) == 0:
            i += 1
            continue
        if b == 0x00 and len(current) > 0:
            # Null inside a message? Unlikely. Treat as padding before next message
            # but only if we just ended one.
            i += 1
            continue

        # 2-byte CJK character: consume both bytes together
        if _is_cjk_high(b) and i + 1 < n:
            current.append(b)
            current.append(data[i + 1])
            i += 2
            continue

        # MESSAGE_END — split point
        if b == 0x02:
            current.append(b)
            if len(current) > 0:
                messages.append(bytes(current))
            current = bytearray()
            i += 1
            continue

        # Control code — consume it plus its parameters
        if b in CTRL_PARAMS:
            nparams = CTRL_PARAMS[b]
            current.append(b)
            i += 1
            for _ in range(nparams):
                if i < n:
                    current.append(data[i])
                    i += 1
            continue

        # Regular byte (ASCII char, extended Latin, etc.)
        current.append(b)
        i += 1

    # Don't forget the last message if there's no trailing 0x02
    if len(current) > 0:
        # Trim trailing nulls
        while current and current[-1] == 0x00:
            current.pop()
        if current:
            messages.append(bytes(current))

    return messages


# ---------------------------------------------------------------------------
# Known iQue ROM typos → correct character byte substitutions
# Each entry: (high, low) → (correct_high, correct_low)
# These are confirmed against the OOT CN text dump.
# ---------------------------------------------------------------------------
CORRECTIONS: dict[tuple[int, int], tuple[int, int]] = {
    (0xA1, 0x2E): (0xAB, 0xF8),  # 蠃→赢  ("win", not "wasp")
    (0xA5, 0xDA): (0xAC, 0x47),  # 噓→嘘
    (0xA6, 0x05): (0xAB, 0x76),  # 亳→毫
    (0xA6, 0x21): (0xAB, 0x78),  # 汊→汉
    (0xA7, 0x5B): (0xAC, 0x48),  # 寃→冤
}


def apply_corrections(messages: list[bytes]) -> list[bytes]:
    """Apply known byte-level typo corrections to iQue messages.

    Only matches corrections at valid CJK character boundaries:
    a correction pair (hi, lo) must appear as a complete 2-byte CJK
    sequence (hi >= 0xA0). This avoids false matches where the lo
    byte happens to equal a following control code or ASCII byte.
    """
    corrected = []
    changed = 0
    for msg in messages:
        new_msg = bytearray(msg)
        i = 0
        while i < len(new_msg) - 1:
            b = new_msg[i]
            # CJK 2-byte sequence: check if it matches a correction
            if _is_cjk_high(b):
                key = (b, new_msg[i + 1])
                if key in CORRECTIONS:
                    new_hi, new_lo = CORRECTIONS[key]
                    new_msg[i] = new_hi
                    new_msg[i + 1] = new_lo
                    changed += 1
                i += 2
                continue
            # Control code: skip with params
            if b in CTRL_PARAMS:
                nparams = CTRL_PARAMS[b]
                i += 1 + nparams
                continue
            # Regular byte: skip
            i += 1
        corrected.append(bytes(new_msg))
    if changed:
        print(f"Applied {changed} typo correction(s)")
    return corrected


def load_ntsc_text_ids(ntsc_raw_path: str) -> list[int]:
    """Extract textIds from message_raw_ntsc.txt in order.

    Returns the ordered list of textIds as they appear in the NTSC raw file.
    """
    text_ids = []
    with open(ntsc_raw_path, "r", encoding="utf-8") as f:
        for m in re.finditer(r"0x([0-9A-Fa-f]{4})\s*=\s*\{", f.read()):
            text_ids.append(int(m.group(1), 16))
    return text_ids


def format_msg_bytes(msg_bytes: bytes) -> str:
    """Format raw message bytes as hex literal."""
    parts = [f"0x{b:02X}" for b in msg_bytes]
    return ", ".join(parts)


def write_output(messages: list[bytes], text_ids: list[int] | None, output_path: str):
    """Write messages in the format: 0x0001 = { 0x..., 0x..., ... };

    If `text_ids` is provided, use its values (aligned by position).
    Otherwise use sequential numbering starting at 0x0001.
    """
    with open(output_path, "w", encoding="utf-8") as f:
        for idx, msg in enumerate(messages):
            if text_ids and idx < len(text_ids):
                text_id = text_ids[idx]
            else:
                text_id = idx + 1  # fallback: sequential
            hex_str = format_msg_bytes(msg)
            f.write(f"0x{text_id:04X} = {{ {hex_str} }};\n")
    print(f"Wrote {len(messages)} messages to {output_path}")


def main():
    here = Path(__file__).resolve().parent
    input_file = here / "raw" / "cn_message_data_static.bin"
    output_file = here / "txt" / "message_raw_cn_from_ique.txt"
    ntsc_ref = here / "txt" / "message_raw_ntsc.txt"

    with open(input_file, "rb") as f:
        data = f.read()
    print(f"Read {len(data)} bytes from {input_file}")

    messages = split_ique_messages(data)
    print(f"Split into {len(messages)} messages")

    # Apply known typo corrections
    messages = apply_corrections(messages)

    # Load NTSC textId ordering
    text_ids = None
    if ntsc_ref.exists():
        text_ids = load_ntsc_text_ids(str(ntsc_ref))
        print(f"Loaded {len(text_ids)} textIds from NTSC reference: {ntsc_ref}")
        if len(messages) <= len(text_ids):
            print(f"  iQue messages ({len(messages)}) <= NTSC messages ({len(text_ids)}), mapping OK")
        else:
            print(f"  WARNING: iQue has MORE messages than NTSC! Some will use fallback IDs")

    write_output(messages, text_ids, str(output_file))

    # Print a few samples
    print("\n--- Sample entries ---")
    for idx in range(min(5, len(messages))):
        msg = messages[idx]
        tid = text_ids[idx] if text_ids and idx < len(text_ids) else idx + 1
        preview_bytes = msg[:30]
        hex_preview = " ".join(f"{b:02X}" for b in preview_bytes)
        print(f"  0x{tid:04X}  len={len(msg):4d}  {hex_preview}...")

    # Verify first and last end with 0x02
    for idx in [0, 1, len(messages) - 1]:
        if idx < len(messages):
            msg = messages[idx]
            tid = text_ids[idx] if text_ids and idx < len(text_ids) else idx + 1
            ends_with_02 = msg[-1] == 0x02 if msg else False
            print(f"  0x{tid:04X} ends_with_02={ends_with_02}")


if __name__ == "__main__":
    main()
