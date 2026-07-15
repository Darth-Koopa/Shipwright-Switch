# Project Memory

## SOH (Ship of Harkinian) — 设置菜单中文本地化
- 架构：集中式本地化。翻译表在 `soh/soh/SohGui/Localization.cpp`（`gChineseTable`，键须与英文字符串完全一致，含 `\n`/`%d %%`）。`SohGui::L()` 在绘制路径翻译；`SohGui::SetMenuLanguage(bool)` 控制开关。
- **键匹配坑：C++ 相邻字符串字面量拼接不加空格**。源码如 `"...models." "This might..."` 拼接后实为 `"...models.This..."`（无空格）。翻译表键绝不能画蛇添足加尾随空格（曾因 `"boss' models. "` 多了空格导致 Boss 灵魂描述永远匹配不到、一直显示英文）。凡源码是拆成多行相邻字面量的长字符串，键必须严格按拼接后结果写。
- 绘制集中点：`Menu.cpp` 的 `MenuDrawItem`（widget 标签、combobox 选项值）、`DrawElement`（header/sidebar 标签）、搜索结果来源。
- 工具提示在消费点本地化：`UIWidgets.cpp`/`UIWidgets.hpp` 的 `WrappedText(options.tooltip/disabledTooltip)` 处包 `SohGui::L(...)`（避免原地 mutate，确保可切回英文）。
- 语言开关：设置项「Menu Language」绑定 CVar `Menu.Language`（0=EN,1=中文），`Menu::InitElement` 启动时读取。
- 扩展翻译只需往 `gChineseTable` 加条目，无需改调用点。
- libultraship 子模块现已拉全（约 368 文件）。
- **本环境【可】本地编译 SoH**：VS2022 BuildTools 17.14.35 + MSVC v143 已装（`C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools`），但 `cl`/`msbuild` 不在 PATH，须先 `call vcvars64.bat` 注入环境。构建用 **Ninja** 生成器。VPN 代理 `http://127.0.0.1:7897` 可用；vcpkg 依赖已缓存在 `build/x64/vcpkg`；子模块 `libultraship`/`ZAPDTR`/`OTRExporter` 已克隆齐全。
- **构建脚本（根目录）**：Debug 用 `_ninja_configure.bat` + `_ninja_build.bat`（输出 `x64/Debug/soh.exe`，118MB，未优化）；Release 用 `_ninja_configure_release.bat` + `_ninja_build_release.bat`（输出 `x64/Release/soh.exe`，约 37MB，已优化 `/O2`）。Release 构建目录为 `build/ninja-release`（与 Debug 的 `build/ninja` 分开，互不干扰）。
- **⚠️ 试玩/发布必须用 Release（`x64/Release/soh.exe`）**：Debug 版关闭优化（`/Od /RTC1`），帧率远低于 Release，手感差很多。用户曾因误跑 Debug 版而觉"变卡"。`x64/712`、`x64/713` 下的 `soh.exe` 是更早的旧 Release 产物。
- **全量 Release 编译约 5 分钟内可完成**（Ninja 增量快），但 `execute_command` 工具有 300s 硬超时，直接同步跑会被截断（bat 收尾阶段被杀，但编译链接实际已完成，`ninja` 再次运行会报 `no work to do`）。稳妥做法：后台分离进程 `cmd /c start "" cmd /c "_ninja_build_release.bat > release_build.log 2>&1"` 再轮询日志，或直接重跑确认 `no work to do` 即表示已完成。
- 翻译包裹注意：被包裹的英文字符串若其后跟着平台条件字符串拼接（如 Menu.cpp 的 `options2.tooltip`），不能写成 `SohGui::L("Reset") " (Ctrl+R)"`（函数调用后不能直接跟裸字符串字面量），须用 `std::string(SohGui::L("Reset")) + " (Ctrl+R)"`；且 `tooltip` 字段是 `const char*`，不能直接赋 `std::string`，需用局部 `std::string` 再 `.c_str()`。
- **⚠️ GuiWindow 标题绝不能包 `SohGui::L()`**：`SohGui.cpp` 的 `SetupGuiElements()` 中 `gui->AddGuiWindow(make_shared<...>(CVAR, 标题, size))` 的「标题」是 `GuiWindow` map 的键。侧边栏 `WIDGET_WINDOW_BUTTON` 的 `.WindowName(...)` 用英文查找 `GetGuiWindow(name)`；若标题被 L() 翻成中文，键不匹配 → 返回 nullptr → 窗口打开后空白。已修复：所有窗口标题改回英文原串（"Console##SoH"、"Actor Viewer" 等）。侧边栏按钮 label 仍由 UIWidgets 自动翻译，无影响。
