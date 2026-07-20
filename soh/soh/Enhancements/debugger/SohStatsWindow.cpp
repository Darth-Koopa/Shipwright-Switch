#include "SohStatsWindow.h"
#include "soh/OTRGlobals.h"
#include "soh/SohGui/SohGui.hpp"

void SohStatsWindow::DrawElement() {
    const float framerate = ImGui::GetIO().Framerate;
    const float deltatime = ImGui::GetIO().DeltaTime;
    ImGui::PushFont(OTRGlobals::Instance->fontMonoLarger);
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

#if defined(_WIN32)
    ImGui::Text(SohGui::L("Platform: Windows"));
#elif defined(__IOS__)
    ImGui::Text(SohGui::L("Platform: iOS"));
#elif defined(__APPLE__)
    ImGui::Text(SohGui::L("Platform: macOS"));
#elif defined(__linux__)
    ImGui::Text(SohGui::L("Platform: Linux"));
#else
    ImGui::Text(SohGui::L("Platform: Unknown"));
#endif
    ImGui::Text(SohGui::L("Status: %0.3f ms/frame (%0.1f FPS)"), deltatime * 1000.0f, framerate);
    ImGui::PopStyleColor();
    ImGui::PopFont();
}
