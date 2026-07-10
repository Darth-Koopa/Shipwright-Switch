import json, re

rsk = json.load(open(r'_rsk.json', encoding='utf-8'))
import importlib.util
spec = importlib.util.spec_from_file_location("rsk_zh", r'_rsk_zh.py')
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)
trans = mod.trans

loc = r'soh/soh/SohGui/Localization.cpp'
text = open(loc, encoding='utf-8').read()
marker = '    // __TRANSLATION_TAIL__'

# build dedup map EN->ZH
m = {}
missing = []
for rid, en in rsk.items():
    if rid in trans:
        m[en] = trans[rid]
    else:
        missing.append(rid)

def esc(s):
    import re
    # Collapse ANY run of backslashes directly before 'n' into a single REAL
    # newline. This handles 1, 2, 3, ... backslashes uniformly, regardless
    # of how the JSON stored the escaped newline.
    s = re.sub(r'\\+n', '\n', s)
    # Any remaining standalone backslash (not part of \n) -> doubled for C++.
    s = s.replace('\\', '\\\\')
    # Real newline -> a single C++ "\n" escape, so the table key matches
    # the runtime key (which holds a real newline from the C++ source).
    s = s.replace('\n', '\\n')
    s = s.replace('"', '\\"')
    return s

lines = []
for en, zh in m.items():
    lines.append('    { "%s", "%s" },' % (esc(en), esc(zh)))

rsk_marker = '    // ---- randomizer option descriptions (RSK) ----'
block = rsk_marker + '\n' + '\n'.join(lines) + '\n'
j = text.index(marker)
if rsk_marker in text:
    i = text.index(rsk_marker)
    text = text[:i] + block + text[j:]
else:
    text = text[:j] + block + text[j:]
open(loc, 'w', encoding='utf-8').write(text)
print('written', len(m), 'unique desc entries')
print('MISSING translations for', len(missing), 'ids:')
print(missing)
