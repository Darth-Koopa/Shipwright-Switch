#pragma once

#include <string>

// Forward declaration so this header doesn't need to pull in all of imgui.
class ImFont;

namespace SohGui {

// Registers the Simplified-Chinese UI translator with libultraship's StringHelper.
// Call once during menu initialization. The translator reads the
// "gSohGui.Menu.InterfaceLanguage" cvar ("English" / "简体中文") on every call,
// so switching the language in the settings menu takes effect immediately.
void RegisterLocalization();

// Merge Simplified-Chinese glyphs (from DroidSansFallback.ttf, resolved next to soh.exe)
// into the given ImGui font so Chinese text renders instead of boxes. The merge uses
// ImGui's common-simplified-Chinese glyph range and is sized to match `size` (the target
// font's pixel size), so the glyphs align correctly. Call this for EVERY UI font that the
// menu can render with (the menu does NOT use ImGui's built-in default font — it uses the
// Montserrat/Inconsolata fonts created in OTRGlobals), otherwise Chinese shows as boxes.
bool MergeSimplifiedChineseInto(ImFont* dstFont, float size);

} // namespace SohGui
