#pragma once

#include <string>

namespace SohGui {

// Returns the localized (Simplified Chinese) version of the given English source string used in the
// menu UI. When Chinese localization is disabled, or no translation exists, the original string is
// returned unchanged. The returned pointer is stable for the lifetime of the program.
const char* L(const char* english);
inline const char* L(const std::string& english) {
    return L(english.c_str());
}

// Enables/disables Chinese localization for the menu UI. Driven by the "Menu.Language" CVar
// (0 = English, 1 = Chinese).
void SetMenuLanguage(bool chinese);

// Returns whether the menu/UI Chinese localization is currently enabled. Used by non-UI code (e.g.
// game item/scene name lookups) to decide whether to return Chinese names.
bool IsMenuChinese();

} // namespace SohGui
