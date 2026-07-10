import re, importlib.util
loc = open(r'e:\Shipwright-wind-waker-style-cel-shading\soh\soh\SohGui\Localization.cpp', encoding='utf-8', errors='ignore').read()
keys = set(m[0] for m in re.finditer(r'\{\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"', loc))
print('total keys now:', len(keys))
print('tail marker present:', '__TRANSLATION_TAIL__' in loc)
spec = importlib.util.spec_from_file_location('tm', r'e:\Shipwright-wind-waker-style-cel-shading\translations_map.py')
tm = importlib.util.module_from_spec(spec); spec.loader.exec_module(tm)
missing = [k[:50] for k in tm.TRANSLATIONS if k not in keys]
print('keys missing from table:', len(missing))
for m in missing:
    print('  MISSING:', repr(m))
