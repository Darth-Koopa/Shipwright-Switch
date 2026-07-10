import glob
files = [
    'soh/soh/Enhancements/controls/InputViewer.cpp',
    'soh/soh/Enhancements/cosmetics/CosmeticsEditor.cpp',
    'soh/soh/Enhancements/debugger/actorViewer.cpp',
    'soh/soh/Enhancements/debugger/colViewer.cpp',
    'soh/soh/Enhancements/debugger/debugSaveEditor.cpp',
    'soh/soh/Enhancements/debugger/dlViewer.cpp',
    'soh/soh/Enhancements/debugger/hookDebugger.cpp',
    'soh/soh/Enhancements/debugger/MessageViewer.cpp',
    'soh/soh/Enhancements/debugger/SohStatsWindow.cpp',
    'soh/soh/Enhancements/debugger/valueViewer.cpp',
    'soh/soh/Enhancements/ExtraModes/EnemyRandomizer.cpp',
    'soh/soh/Enhancements/Presets/Presets.cpp',
    'soh/soh/Enhancements/randomizer/Plandomizer.cpp',
    'soh/soh/Enhancements/randomizer/randomizer.cpp',
    'soh/soh/Enhancements/randomizer/randomizer_check_tracker.cpp',
    'soh/soh/Enhancements/randomizer/randomizer_entrance_tracker.cpp',
    'soh/soh/Enhancements/randomizer/randomizer_item_tracker.cpp',
    'soh/soh/Enhancements/TimeDisplay/TimeDisplay.cpp',
    'soh/soh/Enhancements/timesplits/TimeSplits.cpp',
]
inc = '#include <ship/utils/StringHelper.h>'
for fp in files:
    s = open(fp, encoding='utf-8').read()
    if inc in s:
        print('skip (have):', fp)
        continue
    lines = s.split('\n')
    idx = 0
    for i, l in enumerate(lines):
        if l.startswith('#include'):
            idx = i
            break
    lines.insert(idx + 1, inc)
    open(fp, 'w', encoding='utf-8').write('\n'.join(lines))
    print('added ->', fp)
print('DONE')
