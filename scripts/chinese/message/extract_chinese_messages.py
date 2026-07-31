#!/usr/bin/env python3
"""
Extract Chinese messages from z_message_CHI.cpp to OTR-compatible binary format.
Output: assets/custom/text/chi_message_data_static/chi_message_data_static
"""

import re
import os
import struct
import sys
from pathlib import Path

def parse_cpp_file(cpp_path):
    """解析 z_message_CHI.cpp，返回消息列表 [(id, typePos, msg_bytes, msg_len), ...]"""
    with open(cpp_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 1. 提取所有消息数据块
    data_blocks = {}
    # 匹配: static const u8 sCHIMsgData_0x0001[] = { 0x1A, 0x13, ... };
    pattern = r'static const u8 (sCHIMsgData_0x[0-9A-F]+)\[\] = \{\s*([^}]+)\s*\};'
    for match in re.finditer(pattern, content):
        name = match.group(1)
        hex_str = match.group(2)
        # 提取所有 0xXX 字节
        bytes_list = re.findall(r'0x([0-9A-F]{2})', hex_str)
        data = bytes(int(b, 16) for b in bytes_list)
        data_blocks[name] = data

    # 2. 提取消息表条目
    messages = []
    # 匹配: { 0x0001, 0x23, (const char*)sCHIMsgData_0x0001, 84 },
    table_pattern = r'\{\s*0x([0-9A-F]+),\s*0x([0-9A-F]+),\s*\(const char\*\)(sCHIMsgData_0x[0-9A-F]+),\s*(\d+)\s*\}'
    for match in re.finditer(table_pattern, content):
        text_id = int(match.group(1), 16)
        type_pos = int(match.group(2), 16)
        data_name = match.group(3)
        msg_len = int(match.group(4))
        if data_name in data_blocks:
            msg_data = data_blocks[data_name]
            # 确保长度匹配
            if len(msg_data) != msg_len:
                print(f"Warning: {data_name} length mismatch: {len(msg_data)} != {msg_len}")
            messages.append((text_id, type_pos, msg_data, msg_len))
        else:
            print(f"Warning: data block {data_name} not found for textId 0x{text_id:04X}")

    # 按 textId 排序（通常已排序，但保序）
    messages.sort(key=lambda x: x[0])
    return messages

def write_binary(messages, output_path):
    """写入二进制文件：文件头 + 消息数量(uint32) + 每个消息条目：
       id(uint16), textboxType(uint8), textboxYPos(uint8), 字符串长度(uint32), 字符串数据
    """
    # 定义文件头
    header = bytes([
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0x54, 0x58, 0x54, 0x4F,  # TXTO
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0xEF, 0xBE, 0xAD, 0xDE,  # EF BE AD DE
        0xEF, 0xBE, 0xAD, 0xDE,  # EF BE AD DE
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
        0x00, 0x00, 0x00, 0x00,  # 00 00 00 00
    ])
    
    with open(output_path, 'wb') as f:
        # 写入文件头
        f.write(header)
        
        # 写入消息数量
        f.write(struct.pack('<I', len(messages)))
        
        # 写入每条消息
        for (text_id, type_pos, msg_data, msg_len) in messages:
            textbox_type = (type_pos >> 4) & 0xF
            textbox_ypos = type_pos & 0xF
            f.write(struct.pack('<H', text_id))
            f.write(struct.pack('<B', textbox_type))
            f.write(struct.pack('<B', textbox_ypos))
            f.write(struct.pack('<I', msg_len))
            f.write(msg_data)

def main():
    HERE = Path(__file__).resolve().parent           # scripts/chinese/message/
    REPO = HERE.parent.parent.parent                 # Shipwright-CN/
    cpp_path = REPO / "soh" / "soh" / "z_message_CHI.cpp"
    output_dir = REPO / "soh" / "assets" / "custom" / "text" / "chi_message_data_static"
    output_file = os.path.join(output_dir, 'chi_message_data_static')
    
    if not os.path.exists(cpp_path):
        print(f"Error: {cpp_path} not found", file=sys.stderr)
        sys.exit(1)
    
    os.makedirs(output_dir, exist_ok=True)
    messages = parse_cpp_file(cpp_path)
    write_binary(messages, output_file)
    print(f"Extracted {len(messages)} Chinese messages to {output_file}")

if __name__ == '__main__':
    main()