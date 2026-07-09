$enc = New-Object System.Text.UTF8Encoding($false)
$root = 'e:\Shipwright-wind-waker-style-cel-shading'
$nl = [System.Environment]::NewLine

# ---------- Menu.cpp ----------
$menu = Join-Path $root 'soh\soh\SohGui\Menu.cpp'
$c = [System.IO.File]::ReadAllText($menu)
if ($c -notmatch 'ship/utils/StringHelper.h') {
    $c = $c.Replace('#include "Menu.h"', ('#include "Menu.h"' + $nl + '#include "ship/utils/StringHelper.h"'))
}
$c = $c.Replace('void Menu::MenuDrawItem(WidgetInfo& widget, uint32_t width, UIWidgets::Colors menuThemeIndex) {', ('void Menu::MenuDrawItem(WidgetInfo& widget, uint32_t width, UIWidgets::Colors menuThemeIndex) {' + $nl + '    std::string translatedName = StringHelper::Translate(widget.name);'))
$c = $c.Replace('widget.name.c_str()', 'translatedName.c_str()')
$c = $c.Replace('"Audio API"', 'StringHelper::Translate("Audio API")')
$c = $c.Replace('"Renderer API (Needs reload)"', 'StringHelper::Translate("Renderer API (Needs reload)")')
$c = $c.Replace('ImGui::Button("Clear")', 'ImGui::Button(StringHelper::Translate("Clear"))')
$c = $c.Replace('"This setting is disabled because: \n"', 'StringHelper::Translate("This setting is disabled because: \n")')
$c = $c.Replace('"Race Lockout Active"', 'StringHelper::Translate("Race Lockout Active")')
$c = $c.Replace('disabledMap.at(option).reason', 'StringHelper::Translate(disabledMap.at(option).reason)')
$c = $c.Replace('fmt::format("  ({} -> {}, Col {})", menuEntry.label, sidebarLabel, i + 1)', 'fmt::format("  ({} -> {}, Col {})", StringHelper::Translate(menuEntry.label), StringHelper::Translate(sidebarLabel), i + 1)')
$c = $c.Replace('fmt::format("  ({} -> {}, {})", entry.menuName, entry.sidebarName, entry.location)', 'fmt::format("  ({} -> {}, {})", StringHelper::Translate(entry.menuName), StringHelper::Translate(entry.sidebarName), StringHelper::Translate(entry.location))')
$c = $c.Replace('bool ModernMenuSidebarEntry(std::string label) {', ('bool ModernMenuSidebarEntry(std::string label) {' + $nl + '    std::string tLabel = StringHelper::Translate(label);'))
$c = $c.Replace('bool ModernMenuHeaderEntry(std::string label) {', ('bool ModernMenuHeaderEntry(std::string label) {' + $nl + '    std::string tLabel = StringHelper::Translate(label);'))
$c = $c.Replace('UIWidgets::RenderText(pos, label.c_str(), ImGui::FindRenderedTextEnd(label.c_str()), true);', 'UIWidgets::RenderText(pos, tLabel.c_str(), ImGui::FindRenderedTextEnd(tLabel.c_str()), true);')
$c = $c.Replace('ImGui::CalcTextSize(label.c_str(), ImGui::FindRenderedTextEnd(label.c_str()), true)', 'ImGui::CalcTextSize(tLabel.c_str(), ImGui::FindRenderedTextEnd(tLabel.c_str()), true)')
$c = $c.Replace('options3.tooltip = "Quit SoH";', 'options3.tooltip = StringHelper::Translate("Quit SoH");')
$c = $c.Replace('"Quit SoH", "Are you sure you want to quit SoH?", "Quit", "Cancel",', 'StringHelper::Translate("Quit SoH"), StringHelper::Translate("Are you sure you want to quit SoH?"), StringHelper::Translate("Quit"), StringHelper::Translate("Cancel"),')
$c = $c.Replace('options2.tooltip = "Reset"', 'options2.tooltip = StringHelper::Translate("Reset")')
$c = $c.Replace('options.tooltip = "Close Menu (Esc)";', 'options.tooltip = StringHelper::Translate("Close Menu (Esc)");')
[System.IO.File]::WriteAllText($menu, $c, $enc)

# ---------- UIWidgets.cpp ----------
$uiw = Join-Path $root 'soh\soh\SohGui\UIWidgets.cpp'
$c = [System.IO.File]::ReadAllText($uiw)
if ($c -notmatch 'ship/utils/StringHelper.h') {
    $c = $c.Replace('#include "UIWidgets.hpp"', ('#include "UIWidgets.hpp"' + $nl + '#include "ship/utils/StringHelper.h"'))
}
$c = $c.Replace('std::string newText(text);', 'std::string newText = StringHelper::Translate(text);')
$c = $c.Replace('std::string uniqueTag = "Reset##" + std::string(label);', 'std::string uniqueTag = StringHelper::Translate("Reset") + "##" + std::string(label);')
$c = $c.Replace('std::string uniqueTag = "Random##" + std::string(label);', 'std::string uniqueTag = StringHelper::Translate("Random") + "##" + std::string(label);')
$c = $c.Replace('std::string uniqueTag = "Rainbow##" + std::string(cvarName) + "Rainbow";', 'std::string uniqueTag = StringHelper::Translate("Rainbow") + "##" + std::string(cvarName) + "Rainbow";')
$c = $c.Replace('std::string uniqueTag = "Lock##" + std::string(cvarName) + "Locked";', 'std::string uniqueTag = StringHelper::Translate("Lock") + "##" + std::string(cvarName) + "Locked";')
$c = $c.Replace('UIWidgets::Button(buttonName.c_str(), UIWidgets::ButtonOptions()', 'UIWidgets::Button(StringHelper::Translate(buttonName).c_str(), UIWidgets::ButtonOptions()')
$c = $c.Replace('if (ImGui::MenuItem(buttonName.c_str()))', 'if (ImGui::MenuItem(StringHelper::Translate(buttonName).c_str()))')
[System.IO.File]::WriteAllText($uiw, $c, $enc)

# ---------- UIWidgets.hpp ----------
$uiwh = Join-Path $root 'soh\soh\SohGui\UIWidgets.hpp'
$c = [System.IO.File]::ReadAllText($uiwh)
if ($c -notmatch 'ship/utils/StringHelper.h') {
    $c = $c.Replace('#include <libultraship/libultraship.h>', ('#include <libultraship/libultraship.h>' + $nl + '#include "ship/utils/StringHelper.h"'))
}
$c = $c.Replace('ImGui::BeginCombo(invisibleLabel, comboMap.at(*value), options.flags)', 'ImGui::BeginCombo(invisibleLabel, StringHelper::Translate(comboMap.at(*value)).c_str(), options.flags)')
$c = $c.Replace('if (ImGui::Selectable(pair.second, pair.first == *value)) {', 'if (ImGui::Selectable(StringHelper::Translate(pair.second), pair.first == *value)) {')
$c = $c.Replace('ImGui::BeginCombo(invisibleLabel, comboVector.at(currentValueIndex), options.flags)', 'ImGui::BeginCombo(invisibleLabel, StringHelper::Translate(comboVector.at(currentValueIndex)).c_str(), options.flags)')
$c = $c.Replace('if (ImGui::Selectable(comboVector.at(i), newValue == *value)) {', 'if (ImGui::Selectable(StringHelper::Translate(comboVector.at(i)), newValue == *value)) {')
$c = $c.Replace('ImGui::BeginCombo(invisibleLabel, comboVector.at(currentValueIndex).c_str(), options.flags)', 'ImGui::BeginCombo(invisibleLabel, StringHelper::Translate(comboVector.at(currentValueIndex)).c_str(), options.flags)')
$c = $c.Replace('if (ImGui::Selectable(comboVector.at(i).c_str(), newValue == *value)) {', 'if (ImGui::Selectable(StringHelper::Translate(comboVector.at(i)).c_str(), newValue == *value)) {')
$c = $c.Replace('trueLabel.c_str()', 'StringHelper::Translate(trueLabel).c_str()')
[System.IO.File]::WriteAllText($uiwh, $c, $enc)

Write-Host 'localize patch done'
