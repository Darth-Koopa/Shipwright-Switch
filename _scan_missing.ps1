$root = "e:/SOHCN/soh/soh"
$locPath = "e:/SOHCN/soh/soh/SohGui/Localization.cpp"

$keys = @{}
foreach ($l in (Get-Content $locPath)) {
    if ($l -match '^\s*\{\s*"((?:[^"\\]|\\.)*)"') { $keys[$matches[1]] = $true }
}

$files = Get-ChildItem -Path $root -Recurse -Include *.cpp
$missing = @{}   # raw candidate -> locations
$patterns = @(
  'ImGui::(?:Text|TextWrapped|BulletText|Button|Checkbox|RadioButton|Selectable|CollapsingHeader|TreeNode|SeparatorText|LabelText|MenuItem|Combo|SetTooltip)\s*\(\s*"((?:[^"\\]|\\.)*)"',
  '\.Tooltip\(\s*"((?:[^"\\]|\\.)*)"',
  '(?:CVarCheckbox|CVarSlider|CVarCombobox|UIWidgets::CVar(?:Checkbox|Slider|Combobox)|UIWidgets::Button|AddWidget)\s*\(\s*"((?:[^"\\]|\\.)*)"'
)

foreach ($f in $files) {
    $lines = Get-Content $f.FullName
    for ($i = 0; $i -lt $lines.Count; $i++) {
        $line = $lines[$i]
        if ($line -match 'SohGui::L\(') { continue }
        if ($line -match 'Localization\.cpp') { continue }
        foreach ($p in $patterns) {
            $m = [regex]::Match($line, $p)
            if ($m.Success) {
                $s = $m.Groups[1].Value
                if (-not $keys.ContainsKey($s)) {
                    if (-not $missing.ContainsKey($s)) { $missing[$s] = @() }
                    $loc = "$($f.Name):$($i+1)"
                    if ($missing[$s] -notcontains $loc) { $missing[$s] += $loc }
                }
            }
        }
    }
}

# 已翻译文件（其候选多为 tooltip 跨行拼接片段，整体已加表），排除
$translated = @('Menu.cpp','SohMenuEnhancements.cpp','SohMenuWindWakerStyle.cpp','SohMenuSettings.cpp','SohMenuDevTools.cpp','SohMenuRandomizer.cpp','SohMenuNetwork.cpp','AudioEditor.cpp','CosmeticsEditor.cpp','ResolutionEditor.cpp','gameplaystats.cpp')
$debuggers = @('actorViewer.cpp','dlViewer.cpp','colViewer.cpp','debugSaveEditor.cpp','hookDebugger.cpp','valueViewer.cpp')

# 过滤噪声
$clean = @{}
foreach ($k in $missing.Keys) {
    $s = $k
    $loc0 = $missing[$k][0]
    $fn = $loc0.Split(':')[0]
    if ($translated -contains $fn) { continue }  # 已翻译文件跳过
    if ($debuggers -contains $fn) { continue }    # 深度调试器跳过（数据字段，价值低）
    # 纯格式/标点
    if ($s -match '^%[sdlu c]$') { continue }
    if ($s -match '^\(\%s\)$') { continue }
    if ($s -match '^[:?]+$') { continue }
    if ($s -match '^##') { continue }            # ImGui 隐藏 ID
    if ($s.Length -lt 4) { continue }           # 过短
    if ($s -cmatch '^[A-Z0-9_]+$') { continue } # 全大写技术串
    $clean[$s] = $missing[$k]
}

# 按文件分组统计
$byFile = @{}
foreach ($k in $clean.Keys) {
    foreach ($loc in $clean[$k]) {
        $fn = $loc.Split(':')[0]
        if (-not $byFile.ContainsKey($fn)) { $byFile[$fn] = 0 }
        $byFile[$fn]++
    }
}
"==== 按文件统计(候选数) ====" | Out-File -Encoding utf8 e:/SOHCN/_scan_clean.txt
$byFile.GetEnumerator() | Sort-Object Value -Descending | ForEach-Object { "$($_.Value)`t$($_.Key)" } | Out-File -Append -Encoding utf8 e:/SOHCN/_scan_clean.txt
"" | Out-File -Append -Encoding utf8 e:/SOHCN/_scan_clean.txt
"==== 候选列表 (串<TAB>位置) ====" | Out-File -Append -Encoding utf8 e:/SOHCN/_scan_clean.txt
$clean.GetEnumerator() | Sort-Object Name | ForEach-Object { "$($_.Key)`t$($_.Value -join ',')" } | Out-File -Append -Encoding utf8 e:/SOHCN/_scan_clean.txt

Write-Host "原始候选: $($missing.Count)  过滤后: $($clean.Count)  涉及文件: $($byFile.Count)"
