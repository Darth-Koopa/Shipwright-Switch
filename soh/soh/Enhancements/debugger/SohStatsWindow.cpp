#include "SohStatsWindow.h"
#include <ship/utils/StringHelper.h>
#include "soh/OTRGlobals.h"

void SohStatsWindow::DrawElement() {
    const float framerate = ImGui::GetIO().Framerate;
    const float deltatime = ImGui::GetIO().DeltaTime;
    ImGui::PushFont(OTRGlobals::Instance->fontMonoLarger);
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

#if defined(_WIN32)
    ImGui::Text(StringHelper::Translate("Platform: Windows").c_str());
#elif defined(__IOS__)
    ImGui::Text(StringHelper::Translate("Platform: iOS").c_str());
#elif defined(__APPLE__)
    ImGui::Text(StringHelper::Translate("Platform: macOS").c_str());
#elif defined(__linux__)
    ImGui::Text(StringHelper::Translate("Platform: Linux").c_str());
#else
    ImGui::Text(StringHelper::Translate("Platform: Unknown").c_str());
#endif
    ImGui::Text(StringHelper::Translate("Status: %0.3f ms/frame (%0.1f FPS)").c_str(), deltatime * 1000.0f, framerate);
    ImGui::PopStyleColor();
    ImGui::PopFont();
}
