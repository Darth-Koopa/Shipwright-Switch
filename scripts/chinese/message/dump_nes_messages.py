#!/usr/bin/env python3
"""
Dump the binary file ntsc_nes_message_data_static into a human-readable format.

The binary file is an OTR resource with format defined by:

  1. ResourceFactoryBinaryTextV0::ReadResource  (TextFactory.cpp:8-31)
     - Reads: uint32 msgCount, then per-message: uint16 id, uint8 type,
       uint8 yPos, string msg

  2. BinaryReader::ReadString                    (BinaryReader.cpp:178-185)
     - Reads: int32 length prefix, then that many bytes

The file has a 0x40-byte OTR resource header before the factory data.

Usage:
    uv run message/dump_nes_messages.py
"""

import struct
from pathlib import Path


def read_message_table(filepath: str) -> list[dict]:
    """Parse the OTR binary message file.

    Returns a list of dicts with keys: id, textboxType, textboxYPos, msg
    """
    with open(filepath, "rb") as f:
        data = f.read()

    # OTR resource file header is 0x40 bytes.
    # Verified from the hex dump: "TXTO" magic at offset 0x04,
    # followed by resource metadata, padded to 0x40.
    HEADER_SIZE = 0x40

    if len(data) < HEADER_SIZE + 4:
        raise ValueError(f"File too small: {len(data)} bytes")

    offset = HEADER_SIZE

    # --- uint32 msgCount (little-endian) ---
    msg_count = struct.unpack_from("<I", data, offset)[0]
    offset += 4

    print(f"Message count: {msg_count}")

    messages = []
    for _ in range(msg_count):
        if offset + 8 > len(data):
            print(f"Warning: truncated at message {len(messages)}")
            break

        # --- uint16 id (LE) ---
        text_id = struct.unpack_from("<H", data, offset)[0]
        offset += 2

        # --- uint8 textboxType ---
        textbox_type = data[offset]
        offset += 1

        # --- uint8 textboxYPos ---
        textbox_ypos = data[offset]
        offset += 1

        # --- int32 msgLength (LE) ---  (ReadString's length prefix)
        msg_len = struct.unpack_from("<i", data, offset)[0]
        offset += 4

        if msg_len < 0 or offset + msg_len > len(data):
            print(f"Warning: bad msg_len={msg_len} at textId=0x{text_id:04X}")
            break

        # --- message bytes ---
        msg_bytes = data[offset : offset + msg_len]
        offset += msg_len

        messages.append({
            "id": text_id,
            "textboxType": textbox_type,
            "textboxYPos": textbox_ypos,
            "msg": msg_bytes,
        })

    print(f"Parsed {len(messages)} messages, last at offset 0x{offset:X}")
    return messages


def format_msg_bytes(msg_bytes: bytes) -> str:
    """Format raw message bytes as hex literal, 16 values per line."""
    parts = [f"0x{b:02X}" for b in msg_bytes]
    # Join with ", " — let the caller handle line wrapping
    return ", ".join(parts)


def write_typepos(messages: list[dict], output_path: str):
    """Write textId → typePos mapping.

    typePos = (textboxType << 4) | textboxYPos, stored as a single byte.
    Format: 0x0001 = 0x23;
    """
    with open(output_path, "w", encoding="utf-8") as f:
        for m in messages:
            typepos = (m["textboxType"] << 4) | m["textboxYPos"]
            f.write(f"0x{m['id']:04X} = 0x{typepos:02X};\n")
    print(f"Wrote {len(messages)} typePos entries to {output_path}")


def write_output(messages: list[dict], output_path: str):
    """Write messages in the format: 0x0001 = { 0x..., 0x..., ... };"""
    with open(output_path, "w", encoding="utf-8") as f:
        for m in messages:
            hex_str = format_msg_bytes(m["msg"])
            f.write(f"0x{m['id']:04X} = {{ {hex_str} }};\n")
    print(f"Wrote {len(messages)} messages to {output_path}")


def main():
    here = Path(__file__).resolve().parent
    input_file = here / "raw" / "ntsc_nes_message_data_static"
    output_file = here / "txt" / "message_raw_ntsc.txt"
    typepos_file = here / "txt" / "message_raw_typepos.txt"

    messages = read_message_table(str(input_file))
    write_output(messages, str(output_file))
    write_typepos(messages, str(typepos_file))

    # Print a few examples
    print("\n--- Sample entries ---")
    for m in messages[:5]:
        preview = m["msg"][:60]
        # Show printable ASCII, escape the rest
        text_preview = "".join(
            chr(b) if 0x20 <= b < 0x7F else f"\\x{b:02X}"
            for b in preview
        )
        print(
            f"  0x{m['id']:04X}  type={m['textboxType']} y={m['textboxYPos']} "
            f"len={len(m['msg']):4d}  '{text_preview}...'"
        )


if __name__ == "__main__":
    main()
