import re, os, glob

root = r'e:\Shipwright-wind-waker-style-cel-shading\soh\soh\SohGui'

# Load existing keys (English) from Localization.cpp
loc = open(os.path.join(root, 'Localization.cpp'), encoding='utf-8', errors='ignore').read()
keys = set(re.findall(r'\{\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"', loc))
key_set = set(keys)

# We need to find string literals used as UI that are (a) NOT wrapped in StringHelper::Translate
# and (b) contain ASCII letters (English). These are candidates for untranslated text.

# Pattern: adjacent string literals concatenated (C preprocessor). We'll find runs.
# Simple approach: find Translate(...) wrapped spans and mark them "translated".
# Then scan for UI-context string literals and report those NOT inside a Translate call.

def is_english(s):
    # contains at least one ASCII letter
    return any('a' <= c <= 'z' or 'A' <= c <= 'Z' for c in s)

# UI string contexts (first literal):
ui_patterns = [
    (r'AddWidget\(\s*[\w.]+\s*,\s*"((?:[^"\\]|\\.)*)"', 'AddWidget'),
    (r'AddMenuEntry\(\s*"((?:[^"\\]|\\.)*)"', 'AddMenuEntry'),
    (r'AddSidebarEntry\(\s*[^,]+,\s*"((?:[^"\\]|\\.)*)"', 'AddSidebarEntry'),
    (r'\.Tooltip\(\s*"((?:[^"\\]|\\.)*)"', 'Tooltip'),
    (r'SeparatorText\(\s*"((?:[^"\\]|\\.)*)"', 'SeparatorText'),
    (r'RegisterPopup\(\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"', 'RegisterPopup'),
    (r'\.tooltip\s*=\s*"((?:[^"\\]|\\.)*)"', 'tooltip='),
]

# For each file, find runs of adjacent string literals to reconstruct full concatenated key.
# A "string run" is a sequence of "... " tokens separated by whitespace/newlines.
strlit = re.compile(r'"((?:[^"\\]|\\.)*)"')

candidates = {}  # (file, lineno) -> full concatenated english string

for f in glob.glob(os.path.join(root, '*.cpp')) + glob.glob(os.path.join(root, '*.h')) + glob.glob(os.path.join(root, '*.hpp')):
    src = open(f, encoding='utf-8', errors='ignore').read()
    lines = src.split('\n')
    # find positions of StringHelper::Translate( to exclude
    translate_spans = [(m.start(), m.end()) for m in re.finditer(r'StringHelper::Translate\s*\(', src)]
    def inside_translate(pos):
        for s, e in translate_spans:
            if s <= pos <= e + 400:  # generous
                return True
        return False
    # For each UI pattern match, reconstruct full concatenated string by extending
    # forward over adjacent string literals.
    for pname, p in [(x[1], x[0]) for x in ui_patterns]:
        for m in re.finditer(p, src, re.S):
            start = m.start()
            if inside_translate(start):
                continue
            # reconstruct full concat: collect consecutive string literals from this point
            # by scanning forward over the match end, grabbing more "... " until a non-string token
            full = m.group(1)
            # gather additional concatenated literals: advance pointer
            pos = m.end()
            # skip whitespace
            rest = src[pos:pos+2000]
            # match a sequence: optional ws/newline then "..." possibly repeated
            for mm in re.finditer(r'\s*"((?:[^"\\]|\\.)*)"', rest):
                # ensure it's a continuation (concatenation) - previous char was a string end
                full += mm.group(1)
            if is_english(full):
                lineno = src[:start].count('\n') + 1
                rel = os.path.relpath(f, root)
                candidates.setdefault((rel, lineno, pname), set()).add(full)

# Report unique english candidates not in key_set
print('=== Untranslated ENGLISH UI strings (not wrapped, not in table) ===')
seen = set()
count = 0
for (rel, lineno, pname), strs in sorted(candidates.items()):
    for s in strs:
        if s in key_set:
            continue
        if s in seen:
            continue
        seen.add(s)
        count += 1
        print('[%s:%d %s] %s' % (rel, lineno, pname, repr(s)))
print('TOTAL:', count)
