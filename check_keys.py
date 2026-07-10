import re
loc = open(r'e:\Shipwright-wind-waker-style-cel-shading\soh\soh\SohGui\Localization.cpp', encoding='utf-8', errors='ignore').read()
# capture key exactly as between first quotes
pat = re.compile(r'\{\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"')
keys = [m.group(1) for m in pat.finditer(loc)]
print('num keys:', len(keys))
print('has About:', 'About' in keys)
print('has select off:', '(Select \\"Off\\" to disable.)' in keys)
# show first 3 keys raw
for k in keys[:3]:
    print(repr(k))
# check a known extracted line
ext = open(r'e:\Shipwright-wind-waker-style-cel-shading\extracted_strings.txt', encoding='utf-8').read().split('\n')
print('extracted line1 repr:', repr(ext[0]))
print('extracted line1 in keys:', ext[0] in keys)
