import json, re, importlib.util

trick = json.load(open(r'_trick.json', encoding='utf-8'))
spec = importlib.util.spec_from_file_location("trick_zh", r'_trick_zh.py')
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)
td = mod.td  # dict rt -> {'name': zh, 'desc': zh}

loc = r'soh/soh/SohGui/Localization.cpp'
text = open(loc, encoding='utf-8').read()
tail = '    // __TRANSLATION_TAIL__'
trick_start = '    // ---- trick names ----'

name_map = {}
desc_map = {}
missing = []
for rt, v in trick.items():
    en_name = v['name']
    en_desc = v['desc']
    if rt in td:
        if td[rt].get('name'):
            name_map[en_name] = td[rt]['name']
        if td[rt].get('desc'):
            desc_map[en_desc] = td[rt]['desc']
    else:
        missing.append(rt)

def esc(s):
    import re
    # Collapse ANY run of backslashes directly before 'n' into a single REAL
    # newline, then emit a single C++ "\n" escape. Handles 1..N backslashes.
    s = re.sub(r'\\+n', '\n', s)
    s = s.replace('\\', '\\\\')
    s = s.replace('\n', '\\n')
    s = s.replace('"', '\\"')
    return s

lines = []
for en, zh in name_map.items():
    lines.append('    { "%s", "%s" },' % (esc(en), esc(zh)))
lines.append('    // ---- trick descriptions ----')
for en, zh in desc_map.items():
    lines.append('    { "%s", "%s" },' % (esc(en), esc(zh)))

block = trick_start + '\n' + '\n'.join(lines) + '\n'
j = text.index(tail)
if trick_start in text:
    i = text.index(trick_start)
    text = text[:i] + block + text[j:]
else:
    text = text[:j] + block + text[j:]
open(loc, 'w', encoding='utf-8').write(text)
print('written', len(name_map), 'trick names,', len(desc_map), 'trick desc')
print('MISSING translations for', len(missing), 'tricks')
