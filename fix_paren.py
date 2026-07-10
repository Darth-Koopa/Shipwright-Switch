import re

FILES = [
    r'soh\soh\SohGui\SohMenuEnhancements.cpp',
    r'soh\soh\SohGui\ResolutionEditor.cpp',
]


def is_fmt_context(s, i):
    """True if the Translate call at i is the immediate first arg of fmt::format(."""
    head = s[:i]
    head = head.rstrip()
    marker = 'StringHelper::Translate('
    pos = head.rfind(marker)
    if pos == -1:
        return False
    head2 = head[:pos].rstrip()
    return head2.endswith('fmt::format(')


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
            fmt = is_fmt_context(s, i)
            m = k
            while m < L and s[m] in ' \t\r\n':
                m += 1
            has_cstr = s.startswith('.c_str()', m)
            if fmt:
                if has_cstr:
                    out.append(s[i:m])           # Translate(...) without .c_str()
                    i = m + len('.c_str()')
                    changed = True
                    continue
                else:
                    out.append(s[i:k])
                    i = k
                    continue
            else:
                if has_cstr:
                    out.append(s[i:m + len('.c_str()')])
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


for f in FILES:
    fix_file(f)
print('DONE')
