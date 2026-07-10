import re

root = r'e:\Shipwright-wind-waker-style-cel-shading\soh\soh\SohGui'

# Load existing keys from Localization.cpp
loc = open(root + r'\Localization.cpp', encoding='utf-8', errors='ignore').read()
key_set = set(m[0] for m in re.finditer(r'\{\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"', loc))

# Load extracted strings
extracted = open(r'e:\Shipwright-wind-waker-style-cel-shading\extracted_strings.txt', encoding='utf-8').read().split('\n')
extracted = [s for s in extracted if s]

def has_cjk(s):
    return any('\u4e00' <= c <= '\u9fff' for c in s)

def is_english(s):
    # must contain ascii letters and no CJK
    if has_cjk(s):
        return False
    return any('a' <= c <= 'z' or 'A' <= c <= 'Z' for c in s)

missing = []
for s in extracted:
    if is_english(s) and s not in key_set:
        missing.append(s)

print('Total extracted:', len(extracted))
print('English not in table (missing):', len(missing))
print()
for s in sorted(missing):
    print(s)
