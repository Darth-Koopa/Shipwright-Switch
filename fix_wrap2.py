import glob

TARGETS = [
    r'soh\soh\SohGui\SohMenuEnhancements.cpp',
    r'soh\soh\SohGui\ResolutionEditor.cpp',
]


def fix_file(path):
    s = open(path, encoding='utf-8').read()
    out = []
    i = 0
    L = len(s)
    changed = False
    while i < L:
        if s.startswith('StringHelper::Translate(', i):
            p = s.index('(', i)
            depth = 1
            k = p + 1
            while k < L and depth > 0:
                c = s[k]
                if c == '(':
                    depth += 1
                elif c == ')':
                    depth -= 1
                k += 1
            # k = index right after Translate's closing ')'
            preceding = s[max(0, i - 120):i]
            # fmt::format context ONLY when Translate is the immediate first argument:
            in_fmt = preceding.rstrip().endswith('fmt::format(')
            m = k
            while m < L and s[m] in ' \t\r\n':
                m += 1
            has_cstr = s.startswith('.c_str()', m)
            if in_fmt:
                # fmt::format wants a std::string as the format arg -> must NOT have .c_str()
                if has_cstr:
                    out.append(s[i:m])           # drop the erroneous .c_str()
                    i = m + len('.c_str()')
                    changed = True
                    continue
                else:
                    out.append(s[i:k])
                    i = k
                    continue
            else:
                if has_cstr:
                    out.append(s[i:k])
                    i = m + len('.c_str()')
                    continue
                else:
                    out.append(s[i:k])
                    out.append('.c_str()')
                    i = k
                    changed = True
                    continue
        else:
            out.append(s[i])
            i += 1
    if changed:
        open(path, 'w', encoding='utf-8').write(''.join(out))
        print('FIXED', path)
    else:
        print('NOCHANGE', path)


for f in TARGETS:
    fix_file(f)
print('DONE')
