import re, os, glob

root = r'e:\Shipwright-wind-waker-style-cel-shading\soh\soh\SohGui'

# 1) load existing translation keys from Localization.cpp
loc = open(os.path.join(root, 'Localization.cpp'), encoding='utf-8', errors='ignore').read()
keys = set()
for m in re.finditer(r'\{\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"', loc):
    keys.add(m.group(1))

# 2) find every string passed to StringHelper::Translate (already wrapped)
wrapped = set()
for f in glob.glob(os.path.join(root, '*.cpp')) + glob.glob(os.path.join(root, '*.h')) + glob.glob(os.path.join(root, '*.hpp')):
    src = open(f, encoding='utf-8', errors='ignore').read()
    for m in re.finditer(r'StringHelper::Translate\(\s*"((?:[^"\\]|\\.)*)"', src):
        wrapped.add(m.group(1))

# 3) patterns for UI strings (from extract_strings.py) - first segment of each literal
patterns = [
    r'AddWidget\(\s*[\w.]+\s*,\s*"((?:[^"\\]|\\.)*)"',
    r'AddMenuEntry\(\s*"((?:[^"\\]|\\.)*)"',
    r'AddSidebarEntry\(\s*[^,]+,\s*"((?:[^"\\]|\\.)*)"',
    r'\.Tooltip\(\s*"((?:[^"\\]|\\.)*)"',
    r'SeparatorText\(\s*"((?:[^"\\]|\\.)*)"',
    r'RegisterPopup\(\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"',
    r'\.tooltip\s*=\s*"((?:[^"\\]|\\.)*)"',
]

ui_strings = set()
combos = set()
for f in glob.glob(os.path.join(root, '*.cpp')) + glob.glob(os.path.join(root, '*.h')) + glob.glob(os.path.join(root, '*.hpp')):
    src = open(f, encoding='utf-8', errors='ignore').read()
    for p in patterns:
        for m in re.finditer(p, src, re.S):
            for i in range(1, (m.lastindex or 0) + 1):
                s = m.group(i)
                if s:
                    ui_strings.add(s)
    for m in re.finditer(r'\{\s*[^,{}]+\s*,\s*"((?:[^"\\]|\\.)*)"\s*\}', src):
        combos.add(m.group(1))
    for m in re.finditer(r'\{\s*\[[^\]]*\]\s*,\s*"((?:[^"\\]|\\.)*)"', src):
        combos.add(m.group(1))

all_ui = ui_strings | combos

# a string is "translated" if: it appears as a whole key in gChineseTable,
# OR it is exactly a wrapped Translate literal (which also must be a key).
# Missing = a UI string whose literal is NOT a key in the table.
missing = sorted(s for s in all_ui if s not in keys)

# also report wrapped literals missing from keys (should be empty ideally)
wrapped_missing = sorted(w for w in wrapped if w not in keys)

print('=== UI strings NOT present as keys in Localization.cpp (count=%d) ===' % len(missing))
for s in missing:
    print(repr(s))
print()
print('=== StringHelper::Translate literals missing from keys (count=%d) ===' % len(wrapped_missing))
for s in wrapped_missing:
    print(repr(s))
