import re, os, glob

root = r'e:\Shipwright-wind-waker-style-cel-shading\soh\soh\SohGui'

loc = open(os.path.join(root, 'Localization.cpp'), encoding='utf-8', errors='ignore').read()
key_set = set(m.group(1) for m in re.finditer(r'\{\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"', loc))

# find all Translate()-wrapped full strings first (so we can skip already-wrapped)
translated_full = set()
for f in glob.glob(os.path.join(root, '*.cpp')) + glob.glob(os.path.join(root, '*.h')) + glob.glob(os.path.join(root, '*.hpp')):
    src = open(f, encoding='utf-8', errors='ignore').read()
    for m in re.finditer(r'StringHelper::Translate\(\s*("(?:[^"\\]|\\.)*"(?:\s*"[^"\\]+")*)', src):
        # reconstruct concatenated
        full = ''.join(re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(1)))
        translated_full.add(full)

# Now find UI-string contexts that are NOT wrapped in Translate.
# Strategy: tokenize the file into a sequence; for each UI-call start, scan the
# statement/argument and collect a C-string-concatenation run delimited by commas/semicolons/parens.
ui_call_re = re.compile(r'(AddWidget\(\s*[\w.]+\s*,\s*|AddMenuEntry\(\s*|AddSidebarEntry\(\s*[^,]+,\s*|CheckboxOptions\(\)\.Tooltip\(\s*|SeparatorText\(\s*|RegisterPopup\(\s*|BtnSelectorOptions\(\)\.Tooltip\(\s*|\.tooltip\s*=\s*)"')

def has_cjk(s):
    return any('\u4e00' <= c <= '\u9fff' for c in s)

def is_english(s):
    if has_cjk(s):
        return False
    return any('a' <= c <= 'z' or 'A' <= c <= 'Z' for c in s)

results = {}
for f in glob.glob(os.path.join(root, '*.cpp')) + glob.glob(os.path.join(root, '*.h')) + glob.glob(os.path.join(root, '*.hpp')):
    src = open(f, encoding='utf-8', errors='ignore').read()
    for m in ui_call_re.finditer(src):
        # start right after the opening quote we matched (the call's first literal begins at m.end()-1 which is the quote)
        qpos = m.end() - 1  # position of opening quote
        # collect concatenation: from qpos, gather balanced string literals while only whitespace separates them
        i = qpos
        n = len(src)
        full = ''
        # parse first literal
        assert src[i] == '"'
        # read until matching close quote (handling escapes)
        j = i + 1
        buf = ''
        while j < n:
            c = src[j]
            if c == '\\':
                buf += c + src[j+1]
                j += 2
                continue
            if c == '"':
                j += 1
                break
            buf += c
            j += 1
        full = buf
        # now try to continue concatenation: skip whitespace; if next non-ws is a '"', continue; else stop
        k = j
        while k < n and src[k] in ' \t\r\n':
            k += 1
        while k < n and src[k] == '"':
            # read this literal
            k += 1
            buf2 = ''
            while k < n:
                c = src[k]
                if c == '\\':
                    buf2 += c + src[k+1]
                    k += 2
                    continue
                if c == '"':
                    k += 1
                    break
                buf2 += c
                k += 1
            full += buf2
            # skip ws, check for another quote
            while k < n and src[k] in ' \t\r\n':
                k += 1
            # if next is ',' ')' ';' or other -> stop concatenation
            if k >= n or src[k] != '"':
                break
        if is_english(full) and full not in key_set and full not in translated_full:
            rel = os.path.relpath(f, root)
            ln = src[:m.start()].count('\n') + 1
            results.setdefault((rel, ln), full)

print('=== Unwrapped ENGLISH UI string literals (concatenated, not in table) ===')
print('count:', len(results))
for (rel, ln), s in sorted(results.items()):
    print('[%s:%d] %s' % (rel, ln, repr(s)))
