import re, os, glob, sys
from translations_map import TRANSLATIONS

DRYRUN = '--apply' not in sys.argv

root = r'e:\Shipwright-wind-waker-style-cel-shading'
sohgui = root + r'\soh\soh\SohGui'

def read_literal(src, i):
    assert src[i] == '"'
    j = i + 1; n = len(src); buf = ''
    while j < n:
        c = src[j]
        if c == '\\':
            buf += c + src[j+1]; j += 2; continue
        if c == '"':
            j += 1; return buf, j
        buf += c; j += 1
    return buf, j

starter = re.compile(r'(AddWidget\(\s*[\w.]+\s*,\s*|AddMenuEntry\(\s*|AddSidebarEntry\(\s*[^,]+,\s*|'
                     r'CheckboxOptions\(\)\.Tooltip\(\s*|SeparatorText\(\s*|RegisterPopup\(\s*|'
                     r'BtnSelectorOptions\(\)\.Tooltip\(\s*|\.tooltip\s*=\s*|\.Tooltip\(\s*|'
                     r'AddSelection\(\s*[^,]+,\s*|AddCombo\(\s*[^,]+,\s*|ImGui::Text\(\s*|ImGui::TextWrapped\(\s*|'
                     r'ImGui::MenuItem\(\s*|ImGui::Button\(\s*|\.Label\(\s*)"')

def read_concat_runs(src):
    runs = []
    for m in starter.finditer(src):
        qpos = m.end() - 1
        if src[qpos] != '"':
            continue
        buf, j = read_literal(src, qpos)
        full = buf
        while True:
            k = j
            while k < len(src) and src[k] in ' \t\r\n':
                k += 1
            if k < len(src) and src[k] == '"':
                buf2, j2 = read_literal(src, k)
                full += buf2; j = j2
            else:
                break
        runs.append((qpos, j, full))
    return runs

# Build reverse map per file
todo = []
for f in glob.glob(sohgui + r'\*.cpp') + glob.glob(sohgui + r'\*.h') + glob.glob(sohgui + r'\*.hpp') \
         + glob.glob(root + r'\soh\soh\Enhancements\**\*.cpp') + glob.glob(root + r'\soh\soh\Enhancements\**\*.h') \
         + glob.glob(root + r'\soh\soh\Enhancements\**\*.hpp') \
         + glob.glob(root + r'\libultraship\src\**\*.cpp') + glob.glob(root + r'\libultraship\src\**\*.h') \
         + glob.glob(root + r'\libultraship\src\**\*.hpp'):
    src = open(f, encoding='utf-8', errors='ignore').read()
    for qpos, jend, full in read_concat_runs(src):
        if full in TRANSLATIONS:
            todo.append((f, qpos, jend, full))

byfile = {}
for f, qpos, jend, full in todo:
    byfile.setdefault(f, []).append((qpos, jend, full))

applied = 0
for f, items in byfile.items():
    src = open(f, encoding='utf-8', errors='ignore').read()
    items_sorted = sorted(items, key=lambda x: x[0], reverse=True)
    new_src = src
    for qpos, jend, full in items_sorted:
        seg = new_src[qpos:jend]
        replacement = 'StringHelper::Translate(' + seg + ').c_str()'
        new_src = new_src[:qpos] + replacement + new_src[jend:]
    if not DRYRUN:
        open(f, 'w', encoding='utf-8').write(new_src)
    applied += len(items)

print(('[DRYRUN] ' if DRYRUN else 'Applied wraps to '), applied, 'strings across', len(byfile), 'files.')

# Append keys to Localization.cpp at anchor
loc_path = sohgui + r'\Localization.cpp'
loc = open(loc_path, encoding='utf-8', errors='ignore').read()
marker = '    // __TRANSLATION_TAIL__'
assert marker in loc, 'anchor not found'
block_lines = []
for eng, zh in TRANSLATIONS.items():
    key_src = eng.replace('\\', '\\\\').replace('"', '\\"')
    key_src = key_src.replace('\n', '\\n').replace('\r', '\\r')
    val_src = zh.replace('\\', '\\\\').replace('"', '\\"')
    val_src = val_src.replace('\n', '\\n').replace('\r', '\\r')
    block_lines.append('    { "%s", "%s" },' % (key_src, val_src))
block = '\n'.join(block_lines) + '\n\n'
loc = loc.replace(marker, block + marker, 1)
if not DRYRUN:
    open(loc_path, 'w', encoding='utf-8').write(loc)
print(('[DRYRUN] ' if DRYRUN else 'Added '), len(TRANSLATIONS), 'keys to Localization.cpp')
