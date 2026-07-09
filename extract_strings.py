import re, os, glob

root = r'e:\Shipwright-wind-waker-style-cel-shading\soh\soh\SohGui'
files = []
for ext in ('*.cpp', '*.h', '*.hpp'):
    files += glob.glob(os.path.join(root, ext))

strings = set()

# widget name: AddWidget(path, "name", TYPE)
# AddMenuEntry("name", ...)
# AddSidebarEntry(section, "name", n)
# .Tooltip("...")
# SeparatorText("...")
# RegisterPopup("a","b","c","d",
# options?.tooltip = "..."
# StringHelper::Translate("...")
# generic { key, "value" }  (combobox option maps)
patterns = [
    r'AddWidget\(\s*[\w.]+\s*,\s*"((?:[^"\\]|\\.)*)"',
    r'AddMenuEntry\(\s*"((?:[^"\\]|\\.)*)"',
    r'AddSidebarEntry\(\s*[^,]+,\s*"((?:[^"\\]|\\.)*)"',
    r'\.Tooltip\(\s*"((?:[^"\\]|\\.)*)"',
    r'SeparatorText\(\s*"((?:[^"\\]|\\.)*)"',
    r'RegisterPopup\(\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"',
    r'\.tooltip\s*=\s*"((?:[^"\\]|\\.)*)"',
    r'StringHelper::Translate\(\s*"((?:[^"\\]|\\.)*)"',
]

for f in files:
    src = open(f, encoding='utf-8', errors='ignore').read()
    for p in patterns:
        for m in re.finditer(p, src, re.S):
            for i in range(1, (m.lastindex or 0) + 1):
                s = m.group(i)
                if s is not None:
                    strings.add(s)
    # combobox option maps: { key, "value" }  (whole file)
    for m in re.finditer(r'\{\s*[^,{}]+\s*,\s*"((?:[^"\\]|\\.)*)"\s*\}', src):
        strings.add(m.group(1))
    # disabledMap reasons: { [...], "reason" }
    for m in re.finditer(r'\{\s*\[[^\]]*\]\s*,\s*"((?:[^"\\]|\\.)*)"', src):
        strings.add(m.group(1))

out = sorted(strings)
with open(r'e:\Shipwright-wind-waker-style-cel-shading\extracted_strings.txt', 'w', encoding='utf-8') as o:
    for s in out:
        o.write(s + '\n')
print('total unique strings:', len(out))
