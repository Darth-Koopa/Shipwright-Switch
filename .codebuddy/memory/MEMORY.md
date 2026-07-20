# 项目记忆：Shipwright-CN 自定义纹理接入方法

> 跨项目共享经验库：`E:\codebuddyEXPshare\MEMORY.md`（开新项目/其他项目时让 AI 先读它即可复用通用经验）。

## soh/assets/custom 中自定义（CHI 中文）纹理如何被使用

资产管线（参考 `do_action_static` 的 CHI 纹理做法）：
1. PNG 放在 `soh/assets/custom/textures/<folder>/`，**纹理必须带 N64 格式后缀**才会被 ZAPD 当成纹理打包；裸 `.png`（无后缀）会被当成**原始二进制文件**原样塞进 o2r（不是纹理、不占纹理名），与 `.ia8.png` 纹理**不会重名冲突**，只是多占约 1~2KB。所以「保留原图 `xxx.png` + 另生成 `xxx.ia8.png`」是安全且不破坏原图的标准做法；想让 o2r 干净就把源 PNG 移到 `assets/custom` 之外。
   - 后缀约定（ZAPD 约定）：`.ia4.png`(IA4)、`.ia8.png`(IA8/8bpp=4位亮度+4位透明)、`.ia16.png`(IA16)、`.i4/.i8/.rgba16/.rgba32`。
   - ⚠️ **实测更正（2026-07-16）**：本项目里 ZAPD 把 `ovl_End_Title` 的 `sXxxCHITex.ia8.png` 实际打包成 **I8（1 字节/texel，灰度）**，并非 IA8（2 字节）。证据：`soh.o2r` 里 `sTheEndCHITex` 大小 2112B = 81×25×1、`sTheLegendOfZeldaCHITex` 3112B = 121×25×1、`sOcarinaOfTimeCHITex` 2008B = 113×17×1，且像素字节为 0/255 灰度。故 `.ia8.png` 必须按 **`G_IM_FMT_I, G_IM_SIZ_8b`** 加载，否则跨度翻倍 → 斜杠乱码。**其他文件夹（如 title_static）的 `.ia8.png`/`.ia16.png` 是否也是 I8 尚未逐一验证，接生前务必按 o2r 实际字节数/（w*h）核算 bytesPerTexel，不要默认 IA8。**
   - I8 加载用 `G_IM_FMT_I, G_IM_SIZ_8b`；I 格式把强度同时当 alpha，故黑底(I=0)→透明（火焰透出）、白字(I=255)→不透明。
   - **⚠️ ZAPD `botr`（GenerateSohOtr 自定义 otr 生成）遇到 `.i8.png` 会报 "Error when building custom otr file..." 崩溃 —— 但根因是源 PNG 用了灰度 `L` 模式，ZAPD 的 PNG 读取器处理灰度图时崩。解法：源 PNG 必须是 **RGBA 模式**（把亮度铺到 R/G/B 三通道、alpha=255，背景纯黑 RGB=0），文件名仍用 `.i8.png`，ZAPD 的 I8 路径读 `.r` 通道即可正常打包。所以 I8 可用，不要因为它“崩溃”就放弃。I8 加载用 `G_IM_FMT_I, G_IM_SIZ_8b`；I 格式把强度同时当 alpha，故黑底(I=0)→透明（火焰透出）、白字(I=255)→不透明，视觉与 IA8 等价。
2. 在 `soh/assets/textures/<folder>/<folder>.h` 中声明符号，映射到 `__OTR__textures/<folder>/<Name>`：
   ```
   #define dg<Name> "__OTR__textures/<folder>/<Name>"
   static const ALIGN_ASSET(2) char <Name>[] = dg<Name>;
   ```
3. 运行时在 overlay 绘制代码里按 `gSaveContext.language`（ENG=0,GER=1,FRA=2,JPN=3,CHI=4）选择对应纹理数组项。
4. 构建时 CMake 用 `OTRExporter/extract_assets.py ... --custom-otr-file soh.o2r --custom-assets-path soh/assets/custom` 把整棵 custom 目录递归打包进 OTR；符号即按相对路径成为资源名。

相关脚本：`scripts/chinese/texture_extract/extract.py`（从 iQue ROM 按 XML 抽取，输出带格式后缀的 PNG）、`scripts/chinese/hd_textures/generate_hd_menu_o2r.py`（生成 HD 纹理 o2r，依赖 custom CHI PNG 的格式后缀判断类型）。

## 文件选择菜单（title_static）CHI 纹理接入（2026-07-14）
- 用户在 `soh/assets/custom/textures/title_static/` 添加了 34 个 `gFileSel*CHITex` 图（最初是纯 `.png`，已按格式重命名为 `.ia8.png`/`.ia16.png`）。
- 在 `soh/assets/textures/title_static/title_static.h` 末尾新增 34 个 CHI 符号声明（// #region SOH [Chinese]）。
- 在 `z_file_choose.c` 接入：`sTitleLabels`/`sWarningLabels`/`sFileButtonTextures`/`sActionButtonTextures`/`sOptionsButtonTextures` 的 CHI 行、`controlsTextures` 的 CHI 项。
- 在 `z_file_nameset_PAL.c` 接入：`sNameLabelTextures`/`sBackspaceEndTextures` CHI 项、`gOptionsMenuHeaders`(Options/SOUND/LTargeting→用 gFileSelZTargetingCHITex/CheckBrightness)、`gOptionsMenuSettings`(Stereo/Headset/Surround/Switch/Hold)。
- 注意：`gFileSelCheckBrightnessCHITex` 实际宽 96px，已把 `gOptionsMenuHeaders[3]` 的 CHI 宽度由 128 改为 96。
- `gFileSelZTargetingCHITex` 未被原代码引用（原代码用 `gFileSelLTargetingENGTex`），已作为 L-Targeting 选项的 CHI 变体接入。
- `FileChoose_GetQuestChooseTitleTexName`/`GetSohOptionsTitleTexName` 无 CHI 分支，CHI 回退 ENG（用户未提供对应 CHI 图）。

## 结局画面（ovl_End_Title）CHI 纹理接入（2026-07-16，**最终 I8，纯黑白源图**）
- 中文模式下用 `ovl_End_Title` 的 3 张中文图替换英文原版（`z_end_title.c` 的 `EndTitle_Draw...` 绘制块）：`sTheLegendOfZeldaCHITex`(120×24)、`sOcarinaOfTimeCHITex`(112×16)、`sTheEndCHITex`(80×24) —— **尺寸必须与英文原版完全一致**（之前误用 121×25/113×17/81×25 这个 +1 尺寸，导致每行错位 1px 斜向剪切）。中文文字：塞尔达传说 / 时之笛 / 结束。
- **⚠️ 源 PNG 必须是纯黑白（关键！）**：像素必须是 `R=G=B=A=255`（文字）/ `0`（背景），即真正 1-bit 黑白。生成器 `scripts/chinese/texture_extract/gen_end_title_chi.py`（用 `simhei.ttf` 渲染，再把每个像素强制归一到 255/0）。**之前的 Bug B「只显示一团橙色糊块、没字只有特效」正是源 PNG 用了灰度抗锯齿（R 通道是 67/51/17 之类的中间灰、alpha=覆盖度），ZAPD 打包 I8 取到的不是清晰白字黑底，结果是一团灰块**——所以一定要纯黑白，I8 数据才会是清晰的 255/0。
- **I8 打包确认**：ZAPD 把 `.ia8.png` 打包成 **I8（1 字节/texel）**，Type 标为 8(IA8) 但 `RawDataSize`=宽×高×1。o2r 纹理头 = 64 字节(0x40) + `uint32 Type/Width/Height/RawDataSize`，像素数据从 0x50 开始。代码用 `G_IM_FMT_I, G_IM_SIZ_8b` 加载。
- **combine（CHI 分支）**：`RGB=ENVIRONMENT(orange 255,120,30), Alpha=TEXEL0(intensity)*PRIMITIVE(fade-in)`，即橙字 + alpha=灰度×endAlpha。英文原版仍走 IA8 分支。
- 符号声明加在 `soh/assets/overlays/ovl_End_Title/ovl_End_Title.h`（// #region SOH [Chinese]），路径用 `textures/` 前缀：`__OTR__textures/overlays/ovl_End_Title/<Name>`（CHI 是 custom 资源；英文原版用 `__OTR__overlays/ovl_End_Title/<Name>` 无 `textures/` 前缀）。`LANGUAGE_CHI` 在 `z64.h` 全局定义。

## ⚠️ 职员表（staff credits）中文渲染路径修正（2026-07-16）
- 职员表是**消息系统文本**（id 0x0500–0x052F），不是纹理 → 所以通关后职员表是以**对话框/字幕框**形式显示（这是正常表现，不是 bug）。
- `z_message_PAL.c` 的中文双字节解码分支原本被 `!sTextIsCredits` 排除（line ~2730），导致职员表即使塞了中文字节也走 `Font_LoadChar(temp_s2-' ')` → 乱码/英文。**修复**：去掉 `!sTextIsCredits` 条件，让职员表也走 `gSaveContext.language==LANGUAGE_CHI && ... >=0xA0` 的 2 字节解码（`Font_LoadCharChinese` + `0xFE` 全宽标记）。已验证英文职员表里仅有的 `>=0xA0` 字节都是 `0x11(FADE2)` 的参数，已被控制码分支消费，故该改动对英文职员表无副作用。
- 数据来源：`soh/soh/z_staff_CHI.cpp`（方法 B 内嵌，48 条）。当前是**英文占位**（按之前「先英文验证」计划），需替换为中文字节数组。生成器 `scripts/chinese/message/generate_staff_chi.py` 现从 `oot.o2r` 抽英文；换中文时改其数据来源（中文 staff .bin 或翻译后的字节）。

## ⚠️ GenerateSohOtr 打包新文件夹的瞬时丢失坑（2026-07-16）
- 首次对 custom 目录新增文件夹（如 `ovl_End_Title`）后立即 `run_gen_o2r.bat`，custom OTR 生成用的 `Directory::ListFiles`（`fs::recursive_directory_iterator`）可能瞬时漏掉刚写入的新文件夹，导致新纹理没进 o2r（日志里该文件夹完全不出现、且无报错、`GEN_EXIT=0`）。**解法：删除所有 `soh.o2r`（含 `soh/soh.o2r`、`x64/Release/soh.o2r`、`build/soh/soh.o2r`）后重跑一次 `run_gen_o2r.bat` 即可正常收录**。
- 验证打包：用 `zipfile` 读 `x64/Release/soh.o2r` 列 namelist，按资源路径（如 `textures/overlays/ovl_End_Title/<Name>`、裸 `.png` 也会作为原始 blob 进包）核对。注意纹理符号名多用 `CHN`（如 `gTitlePressStartCHNTex`），grep 时用 `CHN` 而非 `CHI`，否则会误判"缺失"。
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
