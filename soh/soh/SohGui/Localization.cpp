#include "Localization.h"

#include <string>
#include <unordered_map>

#include "ship/window/gui/IconsFontAwesome4.h"

namespace SohGui {

static bool gMenuChinese = false;

void SetMenuLanguage(bool chinese) {
    gMenuChinese = chinese;
}

bool IsMenuChinese() {
    return gMenuChinese;
}

// Simplified Chinese translation table. The key must exactly match the English source string used in
// the UI code (including newlines '\n' and format specifiers such as "%d %%"). Entries missing from
// this table are displayed in their original English.
static const std::unordered_map<std::string, std::string> gChineseTable = {
    // ---- Top-level menu headers ----
    { "Settings", "设置" },
    { "Enhancements", "增强功能" },
    { "Randomizer", "随机生成" },
    { "Dev Tools", "开发工具" },
    { "Network", "网络" },
    { "Wind Waker Style", "风之杖风格" },

    // ---- Preset section labels (Presets.cpp) ----
    { "Cosmetics", "外观" },
    { "Rando Settings", "随机设置" },
    { "Trackers", "追踪器" },
    { "Save Settings", "保存设置" },
    { "Save Enhancements", "保存增强功能" },
    { "Save Audio", "保存音频" },
    { "Save Cosmetics", "保存外观" },
    { "Save Rando Settings", "保存随机设置" },
    { "Save Trackers", "保存追踪器" },
    { "Save Network", "保存网络" },

    // ---- Settings sidebars ----
    { "General", "常规" },
    { "Audio", "音频" },
    { "Graphics", "画面" },
    { "Controls", "操作" },
    { "Input Viewer", "输入显示器" },
    { "Notifications", "通知" },
    { "Mod Menu", "MOD 菜单" },

    // ---- Enhancements sidebars ----
    { "Skips & Speed-ups", "跳过与加速" },
    { "Items", "道具" },
    { "Fixes", "修复" },
    { "Difficulty", "难度" },
    { "Minigames", "小游戏" },
    { "Extra Modes", "额外模式" },
    { "Cheats", "作弊" },
    { "Cosmetics Editor", "外观编辑器" },
    { "Audio Editor", "音频编辑器" },
    { "Gameplay Stats", "游戏统计" },
    { "Time Splits", "时间分段" },
    { "Timers", "计时器" },

    // ---- Randomizer sidebars ----
    { "Locations", "地点" },
    { "Tricks/Glitches", "技巧/漏洞" },
    { "Plandomizer", "计划随机" },
    { "Item Tracker", "道具追踪" },
    { "Entrance Tracker", "入口追踪" },
    { "Check Tracker", "检查追踪" },

    // ---- Dev Tools sidebars ----
    { "Stats", "统计" },
    { "Console", "控制台" },
    { "Save Editor", "存档编辑器" },
    { "Hook Debugger", "钩子调试器" },
    { "Collision Viewer", "碰撞查看器" },
    { "Actor Viewer", "角色查看器" },
    { "DList Viewer", "显示列表查看器" },
    { "Value Viewer", "数值查看器" },
    { "Message Viewer", "信息查看器" },
    { "Gfx Debugger", "图形调试器" },

    // ---- Network sidebars ----
    { "Crowd Control", "人群控制" },
    { "Anchor", "锚点" },

    // ---- Wind Waker Style sidebars ----
    { "Cel Shading", "卡通渲染" },
    { "Lights", "光照" },
    { "Actor Shadows", "角色阴影" },
    { "Sky", "天空" },

    // ---- General section ----
    { "Menu Settings", "菜单设置" },
    { "Menu Theme", "菜单主题" },
    { "Changes the Theme of the Menu Widgets.", "更改菜单组件的主题。" },
    { "Menu Controller Navigation", "菜单手柄导航" },
    { "Allows controller navigation of the port menu (Settings, Enhancements,...)\nCAUTION: This will disable game "
      "inputs while the menu is visible.\n\nD-pad to move between items, A to select, B to move up in scope.",
      "允许使用手柄在移植菜单（设置、增强功能……）中导航。\n注意：菜单显示时这将禁用游戏输入。\n\n使用方向键在选项间移动，A "
      "键选择，B 键返回上一级。" },
    { "Allow background inputs", "允许后台输入" },
    { "Allows controller inputs to be picked up by the game even when the game window isn't the focused window.",
      "即使游戏窗口不是当前焦点窗口，也允许游戏接收手柄输入。" },
    { "Menu Background Opacity", "菜单背景不透明度" },
    { "Sets the opacity of the background of the port menu.", "设置移植菜单背景的不透明度。" },
    { "General Settings", "常规设置" },
    { "Cursor Always Visible", "始终显示光标" },
    { "Makes the cursor always visible, even in full screen.", "使光标始终可见，即使在全屏模式下。" },
    { "Search In Sidebar", "在侧边栏中搜索" },
    { "Displays the Search menu as a sidebar entry in Settings instead of in the header.",
      "将搜索菜单显示为设置中的侧边栏项，而非顶部标题栏。" },
    { "Search Input Autofocus", "搜索输入框自动聚焦" },
    { "Search input box gets autofocus when visible. Does not affect using other widgets.",
      "搜索输入框显示时自动获得焦点。不影响使用其他组件。" },
    { "Reset Button Combination:", "重置按键组合：" },
    { "Open App Files Folder", "打开应用文件文件夹" },
    { "Opens the folder that contains the save and mods folders, etc.",
      "打开包含存档和 MOD 等文件夹的目录。" },
    { "Boot", "启动" },
    { "Boot Sequence", "启动序列" },
    { "Configure what happens when starting or resetting the game.\n\nDefault: LUS logo -> N64 logo\nAuthentic: N64 "
      "logo only\nFile Select: Skip to file select menu\nDebug Warp Screen: Skip to the debug warp screen\nWarp "
      "Point: Skip to active warp point (if set), see Dev Tools -> General",
      "配置启动或重置游戏时的行为。\n\n默认：LUS 标志 -> N64 标志\n原版：仅 N64 标志\n文件选择：跳转到文件选择菜单\n调试传送界面："
      "跳转到调试传送界面\n传送点：跳转到当前激活的传送点（若已设置），详见开发工具 -> 常规" },
    { "Languages", "语言" },
    { "Translate Title Screen", "翻译标题画面" },
    { "Language", "游戏文本语言" },
    { "Menu Language", "菜单语言" },
    { "Sets the language used for the settings/menu interface.", "设置菜单界面所使用的语言。" },
    { "Accessibility", "辅助功能" },
    { "Text to Speech", "文字转语音" },
    { "Enables text to speech for in game dialog", "为游戏内对话启用文字转语音。" },
    { "Disable Idle Camera Re-Centering", "禁用闲置镜头回正" },
    { "Disables the automatic re-centering of the camera when idle.", "禁用镜头在闲置时自动回正。" },
    { "Disable Screen Flash for Finishing Blow", "禁用击杀白屏闪烁" },
    { "Disables the white screen flash on enemy kill.", "禁用击败敌人时的白色屏幕闪烁。" },
    { "Disable Jabu Wobble", "禁用 Jabu 晃动" },
    { "Disable the geometry wobble and camera distortion inside Jabu.", "禁用 Jabu 内部的几何体晃动和镜头扭曲。" },
    { "EXPERIMENTAL", "实验性功能" },
    { "ImGui Menu Scaling", "ImGui 菜单缩放" },
    { "Changes the scaling of the ImGui menu elements.", "更改 ImGui 菜单元素的缩放比例。" },
    { "About", "关于" },
    { "Ship Of Harkinian", "哈肯尼安之船" },

    // ---- Audio section ----
    { "Master Volume: %d %%", "主音量：%d %%" },
    { "Main Music Volume: %d %%", "主音乐音量：%d %%" },
    { "Sub Music Volume: %d %%", "副音乐音量：%d %%" },
    { "Fanfare Volume: %d %%", "典礼音乐音量：%d %%" },
    { "Sound Effects Volume: %d %%", "音效音量：%d %%" },
    { "Audio API (Needs reload)", "音频接口（需要重启）" },
    { "Audio API", "音频接口" },
    { "Sets the audio API used by the game. Requires a relaunch to take effect.",
      "设置游戏使用的音频接口。需要重新启动才能生效。" },
    { "Only one audio API is available on this platform.", "此平台仅有一个可用的音频接口。" },
    { "Sets the renderer API used by the game.", "设置游戏使用的渲染接口。" },
    { "Only one renderer API is available on this platform.", "此平台仅有一个可用的渲染接口。" },

    // ---- Graphics section ----
    { "Graphics Options", "画面选项" },
    { "Toggle Fullscreen", "切换全屏" },
    { "Toggles Fullscreen On/Off.", "开启/关闭全屏模式。" },
    { "Internal Resolution", "内部分辨率" },
    { "Multiplies your output resolution by the value inputted, as a more intensive but effective form of "
      "anti-aliasing.",
      "将输出分辨率乘以输入的值，作为一种更消耗性能但更有效的抗锯齿方式。" },
    { "Anti-aliasing (MSAA)", "抗锯齿（MSAA）" },
    { "Activates MSAA (multi-sample anti-aliasing) from 2x up to 8x, to smooth the edges of rendered "
      "geometry.\nHigher sample count will result in smoother edges on models, but may reduce performance.",
      "启用 MSAA（多重采样抗锯齿），从 2x 到 8x，以平滑渲染几何体的边缘。\n采样数越高，模型边缘越平滑，但可能降低性能。" },
    { "Current FPS", "当前 FPS" },
    { "Uses Matrix Interpolation to create extra frames, resulting in smoother graphics. This is purely visual and "
      "does not impact game logic, execution of glitches etc.\n\nA higher target FPS than your monitor's refresh "
      "rate will waste resources, and might give a worse result.",
      "使用矩阵插值生成额外的帧，从而获得更流畅的画面。这纯粹是视觉上的，不影响游戏逻辑、漏洞的执行等。\n\n目标 FPS 高于显示器"
      "刷新率会浪费资源，并可能产生更差的效果。" },
    { "Match Refresh Rate", "匹配刷新率" },
    { "Matches interpolation value to the refresh rate of your display.", "将插值值与显示器的刷新率相匹配。" },
    { "Renderer API (Needs reload)", "渲染接口（需要重启）" },
    { "Enable Vsync", "启用垂直同步" },
    { "Removes tearing, but clamps your max FPS to your displays refresh rate.",
      "消除画面撕裂，但会将最大 FPS 限制在显示器的刷新率。" },
    { "Windowed Fullscreen", "窗口化全屏" },
    { "Enables Windowed Fullscreen Mode.", "启用窗口化全屏模式。" },
    { "Allow multi-windows", "允许多窗口" },
    { "Allows multiple windows to be opened at once. Requires a reload to take effect.",
      "允许同时打开多个窗口。需要重新加载才能生效。" },
    { "Texture Filter (Needs reload)", "纹理过滤（需要重启）" },
    { "Sets the applied Texture Filtering.", "设置所应用的纹理过滤方式。" },
    { "Advanced Graphics Options", "高级画面选项" },

    // ---- Controls section ----
    { "Clear Devices", "清除设备" },
    { "Controller Bindings", "控制器绑定" },
    { "Popout Bindings Window", "弹出绑定窗口" },
    { "Enables the separate Bindings Window.", "启用独立的绑定窗口。" },
    { "Toggle Input Viewer", "切换输入显示器" },
    { "Toggles the Input Viewer.", "切换输入显示器的显示。" },
    { "Popout Input Viewer Settings", "弹出输入显示器设置" },
    { "Enables the separate Input Viewer Settings Window.", "启用独立的输入显示器设置窗口。" },

    // ---- Notifications section ----
    { "Position", "位置" },
    { "Which corner of the screen notifications appear in.", "通知显示在屏幕的哪个角落。" },
    { "Duration (seconds):", "持续时间（秒）：" },
    { "How long notifications are displayed for.", "通知显示的时长。" },
    { "Background Opacity", "背景不透明度" },
    { "How opaque the background of notifications is.", "通知背景的不透明度。" },
    { "Size:", "大小：" },
    { "How large notifications are.", "通知的大小。" },
    { "Test Notification", "测试通知" },
    { "Displays a test notification.", "显示一个测试通知。" },
    { "Mute Notification Sound", "静音通知声音" },
    { "Prevent notifications from playing a sound.", "阻止通知播放声音。" },

    // ---- Mod Menu section ----
    { "Popout Mod Menu Window", "弹出 MOD 菜单窗口" },
    { "Enables the separate Mod Menu Window.", "启用独立的 MOD 菜单窗口。" },

    // ---- Window names / popout window titles ----
    { "Configure Controller", "配置控制器" },
    { "Port Menu", "移植菜单" },
    { "Console##SoH", "控制台##SoH" },
    { "Stats##Soh", "统计##Soh" },
    { "GfxDebugger##SoH", "图形调试器##SoH" },
    { "Mod Menu", "MOD 菜单" },
    { "Audio Editor", "音频编辑器" },
    { "Input Viewer Settings", "输入显示器设置" },
    { "Cosmetics Editor", "外观编辑器" },
    { "Actor Viewer", "角色查看器" },
    { "Collision Viewer", "碰撞查看器" },

    // ---- Collision Viewer 窗口 ----
    { "Enabled", "启用" },
    { "Scene", "场景" },
    { "Bg Actors", "背景物体" },
    { "Col Check", "碰撞检测" },
    { "Waterbox", "水体" },
    { "Scarecrow Spawn", "稻草人生成点" },
    { "Apply as decal", "作为贴花应用" },
    { "Applies the collision as a decal display. This can be useful if there is z-fighting occuring with the scene geometry, but can cause other artifacts.",
      "将碰撞以贴花方式显示。当场景几何体出现 z-fighting（深度冲突）时这很有用，但可能引起其它显示瑕疵。" },
    { "Shaded", "着色" },
    { "Applies the scene's shading to the collision display.", "将场景的着色应用到碰撞显示上。" },
    { "Colors", "颜色" },
    { "Normal", "正常" },
    { "Hookshot", "短钩" },
    { "Entrance", "入口" },
    { "Special Surface (Grass/Sand/Etc)", "特殊表面（草/沙/等）" },
    { "Interactable (Vines/Crawlspace/Etc)", "可交互物（藤蔓/爬行空间/等）" },
    { "Slope", "斜坡" },
    { "Void", "虚空" },
    { "OC", "物体" },
    { "AC", "角色" },
    { "AT", "攻击" },
    { "Solid", "实心" },
    { "Transparent", "透明" },
    { "View and change the colors used for collision display.", "查看并更改用于碰撞显示的颜色。" },
    { "Resets this color to its default value", "将此颜色重置为默认值。" },
    { "Generates a random color value to use", "生成随机颜色值以使用。" },

    // ---- Actor Viewer 窗口 ----
    { "Actor Name Tags", "角色名称标签" },
    { "Display Items", "显示项目" },
    { "Name tags with Z-Buffer", "带 Z 缓冲的名称标签" },
    { "Adds \"name tags\" above actors for identification", "在角色头顶添加\"名称标签\"以便识别" },
    { "Click to add display items on the name tags", "点击在名称标签上添加显示项" },
    { "Allow name tags to be obstructed when behind geometry and actors", "允许名称标签被几何体与角色遮挡" },
    { "Actor Type", "角色类型" },
    { "Please select", "请选择" },
    { "Actor", "角色" },
    { "Selected Actor", "已选角色" },
    { "Select an actor to display information.", "选择一个角色以显示信息。" },
    { "Fetch from Target", "从目标获取" },
    { "Fetch from Held", "从手持获取" },
    { "Fetch from Interaction", "从交互获取" },
    { "Grabs actor with target arrow above it. You might need C-Up for enemies", "抓取头顶有目标箭头的角色。对敌人可能需要按 C-Up" },
    { "Grabs actor that Link is holding", "抓取林克手持的角色" },
    { "Grabs actor from \"interaction range\"", "抓取「交互范围」内的角色" },
    { "Changes the actor specific param menus with a direct input", "切换为直接输入的角色特定参数菜单" },
    { "New...", "新建..." },
    { "Search Actor", "搜索角色" },
    { "params", "参数" },
    { "New Actor Position", "新角色位置" },
    { "New Actor Rotation", "新角色旋转" },
    { "Fetch from Link", "从林克获取" },
    { "Actor Position", "角色位置" },
    { "Actor Rotation", "角色旋转" },
    { "Actor Specific Data", "角色特定数据" },
    { "Background (Prop type 1)", "背景（道具类型 1）" },
    { "Player", "玩家" },
    { "Bomb", "炸弹" },
    { "NPC", "NPC" },
    { "Enemy", "敌人" },
    { "Prop type 2", "道具类型 2" },
    { "Item/Action", "道具/动作" },
    { "Misc.", "杂项" },
    { "Boss", "Boss" },
    { "Door", "门" },
    { "Chest", "宝箱" },

    { "Save Editor", "存档编辑器" },
    { "Flags", "标志" },
    { "Quest Status", "任务状态" },
    { "Game Inactive", "游戏未激活" },
    { "Debug File", "调试文件" },
    { "File Number", "文件编号" },
    { "Name", "名称" },
    { "Player Name", "玩家名" },
    { "Player Name Language", "玩家名语言" },
    { "Encoding used for Player Name", "玩家名使用的编码" },
    { "Max Health", "最大生命" },
    { "Maximum health. 16 units per full heart", "最大生命值。每 16 单位为一颗心" },
    { "Double Defense", "双重防御" },
    { "Is double defense unlocked? Replaces Giant's knife", "是否已解锁双重防御？（替代巨人刀）" },
    { "Magic Level", "魔法等级" },
    { "Current magic level", "当前魔法等级" },
    { "Single", "单倍" },
    { "Double", "双倍" },
    { "Current magic. 48 units per magic level", "当前魔法值。每级魔法 48 单位" },
    { "Rupees", "卢比" },
    { "Current rupees", "当前卢比数量" },
    { "Dawn", "黎明" },
    { "Noon", "正午" },
    { "Sunset", "黄昏" },
    { "Midnight", "午夜" },
    { "Total Days", "总天数" },
    { "Total number of days elapsed since the start of the game", "自游戏开始以来经过的总天数" },
    { "Deaths", "死亡次数" },
    { "Total number of deaths", "总死亡次数" },
    { "Has BGS", "拥有大格雷之剑" },
    { "Is Biggoron sword unlocked? Replaces Giant's knife", "是否已解锁大格雷之剑？替代巨人之刀" },
    { "Sword Health", "剑的耐久" },
    { "Giant's knife health. Default is 8. Must be >0 for Biggoron sword to work", "巨人刀的耐久。默认为 8。大格雷之剑需大于 0 方可生效" },
    { "Bgs Day Count", "大格雷之剑天数计数" },
    { "Total number of days elapsed since receiving claim check from Biggoron", "自大格雷处收到取货单以来经过的总天数" },
    { "Entrance Index", "入口索引" },
    { "From which entrance did Link arrive?", "林克是从哪个入口到达的？" },
    { "Cutscene Index", "过场动画索引" },
    { "Which cutscene is this?", "这是哪一个过场动画？" },
    { "Navi Timer", "娜薇计时器" },
    { "Navi wants to talk at 600 units, decides not to at 3000.", "娜薇在 600 单位时欲对话，3000 单位时决定不对话。" },
    { "Timer State", "计时器状态" },
    { "Heat timer, race timer, etc. Has white font", "过热计时器、竞速计时器等，以白色字体显示" },
    { "Timer Seconds", "计时器秒数" },
    { "Time, in seconds", "时间，以秒为单位" },
    { "Sub-Timer State", "子计时器状态" },
    { "Trade timer, Ganon collapse timer, etc. Has yellow font", "交易计时器、盖侬崩溃计时器等，以黄色字体显示" },
    { "Sub-Timer Seconds", "子计时器秒数" },
    { "Sound setting", "声音设置" },
    { "Stereo", "立体声" },
    { "Mono", "单声道" },
    { "Headset", "耳机" },
    { "Surround", "环绕声" },
    { "64 DD file?", "64DD 文件？" },
    { "WARNING! If you save, your file may be locked! Use caution!", "警告！保存后你的存档可能会被锁定！请谨慎操作！" },
    { "Z Target Mode", "Z 瞄准模式" },
    { "Z-Targeting behavior", "Z 瞄准行为" },
    { "Hold", "按住" },
    { "Triforce Pieces", "三角力量碎片" },
    { "Currently obtained Triforce Pieces. For Triforce Hunt.", "当前已获得的三角神力碎片。用于三角神力狩猎。" },
    { "Minigames", "小游戏" },
    { "Horseback Archery", "骑马射箭" },
    { "Big Poe Points", "大妖婆点数" },
    { "Fishing", "钓鱼" },
    { "Malon's Obstacle Course", "玛隆的障碍赛道" },
    { "Running Man Race", "奔跑男子竞速" },
    { "Dampe's Race", "达培的竞速" },
    { "PAL", "PAL" },
    { "NTSC JPN", "NTSC 日版" },
    { "NTSC ENG", "NTSC 英版" },
    { "File 1", "文件 1" },
    { "File 2", "文件 2" },
    { "File 3", "文件 3" },
    { "Player State", "玩家状态" },
    { "Current Scene", "当前场景" },
    { "Switch", "开关" },
    { "Temp Switch", "临时开关" },
    { "Clear", "清除" },
    { "Temp Clear", "临时清除" },
    { "Collect", "收集" },
    { "Temp Collect", "临时收集" },
    { "Chest", "宝箱" },
    { "Set All", "全部设置" },
    { "Clear All", "全部清除" },
    { "Reload Flags", "重新加载标志" },
    { "Save Flags", "保存标志" },
    { "Clear Flags", "清除标志" },
    { "Saved Scene Flags", "已保存的场景标志" },
    { "Map", "地图" },
    { "Current", "当前" },
    { "Rooms", "房间" },
    { "Floors", "楼层" },
    { "Gold Skulltulas", "金色骷髅蜘蛛" },
    { "Flags", "标志" },
    { "Keep GS Count Updated", "保持金色骷髅计数更新" },
    { "Automatically adjust the number of gold skulltula tokens acquired based on set flags.", "根据已设置的标志自动调整已获得的金色骷髅令牌数。" },
    { "Event Check Inf Flags", "事件检查信息标志" },
    { "Item Get Inf Flags", "道具获取信息标志" },
    { "Inf Flags", "信息标志" },
    { "Event Inf Flags", "事件信息标志" },
    { "stateFlags1", "状态标志1" },
    { "stateFlags2", "状态标志2" },
    { "stateFlags3", "状态标志3" },
    { "unk_6AE_rotFlags", "未知_6AE_旋转标志" },
    { "Deku Tree", "德库树" },
    { "Dodongo's Cavern", "多东哥洞窟" },
    { "Inside Jabu-Jabu's Belly", "加卜加卜腹内" },
    { "Forest Temple", "森林神殿" },
    { "Fire Temple", "火之神殿" },
    { "Water Temple", "水之神殿" },
    { "Spirit Temple", "魂之神殿" },
    { "Shadow Temple", "暗之神殿" },
    { "Bottom of the Well", "井底" },
    { "Ice Cavern", "冰之洞窟" },
    { "Hyrule Field", "海拉鲁平原" },
    { "Lon Lon Ranch", "隆隆牧场" },
    { "Kokiri Forest", "科克里森林" },
    { "Lost Woods, Sacred Forest Meadow", "失落的森林，神圣森林草地" },
    { "Castle Town and Ganon's Castle", "城邑与盖侬城堡" },
    { "Death Mountain Trail, Goron City", "死神山径，格雷城" },
    { "Kakariko Village", "卡卡利科村" },
    { "Zora Fountain, River", "卓拉之泉，河流" },
    { "Lake Hylia", "海拉鲁湖" },
    { "Gerudo Valley", "格鲁德大峡谷" },
    { "Gerudo Fortress", "格鲁德要塞" },
    { "Desert Colossus, Haunted Wasteland", "巨大邪神像，幻影沙漠" },
    { "Bullet Bag", "子弹袋" },
    { "Quiver", "箭袋" },
    { "Bomb Bag", "炸弹口袋" },
    { "Scale", "鱼鳞" },
    { "Strength", "力量" },
    { "Wallet", "钱包" },
    { "Deku Stick Capacity", "德库木棒容量" },
    { "Deku Nut Capacity", "德库坚果容量" },
    { "Bombchu Bag Capacity", "炸弹鼠袋容量" },
    { "Child (99)", "儿童（99）" },
    { "Adult (200)", "成人（200）" },
    { "Giant (500)", "巨大（500）" },
    { "Tycoon (999)", "巨富（999）" },
    { "Link's Position", "林克的位置" },
    { "Link's Rotation", "林克的旋转" },
    { "Link's Model Rotation", "林克模型的旋转" },
    { "Linear Velocity", "线速度" },
    { "Y Velocity", "Y 轴速度" },
    { "Wall Height", "墙面高度" },
    { "Invincibility Timer", "无敌计时器" },
    { "Gravity", "重力" },
    { "Adult", "成人" },
    { "Child", "儿童" },
    { "Link Age on Load", "载入时的林克年龄" },
    { "Link's Current Equipment", "林克当前装备" },
    { "Sword", "剑" },
    { "Shield", "盾" },
    { "Tunic", "外衣" },
    { "Boots", "靴子" },
    { "Kokiri Sword", "科克里之剑" },
    { "Master Sword", "大师之剑" },
    { "Biggoron's Sword", "大格雷之剑" },
    { "Fishing Pole", "钓竿" },
    { "Deku Shield", "德库盾" },
    { "Hylian Shield", "海拉鲁盾" },
    { "Mirror Shield", "镜盾" },
    { "Kokiri Tunic", "科克里外衣" },
    { "Goron Tunic", "格雷外套" },
    { "Zora Tunic", "卓拉外套" },
    { "Kokiri Boots", "科克里靴" },
    { "Iron Boots", "铁靴" },
    { "Hover Boots", "悬浮靴" },
    { "Current Items", "当前道具" },
    { "B Button", "B 按钮" },
    { "C Left", "C 左" },
    { "C Down", "C 下" },
    { "C Right", "C 右" },
    { "Current D-pad Items", "当前十字键道具" },
    { "D-pad Up  ", "十字键上" },
    { "D-pad Down", "十字键下" },
    { "D-pad Left", "十字键左" },
    { "D-pad Right", "十字键右" },
    { "State Flags", "状态标志" },
    { "Adult trade quest items", "成人交换任务道具" },
    { "Ammo", "弹药" },
    { "Restrict to valid items", "限制为有效道具" },
    { "Restricts items and ammo to only what is possible to legally acquire in-game", "将道具与弹药限制为游戏内可合法获取的范围" },
    { "No flags match the current search.", "没有标志匹配当前搜索。" },
    { "Current game state does not have an active scene", "当前游戏状态没有活动场景" },
    { "GS Count", "金色骷髅数" },
    { "PoH count", "心之碎片数" },
    { "Barinade's Lair does not have small keys", "巴里内德巢穴没有小钥匙" },
    { "Glitched", "异常" },
    { "Permanently-saved switch flags", "永久保存的开关标志" },
    { "Temporary switch flags. Unset on scene transitions", "临时开关标志。场景切换时清除" },
    { "Permanently-saved room-clear flags", "永久保存的房间清除标志" },
    { "Temporary room-clear flags. Unset on scene transitions", "临时房间清除标志。场景切换时清除" },
    { "Permanently-saved collect flags", "永久保存的收集标志" },
    { "Temporary collect flags. Unset on scene transitions", "临时收集标志。场景切换时清除" },
    { "Permanently-saved chest flags", "永久保存的宝箱标志" },
    { "Switch flags", "开关标志" },
    { "Room-clear flags", "房间清除标志" },
    { "Collect flags", "收集标志" },
    { "Chest flags", "宝箱标志" },
    { "Flags for visted rooms", "已访问房间的标志" },
    { "Flags for visted floors", "已访问楼层的标志" },
    { "Number of gold skulltula tokens aquired", "已获得的金色骷髅代币数量" },
    { "GS unlocked", "金色骷髅已解锁" },
    { "If unlocked, enables showing the gold skulltula count in the quest status menu", "若解锁，在任务状态菜单显示金色骷髅数量" },
    { "The number of pieces of heart acquired towards the next heart container", "距下一个心之容器已获得的心之碎片数量" },
    { "For Link's rotation in relation to the world", "林克相对世界的旋转" },
    { "For Link's actual model", "林克实际模型的旋转" },
    { "Link's speed along the XZ plane", "林克在 XZ 平面的速度" },
    { "Link's speed along the Y plane. Caps at -20", "林克在 Y 轴的速度。上限 -20" },
    { "Height used to determine whether Link can climb or grab a ledge at the top", "用于判断林克能否攀爬或抓住顶部边缘的高度" },
    { "Can't take damage while this is nonzero", "此值非零时无法受到伤害" },
    { "Rate at which Link falls. Default -4.0f", "林克下落的速率。默认 -4.0f" },
    { "This will change Link's age when you load a map", "加载地图时将改变林克的年龄" },
    { "Current File Number", "当前文件编号" },
    { "Encoding used for Player Name", "玩家名称使用的编码" },
    { "Current health. 16 units per full heart", "当前生命值。每颗心 16 单位" },
    { "Is double defense unlocked?", "是否已解锁双重防御？" },
    { "Current magic level", "当前魔法等级" },
    { "Current magic. 48 units per magic level", "当前魔法值。每级魔法 48 单位" },
    { "Time of day", "一天中的时间" },
    { "Is Biggoron sword unlocked? Replaces Giant's knife", "是否已解锁大格雷之剑？替代巨人之刀" },
    { "Sound setting", "声音设置" },
    { "WARNING! If you save, your file may be locked! Use caution!", "警告！保存后存档可能被锁定！请谨慎操作！" },
    { "Z-Targeting behavior", "Z 瞄准行为" },
    { "Used the Sinking lure to catch it.", "使用了沉钩 lure 钓到它。" },
    { "Played at least one game as a child", "童年时期至少玩过一次" },
    { "Played at least one game as an adult", "成年时期至少玩过一次" },
    { "Got the prize item (Golden Scale, unless rando.)\nUnlocks Sinking Lure for Adult Link.", "获得奖品道具（金色鳞片，随机模式除外）。\n为成年林克解锁沉钩 lure。" },
    { "The owner's now visibly bald when Adult Link.", "成年林克时，店主明显秃头。" },
    { "Save current scene flags. Normally happens on scene exit", "保存当前场景标志。通常在离开场景时发生" },
    { "Clear current scene flags. Reload scene to see changes", "清除当前场景标志。重新加载场景以查看更改" },
    { "Open flags for current scene", "打开当前场景的标志" },
    { "Determines weather and school size during dawn/dusk.", "决定黎明/黄昏时的天气与鱼塘大小。" },
    { "Bombchu Bag Capapcity", "炸弹鼠袋容量" },
    { "Hook Debugger", "钩子调试器" },
    { "Expand All", "全部展开" },
    { "Collapse All", "全部折叠" },
    { "No hooks found", "未找到钩子" },
    { "Total Registered", "已注册总数" },
    { "ID", "ID" },
    { "Type", "类型" },
    { "Area", "区域" },
    { "To", "至" },
    { "From", "从" },
    { "Registration Info", "注册信息" },
    { "# Calls", "调用次数" },
    { "Normal", "普通" },
    { "Ptr", "指针" },
    { "Filter", "过滤器" },
    { "[UNKNOWN]", "[未知]" },
    { "[Unavailable]", "[不可用]" },
    { "OnZTitleInit", "标题画面初始化时" },
    { "OnZTitleUpdate", "标题画面更新时" },
    { "OnLoadGame", "载入游戏时" },
    { "OnExitGame", "退出游戏时" },
    { "OnGameStateMainStart", "游戏主状态开始时" },
    { "OnGameFrameUpdate", "游戏帧更新时" },
    { "OnCameraState", "摄像机状态时" },
    { "OnItemReceive", "获得道具时" },
    { "OnEquipmentDelete", "删除装备时" },
    { "OnSaleEnd", "交易结束时" },
    { "OnTransitionEnd", "场景切换结束时" },
    { "OnSceneInit", "场景初始化时" },
    { "AfterSceneCommands", "场景指令之后" },
    { "OnSceneFlagSet", "场景标志置位时" },
    { "OnSceneFlagUnset", "场景标志清除时" },
    { "OnFlagSet", "标志置位时" },
    { "OnFlagUnset", "标志清除时" },
    { "OnSceneSpawnActors", "场景生成角色时" },
    { "OnLinkSkeletonInit", "林克骨骼初始化时" },
    { "OnLinkEquipmentChange", "林克装备变化时" },
    { "OnPlayerUpdate", "林克更新时" },
    { "OnSetDoAction", "设置动作时" },
    { "OnPlayerSfx", "林克音效时" },
    { "OnOcarinaSongAction", "陶笛乐曲动作时" },
    { "OnOcarinaNote", "陶笛音符时" },
    { "OnCuccoOrChickenHatch", "古古鸡/鸡孵化时" },
    { "OnShopSlotChange", "商店槽位变化时" },
    { "OnDungeonKeyUsed", "使用地牢钥匙时" },
    { "ShouldActorInit", "应初始化角色时" },
    { "OnActorInit", "角色初始化时" },
    { "OnActorSpawn", "角色生成时" },
    { "ShouldActorUpdate", "应更新角色时" },
    { "OnActorUpdate", "角色更新时" },
    { "OnActorDraw", "角色绘制时" },
    { "OnActorKill", "角色击杀时" },
    { "OnActorDestroy", "角色销毁时" },
    { "OnEnemyDefeat", "敌人击败时" },
    { "OnBossDefeat", "Boss 击败时" },
    { "OnTimestamp", "时间戳时" },
    { "OnPlayerBonk", "林克撞击时" },
    { "OnPlayerSetModels", "林克设置模型时" },
    { "OnPlayerHealthChange", "林克生命变化时" },
    { "OnPlayerBottleUpdate", "林克空瓶更新时" },
    { "OnPlayerHoldUpShield", "林克举盾时" },
    { "OnPlayerFirstPersonControl", "林克第一人称控制时" },
    { "OnPlayerProcessStick", "林克处理摇杆时" },
    { "OnPlayerShieldControl", "林克盾牌控制时" },
    { "OnPlayDestroy", "游戏销毁时" },
    { "OnPlayDrawBegin", "游戏绘制开始时" },
    { "OnPlayDrawEnd", "游戏绘制结束时" },
    { "OnPlayDrawWorldLights", "游戏绘制世界光照时" },
    { "OnPlayDrawSkyGradient", "游戏绘制天空渐变时" },
    { "OnPlayDrawSky", "游戏绘制天空时" },
    { "OnPlayDrawSkyClouds", "游戏绘制天空云层时" },
    { "OnVanillaBehavior", "原版行为时" },
    { "OnSaveFile", "保存文件时" },
    { "OnLoadFile", "载入文件时" },
    { "OnDeleteFile", "删除文件时" },
    { "OnDialogMessage", "对话消息时" },
    { "OnPresentTitleCard", "显示标题卡时" },
    { "OnInterfaceUpdate", "界面更新时" },
    { "OnKaleidoscopeUpdate", "万花筒更新时" },
    { "OnPresentFileSelect", "显示文件选择时" },
    { "OnUpdateFileSelectSelection", "更新文件选择项时" },
    { "OnUpdateFileSelectConfirmationSelection", "更新文件选择确认项时" },
    { "OnUpdateFileCopySelection", "更新文件复制项时" },
    { "OnUpdateFileCopyConfirmationSelection", "更新文件复制确认项时" },
    { "OnUpdateFileEraseSelection", "更新文件删除项时" },
    { "OnUpdateFileEraseConfirmationSelection", "更新文件删除确认项时" },
    { "OnUpdateFileAudioSelection", "更新文件音频项时" },
    { "OnUpdateFileTargetSelection", "更新文件目标项时" },
    { "OnUpdateFileLanguageSelection", "更新文件语言项时" },
    { "OnUpdateFileQuestSelection", "更新文件任务项时" },
    { "OnUpdateFileBossRushOptionSelection", "更新文件 Boss 速通选项时" },
    { "OnUpdateFileRandomizerOptionSelection", "更新文件随机化选项时" },
    { "OnUpdateFileNameSelection", "更新文件名选择时" },
    { "OnFileChooseMain", "文件选择主界面时" },
    { "OnGenerationCompletion", "生成完成时" },
    { "OnSetGameLanguage", "设置游戏语言时" },
    { "OnAssetAltChange", "资源变体变化时" },
    { "OnKaleidoUpdate", "万花筒界面更新时" },
    { "OnOpenText", "打开文本时" },
    { "OnSeqPlayerInit", "音序播放器初始化时" },
    { "OnRandoSetCheckStatus", "随机化设置检查状态时" },
    { "OnRandoSetIsSkipped", "随机化设置是否跳过时" },
    { "OnRandoEntranceDiscovered", "随机化发现入口时" },
    { "Display List Viewer", "显示列表查看器" },
    { "Search Display Lists", "搜索显示列表" },
    { "Active Display List", "当前显示列表" },
    { "Value Viewer", "数值查看器" },
    { "Enable Printing", "启用打印" },
    { "Select a value", "选择一个数值" },
    { "Time", "时间" },
    { "Age", "年龄" },
    { "Navi Timer", "娜薇计时器" },
    { "Entrance ID", "入口 ID" },
    { "Cutscene ID", "过场动画 ID" },
    { "Link X", "林克 X" },
    { "Link Y", "林克 Y" },
    { "Link Z", "林克 Z" },
    { "Link Yaw", "林克偏航角" },
    { "Link Velocity", "林克速度" },
    { "Link X Velocity", "林克 X 速度" },
    { "Link Y Velocity", "林克 Y 速度" },
    { "Link Z Velocity", "林克 Z 速度" },
    { "Analog Stick X", "模拟摇杆 X" },
    { "Analog Stick Y", "模拟摇杆 Y" },
    { "getItemID", "获取道具 ID" },
    { "getItemEntry", "获取道具条目" },
    { "Message Viewer", "信息查看器" },
    { "Enter a string using Custom Message Syntax to preview it in-game. Any newline (\\n) characters inserted by the Enter key will be stripped from the output.", "输入使用自定义信息语法的字符串以在游戏内预览。通过回车键插入的换行符（\\n）将在输出中被移除。" },
    { "Gameplay Stats", "游戏统计" },
    { "Check Tracker", "检查追踪器" },
    { "Check Tracker Settings", "检查追踪器设置" },
    { "Entrance Tracker", "入口追踪器" },
    { "Entrance Tracker Settings", "入口追踪器设置" },
    { "Item Tracker", "道具追踪器" },
    { "Item Tracker Settings", "道具追踪器设置" },
    { "Time Splits", "时间分段" },
    { "Plandomizer Editor", "计划随机编辑器" },
    { "Notifications Window", "通知窗口" },
    { "Additional Timers", "附加计时器" },
    { "Anchor Room", "锚点房间" },
    { "Modal Window", "模态窗口" },

    // ---- Combobox option maps ----
    { "Small", "小" },
    { "Normal", "正常" },
    { "Large", "大" },
    { "X-Large", "特大" },
    { "Red", "红色" },
    { "Dark Red", "深红" },
    { "Orange", "橙色" },
    { "Green", "绿色" },
    { "Dark Green", "深绿" },
    { "Light Blue", "浅蓝" },
    { "Blue", "蓝色" },
    { "Dark Blue", "深蓝" },
    { "Indigo", "靛蓝" },
    { "Violet", "紫罗兰" },
    { "Purple", "紫色" },
    { "Brown", "棕色" },
    { "Gray", "灰色" },
    { "Dark Gray", "深灰" },
    { "Three-Point", "三点采样" },
    { "Linear", "线性" },
    { "None", "无" },
    { "Top Left", "左上" },
    { "Top Right", "右上" },
    { "Bottom Left", "左下" },
    { "Bottom Right", "右下" },
    { "Hidden", "隐藏" },
    { "Default", "默认" },
    { "Authentic", "原版" },
    { "File Select", "文件选择" },
    { "Debug Warp Screen", "调试传送界面" },
    { "Warp Point", "传送点" },
    { "English", "英语" },
    { "German", "德语" },
    { "French", "法语" },
    { "Japanese", "日语" },
    { "Chinese", "中文" },

    // ---- Menu chrome ----
    { "Search...", "搜索……" },
    { "Start typing to see results.", "开始输入以查看结果。" },
    { "Search Results", "搜索结果" },
    { "Clear Search", "清除搜索" },
    { "No results found", "未找到结果" },
    { "Clear", "清除" },
    { "Quit SoH", "退出 SoH" },
    { "Are you sure you want to quit SoH?", "确定要退出 SoH 吗？" },
    { "Quit", "退出" },
    { "Cancel", "取消" },
    { "Reset", "重置" },
    { "Close Menu (Esc)", "关闭菜单 (Esc)" },
    { "This", "这是" },
    { "is a", "一条" },
    { "test.", "测试通知。" },
    { "Clear Config", "清除配置" },
    // ===========================================================================
    //  Shared combobox option maps (Enhancements / DevTools / Randomizer)
    // ===========================================================================
    { "Vanilla", "原版" },
    { "Vanilla (1x)", "原版 (1x)" },
    { "Faster Run", "更快奔跑" },
    { "Faster + Longer Jump", "更快且跳得更高" },
    { "Unbreakable", "不可破坏" },
    { "Unbreakable + Always on Fire", "不可破坏且始终燃烧" },
    { "Navi", "娜薇" },
    { "NPCs", "NPC" },
    { "All", "全部" },
    { "Ocarina of Time", "时光之笛" },
    { "Ocarina of Time + Master Sword", "时光之笛 + 大师之剑" },
    { "Any Ocarina", "任意时光之笛" },
    { "Any Ocarina + Master Sword", "任意时光之笛 + 大师之剑" },
    { "Once", "一次" },
    { "Always", "总是" },
    { "Never", "从不" },
    { "Disabled", "禁用" },
    { "Random", "随机" },
    { "Random (Seeded)", "随机（固定种子）" },
    { "Dungeons", "地牢" },
    { "Dungeons (Vanilla)", "地牢（原版）" },
    { "Dungeons (MQ)", "地牢（MQ）" },
    { "Dungeons Random", "地牢随机" },
    { "Dungeons Random (Seeded)", "地牢随机（固定种子）" },
    { "Double (2x)", "双倍 (2x)" },
    { "Quadruple (4x)", "四倍 (4x)" },
    { "Octuple (8x)", "八倍 (8x)" },
    { "Foolish (16x)", "愚蠢 (16x)" },
    { "Ridiculous (32x)", "荒谬 (32x)" },
    { "Merciless (64x)", "残忍 (64x)" },
    { "Pure Torture (128x)", "纯折磨 (128x)" },
    { "OHKO (256x)", "一击必杀 (256x)" },
    { "OHKO", "一击必杀" },
    { "No Damage", "无伤害" },
    { "0.25 Hearts", "0.25 心" },
    { "0.5 Hearts", "0.5 心" },
    { "1 Heart", "1 心" },
    { "2 Hearts", "2 心" },
    { "4 Hearts", "4 心" },
    { "8 Hearts", "8 心" },
    { "Jalapeño", "哈拉佩尼奥椒" },
    { "Serrano", "塞拉诺椒" },
    { "Habanero", "哈瓦那椒" },
    { "Ghost Pepper", "鬼椒" },
    { "Dampe's Inferno", "达培的炼狱" },
    { "Only in Rando", "仅随机模式" },
    { "Consistent Vanish", "一致消失" },
    { "No Vanish", "不消失" },
    { "Child Toggle", "童年切换" },
    { "Both Ages", "两个年龄段" },
    { "Trace", "跟踪" },
    { "Debug", "调试" },
    { "Info", "信息" },
    { "Warn", "警告" },
    { "Error", "错误" },
    { "Critical", "严重" },
    { "Off", "关闭" },
    { "Maxed", "满级" },
    { "Junk Items", "垃圾道具" },
    { "All Items", "全部道具" },

    // ---- New section / sidebar labels ----
    { "Quality of Life", "生活质量" },
    { "Sail", "帆" },
    { "Misc", "杂项" },
    { "Misc.", "杂项。" },

    // ---- SohMenu disabledMap messages ----
    { "This setting is disabled because: \n", "此设置被禁用，原因：\n" },
    { "Disabling VSync not supported", "不支持禁用垂直同步" },
    { "Windowed Fullscreen not supported", "不支持窗口化全屏" },
    { "Multi-viewports not supported", "不支持多视口" },
    { "Available Only on DirectX", "仅在 DirectX 上可用" },
    { "Not Available on DirectX", "在 DirectX 上不可用" },
    { "Match Refresh Rate is Enabled", "已启用匹配刷新率" },
    { "Advanced Resolution Enabled", "已启用高级分辨率" },
    { "Vertical Resolution Toggle Enabled", "已启用垂直分辨率切换" },
    { "N64 Mode Enabled", "已启用 N64 模式" },
    { "Save Not Loaded", "未载入存档" },
    { "Debug Mode is Disabled", "调试模式已禁用" },
    { "Frame Advance is Disabled", "帧前进已禁用" },
    { "Advanced Resolution is Disabled", "高级分辨率已禁用" },
    { "Vertical Resolution Toggle is Off", "垂直分辨率切换已关闭" },

    // ===========================================================================
    //  Enhancements — widget labels
    // ===========================================================================
    { "Saving", "自动保存" },
    { "Autosave", "自动保存" },
    { "Notification on Autosave", "自动保存时通知" },
    { "Remember Save Location", "记住存档位置" },
    { "Containers Match Contents", "容器外观匹配内容" },
    { "Containers of Agony", "痛苦容器" },
    { "Nighttime GS Always Spawn", "夜间黄金骷髅蜘蛛始终出现" },
    { "Pull Grave During the Day", "白天可拉动墓碑" },
    { "Dampe Appears All Night", "达普整夜出现" },
    { "Exit Market at Night", "夜间可离开集市" },
    { "Shops and Games Always Open", "商店与小游戏全天开放" },
    { "Pause Menu", "暂停菜单" },
    { "Allow the Cursor to be on Any Slot", "允许光标停留任意槽位" },
    { "Pause Warp", "暂停菜单传送" },
    { "Controls", "操作" },
    { "Answer Navi Prompt with L Button", "用 L 键回应娜薇提示" },
    { "Don't Require Input for Credits Sequence", "过场字幕无需输入" },
    { "Include Held Inputs at the Start of Pause Buffer Input Window", "暂停缓冲输入窗口起始包含按住的输入" },
    { "Pause Buffer Input Window: %d frames", "暂停缓冲输入窗口：%d 帧" },
    { "Simulated Input Lag: %d frames", "模拟输入延迟：%d 帧" },
    { "Reworked Targeting", "重做瞄准" },
    { "Target Switch Button Combination:", "切换目标按键组合：" },
    { "Item Count Messages", "道具数量提示" },
    { "Gold Skulltula Tokens", "金色骷髅蜘蛛代币" },
    { "Pieces of Heart", "爱心碎片" },
    { "Heart Containers", "心之容器" },
    { "Disable Crit Wiggle", "禁用低血量镜头抖动" },
    { "Better Owl", "更聪明的猫头鹰" },
    { "Convenience", "便利" },
    { "Quit Fishing at Door", "在门口退出钓鱼" },
    { "Instant Putaway", "瞬间收起道具" },
    { "Navi Timer Resets on Scene Change", "切换场景重置娜薇计时器" },
    { "Link's Cow in Both Time Periods", "林克之牛在两个时段通用" },
    { "Skip Child Stealth", "跳过童年潜行" },
    { "Skip Tower Escape", "跳过逃塔" },
    { "Skip Playing Scarecrow's Song", "跳过演奏稻草人之歌" },
    { "Faster Rupee Accumulator", "更快的卢比累积" },
    { "No Skulltula Freeze", "黄金骷髅蜘蛛不冻结" },
    { "Skip Save Confirmation", "跳过保存确认" },
    { "Link as Default File Name", "默认文件名设为林克" },
    { "Spawn Bean Skulltula Faster", "更快生成豆藤骷髅蜘蛛" },
    { "Biggoron Forge Time: %d days", "大格雷锻造时间：%d 天" },
    { "Cutscenes", "过场动画" },
    { "All##Skips", "全部##跳过" },
    { "None##Skips", "无##跳过" },
    { "Skip Intro", "跳过开场" },
    { "Skip Entrance Cutscenes", "跳过入口过场" },
    { "Skip Story Cutscenes", "跳过剧情过场" },
    { "Skip Song Cutscenes", "跳过奏乐过场" },
    { "Skip Boss Introductions", "跳过 Boss 登场" },
    { "Quick Boss Deaths", "快速击杀 Boss" },
    { "Skip One Point Cutscenes (Chests, Door Unlocks, etc.)", "跳过单点过场（宝箱、开门等）" },
    { "Skip Owl Interactions", "跳过猫头鹰互动" },
    { "Skip Misc Interactions", "跳过其他互动" },
    { "Disable Title Card", "禁用标题卡" },
    { "Exclude Glitch-Aiding Cutscenes", "排除有助漏洞的过场" },
    { "Text", "文字" },
    { "Skip Bottle Pickup Messages", "跳过拾取瓶子提示" },
    { "Skip Consumable Item Pickup Messages", "跳过拾取消耗品提示" },
    { "Skip Forced Dialog", "跳过强制对话" },
    { "Skip Text", "跳过文字" },
    { "Text Speed: %dx", "文字速度：%dx" },
    { "Slow Text Speed: %dx", "慢速文字速度：%dx" },
    { "Changes the speed of sections of text that normally are paced slower than the text surrounding it.",
      "改变文本中通常比周围文字节奏更慢的部分的速度。" },
    { "Animations", "动画" },
    { "Faster Heavy Block Lift", "更快举起重块" },
    { "Faster Shadow Ship", "更快阴影船" },
    { "Fast Chests", "快速开箱" },
    { "Skip Water Take Breath Animation", "跳过出水换气动画" },
    { "Empty Bottles Faster", "更快倒空瓶子" },
    { "Vine/Ladder Climb Speed +%d", "攀爬藤蔓/梯子速度 +%d" },
    { "Block Pushing Speed +%d", "推块速度 +%d" },
    { "Crawl Speed %dx", "爬行速度 %dx" },
    { "Exclude Glitch-Aiding Crawlspaces", "排除有助漏洞的爬行通道" },
    { "King Zora Speed: %.2fx", "卓拉之王速度：%.2fx" },
    { "Faster Pause Menu", "更快的暂停菜单" },
    { "Mods", "模组" },
    { "Disable Bomb Billboarding", "禁用炸弹广告牌朝向" },
    { "Disable Grotto Fixed Rotation", "禁用洞穴固定旋转" },
    { "Disable Link's Sword Trail", "禁用林克剑光轨迹" },
    { "Disable 2D Pre-Rendered Scenes", "禁用 2D 预渲染场景" },
    { "Disable Fixed Camera", "禁用固定镜头" },
    { "Ingame Text Spacing: %d", "游戏内文字间距：%d" },
    { "Models & Textures", "模型与纹理" },
    { "Disable LOD", "禁用细节层次(LOD)" },
    { "Enemy Health Bars", "敌人血条" },
    { "Enable 3D Dropped Items/Projectiles", "启用 3D 掉落道具/抛射物" },
    { "Animated Link in Pause Menu", "暂停菜单林克动画" },
    { "Show Age-Dependent Equipment", "显示随年龄变化的装备" },
    { "Scale Adult Equipment as Child", "儿童期缩放成人装备" },
    { "Show Gauntlets in First-Person", "第一人称显示护腕" },
    { "Show Chains on Both Sides of Locked Doors", "上锁门两侧显示锁链" },
    { "Color Temple of Time's Medallions", "时之神殿勋章上色" },
    { "UI", "界面" },
    { "Minimal UI", "极简界面" },
    { "Disable Hot/Underwater Warning Text", "禁用高温/水下警告文字" },
    { "Remember Minimap State Between Areas", "区域间记住小地图状态" },
    { "Visual Stone of Agony", "视觉振动石" },
    { "Disable HUD Heart Animations", "禁用 HUD 爱心动画" },
    { "Glitch Line-up Tick", "漏洞对齐刻度" },
    { "Disable Black Bar Letterboxes", "禁用黑边信箱模式" },
    { "Dynamic Wallet Icon", "动态钱包图标" },
    { "Always Show Dungeon Entrances", "始终显示地牢入口" },
    { "More Info in File Select", "文件选择显示更多信息" },
    { "Better Ammo Rendering in Pause Menu", "暂停菜单更好的弹药显示" },
    { "Enable Passage of Time on File Select", "文件选择界面时间流逝" },
    { "N64 Mode", "N64 模式" },
    { "Remove Spin Attack Darkness", "移除旋转攻击黑暗" },
    { "Disable Link Spinning With Goron Pot", "禁用林克随格雷壶旋转" },
    { "Draw Distance", "绘制距离" },
    { "Increase Actor Draw Distance: %dx", "增加角色绘制距离：%dx" },
    { "Disable Kokiri Fade", "禁用科克里淡入" },
    { "Widescreen Actor Culling", "宽屏角色剔除" },
    { "Cull Glitch Useful Actors", "剔除有助漏洞的角色" },
    { "Equipment", "装备" },
    { "Equip Items on Dpad", "方向键装备道具" },
    { "Allow unequipping Items", "允许卸下道具" },
    { "Assignable Shields, Tunics and Boots", "可分配的盾、外衣与靴子" },
    { "Equipment Toggle", "装备开关" },
    { "Allow Strength Equipment to be Toggled", "允许切换力量装备" },
    { "Unsheathe Sword Without Slashing", "拔剑不挥砍" },
    { "Sword Toggle Options", "剑切换选项" },
    { "Ask to Equip New Items", "提示装备新道具" },
    { "Ocarina", "时光之笛" },
    { "Prevent Dropped Ocarina Inputs", "防止掉落时光之笛输入丢失" },
    { "Fast Ocarina Playback", "快速时光之笛演奏" },
    { "Time Travel with Song of Time", "用时之之歌时间穿越" },
    { "Masks", "面具" },
    { "Bunny Hood Effect", "兔耳头巾效果" },
    { "Masks Equippable as Adult", "成人可装备面具" },
    { "Persistent Masks", "面具持久装备" },
    { "Invisible Bunny Hood", "隐形兔耳头巾" },
    { "Mask Select in Inventory", "物品栏选择面具" },
    { "Explosives", "炸药" },
    { "Remote Bombchu", "遥控炸弹鼠" },
    { "Deku Nuts Explode Bombs", "德库坚果引爆炸弹" },
    { "Remove Explosive Limit", "移除炸药数量上限" },
    { "Static Explosion Radius", "固定爆炸半径" },
    { "Prevent Bombchus Forcing First-Person", "防止炸弹鼠强制第一人称" },
    { "Better Bombchu Shopping", "更好的炸弹鼠购物" },
    { "Bow / Slingshot", "弓 / 弹弓" },
    { "Equip Multiple Arrows at Once", "同时装备多种箭" },
    { "Skip Magic Arrow Equip Animation", "跳过魔法箭装备动画" },
    { "Blue Fire Arrows", "蓝火之箭" },
    { "Sunlight Arrows", "阳光之箭" },
    { "Bow as Child/Slingshot as Adult", "童年用弓/成人用弹弓" },
    { "Aiming Reticle for the Bow/Slingshot", "弓/弹弓瞄准准星" },
    { "Arrow Cycle", "箭种循环" },
    { "Hookshot", "短钩" },
    { "Targetable Hookshot Reticle", "可钩锁定的钩爪准星" },
    { "Boomerang", "飞旋镖" },
    { "Instant Boomerang Recall", "瞬间召回飞旋镖" },
    { "Aim Boomerang in First-Person Mode", "第一人称瞄准飞旋镖" },
    { "Aiming Reticle for Boomerang", "飞旋镖瞄准准星" },
    { "Magic Spells", "魔法" },
    { "Better Farore's Wind", "更好的花柔之风" },
    { "Faster Farore's Wind", "更快的花柔之风" },
    { "Bottles", "瓶子" },
    { "Rebottle Blue Fire", "重新装瓶蓝火" },
    { "Gameplay Fixes", "玩法修复" },
    { "Fix the Gravedigging Tour Glitch", "修复挖墓之旅漏洞" },
    { "Fix Dampé Going Backwards", "修复达培倒退" },
    { "Fix Kokiri Forest Quest State", "修复科克里森林任务状态" },
    { "Fix Raised Floor Switches", "修复抬起的地板开关" },
    { "Fix Zora Hint Dialogue", "修复卓拉提示对话" },
    { "Fix Falling from Vine Edges", "修复从藤蔓边缘坠落" },
    { "Fix Bush Item Drops", "修复灌木道具掉落" },
    { "Fix Enemies not Spawning Near Water", "修复水边敌人不刷出" },
    { "Fix Poacher's Saw Softlock", "修复偷猎者锯子卡死" },
    { "Fix Anubis Fireballs", "修复阿努比斯火球" },
    { "Fix Goron City Doors After Fire Temple", "修复火之神殿后的格雷城大门" },
    { "Item-related Fixes", "道具相关修复" },
    { "Fix Deku Nut Upgrade", "修复德库坚果升级" },
    { "Fix Megaton Hammer Crouch Stab", "修复巨型锤下蹲刺击" },
    { "Remove Power Crouch Stab", "移除强力下蹲刺击" },
    { "Fix Broken Giant's Knife Bug", "修复破裂巨人之刀漏洞" },
    { "Camera Fixes", "镜头修复" },
    { "Fix Camera Drift", "修复镜头漂移" },
    { "Fix Camera Swing", "修复镜头摆动" },
    { "Fix Hanging Ledge Swing Rate", "修复悬挂边缘摆动速率" },
    { "Graphical Fixes", "画面修复" },
    { "Fix L&R Pause Menu", "修复暂停菜单 L&R" },
    { "Fix Dungeon Entrances", "修复地牢入口" },
    { "Fix Two-Handed Idle Animations", "修复双手待机动画" },
    { "Fix Navi Text HUD Position", "修复娜薇文字 HUD 位置" },
    { "Fix Gerudo Warrior's Clothing Colors", "修复格鲁德战士服装颜色" },
    { "Fix Out of Bounds Textures", "修复越界纹理" },
    { "Fix Link's Eyes Open while Sleeping", "修复林克睡眠时睁眼" },
    { "Fix Hand Holding Hammer", "修复持锤手部" },
    { "Audio Fixes", "音频修复" },
    { "Fix Missing Jingle after 5 Silver Rupees", "修复 5 枚银卢比后缺失铃音" },
    { "Desync Fixes", "不同步修复" },
    { "Fix Darunia Dancing too Fast", "修复达鲁尼亚跳舞过快" },
    { "Fix Credits Timing (PAL)", "修复制作人员名单 timing（PAL）" },
    { "Graphical Restorations", "画面还原" },
    { "Red Ganon Blood", "红色盖侬之血" },
    { "Restore Old Gold Skulltula Cutscene", "还原旧版金色骷髅蜘蛛过场" },
    { "Pulsate Boss Icon", "Boss 图标脉动" },
    { "Glitch Restorations", "漏洞还原" },
    { "Fish while Hovering", "悬浮时钓鱼" },
    { "N64 Weird Frames", "N64 诡异帧" },
    { "Bombchus Out of Bounds", "炸弹鼠越界" },
    { "Quick Putaway", "快速收起" },
    { "Quick Bongo Kill", "快速击杀邦哥邦哥" },
    { "Early Eyeball Frog", "提前获得大眼青蛙" },
    { "Misc Restorations", "其他还原" },
    { "Fix L&Z Page Switch in Pause Menu", "修复暂停菜单 L&Z 翻页" },
    { "Wide Door Ranges", "宽门触发范围" },
    { "Grave Hole Jumps", "墓穴跳跃" },
    { "Health", "生命" },
    { "Permanent Heart Loss", "永久失去心之容器" },
    { "Damage Multiplier", "伤害倍率" },
    { "Fall Damage Multiplier", "坠落伤害倍率" },
    { "Void Damage Multiplier", "虚空伤害倍率" },
    { "Bonk Damage Multiplier", "撞击伤害倍率" },
    { "Spawn with Full Health", "满血生成" },
    { "No Heart Drops", "不掉落爱心" },
    { "Drops", "掉落" },
    { "No Random Drops", "无随机掉落" },
    { "Enable Bombchu Drops", "启用炸弹鼠掉落" },
    { "Trees Drop Sticks", "树木掉落树枝" },
    { "Dampe Drop Rate", "达培掉落速率" },
    { "Miscellaneous", "杂项" },
    { "Delete File on Death", "死亡删除存档" },
    { "Switch Timer Multiplier", "开关计时器倍率" },
    { "Always Win Goron Pot", "始终赢得格雷壶" },
    { "Always Win Dampe Digging Game", "始终赢得达培挖掘游戏" },
    { "All Dogs are Richard", "所有狗都是理查德" },
    { "Cuccos Stay Put Multiplier: %dx", "咕咕停留倍率：%dx" },
    { "Cuccos Needed By Anju: %d", "安ju 需要的咕咕数：%d" },
    { "Enemies", "敌人" },
    { "Hyper Bosses", "超级 Boss" },
    { "Hyper Enemies", "超级敌人" },
    { "Enable Visual Guard Vision", "启用视觉守卫视野" },
    { "Leever Spawn Rate: %d seconds", "利弗刷出速率：%d 秒" },
    { "Shooting Gallery", "射击场" },
    { "Customize Behavior##Shooting", "自定义行为##射击场" },
    { "Instant Win", "瞬间胜利" },
    { "No Rupee Randomization", "卢比不随机" },
    { "Child Starting Ammunition: %d seeds", "童年初始弹药：%d 颗种子" },
    { "Adult Starting Ammunition: %d arrows", "成人初始弹药：%d 支箭" },
    { "Bombchu Bowling", "炸弹鼠保龄球" },
    { "Customize Behavior##Bowling", "自定义行为##保龄球" },
    { "Remove Small Cucco", "移除小咕咕" },
    { "Remove Big Cucco", "移除大咕咕" },
    { "Bombchu Count: %d bombchus", "炸弹鼠数量：%d 只" },
    { "Frogs' Ocarina Game", "青蛙时光之笛游戏" },
    { "Customize Behavior##Frogs", "自定义行为##青蛙" },
    { "Instant Win##Frogs", "瞬间胜利##青蛙" },
    { "Unlimited Playback Time##Frogs", "无限回放时间##青蛙" },
    { "Modify Note Timer: %dx", "修改音符计时：%dx" },
    { "Lost Woods Ocarina Game", "迷失森林时光之笛游戏" },
    { "Customize Behavior##LostWoods", "自定义行为##迷失森林" },
    { "Instant Win##LostWoods", "瞬间胜利##迷失森林" },
    { "Note Play Speed: %dx", "音符演奏速度：%dx" },
    { "Unlimited Playback Time##LostWoods", "无限回放时间##迷失森林" },
    { "Number of Starting Notes: %d notes", "起始音符数：%d 个" },
    { "Round One Notes: %d notes", "第一轮音符数：%d 个" },
    { "Round Two Notes: %d notes", "第二轮音符数：%d 个" },
    { "Round Three Notes: %d notes", "第三轮音符数：%d 个" },
    { "Forest Temple", "森林神殿" },
    { "Solve Amy's Puzzle", "解开艾米拼图" },
    { "Fishing", "钓鱼" },
    { "Customize Behavior##Fishing", "自定义行为##钓鱼" },
    { "Instant Fishing", "瞬间钓鱼" },
    { "Guarantee Bite", "保证咬钩" },
    { "Fish never Escape", "鱼绝不挣脱" },
    { "Loaches always Appear", "泥鳅始终出现" },
    { "Skip Keep Confirmation", "跳过保留确认" },
    { "All Fish are Hyrule Loaches", "所有鱼都是海拉鲁泥鳅" },
    { "Child Minimum Weight: %d lbs.", "童年最小重量：%d 磅" },
    { "Adult Minimum Weight: %d lbs.", "成人最小重量：%d 磅" },
    { "Bounce off Walls", "撞墙反弹" },
    { "Mirrored World", "镜像世界" },
    { "Ivan the Fairy (Coop Mode)", "仙女伊万（合作模式）" },
    { "Dogs Follow You Everywhere", "狗随处跟随" },
    { "Rupee Dash Mode", "卢比冲刺模式" },
    { "Rupee Dash Interval %d seconds", "卢比冲刺间隔 %d 秒" },
    { "Shadow Tag Mode", "影子捉人模式" },
    { "Hurt Container Mode", "伤害容器模式" },
    { "Additional Traps", "额外陷阱" },
    { "Trap Options", "陷阱选项" },
    { "Tier 1 Traps:", "一级陷阱：" },
    { "Freeze Traps", "冰冻陷阱" },
    { "Burn Traps", "燃烧陷阱" },
    { "Shock Traps", "电击陷阱" },
    { "Tier 2 Traps:", "二级陷阱：" },
    { "Knockback Traps", "击退陷阱" },
    { "Speed Traps", "加速陷阱" },
    { "Bomb Traps", "炸弹陷阱" },
    { "Tier 3 Traps:", "三级陷阱：" },
    { "Void Traps", "虚空陷阱" },
    { "Ammo Traps", "弹药陷阱" },
    { "Death Traps", "死亡陷阱" },
    { "Teleport Traps", "传送陷阱" },
    { "Infinite...", "无限……" },
    { "Money", "金钱" },
    { "Health", "生命" },
    { "Ammo", "弹药" },
    { "Magic", "魔法" },
    { "Nayru's Love", "娜茹之爱" },
    { "Epona Boost", "伊波纳冲刺" },
    { "Timeless Equipment", "无时限装备" },
    { "Unrestricted Items", "无限制道具" },
    { "Super Tunic", "超级外衣" },
    { "Fireproof Deku Shield", "防火德库盾" },
    { "Shield with Two-Handed Weapons", "双手武器持盾" },
    { "Deku Sticks:", "德库木棒：" },
    { "Bomb Timer Multiplier: %.2fx", "炸弹计时倍率：%.2fx" },
    { "Hookshot Everything", "钩爪抓一切" },
    { "Hookshot Reach Multiplier: %.2fx", "钩爪距离倍率：%.2fx" },
    { "No Clip", "穿墙" },
    { "Climb Everything", "攀爬一切" },
    { "Moon Jump on L", "L 键月步跳" },
    { "No ReDead/Gibdo Freeze", "避免 ReDead/Gibdo 冻结" },
    { "Keese/Guay don't Target You", "凯西/瓜伊不锁定你" },
    { "Disable Haunted Wasteland Sandstorm", "禁用鬼魅荒野沙暴" },
    { "Targetable Gold Skulltula", "可锁定的黄金骷髅蜘蛛" },
    { "Glitch Aids", "漏洞辅助" },
    { "Easy Frame Advancing with Pause", "暂停时简易帧前进" },
    { "Easy ISG", "简易 ISG" },
    { "Easy QPA", "简易 QPA" },
    { "Clear Cutscene Pointer", "清除过场指针" },
    { "Despawn Timers", "消失计时器" },
    { "Drops Don't Despawn", "掉落物不消失" },
    { "Fish don't Despawn", "鱼不消失" },
    { "Bugs don't Despawn", "虫子不消失" },
    { "Freeze Time", "冻结时间" },
    { "Time Sync", "时间同步" },
    { "Instant Age Change", "瞬间切换年龄" },
    { "Change Age", "切换年龄" },
    { "Speed Modifier", "速度修改器" },
    { "Toggle modifier instead of holding", "切换修改器而非按住" },
    { "Don't affect jump distance/velocity", "不影响跳跃距离/速度" },
    { "Multiplier:", "倍率：" },
    { "Button Combination:", "按键组合：" },
    { "Save States", "存档状态" },
    { "I promise I have read the warning", "我承诺已阅读警告" },
    { "I understand, enable save states", "我理解，启用存档状态" },
    { "Beta Quest", "测试版任务" },
    { "Enable Beta Quest", "启用测试版任务" },
    { "Beta Quest World: %d", "测试版任务世界：%d" },
    { "Popout Cosmetics Editor Window", "弹出外观编辑器窗口" },
    { "Popout Audio Editor Window", "弹出音频编辑器窗口" },
    { "Popout Gameplay Stats Window", "弹出游戏统计窗口" },
    { "Popout Time Splits Window", "弹出时间分段窗口" },
    { "Toggle Timers Window", "切换计时器窗口" },
    { "Font Scale: %.2fx", "字体缩放：%.2fx" },
    { "Hide Background", "隐藏背景" },

    // ===========================================================================
    //  Enhancements — tooltips (part 1: QoL / Graphics / Items)
    // ===========================================================================
    { "Save the game automatically on a 3 minute interval and when soft-resetting the game. The interval "
      "autosave will wait if the game is paused in any way (dialogue, pause screen up, cutscenes, "
      "etc.).\n\n"
      "The soft-reset save will *not* trigger in cutscene maps like the Chamber of Sages!",
      "每 3 分钟以及软重置游戏时自动保存。暂停（对话、暂停菜单、过场等）时自动保存会等待。\n\n"
      "软重置存档不会在过场地图（如贤者之间）触发！" },
    { "Show a notification when the game is autosaved.", "自动保存时显示通知。" },
    { "When loading a save, places Link at the last entrance he went through.\n"
      "This doesn't work if the save was made in grottos, fairy fountains, or dungeons.",
      "载入存档时将林克放在他最后通过的入口。\n在洞穴、妖精泉或地牢中存档时无效。" },
    { "Toggle to change container textures to match their contents in randomizer games.\n"
      "Categories: Major items, Lesser items, Junk items, Small keys, Boss keys, Skulltula Tokens.",
      "在随机模式切换容器纹理以匹配内容。\n分类：主要道具、次要道具、垃圾道具、小钥匙、Boss 钥匙、骷髅蜘蛛代币。" },
    { "Only change the texture of containers if you have the Stone of Agony.", "仅当你拥有振动石时更改容器纹理。" },
    { "Nighttime Skulltulas will spawn during both day and night.", "夜间骷髅蜘蛛在白天与夜晚都会出现。" },
    { "Allows graves to be pulled when child during the day.", "允许童年白天拉动墓碑。" },
    { "Makes Dampe appear anytime during the night, not just his usual working hours.", "让达培整夜出现，而非仅工作时间。" },
    { "Allows exiting Hyrule Castle Market Town to Hyrule Field at night by speaking to the guard "
      "next to the gate.",
      "夜间与门口守卫对话可从海拉鲁城集市前往海拉鲁平原。" },
    { "Shops and Minigames are open both day and night. Requires a scene reload to take effect.",
      "商店与小游戏全天开放。需重新加载场景生效。" },
    { "This is not compatible with the Locked Overworld Doors Randomizer option.", "与\"锁定地表门\"随机选项不兼容。" },
    { "Allows the cursor on the pause menu to be over any slot. Sometimes required in Randomizer "
      "to select certain items.",
      "允许暂停菜单光标停留在任意槽位。随机模式中选取某些道具时可能需要。" },
    { "Selection of warp song in pause menu initiates a warp. Disables song playback.", "暂停菜单选择传送歌即传送。禁用歌曲演奏。" },
    { "Speak to Navi with L but enter First-Person Camera with C-Up.", "用 L 与娜薇对话，用 C-Up 进入第一人称镜头。" },
    { "Removes the Input Requirement on Text boxes after defeating Ganon, allowing the Credits "
      "Sequence to continue to progress.",
      "移除击败盖侬后文本框的输入要求，使制作人员名单继续推进。" },
    { "Typically, inputs that are held prior to the buffer window are not included in the buffer. This "
      "setting changes that behavior to include them. This may cause some inputs to be re-triggered "
      "undesireably, for instance Z-Targeting something you might not want to.",
      "通常缓冲窗口前按住的输入不计入缓冲。此设置改变该行为将其纳入。可能导致某些输入被意外重复触发，"
      "例如锁定你不想锁定的目标。" },
    { "Adds back in a delay after unpausing before the game resumes playing again, where inputs can be "
      "held prematurely to be input immediately after the game resumes. This essentially brings back "
      "behaviour from console releases which are lost on default because SoH isn't limited to N64 hardware.",
      "取消暂停后恢复游戏前加入延迟，可提前按住输入以在恢复后立即输入。这还原了主机版本的行为，"
      "因 SoH 不受 N64 硬件限制而默认丢失。" },
    { "Buffers your inputs to be executed a specified amount of frames later.", "将输入延迟指定帧数后执行。" },
    { "Reworks targeting functionality\n"
      "- Press Z while locked always untargets (in Toggle mode)\n"
      "- Use the configured button combo to switch between targets",
      "重做瞄准功能\n- 锁定时按 Z 始终取消锁定（切换模式）\n- 用配置的按键组合切换目标" },
    { "Buttons to activate target switching.", "激活目标切换的按键。" },
    { "Disable Random Camera Wiggle at Low Health.", "禁用低血量随机镜头抖动。" },
    { "The default response to Kaepora Gaebora is always that you understood what he said.", "对卡波拉·盖波拉默认回答\"已理解\"。" },
    { "Fisherman asks if you want to quit at the door if you try to leave the Fishing Pond "
      "while still holding the Fishing Rod.",
      "若持竿试图离开鱼塘，渔夫会询问是否退出。" },
    { "Allow Link to put items away without having to wait around.", "允许林克直接收起道具，无需等待。" },
    { "Resets the Navi timer on scene change. If you have already talked to her, she will try and talk "
      "to you again, instead of needing a save warp or death.",
      "切换场景重置娜薇计时器。若已与她对话过，她会再次尝试对话，无需存档传送或死亡。" },
    { "Allows the Lon Lon Ranch Obstacle Course reward to be shared across time periods.", "允许隆隆牧场障碍赛奖励在两个时段通用。" },
    { "Always: Link must always play Zelda's Lullaby to open the waterfall entrance to Zora's Domain.\n"
      "Once: Link only needs to play Zelda's Lullaby once to open the waterfall; after that, it stays "
      "open permanently.\n"
      "Never: Link never needs to play Zelda's Lullaby to open the waterfall. He only needs to have "
      "learned it and have an Ocarina.",
      "总是：林克必须始终演奏塞尔达的摇篮曲才能打开通往卓拉之域的瀑布入口。\n"
      "一次：林克只需演奏一次，之后永久开启。\n"
      "从不：林克无需演奏，只需学过且有笛子。" },
    { "Allow Link to enter Jabu-Jabu without feeding him a fish.", "允许林克不喂鱼进入加卜加卜。" },
    { "This setting is forcefully enabled because a randomizer savefile with \"Jabu-Jabu: Open\" is loaded.",
      "随机存档\"加卜加卜：开启\"已载入，此设置被强制启用。" },
    { "Allows you to change the number of days it takes for Biggoron to forge the Biggoron's Sword.",
      "可更改大格雷锻造大剑所需天数。" },
    { "Disables bombs always rotating to face the camera. To be used in conjunction with mods that want to "
      "replace bombs with 3D objects.",
      "禁用炸弹始终朝向镜头旋转。配合将炸弹替换为 3D 物体的 MOD 使用。" },
    { "Disables Grottos rotating with the Camera. To be used in conjuction with mods that want to "
      "replace grottos with 3D objects.",
      "禁用洞穴随镜头旋转。配合将洞穴替换为 3D 物体的 MOD 使用。" },
    { "Disables the sword trail effect when swinging Link's sword. Useful when using mods that replace "
      "Link's sword model.",
      "禁用林克挥剑的剑光轨迹。使用替换林克剑模型的 MOD 时有用。" },
    { "Disables 2D pre-rendered backgrounds. Enable this when using a mod that implements 3D backdrops "
      "for these areas.\nRequires Scene Change to alter.",
      "禁用 2D 预渲染背景。使用为这些区域实现 3D 背景的 MOD 时启用。\n需切换场景生效。" },
    { "Disables the fixed camera in maps that use 2D pre-rendered backgrounds. Enable this when using a "
      "mod that implements 3D backdrops for these areas.\nRequires Scene Change to alter.",
      "禁用使用 2D 背景地图的固定镜头。使用 3D 背景 MOD 时启用。\n需切换场景生效。" },
    { "Requires \"Disable 2D Pre-Rendered Scenes\" to be enabled.", "需要启用\"禁用 2D 预渲染场景\"。" },
    { "Space between text characters (useful for HD font textures).", "文字字符间距（适用于高清字体纹理）。" },
    { "Turns off the Level of Detail setting, making models use their Higher-Poly variants at any distance.",
      "关闭细节层次设置，使模型在任何距离使用更高面数版本。" },
    { "Renders a health bar for Enemies when Z-Targeted.", "锁定敌人时显示血条。" },
    { "Replaces most 2D items and projectiles on the overworld with their equivalent 3D models.",
      "将地表大部分 2D 道具与抛射物替换为等效 3D 模型。" },
    { "Turns the Static Image of Link in the Pause Menu's Equipment Subscreen into a model cycling "
      "through his idle animations.",
      "将暂停菜单装备栏中林克的静态图变为循环待机动画的模型。" },
    { "Makes all equipment visible, regardless of age.", "不论年龄显示所有装备。" },
    { "Scales all of the Adult Equipment, as well as moving some a bit, to fit on Child Link better. May "
      "not work properly with some mods.",
      "缩放成人装备以更贴合童年林克（并略微移动部分）。某些 MOD 下可能不正常。" },
    { "Renders Gauntlets when using the Bow and Hookshot like in OoT3D.", "如 OoT3D 般使用弓与钩爪时显示护腕。" },
    { "Displays an icon and plays a sound when Stone of Agony should be activated, for those without rumble.",
      "为无震动玩家，在应激活振动石时显示图标并播放声音。" },
    { "Disables the Beating Animation of the Hearts on the HUD.", "禁用 HUD 爱心跳动动画。" },
    { "Displays a tick in the top center of the screen to help with glitch line-ups in SoH, since "
      "traditional UI based line-ups do not work outside of 4:3",
      "屏幕顶部中央显示刻度，辅助 SoH 中的漏洞对齐（传统 UI 对齐在 4:3 外无效）。" },
    { "Disables Black Bar Letterboxes during cutscenes and Z-Targeting. NOTE: There may be minor visual "
      "glitches that were covered up by the black bars. Please disable this setting before reporting a bug.",
      "禁用过场与锁定时黑边信箱模式。注意：可能有被黑边遮盖的轻微视觉故障，报告 bug 前请先关闭此设置。" },
    { "Changes the Rupee in the Wallet icon to match the wallet size you currently have.", "钱包图标中的卢比随当前钱包大小变化。" },
    { "Always shows dungeon entrance icons on the Minimap.", "小地图始终显示地牢入口图标。" },
    { "Shows what items you have collected in the File Select screen, like in N64 Randomizer.", "文件选择界面显示已收集道具，如 N64 随机版。" },
    { "Ammo counts in the pause menu will work correctly regardless of the position of items in the Inventory.",
      "暂停菜单弹药计数正确，不受物品栏位置影响。" },
    { "The skybox in the background of the File Select screen will go through the day and night cycle over time.",
      "文件选择界面背景天空盒随时间昼夜循环。" },
    { "Sets the aspect ratio to 4:3 and lowers resolution to 240p, the N64's native resolution.",
      "设置 4:3 比例并将分辨率降至 240p（N64 原生分辨率）。" },
    { "Remove the Darkness that appears when charging a Spin Attack.", "移除蓄力旋转攻击时的黑暗效果。" },
    { "Link will not spin when the Goron Pot starts to spin.", "格雷壶旋转时林克不会跟着转。" },
    { "Increases the range in which Actors/Objects are drawn.", "增加角色/物体的绘制范围。" },
    { "The Kokiri are mystical beings that fade into view when approached. Enabling this will remove their "
      "draw distance.",
      "科克里是接近时淡入的神秘生物。启用后将移除其绘制距离。" },
    { "Adjusts the Horizontal Culling Plane to account for Widescreen Resolutions.", "调整水平剔除平面以适应宽屏分辨率。" },
    { "Requires Actor Draw Distance to be increased or Widscreen Actor Culling to be enabled.", "需要增加角色绘制距离或启用宽屏角色剔除。" },
    { "Exclude Actors that are useful for Glitches from the extended culling ranges. Some actors may still "
      "draw in the extended ranges, but will not \"update\" so that certain glitches that leverage the "
      "original culling requirements will still work.\n\nThe following actors are excluded:\n"
      " - White Clothed Gerudos\n"
      " - King Zora\n"
      " - Gossip Stones\n"
      " - Boulders\n"
      " - Blue Warps\n"
      " - Darunia\n"
      " - Gold Skulltulas",
      "从扩展剔除范围中排除有助漏洞的角色。部分角色仍会绘制，但不会\"更新\"，使依赖原始剔除要求的漏洞仍可用。\n\n"
      "排除以下角色：\n - 白衣格鲁德\n - 卓拉之王\n -  gossip 石\n - 巨石\n - 蓝色传送点\n - 达鲁尼亚\n - 黄金骷髅蜘蛛" },
    { "Equip items and equipment on the D-pad. If used with \"D-pad on Pause Screen\", you must "
      "hold C-Up to equip instead of navigate.",
      "用方向键装备道具与装备。若配合\"暂停菜单方向键\"，需按住 C-Up 装备而非导航。" },
    { "Allows unequipping items from C-Buttons/D-pad by hovering over an equipped item and pressing the "
      "button it's equipped to.",
      "悬停在已装备道具上并按下其装备键，可卸下该道具。" },
    { "Allows equipping Shields, Tunics and Boots to C-Buttons/D-pad.", "允许将盾、外衣与靴子装备到 C 键/方向键。" },
    { "Allows equipment to be removed by toggling it on/off\n the equipment subscreen.", "可通过开关在装备栏移除装备。" },
    { "Allows Strength to be toggled on and off by pressing A on the Strength Upgrade in the Equipment "
      "Subscreen of the Pause Menu. This allows performing some glitches that require the player to not "
      "have Strength.",
      "在暂停菜单装备栏的力量升级上按 A 可切换力量开关。可触发某些需要无力量状态的漏洞。" },
    { "Allows Link to unsheathe sword without slashing automatically.", "允许林克拔剑而不自动挥砍。" },
    { "Introduces Options for unequipping Link's sword\n\n"
      "None: Only Biggoron's Sword/Giant's Knife can be toggled. Doing so will equip the Master Sword.\n\n"
      "Child Toggle: This will allow for completely unequipping any sword as Child link.\n\n"
      "Both Ages: Any sword can be unequipped as either age. This may lead to swordless glitches as adult.",
      "引入卸下林克之剑的选项\n\n"
      "无：仅大格雷之剑/巨人之刀可切换，切换后将装备大师之剑。\n\n"
      "童年切换：童年可完全卸下任意剑。\n\n"
      "两个年龄段：任意年龄可卸下任意剑，成人时可能导致无剑漏洞。" },
    { "Adds a prompt to equip newly-obtained Swords, Shields, and Tunics.", "获得新剑、盾、外衣时提示装备。" },
    { "Prevent dropping inputs when playing the Ocarina too quickly.", "防止过快演奏时光之笛时输入丢失。" },
    { "Skip the part where the Ocarina Playback is called when you play a song.", "跳过演奏歌曲时调用时光之笛回放的部分。" },
    { "Allows Link to freely change age by playing the Song of Time.\n"
      "Time Blocks can still be used properly.\n\n"
      "Requirements:\n"
      " - Obtained the Song of Time\n"
      " - Obtained the Ocarina of Time (depends on selection)\n"
      " - Obtained the Master Sword (depends on selection)\n"
      " - Not within range of a Time Block\n"
      " - Not within range of Ocarina Playing spots",
      "允许林克演奏时之之歌自由切换年龄。\n时间方块仍正常使用。\n\n"
      "要求：\n - 已学会时之之歌\n - 已获得时光之笛（取决于选择）\n - 已获得大师之剑（取决于选择）\n"
      " - 不在时间方块范围内\n - 不在演奏点范围内" },
    { "Wearing the Bunny Hood grants a speed and jump boost like in Majora's Mask.\n"
      "Can also be limited to only the speed boost.\n"
      "The effects of either option are not accounted for in Randomizer logic.\n"
      "Also disables NPC's reactions to wearing the Bunny Hood.",
      "戴兔耳头巾可获得如马朱拉假面般的速度与跳跃加成。\n也可仅限速度加成。\n"
      "随机逻辑不计入任一选项效果。\n同时禁用 NPC 对兔耳头巾的反应。" },
    { "Allows masks to be equipped normally from the pause menu as adult.", "允许成人从暂停菜单正常装备面具。" },
    { "Stops masks from automatically unequipping on certain situations:\n"
      "- When entering a new scene\n"
      "- When not in any C-Button or the D-pad\n"
      "- When saving and quitting\n"
      "- When dying\n"
      "- When traveling through time (if \"Masks Equippable as Adult\" is activated)",
      "阻止面具在以下情况自动卸下：\n- 进入新场景\n- 未在任何 C 键或方向键\n- 保存退出\n- 死亡\n"
      "- 穿越时间（若启用\"成人可装备面具\"）" },
    { "Turns Bunny Hood Invisible while still maintaining its effects.", "兔耳头巾隐形但保留效果。" },
    { "After completing the mask trading sub-quest, press A and any direction on the mask "
      "slot to change masks.",
      "完成面具交换支线后，在面具槽按 A 加任意方向可更换面具。" },
    { "Allows you to control a Bombchu after dropping it.\nControl Stick: Steer\nB: Detonate\nA: Quit Control",
      "放下炸弹鼠后可控制它。\n控制杆：转向\nB：引爆\nA：退出控制" },
    { "Make Deku Nuts explode Bombs, similar to how they interact with Bombchus. "
      "This does not affect Bomb Flowers.",
      "让德库坚果引爆炸弹，类似其与炸弹鼠的互动。不影响炸弹花。" },
    { "Removes the cap of 3 active explosives being deployed at once.", "移除同时部署 3 个爆炸物的上限。" },
    { "Explosions are now a static size, like in Majora's Mask and OoT3D. Makes Bombchu "
      "hovering much easier.",
      "爆炸现为固定大小，如马朱拉假面与 OoT3D。使炸弹鼠悬停更容易。" },
    { "Prevent Bombchus from forcing the camera into first-person mode when released.", "防止炸弹鼠释放时强制第一人称镜头。" },
    { "Bombchus do not sell out when bought, and a 10 pack of Bombchus costs 99 rupees instead of 100.",
      "炸弹鼠购买不售罄，10 个装售价为 99 卢比而非 100。" },
    { "Allow the Bow and Magic Arrows to be equipped at the same time on different slots. "
      "NOTE: This will disable the behavior of the 'Equip Dupe' glitch.",
      "允许弓与魔法箭在不同槽位同时装备。注意：这会禁用\"装备复制\"漏洞行为。" },
    { "Allows Ice Arrows to melt Red Ice. May require a room reload if toggled during gameplay.", "允许冰箭融化红冰。游戏中切换可能需要重加载房间。" },
    { "Allows Light Arrows to activate Sun Switches. May require a room reload if toggled during gameplay.", "允许光箭激活太阳开关。游戏中切换可能需要重加载房间。" },
    { "Allows Child Link to use a Bow with Arrows.\nAllows Adult Link to use a Slingshot with Seeds.\n\n"
      "Requires glitches or the 'Timeless Equipment' cheat to equip.",
      "允许童年林克用弓射箭。\n允许成人林克用弹弓射种子。\n\n装备需要漏洞或\"无时限装备\"作弊。" },
    { "Aiming with a Bow or Slingshot will display a reticle as with the Hookshot when the projectile is ready to fire.",
      "用弓或弹弓瞄准且抛射物就绪时，显示如钩爪般的准星。" },
    { "Allows cycling between different arrow types (Normal, Fire, Ice, Light) while aiming the bow. "
      "Press the R button to cycle to the next available arrow type. "
      "Only works when aiming and only cycles to arrow types you own with sufficient magic.",
      "瞄准时可在不同箭种（普通、火、冰、光）间循环。按 R 切换到下一个可用箭种。"
      "仅在瞄准时有效，且只循环到你拥有足够魔法的箭种。" },
    { "Makes the Hookshot Reticle use a different color when aiming at hookshotable collision.", "钩爪准星在可钩锁定时变为不同颜色。" },
    { "Instantly return the Boomerang to Link by pressing its item button while it's in the air.", "飞旋镖在空中时按道具键瞬间召回。" },
    { "Change aiming for the Boomerang from Third-Person to First-Person to see past Link's head.", "将飞旋镖瞄准从第三人称改为第一人称，可越过林克头部。" },
    { "Aiming with the Boomerang will display a reticle as with the Hookshot.", "用飞旋镖瞄准时显示如钩爪般的准星。" },
    { "Helps FW persist between ages, gives Child and Adult separate FW points, and can "
      "be used in more places.",
      "帮助花柔之风跨年龄保留，童年与成人有独立法点，可在更多地点使用。" },
    { "Greatly decreases cast time of Farore's Wind magic spell.", "大幅减少花柔之风的施法时间。" },
    { "Blue Fire dropped from bottle can be bottled.", "瓶中掉落的蓝火可重新装瓶。" },

    // ===========================================================================
    //  Enhancements — tooltips (part 2: Fixes / Difficulty / Minigames / Extra Modes / Cheats)
    // ===========================================================================
    { "Fixes a bug where the Gravedigging Tour Heart Piece disappears if the area reloads.",
      "修复区域重载后挖墓之旅爱心消失的漏洞。" },
    { "This setting is always enabled in randomized save files.", "随机存档中此设置始终启用。" },
    { "Fixes Dampé going backwards in certain circumstances when the player is going backwards.", "修复玩家后退时达培倒退。" },
    { "Fixes kokiri animation state to match their text state when getting Zelda's Letter before Kokiri Emerald.",
      "修复获得卓拉之信前科克里动画状态与文字状态不匹配。" },
    { "Fixes the two raised floor switches, the one in Forest Temple Basement and the one at the top of Fire "
      "Temple. This will lower them, making activating them easier.",
      "修复森林神殿地下与火之神殿顶部的两个抬起地板开关，将其降低以便更易激活。" },
    { "Fixes one Zora's dialogue giving a hint about bringing Ruto's Letter to King Zora to properly occur "
      "before moving King Zora rather than after.",
      "修复某卓拉提示对话，使\"带茹特之信给卓拉之王\"在移动卓拉之王前而非之后出现。" },
    { "Prevents immediately falling off climbable surfaces if climbing on the edges.", "防止在边缘攀爬时立即掉落。" },
    { "Fixes the bushes to drop items correctly rather than spawning undefined items.", "修复灌木正确掉落道具而非生成未定义道具。" },
    { "Causes respawning enemies, like Stalchildren, to appear on land near bodies of water. "
      "Fixes an incorrect calculation that acted like water underneath ground was above it.",
      "使重生敌人（如斯塔儿童）出现在水边陆地。修复将地下水体误判为上方的水体计算错误。" },
    { "This option is forced on when Skip Text is enabled.", "启用\"跳过文字\"时此选项被强制开启。" },
    { "Prevents the Poacher's Saw softlock from mashing through the text, or with Skip Text enabled.",
      "防止偷猎者锯子因连按文字或启用跳过文字而卡死。" },
    { "Make Anubis Fireballs do Fire damage when reflected back at them with the Mirror Shield.",
      "用镜盾反弹时阿努比斯火球造成火焰伤害。" },
    { "Forces Goron City doors open if you somehow complete Fire Temple without talking to Goron Link "
      "and receiving the Goron Tunic.",
      "若未与格雷林克对话获得格雷外衣却完成火之神殿，强制打开格雷城大门。" },
    { "Prevents the Forest Stage Deku Nut upgrade from becoming unobtainable after receiving the Poacher's Saw.",
      "防止获得偷猎者锯子后德库坚果升级无法获取。" },
    { "Make the Megaton Hammer's crouch stab able to destroy rocks without first swinging it normally.",
      "使巨型锤下蹲刺击可直接破坏岩石，无需先普通挥砍。" },
    { "Make crouch stabbing always do the same damage as a regular slash.", "下蹲刺击伤害与普攻相同。" },
    { "This setting is forcefully enabled when you are playing a Randomizer.", "随机模式下此设置被强制启用。" },
    { "Fixes the Broken Giant's Knife flag not being reset when Medigoron fixes it.", "修复梅迪格雷修复时破裂巨人之刀标志未重置。" },
    { "Fixes camera slightly drifting to the left when standing still due to a math error. May impact certain glitches.",
      "修复静止时镜头因计算错误向左轻微漂移。可能影响某些漏洞。" },
    { "Fixes camera getting stuck on collision when standing still. Also fixes slight shift back in camera "
      "when Link stops moving. May impact certain glitches.",
      "修复静止时镜头卡在碰撞上。也修复林克停止移动时镜头轻微回移。可能影响某些漏洞。" },
    { "Fixes camera swing rate when the player falls off a ledge and the camera swings around. May impact certain glitches.",
      "修复玩家掉下边缘时镜头摆动速率。可能影响某些漏洞。" },
    { "Makes the L and R buttons in the pause menu the same color.", "暂停菜单 L 和 R 按钮同色。" },
    { "Removes the Dungeon Entrance icon on the top-left corner of the screen when no dungeon is present on the current map.",
      "当前地图无地牢时移除屏幕左上角地牢入口图标。" },
    { "Re-Enables the two-handed idle animation, a seemingly finished animation that was disabled on accident "
      "in the original game.",
      "重新启用双手待机动画——原版中意外被禁用的看似已完成的动画。" },
    { "Correctly centers the Navi text prompt on the HUD's C-Up button.", "正确居中 HUD C-Up 上的娜薇文字提示。" },
    { "Prevent the Gerudo Warrior's clothes changing color when changing Link's tunic or using bombs in front of her.",
      "防止更换林克外衣或在其面前用炸弹时格鲁德战士服装变色。" },
    { "Fixes authentic out of bounds texture reads, instead loading textures with the correct size.",
      "修复原版越界纹理读取，改为加载正确尺寸的纹理。" },
    { "Fixes Link's eyes being open in the opening cutscene when he is supposed to be sleeping.",
      "修复开场林克本应睡眠却睁眼。" },
    { "Fixes Adult Link having a backwards Left hand when holding the Megaton Hammer.", "修复成人林克持巨型锤时左手反向。" },
    { "Disabled: Paths vanish more the higher the resolution (Z-Fighting is based on resolution).\n"
      "Consistent: Certain paths vanish the same way in all resolutions.\n"
      "No Vanish: Paths do not vanish, Link seems to sink in to some paths.\n"
      "This might affect other decal effects.",
      "禁用：分辨率越高路径越易消失（Z 冲突取决于分辨率）。\n"
      "一致：某些路径在所有分辨率下以相同方式消失。\n"
      "不消失：路径不消失，林克似乎陷入某些路径。\n"
      "这可能影响其他贴花效果。" },
    { "Adds 5 higher pitches for the Silver Rupee Jingle for the rooms with more than 5 Silver Rupees. "
      "Only relevant for playthroughs involving Master Quest Dungeons.",
      "为超过 5 枚银卢比的房间增加 5 个更高音高的银卢比铃音。仅与包含 MQ 地牢的流程相关。" },
    { "Fixes Darunia's dancing speed so he dances to the beat of Saria's Song, like in the Original Game.",
      "修复达鲁尼亚跳舞速度，使其如原版般合着萨莉亚之歌的节拍跳舞。" },
    { "Extend certain credits scenes so the music lines up properly with the visuals. (PAL only)",
      "延长某些制作人员名单场景，使音乐与画面正确对齐。（仅 PAL）" },
    { "Restore the original red blood from NTSC 1.0/1.1. Disable for Green blood.", "还原 NTSC 1.0/1.1 的原始红血。关闭则为绿血。" },
    { "Restore pre-release behavior where defeating a Gold Skulltula will play a cutscene showing it die.",
      "还原击败黄金骷髅蜘蛛播放死亡过场的预发布行为。" },
    { "Restores an unfinished feature to pulsate the boss room icon when you are in the boss room.", "还原 Boss 房间图标脉动这一未完成的特性。" },
    { "Restore a bug from NTSC 1.0 that allows casting the Fishing Rod while using the Hover Boots.", "还原 NTSC 1.0 中悬浮靴时抛竿的漏洞。" },
    { "Restores N64 Weird Frames allowing weirdshots and weirdslides to behave the same as N64.", "还原 N64 诡异帧，使诡异 shot 与诡异 slide 与 N64 一致。" },
    { "Allows Bombchus to explode out of bounds. Similar to GameCube and Wii VC.", "允许炸弹鼠越界爆炸。类似 GameCube 与 Wii VC。" },
    { "Restore a bug from NTSC 1.0 that allows putting away an item without an animation and performing Putaway Ocarina Items.",
      "还原 NTSC 1.0 中无动画收起道具并执行收起时光之笛道具的漏洞。" },
    { "Restore a bug from NTSC 1.0 that allows bypassing Bongo Bongo's intro cutscene to quickly kill him.",
      "还原 NTSC 1.0 中跳过邦哥邦哥登场过场快速击杀的漏洞。" },
    { "Restores a bug from NTSC 1.0/1.1 that allows you to obtain the eyeball frog from King Zora instead of the Zora Tunic by Holding Shield.",
      "还原 NTSC 1.0/1.1 中持盾从卓拉之王获得大眼青蛙而非卓拉外衣的漏洞。" },
    { "Makes L and R switch pages like on the GameCube. Z opens the Debug Menu instead.", "使 L 和 R 如 GameCube 翻页。Z 改为打开调试菜单。" },
    { "Restores the wider range of certain shutter doors from NTSC 1.0.\nNotably affects Jabu-Jabu and boss doors.",
      "还原 NTSC 1.0 某些卷帘门更宽的范围。\n明显影响加卜加卜与 Boss 门。" },
    { "Restores NTSC 1.0 behavior where Link jumps over grave holes and grabs the ledges.", "还原 NTSC 1.0 林克跳过墓穴并抓住边缘的行为。" },
    { "When you lose 4 quarters of a heart you will permanently lose that Heart Container.\n\n"
      "Disabling this after the fact will restore your Heart Containers.",
      "失去 1 颗心（4 个心块）时永久失去该心之容器。\n\n事后关闭此选项将恢复心之容器。" },
    { "Modifies all sources of damage not affected by other sliders:\n"
      "2x: Can survive all common attacks from the start of the game.\n"
      "4x: Dies in 1 hit to any substantial attack from the start of the game.\n"
      "8x: Can only survive trivial damage from the start of the game.\n"
      "16x: Can survive all common attacks with max health without double defense.\n"
      "32x: Can survive all common attacks with max health and double defense.\n"
      "64x: Can survive trivial damage with max health without double defense.\n"
      "128x: Can survive trivial damage with max health and double defense.\n"
      "256x: Cannot survive damage.",
      "修改其他滑块未覆盖的所有伤害来源：\n"
      "2x：游戏开始即可承受所有常见攻击。\n"
      "4x：游戏开始受到任何实质攻击即一击死亡。\n"
      "8x：游戏开始仅能承受微不足道的伤害。\n"
      "16x：满血无双倍防御可承受所有常见攻击。\n"
      "32x：满血双倍防御可承受所有常见攻击。\n"
      "64x：满血无双倍防御可承受微不足道伤害。\n"
      "128x：满血双倍防御可承受微不足道伤害。\n"
      "256x：无法承受任何伤害。" },
    { "Modifies all fall damage:\n"
      "2x: Can survive all fall damage from the start of the game.\n"
      "4x: Can only survive short fall damage from the start of the game.\n"
      "8x: Cannot survive any fall damage from the start of the game.\n"
      "16x: Can survive all fall damage with max health without double defense.\n"
      "32x: Can survive all fall damage with max health and double defense.\n"
      "64x: Can survive short fall damage with double defense.\n"
      "128x: Cannot survive fall damage.",
      "修改所有坠落伤害：\n"
      "2x：游戏开始可承受所有坠落伤害。\n"
      "4x：游戏开始仅能承受短距离坠落伤害。\n"
      "8x：游戏开始无法承受任何坠落伤害。\n"
      "16x：满血无双倍防御可承受所有坠落伤害。\n"
      "32x：满血双倍防御可承受所有坠落伤害。\n"
      "64x：双倍防御可承受短距离坠落伤害。\n"
      "128x：无法承受坠落伤害。" },
    { "Modifies damage taken after falling into a void:\n"
      "2x: Can survive void damage from the start of the game.\n"
      "4x: Cannot survive void damage from the start of the game.\n"
      "8x: Can survive void damage twice with max health without double defense.\n"
      "16x: Can survive void damage with max health without double defense.\n"
      "32x: Can survive void damage with max health and double defense.\n"
      "64x: Cannot survive void damage.",
      "修改掉入虚空后的伤害：\n"
      "2x：游戏开始可承受虚空伤害。\n"
      "4x：游戏开始无法承受虚空伤害。\n"
      "8x：满血无双倍防御可承受两次虚空伤害。\n"
      "16x：满血无双倍防御可承受虚空伤害。\n"
      "32x：满血双倍防御可承受虚空伤害。\n"
      "64x：无法承受虚空伤害。" },
    { "Modifies Damage taken after Bonking.", "修改撞击所受伤害。" },
    { "Respawn with Full Health instead of 3 hearts.", "重生时满血而非 3 心。" },
    { "Disables Heart Drops, but not Heart Placements, like from a Deku Scrub running off.\n"
      "This simulates Hero Mode from other games in the series.",
      "禁用爱心掉落但不禁用爱心放置（如德库灌木逃跑时）。\n这模拟了系列其他作品中的英雄模式。" },
    { "Disables Random Drops, except from the Goron Pot, Dampe, and Bosses.", "禁用随机掉落（格雷壶、达培与 Boss 除外）。" },
    { "Bombchus will sometimes drop in place of Bombs.", "炸弹鼠有时会替代炸弹掉落。" },
    { "This setting is forcefully enabled because a randomized savefile with \"Enable Bombchu Drops\" is loaded.",
      "随机存档\"启用炸弹鼠掉落\"已载入，此设置被强制启用。" },
    { "Bonking into Trees will have a chance to drop up to 3 Sticks. Must have obtained sticks previously.",
      "撞树有几率掉落最多 3 根树枝。需此前已获得树枝。" },
    { "Adjusts rate Dampe drops flames during race.", "调整比赛中达培掉落火焰的速率。" },
    { "Dying will delete your file.\n\n" ICON_FA_EXCLAMATION_TRIANGLE " WARNING " ICON_FA_EXCLAMATION_TRIANGLE
      "\nTHIS IS NOT REVERSIBLE!\nUSE AT YOUR OWN RISK!",
      "死亡将删除你的存档。\n\n" ICON_FA_EXCLAMATION_TRIANGLE " 警告 " ICON_FA_EXCLAMATION_TRIANGLE
      "\n此操作不可逆！\n后果自负！" },
    { "-5 will be half as much time, +5 will be 6x as much time. Affects timed switches, torches, GTG statue "
      "eyes, & doors in race with Dampe.",
      "-5 为一半时间，+5 为 6 倍时间。影响定时开关、火把、GTG 雕像眼及与达培比赛中的门。" },
    { "Always get the Heart Piece/Purple Rupee from the Spinning Goron Pot.", "始终从旋转格雷壶获得爱心/紫卢比。" },
    { "Always win the Heart Piece/Purple Rupee on the first dig in Dampe's Grave Digging game. "
      "In a Randomizer file, this defaults to on if this enhancement has never been changed.",
      "始终在达培挖掘游戏首次挖掘获胜。随机存档中若从未改动此增强，默认开启。" },
    { "All dogs can be traded in and will count as Richard.", "所有狗都可交换并计为理查德。" },
    { "Cuccos will stay in place longer after putting them down, by a multiple of the value of the slider.",
      "咕咕放下后停留时间按滑块值的倍数延长。" },
    { "The amount of cuccos needed to receive bottle from Anju the Cucco Lady.", "从养鸡女安ju 处获得瓶子所需咕咕数。" },
    { "All Major Bosses move and act twice as fast.", "所有主要 Boss 移动与行动速度翻倍。" },
    { "All Regular Enemies and Mini-Bosses move and act twice as fast.", "所有普通敌人与迷你 Boss 移动与行动速度翻倍。" },
    { "The time between groups of Leevers spawning.", "利弗成群刷出的间隔。" },
    { "Turn on/off changes to the shooting gallery behavior.", "开启/关闭对射击场行为的改动。" },
    { "Skips the Shooting Gallery minigame.", "跳过射击场小游戏。" },
    { "Forces the rupee order to not be randomized as adult, making it the same as child.", "强制成人卢比顺序不随机，与童年相同。" },
    { "The ammunition at the start of the Shooting Gallery minigame as Child.", "童年射击场小游戏开始时的弹药。" },
    { "The ammunition at the start of the Shooting Gallery minigame as Adult.", "成人射击场小游戏开始时的弹药。" },
    { "Turn on/off changes to the Bombchu Bowling behavior.", "开启/关闭对炸弹鼠保龄球行为的改动。" },
    { "This option is disabled because \"Customize Behavior\" is turned off.", "此选项已禁用，因为\"自定义行为\"已关闭。" },
    { "This option is disabled because Shuffle Beehives is not enabled.", "此选项已禁用，因为\"洗牌蜂巢\"未启用。" },
    { "Prevents the small Cucco from appearing in the Bombchu Bowling minigame.", "防止小咕咕出现在炸弹鼠保龄球小游戏。" },
    { "Prevents the big Cucco from appearing in the Bombchu Bowling minigame.", "防止大咕咕出现在炸弹鼠保龄球小游戏。" },
    { "The number of Bombchus available at the start of the Bombchu Bowling minigame.", "炸弹鼠保龄球小游戏开始时的炸弹鼠数量。" },
    { "Turn on/off changes to the Frogs' Ocarina Game behavior.", "开启/关闭对青蛙时光之笛游戏行为的改动。" },
    { "Skips the Frogs' Ocarina Game.", "跳过青蛙时光之笛游戏。" },
    { "Removes the timer to play back the song.", "移除回放歌曲的计时器。" },
    { "Adjusts the time allowed for playback before failing.", "调整失败前允许的回放时间。" },
    { "Turn on/off changes to the Lost Woods Ocarina Game behavior.", "开启/关闭对迷失森林时光之笛游戏行为的改动。" },
    { "Skips the Lost Woods Ocarina Memory Game.", "跳过迷失森林时光之笛记忆游戏。" },
    { "Adjust the speed that the Skull Kids play the notes.", "调整骷髅儿童演奏音符的速度。" },
    { "Adjust the number of notes the Skull Kids play to start the first round.", "调整骷髅儿童第一轮起始演奏的音符数。" },
    { "Adjust the number of notes you need to play to end the first round.", "调整结束第一轮所需演奏的音符数。" },
    { "Adjust the number of notes you need to play to end the second round.", "调整结束第二轮所需演奏的音符数。" },
    { "Adjust the number of notes you need to play to end the third round.", "调整结束第三轮所需演奏的音符数。" },
    { "Amy's block pushing puzzle instantly solved.", "艾米的推块谜题瞬间解开。" },
    { "Turn on/off changes to the Fishing behavior.", "开启/关闭对钓鱼行为的改动。" },
    { "All fish will be caught instantly.", "所有鱼瞬间上钩。" },
    { "When a line is stable, guarantee bite. Otherwise use Default logic.", "线稳定时保证咬钩，否则使用默认逻辑。" },
    { "Once a hook as been set, Fish will never let go while being reeled in.", "一旦咬钩，收线时鱼绝不挣脱。" },
    { "Loaches will always appear in the fishing pond instead of every four visits.", "泥鳅始终出现在鱼塘，而非每四次访问一次。" },
    { "The Pond Owner will not ask to confirm if you want to keep a smaller Fish.", "鱼塘主不再询问是否保留较小的鱼。" },
    { "Every fish in the Fishing Pond will always be a Hyrule Loach.\n\nNOTE: This requires reloading the area.",
      "鱼塘中所有鱼始终为海拉鲁泥鳅。\n\n注意：需要重新加载区域。" },
    { "The minimum weight for the unique Fishing Reward as a child.", "童年独特钓鱼奖励的最小重量。" },
    { "The minimum weight for the unique fishing reward as an adult.", "成人独特钓鱼奖励的最小重量。" },
    { "Allows Link to bounce off walls when linear velocity is high enough, this is "
      "relevant when frequently being knocked back by traps, CC, or in Anchor.",
      "线性速度足够时林克可撞墙反弹，在与陷阱、CC 或锚点频繁被击退时有用。" },
    { "Mirrors the world horizontally:\n\n"
      " - Always: Always mirror the world.\n"
      " - Random: Randomly decide to mirror the world on each scene change.\n"
      " - Random (Seeded): Scenes are mirrored based on the current randomizer seed/file.\n"
      " - Dungeons: Mirror the world in Dungeons.\n"
      " - Dungeons (Vanilla): Mirror the world in Vanilla Dungeons.\n"
      " - Dungeons (MQ): Mirror the world in MQ Dungeons.\n"
      " - Dungeons Random: Randomly decide to mirror the world in Dungeons.\n"
      " - Dungeons Random (Seeded): Dungeons are mirrored based on the current randomizer seed/file.",
      "水平镜像世界：\n\n"
      " - 总是：始终镜像世界。\n"
      " - 随机：每次切换场景随机决定镜像。\n"
      " - 随机（固定种子）：场景依据当前随机种子/存档镜像。\n"
      " - 地牢：在地牢中镜像世界。\n"
      " - 地牢（原版）：在原版地牢中镜像。\n"
      " - 地牢（MQ）：在 MQ 地牢中镜像。\n"
      " - 地牢随机：在地牢中随机决定镜像。\n"
      " - 地牢随机（固定种子）：地牢依据当前随机种子/存档镜像。" },
    { "Enables Ivan the Fairy upon the next map change. Player 2 can control Ivan and press the C-Buttons to "
      "use items and mess with Player 1!",
      "下次切换地图启用仙女伊万。玩家 2 可控制伊万并按下 C 键使用道具、干扰玩家 1！" },
    { "Allows dogs to follow you anywhere you go, even if you leave the Market.", "允许狗随处跟随，即使离开集市。" },
    { "Rupees reduce over time, Link suffers damage when the count hits 0.", "卢比随时间减少，归零时林克受到伤害。" },
    { "Interval between Rupee reduction in Rupee Dash Mode.", "卢比冲刺模式中减少卢比的间隔。" },
    { "A Wallmaster follows Link everywhere, don't get caught!", "墙之主随处跟随林克，别被抓到！" },
    { "Changes Heart Piece and Heart Container functionality.\n\n"
      " - Each Heart Container or full Heart Piece reduces Link's Hearts by 1.\n"
      " - Can be enabled retroactively after a File has already started.",
      "改变爱心碎片与心之容器功能：\n\n"
      " - 每个心之容器或完整爱心碎片使林克的心减少 1。\n"
      " - 可在存档已开始后再启用。" },
    { "Enables additional Trap variants.", "启用额外陷阱变体。" },
    { "Allows any item to be equipped, regardless of age.\nAlso allows child to use adult strength upgrades.",
      "允许装备任意道具，不论年龄。也允许童年使用成人力量升级。" },
    { "Allows you to use any item at any location", "允许在任何地点使用任意道具。" },
    { "Makes every tunic have the effects of every other tunic.", "使每件外衣拥有其他所有外衣的效果。" },
    { "Prevents the Deku Shield from burning on contact with fire.", "防止德库盾接触火焰时燃烧。" },
    { "This allows you to put up for shield with any two-handed weapon in hand except for Deku Sticks.",
      "允许手持任何双手武器时举盾（德库木棒除外）。" },
    { "Makes every surface in the game hookshotable.", "使游戏内所有表面可被钩爪钩中。" },
    { "Allows you to walk through walls.", "允许穿墙。" },
    { "Makes every surface in the game climbable.", "使游戏内所有表面可攀爬。" },
    { "Holding L makes you float into the air.", "按住 L 让你浮空。" },
    { "Prevents ReDeads and Gibdos from being able to freeze you with their scream.", "防止 ReDead 与 Gibdo 用尖叫冻结你。" },
    { "Keese and Guay no longer target you and simply ignore you as if you were wearing the Skull Mask.",
      "凯西与瓜伊不再锁定你，如同你戴着骷髅面具般忽略你。" },
    { "Disables sandstorm effect in Haunted Wasteland.", "禁用鬼魅荒野的沙暴效果。" },
    { "Allows Z-Targeting Gold Skulltulas.", "允许锁定黄金骷髅蜘蛛。" },
    { "Continue holding START button when unpausing to only advance a single frame and then re-pause.",
      "取消暂停时继续按住 START 键，仅前进一帧后重新暂停。" },
    { "Passive Infinite Sword Glitch\nIt makes your sword's swing effect and hitbox stay active indefinitely.",
      "被动无限剑漏洞\n使剑的挥砍效果与判定框无限期保持激活。" },
    { "Gives you the glitched damage value of the quick put away glitch.", "给予你快速收起漏洞的异常伤害值。" },
    { "Clears the cutscene pointer to a value safe for wrong warps.", "将过场指针清除为适合错误传送的安全值。" },
    { "Drops from enemies, grass, etc. don't disappear after a set amount of time.", "敌人、草等掉落物不会在一段时间后消失。" },
    { "Prevents fish from automatically despawning after a while when dropped.", "防止鱼放下后一段时间自动消失。" },
    { "Prevents bugs from automatically despawning after a while when dropped.", "防止虫子放下后一段时间自动消失。" },
    { "Freezes the time of day.", "冻结时间。" },
    { "Syncs the in-game time with the real world time.", "将游戏内时间与现实时间同步。" },
    { "Switches Link's age and reloads the area.", "切换林克年龄并重新加载区域。" },
    { "Buttons that activate Speed Modifier 1.\n\n"
      "If \"Toggle modifier instead of holding\" is off, hold this combo to apply the modifier.\n"
      "If it is on, tap this combo to toggle the modifier on/off.",
      "激活速度修改器 1 的按键。\n\n"
      "若\"切换修改器而非按住\"关闭，按住此组合键应用修改器。\n"
      "若开启，轻按此组合键开关修改器。" },
    { "F5 to save, F6 to change slots, F7 to load", "F5 保存，F6 切换槽位，F7 载入。" },
    { "Turns on OoT Beta Quest. *WARNING*: This will reset your game!", "启用 OoT 测试版任务。*警告*：这将重置你的游戏！" },
    { "Set the Beta Quest world to explore. *WARNING*: Changing this will reset your game!\nCtrl+Click to type in a value.",
      "设置要探索的测试版任务世界。*警告*：更改将重置游戏！\nCtrl+点击输入数值。" },
    { "Enables the separate Cosmetics Editor Window.", "启用独立的外观编辑器窗口。" },
    { "Enables the separate Audio Editor Window.", "启用独立的音频编辑器窗口。" },
    { "Enables the separate Gameplay Stats Window.", "启用独立的游戏统计窗口。" },
    { "Enables the separate Time Splits Window.", "启用独立的时间分段窗口。" },
    { "Enables the separate Additional Timers Window.", "启用独立的附加计时器窗口。" },

    // ---- Enhancements — WIDGET_TEXT blocks ----
    { "Be sure to explore the Presets and Enhancements Menus for various Speedups and Quality of life changes!",
      "请探索预设与增强菜单中的各种加速与生活质量改动！" },
    { "These enhancements are only useful in the Randomizer mode but do not affect the randomizer logic.",
      "这些增强仅在随机模式中有用，但不影响随机逻辑。" },
    { "These are NOT like emulator states. They do not save your game progress and they WILL break across "
      "transitions and load zones (like doors). Support for related issues will not be provided.",
      "这些并非模拟器存档。它们不保存游戏进度，并且会在过场与加载区（如门）处失效。相关问题不予提供支持。" },

    // ===========================================================================
    //  Randomizer — static widget labels & tooltips
    // ===========================================================================
    { "Seed Entry", "种子输入" },
    { "Manual seed entry", "手动输入种子" },
    { "Characters from a-z, A-Z, and 0-9 are supported.\nCharacter limit is 1023, after which the seed will be truncated.",
      "支持 a-z、A-Z、0-9 字符。\n字符上限为 1023，超出部分将被截断。" },
    { "Seed", "种子" },
    { "Generate Randomizer", "生成随机种子" },
    { "Spoiler File", "剧透文件" },
    { "Rando-Relevant Navi Hints", "随机相关娜薇提示" },
    { "Replace Navi's overworld quest hints with rando-related gameplay hints.", "用随机相关的玩法提示替换娜薇的地表任务提示。" },
    { "Random Rupee Names", "随机卢比名称" },
    { "When obtaining Rupees, randomize what the Rupee is called in the textbox.", "获得卢比时，随机化文本框中卢比的名称。" },
    { "Use Custom Key Models", "使用自定义钥匙模型" },
    { "Use Custom graphics for Dungeon Keys, Big and Small, so that they can be easily told apart.",
      "为大、小地牢钥匙使用自定义图形，以便轻松区分。" },
    { "Map & Compass Colors Match Dungeon", "地图与罗盘颜色匹配地牢" },
    { "Matches the color of maps & compasses to the dungeon they belong to. This helps identify maps & "
      "compasses from afar and adds a little bit of flair.\n\n"
      "This only applies to seeds with maps & compasses shuffled to \"Any Dungeon\", \"Overworld\", or \"Anywhere\".",
      "将地图与罗盘颜色匹配其所属地牢，便于从远处辨认并增添特色。\n\n"
      "仅适用于地图与罗盘被随机到\"任意地牢\"、\"地表\"或\"任意位置\"的种子。" },
    { "Jabber Nut Colors Match Kind", "jabber 果颜色匹配种类" },
    { "With Shuffle Speak, jabber nut model & color will be generic.", "开启对话随机时，jabber 果的模型与颜色将为通用样式。" },
    { "Quest Item Fanfares", "任务道具典礼音乐" },
    { "Play unique fanfares when obtaining quest items (medallions/stones/songs). Note that these fanfares "
      "can be longer than usual.",
      "获得任务道具（勋章/石头/歌曲）时播放独特的典礼音乐。注意这些音乐可能比平时更长。" },
    { "Mysterious Shuffled Items", "神秘随机道具" },
    { "Displays a \"Mystery Item\" model in place of any freestanding/GS/shop items that were shuffled, and "
      "replaces item names for them and scrubs and merchants, regardless of hint settings, so you never "
      "know what you're getting.",
      "为任何被随机的独立道具/黄金骷髅蜘蛛/商店道具显示\"神秘道具\"模型，并替换它们以及灌木与商人的道具名，"
      "无论提示设置如何，使你永远不知道会得到什么。" },
    { "Simpler Boss Soul Models", "简化 Boss 灵魂模型" },
    { "When shuffling boss souls, they'll appear as a simpler model instead of showing the boss' models."
      "This might make boss souls more distinguishable from a distance, and can help with performance.",
      "随机 Boss 灵魂时，它们显示为更简单的模型而非 Boss 模型。这可能使 Boss 灵魂在远处更易辨认，并有助于性能。" },
    { "Skip Get Item Animations", "跳过获得道具动画" },
    { "Item Scale: %.2f", "道具大小：%.2f" },
    { "The size of the item when it is picked up.", "拾取时道具的大小。" },
    { "Signs Hint Entrances", "标志提示入口" },
    { "If enabled, signs near loading zones will tell you where they lead to.", "启用后，加载区附近的标志会显示其通向何处。" },
    { "Excluded Locations", "排除的地点" },
    { "Tricks/Glitches", "技巧/漏洞" },
    { "Popout Plandomizer Window", "弹出计划随机窗口" },
    { "Enables the separate Randomizer Settings Window.", "启用独立的随机器设置窗口。" },
    { "Toggle Item Tracker", "切换道具追踪" },
    { "Toggles the Item Tracker.", "切换道具追踪的显示。" },
    { "Popout Item Tracker Settings", "弹出道具追踪设置" },
    { "Enables the separate Item Tracker Settings Window.", "启用独立的道具追踪设置窗口。" },
    { "Toggle Entrance Tracker", "切换入口追踪" },
    { "Toggles the Entrance Tracker.", "切换入口追踪的显示。" },
    { "Popout Entrance Tracker Settings", "弹出入口追踪设置" },
    { "Enables the separate Entrance Tracker Settings Window.", "启用独立的入口追踪设置窗口。" },
    { "Toggle Check Tracker", "切换检查追踪" },
    { "Toggles the Check Tracker.", "切换检查追踪的显示。" },
    { "Popout Check Tracker Settings", "弹出检查追踪设置" },
    { "Enables the separate Check Tracker Settings Window.", "启用独立的检查追踪设置窗口。" },
    { "Leave blank for random seed", "留空为随机种子" },
    { "Connecting...##Sail", "连接中……##Sail" },
    { "Connected##Sail", "已连接##Sail" },
    { "Connecting...", "连接中……" },
    { "Connected", "已连接" },
    { "Enable##Sail", "启用##Sail" },
    { "Disable##Sail", "禁用##Sail" },
    { "Enable##CrowdControl", "启用##人群控制" },
    { "Disable##CrowdControl", "禁用##人群控制" },
    { "Host & Port", "主机与端口" },

    // ===========================================================================
    //  Dev Tools — labels & tooltips
    // ===========================================================================
    { "Warping", "传送" },
    { "Popout Menu", "弹出菜单" },
    { "Changes the menu display from overlay to windowed.", "将菜单显示从叠加模式改为窗口模式。" },
    { "Debug Mode", "调试模式" },
    { "Enables Debug Mode, allowing you to select maps with L + R + Z, noclip with L + D-pad Right, and open "
      "the debug menu with L on the pause screen.",
      "启用调试模式，允许用 L+R+Z 选择地图、L+方向右 穿墙、暂停界面按 L 打开调试菜单。" },
    { "Map Select Button Combination:", "地图选择按键组合：" },
    { "No Clip Button Combination:", "穿墙按键组合：" },
    { "OoT Registry Editor", "OoT 注册表编辑器" },
    { "Enables the registry editor.", "启用注册表编辑器。" },
    { "Debug Save File Mode", "调试存档模式" },
    { "Changes the behavior of debug file select creation (creating a save file on slot 1 with debug mode "
      "on):\n"
      "- Off: The debug save file will be a normal savefile.\n"
      "- Vanilla: The debug save file will be the debug save file from the original game.\n"
      "- Maxed: The debug save file will be a save file with all of the items & upgrades.",
      "改变调试存档创建行为（在调试模式开启时于槽位 1 创建存档）：\n"
      "- 关闭：调试存档为普通存档。\n"
      "- 原版：调试存档为原版游戏的调试存档。\n"
      "- 满级：调试存档为拥有全部道具与升级的存档。" },
    { "OoT Skulltula Debug", "OoT 骷髅蜘蛛调试" },
    { "Enables Skulltula Debug, when moving the cursor in the menu above various map icons (boss key, "
      "compass, map screen locations, etc.) will set the GS bits in that area.\n"
      "USE WITH CAUTION AS IT DOES NOT UPDATE THE GS COUNT!",
      "启用骷髅蜘蛛调试，在菜单中将光标移到各种地图图标上方（Boss 钥匙、罗盘、地图位置等）会设置该区域的骷髅蜘蛛位。\n"
      "谨慎使用，因为它不会更新骷髅蜘蛛计数！" },
    { "Resource logging", "资源记录" },
    { "Logs some resources as XML when they're loaded in binary format.", "资源以二进制格式加载时将其记录为 XML。" },
    { "Frame Advance", "帧前进" },
    { "This allows you to advance through the game one frame at a time on command. To advance a frame, hold Z "
      "and tap R on the second controller. Holding Z and R will advance a frame every half second. You can "
      "also use the buttons below.",
      "允许按需逐帧推进游戏。前进一帧：在第二手柄上按住 Z 并轻点 R。按住 Z 和 R 每半秒前进一帧。也可使用下方按钮。" },
    { "Advance 1", "前进 1 帧" },
    { "Advance 1 frame.", "前进 1 帧。" },
    { "Advance (Hold)", "前进（按住）" },
    { "Advance frames while the button is held.", "按住按钮时逐帧前进。" },
    { "Log Level", "日志级别" },
    { "The log level determines which messages are printed to the console. This does not affect the log file output",
      "日志级别决定哪些消息打印到控制台。不影响日志文件输出。" },
    { "Better Debug Warp Screen", "更好的调试传送界面" },
    { "Optimized Debug Warp Screen, with the added ability to chose entrances and time of day.",
      "优化的调试传送界面，并可选择入口与时段。" },
    { "Debug Warp Screen Translation", "调试传送界面翻译" },
    { "Translate the Debug Warp Screen based on the game language.", "根据游戏语言翻译调试传送界面。" },
    { "Warp Points", "传送点" },
    { "Enter warp point name...", "输入传送点名称..." },
    { "Popout Stats Window", "弹出统计窗口" },
    { "Enables the separate Stats Window.", "启用独立的统计窗口。" },
    { "Popout Console", "弹出控制台" },
    { "Enables the separate Console Window.", "启用独立的控制台窗口。" },
    { "Popout Save Editor", "弹出存档编辑器" },
    { "Enables the separate Save Editor Window.", "启用独立的存档编辑器窗口。" },
    { "Popout Hook Debugger", "弹出钩子调试器" },
    { "Enables the separate Hook Debugger Window.", "启用独立的钩子调试器窗口。" },
    { "Popout Collision Viewer", "弹出碰撞查看器" },
    { "Enables the separate Collision Viewer Window.", "启用独立的碰撞查看器窗口。" },
    { "Popout Actor Viewer", "弹出角色查看器" },
    { "Enables the separate Actor Viewer Window.", "启用独立的角色查看器窗口。" },
    { "Popout Display List Viewer", "弹出显示列表查看器" },
    { "Enables the separate Display List Viewer Window.", "启用独立的显示列表查看器窗口。" },
    { "Popout Value Viewer", "弹出数值查看器" },
    { "Enables the separate Value Viewer Window.", "启用独立的数值查看器窗口。" },
    { "Popout Message Viewer", "弹出信息查看器" },
    { "Enables the separate Message Viewer Window.", "启用独立的信息查看器窗口。" },
    { "Popout Gfx Debugger", "弹出图形调试器" },
    { "Enables the separate Gfx Debugger Window.", "启用独立的图形调试器窗口。" },

    // ===========================================================================
    //  Network — labels & tooltips
    // ===========================================================================
    { "The Network features are unavailable because SoH was compiled without network support "
      "(\"ENABLE_REMOTE_CONTROL\" build flag).",
      "网络功能不可用，因为 SoH 是在未启用网络支持（\"ENABLE_REMOTE_CONTROL\"编译标志）的情况下编译的。" },
    { "Sail is a networking protocol designed to facilitate remote control of the Ship of Harkinian "
      "client. It is intended to be utilized alongside a Sail server, for which we provide a few "
      "straightforward implementations on our GitHub. The current implementations available allow "
      "integration with Twitch chat and SAMMI Bot, feel free to contribute your own!\n"
      "\n"
      "Click this button to copy the link to the Sail Github page to your clipboard.",
      "Sail 是一种网络协议，旨在方便远程控制哈肯尼安之船客户端。它需配合 Sail 服务器使用，我们在 GitHub 上提供了几个简单实现。"
      "现有实现可与 Twitch 聊天和 SAMMI Bot 集成，欢迎贡献你自己的实现！\n\n"
      "点击此按钮可将 Sail GitHub 页面的链接复制到剪贴板。" },
    { "About Crowd Control", "关于人群控制" },
    { "Crowd Control is a platform that allows viewers to interact with a streamer's game in real time.\n"
      "\n"
      "Please head over to www.crowdcontrol.live for more information!",
      "人群控制是一个允许观众实时与主播游戏互动的平台。\n\n请前往 www.crowdcontrol.live 了解更多信息！" },
    { "Connect to Crowd Control", "连接到人群控制" },
    { "Additional Settings", "附加设置" },
    { "Enemy Name Tags", "敌人名称标签" },
    { "When viewers spawn enemies, the enemy will have a name tag above them with the viewer's name.",
      "观众生成敌人时，敌人头顶会显示带有观众名字的名称标签。" },
    { "Spawned Enemies Ignored Ingame", "生成的敌人忽略游戏内判定" },
    { "Enemies spawned by CrowdControl won't be considered for \"clear enemy rooms\", so they don't need "
      "to be killed to complete these rooms.",
      "人群控制生成的敌人不计入\"清空敌人房间\"，因此无需击杀它们来完成这些房间。" },

    { "This will completely erase the controls config, including registered devices.\nContinue?",
      "这将彻底清除控制器配置，包括已注册的设备。\n确定继续吗？" },

    // ---- Wind Waker Style sidebars ----
    { "Lights", "光照" },

    // ---- Wind Waker Style: Cel Shading ----
    { "Enable Cel Shading", "启用卡通描边" },
    { "Options", "选项" },
    { "Reset All to Defaults", "全部重置为默认值" },
    { "Ramp Center", "渐变中心" },
    { "Ramp Softness", "渐变柔和度" },
    { "Highlight Intensity", "高光强度" },
    { "Shadow Intensity", "阴影强度" },
    { "Point Light Range", "点光源范围" },
    { "Use Navi as a Light Source", "将娜薇作为光源" },
    { "Transition Time", "过渡时间" },
    { "Light Source Viewer", "光源查看器" },
    { "Highlight Lit Objects", "高亮被照亮物体" },
    { "Re-lights actors and objects with a single dominant light and a soft Wind Waker-style ramp. Only affects objects, not the static scene. Pairs well with cel-shaded texture packs.",
      "用单一主光源和柔和的风之杖风格渐变重新照亮角色与物体。仅影响物体，不影响静态场景。与卡通着色材质包搭配效果更佳。" },
    { "Resets all the Cel Shading sliders below to their default values.",
      "将所有下方的卡通描边滑块重置为默认值。" },
    { "Where the dark-to-light transition sits. Higher = more of the surface stays in shadow.",
      "明暗过渡所处的位置。数值越高，表面停留在阴影中的部分越多。" },
    { "Width of the transition band. Low = a hard cel edge; high = a softer gradient.",
      "过渡带的宽度。低 = 硬朗的卡通边缘；高 = 更柔和的渐变。" },
    { "Brightness of the lit side. Higher = brighter highlights.",
      "受光面的亮度。数值越高，高光越亮。" },
    { "How dark the shadow side gets. 0% = no shadow (flat), 100% = full shadow down to ambient.",
      "阴影面的暗度。0% = 无阴影（平面），100% = 完全降至环境光的阴影。" },
    { "Extends how far a point light can remain an object's key light, as a multiplier on its actual radius (key selection only — the game's real lighting is unchanged). Raise it so an orbiting fairy keeps lighting nearby objects even when it swings to its far side. 1x = the light's literal range.",
      "将点光源能够作为物体主光源的距离，按其实际半径的倍数延伸（仅影响主光源选择——游戏的真实光照不变）。调高后，环绕的精灵即使摆到远侧也能继续照亮附近物体。1x = 光源的实际范围。" },
    { "Let Navi count as a candidate key light for cel shading. Navi blinks on/off and orbits Link, so leaving this on makes the lighting on nearby objects shift around with her. Turn it off to ignore Navi and keep the key light steady (the sun/moon or a torch wins instead).",
      "让娜薇成为卡通着色的主光源候选。娜薇会闪烁并环绕林克，因此开启此项会让附近物体的光照随她移动。关闭则忽略娜薇，保持主光源稳定（由太阳/月亮或火把担任）。" },
    { "How long the key light takes to ease from one source to another. Higher = slower, more deliberate travel between the sun and a fairy/torch.",
      "主光源从一个来源缓动到另一个来源所需的时间。数值越高，太阳与精灵/火把之间的过渡越慢、越从容。" },
    { "Draws a debug ray from each actor for every candidate light (coloured by the light, longer when stronger), a cyan range ring around each point light, and a bold magenta needle down the chosen key light, so you can see which light is winning and where the key points.",
      "为每个候选光源从每个角色绘制一条调试光线（颜色随光源，越强越长）、每个点光源周围一圈青色范围环，以及指向所选主光源的醒目洋红色指针，便于查看当前哪个光源占优及其指向。" },
    { "Renders every cel-shaded object as flat white on the lit side and flat black in shadow (the texture is discarded), so it is obvious which draws are being relit — handy for confirming whether large surfaces like water or lava are getting relit.",
      "将每个卡通着色物体渲染为受光面纯白、阴影面纯黑（丢弃纹理），从而清晰显示哪些绘制被重新照亮——便于确认水面或岩浆等大表面是否已被重新照亮。" },

    // ---- Wind Waker Style: Lights ----
    { "Hide Vanilla Torch Glow", "隐藏原版火把光晕" },
    { "Improve Flame Flicker", "改进火焰闪烁" },
    { "Flicker Speed", "闪烁速度" },
    { "Navi's Light Tint", "娜薇的光晕染色" },
    { "Light Casting", "光池投射" },
    { "Enable Light Casting", "启用光池投射" },
    { "Use Wind Waker default movement", "使用风之杖默认运动" },
    { "Rotation Speed", "旋转速度" },
    { "Size Flicker", "大小闪烁" },
    { "Cast Size", "投射尺寸" },
    { "Light Intensity", "光照强度" },
    { "Enable Navi Light Casting", "启用娜薇光池投射" },
    { "Navi Cast Size", "娜薇投射尺寸" },
    { "Navi Light Intensity", "娜薇光照强度" },
    { "Enable Other Fairy Light Casting", "启用其他精灵光池投射" },
    { "Other Fairy Cast Size", "其他精灵投射尺寸" },
    { "Other Fairy Intensity", "其他精灵光照强度" },
    { "Show Light Spheres", "显示光球" },
    { "Hides the original flat, billboarded, flickering glow circle the game draws over torches and other glow lights (it clashes with the cast pools). Applies while Light Casting is on.",
      "隐藏游戏在火把和其他发光光源上绘制的原始平面、公告板式、闪烁的光晕圈（它与投射光池冲突）。在\"光池投射\"开启时生效。" },
    { "Replaces the game's fast, jagged per-frame torch/flame flicker with a slow, organic Wind Waker flicker. Applied at the source, so it affects the vanilla scene lighting and Cel Shading even when Light Casting is off.",
      "用缓慢、自然的风之杖风格闪烁，替换游戏原本快速、尖锐的逐帧火把/火焰闪烁。在源头应用，因此即使\"光池投射\"关闭，也会影响原版场景光照与卡通着色。" },
    { "How often flames pick a new brightness for the Wind Waker flicker. Higher = faster; lower = a lazier flame.",
      "火焰为风之杖风格闪烁选择新亮度的频率。越高越快；越低火焰越慵懒。" },
    { "Enable \"Improve Flame Flicker\" to adjust this.", "启用\"改进火焰闪烁\"以调整此项。" },
    { "Tints Navi's light toward her current colour. Her light is normally white, but she changes colour when targeting (yellow on enemies, and so on); raise this to let a little of that colour through. Applied at the source, so it tints her cast pool, the objects she lights under Cel Shading, and the vanilla lighting alike. 0% = white.",
      "将娜薇的光晕染向她当前的颜色。她的光通常是白色，但锁定目标时会变色（敌人为黄色等）；调高可让少量该颜色透出。在源头应用，因此会同时染上她的投射光池、卡通着色下她照亮的物体以及原版光照。0% = 白色。" },
    { "Casts a pool of light from each point light (torch, fairy, ...) onto the surrounding world geometry, Wind Waker-style. Affects only the static world, not actors/objects (lit by Cel Shading).",
      "以风之杖风格，从每个点光源（火把、精灵……）向周围世界几何体投射一片光池。仅影响静态世界，不影响角色/物体（由卡通着色照亮）。" },
    { "Pins the pool's tumble and size pulse to the authentic Wind Waker rates. Turn off to reveal and set Rotation Speed and Size Flicker yourself.",
      "将光池的翻滚与大小脉动固定为原版风之杖的速率。关闭后可自行设定\"旋转速度\"和\"大小闪烁\"。" },
    { "Speed of the Wind Waker two-axis tumble that animates the pool's faceted edges, as a multiplier on the authentic rate. 1.0 = authentic; 0 = static.",
      "风之杖双轴翻滚的速度，用于让光池的多面边缘动起来，为原版速率的倍数。1.0 = 原版；0 = 静止。" },
    { "Depth of the Wind Waker size pulse — the pool's dominant flicker. The orb gently grows/shrinks on a slow random walk (re-rolled every ~0.2 s, eased). 1.0 = authentic (~5%); 0 = steady. (Navi is excluded — she isn't a flame.)",
      "风之杖大小脉动的深度——光池的主要闪烁。光球在缓慢随机游走中轻轻胀缩（每约 0.2 秒重掷并缓动）。1.0 = 原版（约 5%）；0 = 稳定。（娜薇除外——她不是火焰。）" },
    { "Size of each light's cast pool, as a multiplier on the light's radius. Smaller keeps the pool tight around the source; larger spreads it wider.",
      "每个光源投射光池的尺寸，为光源半径的倍数。越小光池越紧贴光源；越大铺得越广。" },
    { "Brightness of the cast light pools.", "投射光池的亮度。" },
    { "Also cast a pool from Link's fairy (Navi). Navi darts around quickly, so her pool moves a lot.",
      "同时由林克的精灵（娜薇）投射光池。娜薇移动很快，因此她的光池移动幅度很大。" },
    { "Navi's pool size, separate from the main Cast Size, so you can keep Navi tight without shrinking the torches.",
      "娜薇光池的尺寸，独立于主\"投射尺寸\"，因此可在不缩小火把的情况下让娜薇保持紧凑。" },
    { "Navi's pool brightness, separate from the main Light Intensity.",
      "娜薇光池的亮度，独立于主\"光照强度\"。" },
    { "Makes non-Navi fairies emit light (they don't in vanilla): the fairies that drift around places like Kokiri Forest, and the healing fairies found out in the world (the magic one casts a wider pool). Since it turns them into real light sources, they then cast light pools AND can light nearby objects via Cel Shading, the same as Navi. A cluster of them can make the lighting busy.",
      "让非娜薇的精灵发光（原版中不会）：在科克里森林等地游荡的精灵，以及世界上能找到的治疗精灵（魔法精灵的光池更大）。由于它们变成了真实光源，会同时投射光池，并能像娜薇一样通过卡通着色照亮附近物体。一群聚集时可能让光照显得杂乱。" },
    { "Pool size for non-Navi fairies (Kokiri Forest fairies + the healing fairies), separate from torches and Navi. The magic (big) fairy is already larger than the rest.",
      "非娜薇精灵的光池尺寸（科克里森林精灵 + 治疗精灵），独立于火把和娜薇。魔法（大）精灵本身已比其他精灵更大。" },
    { "Pool brightness for non-Navi fairies, separate from the main Light Intensity.",
      "非娜薇精灵的光池亮度，独立于主\"光照强度\"。" },
    { "Overlays a translucent faceted shell of each light's icosphere — the volume used for its cast pool — tinted by the light, so you can see where the pools are, their size, and their spin. (The renderer has no line primitive, so this is a shell rather than a true wireframe.)",
      "叠加每个光源二十面体的半透明多面外壳——即其投射光池所用的体积——按光源染色，便于查看光池的位置、大小与旋转。（渲染器没有线段图元，因此这是外壳而非真正的线框。）" },

    // ---- Wind Waker Style: Actor Shadows ----
    { "Deku Stick", "德库木棒" },
    { "Enable Deku Stick Light Casting", "启用德库木棒光池投射" },
    { "Deku Stick Cast Size", "德库木棒投射尺寸" },
    { "Enable Actor Shadows", "启用角色阴影" },
    { "Suppress Vanilla Shadows", "隐藏原版阴影" },
    { "Shadows on Walkable Actors", "可行走角色上的阴影" },
    { "Opacity", "不透明度" },
    { "Length", "长度" },
    { "Slab Depth", "板厚度" },
    { "Slab Rise", "板抬升" },
    { "Render Distance: %d", "渲染距离：%d" },
    { "Show Shadow Volume", "显示阴影体积" },
    { "Makes a lit, held Deku stick a real light source at its burning tip (it isn't in vanilla). Like a torch it lights nearby objects via Cel Shading and casts their shadows, and — with Light Casting on — casts its own pool on the world. This one toggle controls all three.",
      "让点燃并持有的德库木棒在其燃烧顶端成为真实光源（原版中不是）。如同火把，它通过卡通着色照亮附近物体并投射其阴影，且——在\"光池投射\"开启时——在世界表面投射自己的光池。这一个开关同时控制这三者。" },
    { "The held Deku stick's pool size, separate from torches, so you can size the stick's pool on its own.",
      "所持德库木棒的光池尺寸，独立于火把，因此可单独调整木棒的光池大小。" },
    { "Replaces the vanilla actor shadows with a shape-based drop shadow for each actor (Link, NPCs, enemies, items, ...): its own silhouette cast from the single key light Cel Shading picks, wrapped onto the real ground so it follows slopes and bumps. Off by default (vanilla shadows). Uses the Cel Shading key selection, but works whether or not Cel Shading itself is on.",
      "用基于形状的落影替换原版角色阴影，为每个角色（林克、NPC、敌人、道具……）生成：从卡通着色所选的单一主光源投射其自身轮廓，贴合真实地面以跟随斜坡与起伏。默认关闭（原版阴影）。使用卡通着色的主光源选择，但无论卡通着色是否开启都能工作。" },
    { "Hide the original game's actor shadows (Link's feet, the NPC/enemy circles, the horse shadow, the sign and snake-statue texture shadows) so only the new shape shadows show. Turn off to draw both.",
      "隐藏游戏原版的角色阴影（林克的脚、NPC/敌人圆圈、马匹阴影、招牌与蛇像纹理阴影），仅显示新的形状阴影。关闭则两者都绘制。" },
    { "Let shadows fall on a few \"floors\" that the game spawns as actors instead of room geometry — the castle-town drawbridge, the Gerudo Valley bridge, and some dungeon platforms. They are drawn just before the shadows so the shadows land on them like normal ground. Off = those surfaces show no shadow (the original behaviour).",
      "让阴影落在一些游戏以角色而非房间几何体生成的\"地板\"上——城堡镇吊桥、格鲁德大峡谷大桥，以及部分迷宫平台。它们在阴影之前绘制，因此阴影会像落在普通地面一样落在它们上面。关闭 = 这些表面不显示阴影（原版行为）。" },
    { "Resets all the Actor Shadows sliders below to their default values.",
      "将所有下方的\"角色阴影\"滑块重置为默认值。" },
    { "How dark the shadow's core is. 0 = invisible; higher = darker.",
      "阴影核心的暗度。0 = 不可见；越高越暗。" },
    { "How long the shadow may get. The key light is raised toward straight-overhead before projecting, so a low light still casts a short shadow tucked under the actor (like the vanilla shadow). Lower = always short and steep; higher = lets a low light stretch the shadow out further.",
      "阴影可能达到的长度。投影前主光源被抬高至接近正上方，因此低角度光源仍会投出紧贴角色下方的短阴影（类似原版阴影）。越低 = 始终短而陡；越高 = 允许低角度光源将阴影拉得更长。" },
    { "How far below the feet the shadow conforms to the ground. The shadow is a thin stencil 'slab' at the feet that wraps onto whatever ground is inside it. Higher = follows ground that dips further (steeper inclines), but past a ledge the shadow creeps further down the drop. Lower = clings tight to the feet and won't spill over cliff edges, but may clip on steep slopes.",
      "阴影在脚底下方贴合地面的深度。阴影是脚边一层薄薄的模板\"板\"，包裹其范围内的任意地面。越高 = 能跟随下凹更深的地面（更陡的斜坡），但越过崖沿后阴影会向更下方蔓延。越低 = 紧贴脚底、不会溢出崖边，但在陡坡上可能出现穿模。" },
    { "How far ABOVE the feet the shadow can climb onto rising ground. Raise this so the shadow still appears where an incline rises higher than the actor's feet (without it, the shadow vanishes on up-slopes). Too high starts to catch the actor's own lower legs, so keep it just above the ground rise you need.",
      "阴影能沿上升地面爬升到脚底上方多高。调高后，在斜坡升得比角色脚底更高处阴影仍会出现（否则在上坡时阴影会消失）。过高会开始捕捉角色自身的小腿，因此只需略高于你所需的地面升高量。" },
    { "Performance: actors farther than this from the camera get no shape shadow (each shadow redraws the actor's whole silhouette once per tap, so distant ones cost more than they're worth). Lower to gain frames in crowded scenes; raise for shadows that stay visible into the distance.",
      "性能：距离相机超过此值的角色不显示形状阴影（每个阴影在每次轻触时重绘角色整个轮廓，因此远处阴影得不偿失）。在拥挤场景中调低以获得帧数；调高则让阴影在更远处仍可见。" },
    { "Draws the actual 3D shadow volume translucently so you can see its shape: black top/bottom caps, blue side walls. The ground inside this volume is what gets shadowed.",
      "半透明地绘制真实的 3D 阴影体积，便于查看其形状：黑色顶/底盖、蓝色侧壁。此体积内部的地面即为被阴影覆盖的部分。" },

    // ---- Wind Waker Style: Sky ----
    { "Use Sky", "使用天空" },
    { "Horizon", "地平线" },
    { "Horizon Height", "地平线高度" },
    { "Horizon Parallax", "地平线视差" },
    { "Sky Gradient", "天空渐变" },
    { "Replace Sky Texture", "替换天空纹理" },
    { "Gradient Brightness", "渐变亮度" },
    { "Clouds", "云" },
    { "Enable Clouds", "启用云" },
    { "Coverage", "覆盖率" },
    { "Drift Speed", "漂移速度" },
    { "Stars", "星星" },
    { "Enable Stars", "启用星星" },
    { "Star Count", "星星数量" },
    { "Star Brightness", "星星亮度" },
    { "Twinkle Speed", "闪烁速度" },
    { "Wind Wisps", "风丝" },
    { "Enable Wind Wisps", "启用风丝" },
    { "Wisp Amount", "风丝数量" },
    { "Wisp Speed", "风丝速度" },
    { "Split-Screen Compare", "分屏对比" },
    { "Replaces the overworld sky with a Wind Waker-style one: a gradient sky dome, drifting puffy clouds with a wispy horizon cloud band, and a twinkling night starfield. Each part can be toggled and tuned below. Texture packs can swap in different cloud art.",
      "用风之杖风格的天空替换地面世界天空：渐变天穹、漂浮的蓬松云朵与朦胧的地平线云带，以及闪烁的夜晚星空。各部分均可在下方单独开关与调节。材质包可替换不同的云朵美术。" },
    { "Raises or lowers the sky's horizon line — the gradient's haze boundary and the horizon cloud band move together. Useful where the visible horizon sits below eye level, like the middle of Hyrule Field.",
      "抬高或降低天空的地平线——渐变的雾气边界与地平线云带会一起移动。在可见地平线低于视线高度（如海拉鲁平原中部）时很有用。" },
    { "How much the sky horizon sinks as the camera climbs. 0% = it follows the camera, always at the same height on screen; 100% = it stays at a fixed world height, so hilltops rise in front of it and valleys look out over it.",
      "相机升高时天空地平线下沉的程度。0% = 跟随相机，在屏幕上始终同一高度；100% = 保持固定的世界高度，因此山顶会从它前方升起、山谷从它上方远眺。" },
    { "Replaces the sky texture with a smooth Wind Waker-style gradient, fading from a hazy horizon up to a deeper sky. The colours shift with the time of day through dawn, dusk and night.",
      "用平滑的风之杖风格渐变替换天空纹理，从朦胧的地平线淡入更深的天空。颜色随一天中的黎明、黄昏与夜晚而变换。" },
    { "Overall brightness of the sky gradient. Raise for a more vivid sky, lower for a moodier one.",
      "天空渐变的整体亮度。调高让天空更鲜明，调低则更显静谧。" },
    { "Drifting Wind Waker-style puffy clouds across the sky, plus the wispy cloud band around the horizon, both riding the wind.",
      "天空中漂浮的风之杖风格蓬松云朵，以及环绕地平线的朦胧云带，两者都随风飘动。" },
    { "How opaque the clouds are.", "云的透明度（不透明度）。" },
    { "How much of the sky the clouds fill — from a few scattered clouds up to fully overcast.",
      "云朵覆盖天空的比例——从零星散云到完全阴天。" },
    { "How fast the clouds drift across the sky on the wind. 1x is Wind Waker's own speed.",
      "云朵随风横越天空的速度。1x 即风之杖自身的速率。" },
    { "A Wind Waker-style twinkling starfield over the night sky: a fixed bright constellation plus hundreds of small stars that shimmer, fading in at dusk and out at dawn.",
      "夜空中风之杖风格的闪烁星空：一组固定的明亮星座，加上数百颗微微闪烁的小星，在黄昏淡入、黎明淡出。" },
    { "Maximum number of stars at full night (the visible count rises and falls with the time of day). Wind Waker uses 1000.",
      "满夜时星星的最大数量（可见数量随一天中的时间增减）。风之杖使用 1000 颗。" },
    { "Overall star brightness. Higher = brighter, more prominent stars.",
      "星星的整体亮度。越高越亮、越醒目。" },
    { "How fast the stars pulse. 1x is Wind Waker's rate — about ten seconds per cycle.",
      "星星闪烁的快慢。1x 即风之杖的速率——约每十秒一个周期。" },
    { "Wind Waker's white wind streaks curling through the sky — occasionally pulling a full loop-de-loop. Their number follows the wind's strength.",
      "风之杖的白色风纹在天空中盘旋——偶尔还会来个完整的翻圈。其数量随风力强弱变化。" },
    { "How many wisps ride the wind (their number also rises and falls with the wind's strength). 1x is Wind Waker's own count.",
      "有多少风丝随风而行（其数量也随风力强弱增减）。1x 即风之杖自身的数量。" },
    { "How fast the wisps fly. 1x is Wind Waker's own speed. The whole flight path scales together, so the curls and loops keep their shape; slower wisps also leave shorter streaks.",
      "风丝飞行的快慢。1x 即风之杖自身的速率。整条飞行路径会一同缩放，因此卷曲与翻圈保持形状；较慢的风丝留下的拖痕也更短。" },
    { "Draws the Wind Waker sky only on the left half of the screen, leaving the original sky visible on the right — a live side-by-side comparison.",
      "仅在屏幕左半边绘制风之杖天空，右半边保留原版天空——形成实时的左右对比。" },

    // ---- Randomizer group / section / sidebar names ----
    { "Logic/Access", "逻辑/通行" },
    { "Win Condition", "胜利条件" },
    { "Area Access", "区域通行" },
    { "Entrances", "入口" },
    { "Dungeon Items", "地牢道具" },
    { "Master Quest", "大师任务" },
    { "Keyrings", "钥匙环" },
    { "Shuffle Items", "洗牌道具" },
    { "Shuffle Shops & Merchants", "洗牌商店与商人" },
    { "Additional Items", "额外道具" },
    { "Hints", "提示" },
    { "Traps", "陷阱" },
    { "Static Hints", "静态提示" },
    { "Equips", "装备" },
    { "Normal Songs", "普通歌曲" },
    { "Warp Songs", "传送歌曲" },
    { "Logical Tricks", "逻辑技巧" },
    { "Logic Options", "逻辑选项" },
    { "Shuffle Dungeon Quest", "洗牌地牢任务" },
    { "Open Settings", "开放设置" },
    { "World Settings", "世界设置" },
    { "Shuffle Settings", "洗牌设置" },
    { "Shuffles", "洗牌" },
    { "Hints/Traps", "提示/陷阱" },
    { "Starting Items", "初始道具" },

    // ---- Randomizer combobox value strings ----
    { "Adult", "成人" },
    { "Advancement", "进阶" },
    { "Age Restricted", "年龄限制" },
    { "All But Beans", "除魔豆外全部" },
    { "All Crates", "所有木箱" },
    { "All Grass", "所有草丛" },
    { "All Items", "所有道具" },
    { "All Pots", "所有陶罐" },
    { "All Tokens", "所有令牌" },
    { "Always open", "始终开放" },
    { "Ambiguous", "模糊" },
    { "Any Dungeon", "任意地牢" },
    { "Anything", "任意" },
    { "Anywhere", "任意地点" },
    { "Balanced", "均衡" },
    { "Bean Merchant Only", "仅魔豆商人" },
    { "Cheap Balanced", "廉价均衡" },
    { "Child", "儿童" },
    { "Closed", "关闭" },
    { "Closed as child", "儿童时期关闭" },
    { "Completed", "已完成" },
    { "Condensed Progressive", "精简进阶" },
    { "Count", "数量" },
    { "Deku Only", "仅德库" },
    { "Don't Skip", "不跳过" },
    { "Dungeon Reward", "地牢奖励" },
    { "Dungeon rewards", "地牢奖励" },
    { "End of Dungeons", "地牢末尾" },
    { "Fairy Ocarina", "精灵陶笛" },
    { "Fast", "快速" },
    { "Fixed", "固定" },
    { "Free", "自由" },
    { "Full", "完整" },
    { "Ganon's Boss Key", "盖侬的 Boss 钥匙" },
    { "Glitchless", "无故障" },
    { "Greg", "格雷格" },
    { "Greg as Reward", "格雷格作为奖励" },
    { "Greg as Wildcard", "格雷格作为万能替换" },
    { "LACS-Dungeons", "LACS-地牢" },
    { "LACS-Medallions", "LACS-徽章" },
    { "LACS-Rewards", "LACS-奖励" },
    { "LACS-Stones", "LACS-石" },
    { "LACS-Tokens", "LACS-令牌" },
    { "LACS-Vanilla", "LACS-原版" },
    { "Mask of Truth", "真实面具" },
    { "Medallion", "徽章" },
    { "Medallions", "徽章" },
    { "Minimal", "最少" },
    { "Need Nothing", "无需任何条件" },
    { "No", "否" },
    { "No Hints", "无提示" },
    { "No Logic", "无逻辑" },
    { "Logic", "逻辑" },
    { "Nothing", "无" },
    { "Obscure", "冷门" },
    { "Ocarina of Time", "时之陶笛" },
    { "On", "开启" },
    { "On (Pack)", "开启（打包）" },
    { "On (Separate)", "开启（分离）" },
    { "On + Ganon", "开启 + 盖侬" },
    { "One-Time Only", "仅一次" },
    { "Open", "开放" },
    { "Overworld", "地面世界" },
    { "Own Dungeon", "自身地牢" },
    { "Plentiful", "丰富" },
    { "Progressive", "进阶" },
    { "Progressive Bags", "进阶背包" },
    { "Random Number", "随机数" },
    { "Range", "范围" },
    { "Scarce", "稀少" },
    { "Selection", "选择" },
    { "Selection Only", "仅选择" },
    { "Set By Wallet", "由钱包设定" },
    { "Set Number", "设定数量" },
    { "Shuffle", "洗牌" },
    { "Shuffle Both", "两者都洗牌" },
    { "Shuffle Fishing Pond", "洗牌钓鱼池" },
    { "Shuffle only Hyrule Loach", "仅洗牌海拉鲁泥鳅" },
    { "Shuffle Overworld Fish", "洗牌地面世界鱼类" },
    { "Simple", "简单" },
    { "Single Bag", "单一背包" },
    { "Skip", "跳过" },
    { "Song Locations", "歌曲地点" },
    { "Song only", "仅歌曲" },
    { "Specific Count", "指定数量" },
    { "Standard Reward", "标准奖励" },
    { "Standard Rewards", "标准奖励" },
    { "Start With", "起始携带" },
    { "Stone", "石" },
    { "Stone of Agony", "振动石" },
    { "Stones", "石" },
    { "Strong", "强" },
    { "Tokens", "令牌" },
    { "Useless", "无用" },
    { "Very Strong", "极强" },
    { "Win", "胜利" },
    { "x1", "x1" },
    { "x1/2", "x1/2" },
    { "x16", "x16" },
    { "x2", "x2" },
    { "x4", "x4" },
    { "x8", "x8" },
    { "Yes", "是" },

    // ---- Randomizer option names (A) ----
    { "10 GS Hint", "10 金骷髅提示" },
    { "100 GS Hint", "100 金骷髅提示" },
    { "20 GS Hint", "20 金骷髅提示" },
    { "30 GS Hint", "30 金骷髅提示" },
    { "40 GS Hint", "40 金骷髅提示" },
    { "50 GS Hint", "50 金骷髅提示" },
    { "Additional Ice Traps", "额外冰冻陷阱" },
    { "All Locations Reachable", "所有地点均可达" },
    { "Base Ice Traps", "基础冰冻陷阱" },
    { "Big Poe Target Count", "大波克目标数量" },
    { "Big Poes Hint", "大波克提示" },
    { "Biggoron's Hint", "大葛葛龙提示" },
    { "Blue Fire Arrows", "蓝火焰箭" },
    { "Bombchu Bag", "炸弹鼠袋" },
    { "Bombchu Drops", "炸弹鼠掉落" },
    { "Boss Door Hints", "Boss 门提示" },
    { "Boss Entrances", "Boss 入口" },
    { "Boss Key Shuffle", "Boss 钥匙洗牌" },
    { "Bottom of the Well Keyring", "井底钥匙环" },
    { "Bottom of the Well Quest", "井底任务" },
    { "Bridge Dungeon Count", "桥梁地牢数量" },
    { "Bridge Medallion Count", "桥梁徽章数量" },
    { "Bridge Reward Count", "桥梁奖励数量" },
    { "Bridge Reward Options", "桥梁奖励选项" },
    { "Bridge Stone Count", "桥梁石数量" },
    { "Bridge Token Count", "桥梁令牌数量" },
    { "Chickens Hint", "鸡提示" },
    { "Closed Forest", "封闭森林" },
    { "Damage Multiplier", "伤害倍率" },
    { "Dampe's Diary Hint", "达培日记提示" },
    { "Decouple Entrances", "解耦入口" },
    { "Deku Tree Quest", "德库树任务" },
    { "Dodongo's Cavern Quest", "多东哥洞穴任务" },
    { "Door of Time", "时之门" },
    { "Dungeon Entrances", "地牢入口" },
    { "Fire Temple Keyring", "火之神殿钥匙环" },
    { "Fire Temple Quest", "火之神殿任务" },
    { "Fishing Pole Hint", "钓竿提示" },
    { "Fishsanity", "鱼类收集" },
    { "Forest Temple Keyring", "森林神殿钥匙环" },
    { "Forest Temple Quest", "森林神殿任务" },
    { "Fortress Carpenters", "堡垒木匠" },
    { "Frog Ocarina Game Hint", "青蛙陶笛游戏提示" },
    { "Full Wallets", "满钱包" },
    { "Ganon's Castle Keyring", "盖侬城堡钥匙环" },
    { "Ganon's Castle Quest", "盖侬城堡任务" },
    { "Ganon's Tower Entrance", "盖侬塔入口" },
    { "Ganon's Trials", "盖侬试炼" },
    { "Ganon's Trials Count", "盖侬试炼数量" },
    { "Ganondorf Hint", "盖侬道夫提示" },
    { "GCBK Dungeon Count", "GCBK 地牢数量" },
    { "GCBK LACS Reward Options", "GCBK LACS 奖励选项" },
    { "GCBK Medallion Count", "GCBK 徽章数量" },
    { "GCBK Reward Count", "GCBK 奖励数量" },
    { "GCBK Stone Count", "GCBK 石数量" },
    { "GCBK Token Count", "GCBK 令牌数量" },
    { "Gerudo Fortress Keyring", "格鲁德要塞钥匙环" },
    { "Gerudo Fortress Keys", "格鲁德要塞钥匙" },
    { "Gerudo Training Ground Keyring", "格鲁德训练场钥匙环" },
    { "Gerudo Training Ground Quest", "格鲁德训练场任务" },
    { "Gold Skulltula Tokens", "金色骷髅蜘蛛代币" },
    { "Gossip Stone Hints", "闲话石提示" },
    { "Greg the Green Rupee Hint", "绿色卢比格雷格提示" },
    { "Grottos Entrances", "洞穴入口" },
    { "Hint Clarity", "提示清晰度" },
    { "Hint Distribution", "提示分布" },
    { "Horseback Archery Hint", "马背射箭提示" },
    { "Hyrule Loach Hint", "海拉鲁泥鳅提示" },
    { "Ice Cavern Quest", "冰之洞窟任务" },
    { "Ice Trap Percent", "冰冻陷阱百分比" },
    { "Include Tycoon Wallet", "包含大亨钱包" },
    { "Infinite Upgrades", "无限升级" },
    { "Interior Entrances", "室内入口" },
    { "Item Pool", "道具池" },
    { "Jabu-Jabu", "加卜加卜" },
    { "Jabu-Jabu's Belly Quest", "加卜加卜之腹任务" },
    { "Kakariko Gate", "卡卡利科大门" },
    { "Key Rings", "钥匙环" },
    { "Keyring Dungeon Count", "钥匙环地牢数量" },
    { "Link's Pocket", "林克的口袋" },
    { "Link's Pocket Reward Type", "林克口袋奖励类型" },
    { "Lock Overworld Doors", "锁定地面世界门" },
    { "Malon Hint", "玛隆提示" },
    { "Maps/Compasses", "地图/指南针" },
    { "Mask Quest", "面具任务" },
    { "Mask Shop Hint", "面具商店提示" },
    { "Medallion Locked Trials", "徽章锁定试炼" },
    { "Merchant Adult Wallet Weight", "商人成人钱包权重" },
    { "Merchant Affordable Prices", "商人可负担价格" },
    { "Merchant Child Wallet Weight", "商人儿童钱包权重" },
    { "Merchant Fixed Price", "商人固定价格" },
    { "Merchant Giant Wallet Weight", "商人巨人钱包权重" },
    { "Merchant Hint Text", "商人提示文本" },
    { "Merchant Lower Bound", "商人下限" },
    { "Merchant No Wallet Weight", "商人无钱包权重" },
    { "Merchant Prices", "商人价格" },
    { "Merchant Tycoon Wallet Weight", "商人大亨钱包权重" },
    { "Merchant Upper Bound", "商人上限" },
    { "Mido's Hint", "米多提示" },
    { "Mix Bosses", "混合 Boss" },
    { "Mix Dungeons", "混合地牢" },
    { "Mix Grottos", "混合洞穴" },
    { "Mix Interiors", "混合室内" },
    { "Mix Overworld", "混合地面世界" },
    { "Mix Thieves' Hideout", "混合盗贼藏身处" },

    // ---- Randomizer option names (B) ----
    { "Mixed Entrance Pools", "混合入口池" },
    { "MQ Dungeon Count", "MQ 地牢数量" },
    { "MQ Dungeon Setting", "MQ 地牢设置" },
    { "Night Skulltula's Expect Sun's Song", "夜间骷髅期待太阳之歌" },
    { "Ocarina of Time Hint", "时之陶笛提示" },
    { "Overworld Entrances", "地面世界入口" },
    { "Overworld Spawns", "地面世界出生点" },
    { "Owl Drops", "猫头鹰掉落" },
    { "Pond Age Split", "池塘年龄切换" },
    { "Pond Fish Count", "池塘鱼数量" },
    { "Rainbow Bridge", "彩虹桥" },
    { "Roc's Feather", "洛克的羽毛" },
    { "Saria's Hint", "萨莉亚提示" },
    { "Scrub Hint Text", "商人（Scrub）提示文本" },
    { "Scrubs Adult Wallet Weight", "Scrub 成人钱包权重" },
    { "Scrubs Affordable Prices", "Scrub 可负担价格" },
    { "Scrubs Child Wallet Weight", "Scrub 儿童钱包权重" },
    { "Scrubs Fixed Price", "Scrub 固定价格" },
    { "Scrubs Giant Wallet Weight", "Scrub 巨人钱包权重" },
    { "Scrubs Lower Bound", "Scrub 下限" },
    { "Scrubs No Wallet Weight", "Scrub 无钱包权重" },
    { "Scrubs Prices", "Scrub 价格" },
    { "Scrubs Shuffle", "Scrub 洗牌" },
    { "Scrubs Tycoon Wallet Weight", "Scrub 大亨钱包权重" },
    { "Scrubs Upper Bound", "Scrub 上限" },
    { "Selected Starting Age", "选定的起始年龄" },
    { "Set Dungeon Quests", "设定地牢任务" },
    { "Shadow Temple Keyring", "暗之神殿钥匙环" },
    { "Shadow Temple Quest", "暗之神殿任务" },
    { "Sheik Light Arrow Hint", "什克光箭提示" },
    { "Shop Shuffle", "商店洗牌" },
    { "Shops Adult Wallet Weight", "商店成人钱包权重" },
    { "Shops Affordable Prices", "商店可负担价格" },
    { "Shops Child Wallet Weight", "商店儿童钱包权重" },
    { "Shops Fixed Price", "商店固定价格" },
    { "Shops Giant Wallet Weight", "商店巨人钱包权重" },
    { "Shops Item Count", "商店道具数量" },
    { "Shops Lower Bound", "商店下限" },
    { "Shops No Wallet Weight", "商店无钱包权重" },
    { "Shops Prices", "商店价格" },
    { "Shops Tycoon Wallet Weight", "商店大亨钱包权重" },
    { "Shops Upper Bound", "商店上限" },
    { "Shuffle 100 GS Reward", "洗牌 100 金骷髅奖励" },
    { "Shuffle Adult Trade", "洗牌成人交易" },
    { "Shuffle Bean Fairies", "洗牌魔豆精灵" },
    { "Shuffle Bean Souls", "洗牌魔豆灵魂" },
    { "Shuffle Beehives", "洗牌蜂巢" },
    { "Shuffle Boss Souls", "洗牌 Boss 灵魂" },
    { "Shuffle Bushes", "洗牌灌木" },
    { "Shuffle Chest Minigame", "洗牌宝箱小游戏" },
    { "Shuffle Child's Wallet", "洗牌儿童钱包" },
    { "Shuffle Climb", "洗牌攀爬" },
    { "Shuffle Cows", "洗牌奶牛" },
    { "Shuffle Crates", "洗牌木箱" },
    { "Shuffle Crawl", "洗牌爬行" },
    { "Shuffle Deku Nut Bag", "洗牌德库坚果袋" },
    { "Shuffle Deku Stick Bag", "洗牌德库木棒袋" },
    { "Shuffle Dungeon Rewards", "洗牌地牢奖励" },
    { "Shuffle Entrances", "洗牌入口" },
    { "Shuffle Fairies in Fountains", "洗牌喷泉中的精灵" },
    { "Shuffle Fairy Spots", "洗牌精灵点" },
    { "Shuffle Fishing Pole", "洗牌钓竿" },
    { "Shuffle Freestanding Items", "洗牌独立道具" },
    { "Shuffle Frog Song Rupees", "洗牌青蛙歌曲卢比" },
    { "Shuffle Gerudo Membership Card", "洗牌格鲁德会员卡" },
    { "Shuffle Gossip Stone Fairies", "洗牌闲话石精灵" },
    { "Shuffle Grab", "洗牌抓取" },
    { "Shuffle Grass", "洗牌草丛" },
    { "Shuffle Jabber Nuts", "洗牌喋喋坚果" },
    { "Shuffle Kokiri Sword", "洗牌科克里之剑" },
    { "Shuffle Master Sword", "洗牌大师之剑" },
    { "Shuffle Merchants", "洗牌商人" },
    { "Shuffle Ocarina Buttons", "洗牌陶笛按钮" },
    { "Shuffle Ocarinas", "洗牌陶笛" },
    { "Shuffle Open Chest", "洗牌开启宝箱" },
    { "Shuffle Pots", "洗牌陶罐" },
    { "Shuffle Songs", "洗牌歌曲" },
    { "Shuffle Swim", "洗牌游泳" },
    { "Shuffle Trees", "洗牌树木" },
    { "Shuffle Weird Egg", "洗牌奇怪的蛋" },
    { "Skeleton Key", "万能钥匙" },
    { "Skip Child Stealth", "跳过儿童潜行" },
    { "Skip Child Zelda", "跳过儿童塞尔达" },
    { "Skip Epona Race", "跳过伊波纳赛跑" },
    { "Skip Planting Beans", "跳过种植魔豆" },
    { "Skip Scarecrow's Song", "跳过稻草人之歌" },
    { "Sleeping Waterfall", "沉睡瀑布" },
    { "Slingshot/Bow Can Break Beehives", "弹弓/弓可击破蜂巢" },
    { "Small Key Shuffle", "小钥匙洗牌" },
    { "Spirit Temple Keyring", "魂之神殿钥匙环" },
    { "Spirit Temple Quest", "魂之神殿任务" },
    { "Start with Bolero of Fire", "起始携带炎之波丽罗" },
    { "Start with Deku Shield", "起始携带德库盾" },
    { "Start with Epona's Song", "起始携带伊波纳之歌" },
    { "Start with Kokiri Sword", "起始携带科克里之剑" },
    { "Start with Magic Beans", "起始携带魔法魔豆" },
    { "Start with Master Sword", "起始携带大师之剑" },
    { "Start with Minuet of Forest", "起始携带森林小步舞曲" },
    { "Start with Nocturne of Shadow", "起始携带暗之夜曲" },
    { "Start with Nut Ammo", "起始携带坚果弹药" },
    { "Start with Ocarina", "起始携带陶笛" },
    { "Start with Prelude of Light", "起始携带光之前奏曲" },
    { "Start with Requiem of Spirit", "起始携带灵之安魂曲" },
    { "Start with Saria's Song", "起始携带萨莉亚之歌" },
    { "Start with Serenade of Water", "起始携带水之小夜曲" },
    { "Start with Song of Storms", "起始携带风暴之歌" },
    { "Start with Song of Time", "起始携带时间之歌" },
    { "Start with Stick Ammo", "起始携带木棒弹药" },
    { "Start with Sun's Song", "起始携带太阳之歌" },
    { "Start with Zelda's Lullaby", "起始携带塞尔达的摇篮曲" },
    { "Starting Age", "起始年龄" },
    { "Starting Hearts", "起始生命" },
    { "Sunlight Arrows", "阳光箭" },
    { "Thieves' Hideout Entrances", "盗贼藏身处入口" },
    { "Token Shuffle", "令牌洗牌" },
    { "ToT Altar Hint", "时之殿祭坛提示" },
    { "Triforce Hunt", "三角力量狩猎" },
    { "Triforce Hunt Required Pieces", "三角力量狩猎所需碎片" },
    { "Triforce Hunt Total Pieces", "三角力量狩猎总碎片" },
    { "Warp Song Hints", "传送歌曲提示" },
    { "Warp Songs", "传送歌曲" },
    { "Water Temple Keyring", "水之神殿钥匙环" },
    { "Water Temple Quest", "水之神殿任务" },
    { "Zora's Fountain", "卓拉喷泉" },
    // ---- Randomizer Tricks: area names ----
    { "General Tricks", "通用技巧" },
    { "Kokiri Forest", "科克里森林" },
    { "Lost Woods", "迷失森林" },
    { "Sacred Forest Meadow", "神圣森林草甸" },
    { "Hyrule Field", "海拉鲁平原" },
    { "Lake Hylia", "海拉鲁湖" },
    { "Gerudo Valley", "格鲁德大峡谷" },
    { "Gerudo Fortress", "格鲁德要塞" },
    { "Haunted Wasteland", "幻影沙漠" },
    { "Desert Colossus", "巨大邪神像" },
    { "Hyrule Market", "海拉鲁市场" },
    { "Hyrule Castle", "海拉鲁城堡" },
    { "Kakariko Village", "卡卡利科村" },
    { "Graveyard", "墓地" },
    { "Death Mountain Trail", "死神山径" },
    { "Goron City", "格雷城" },
    { "Death Mountain Crater", "死亡山脉火山口" },
    { "Zora's River", "卓拉河" },
    { "Zora's Domain", "卓拉领地" },
    { "Zora's Fountain", "卓拉喷泉" },
    { "Lon Lon Ranch", "隆隆牧场" },
    { "Deku Tree", "德库树" },
    { "Dodongo's Cavern", "多东哥洞穴" },
    { "Jabu Jabu's Belly", "加卜加卜之腹" },
    { "Forest Temple", "森林神殿" },
    { "Fire Temple", "火之神殿" },
    { "Water Temple", "水之神殿" },
    { "Spirit Temple", "魂之神殿" },
    { "Shadow Temple", "暗之神殿" },
    { "Bottom of the Well", "井底" },
    { "Ice Cavern", "冰之洞窟" },
    { "Gerudo Training Ground", "格鲁德训练场" },
    { "Ganon's Castle", "盖侬城堡" },

    // ---- Randomizer 地点/检查名称（shortName，经 SohGui::L() 显示）----
    { "Hidden Ceiling Chest", "隐藏天花板宝箱" },
    { "Maze Path First Chest", "迷宫通道第一宝箱" },
    { "Maze Path Second Chest", "迷宫通道第二宝箱" },
    { "Maze Path Third Chest", "迷宫通道第三宝箱" },
    { "Maze Path Final Chest", "迷宫通道最终宝箱" },
    { "Forest Trial Chest", "森林试炼宝箱" },
    { "Water Trial Left Chest", "水之试炼左侧宝箱" },
    { "Water Trial Right Chest", "水之试炼右侧宝箱" },
    { "Shadow Trial Front Chest", "暗之试炼前方宝箱" },
    { "Shadow Trial Golden Gauntlets Chest", "暗之试炼黄金护手宝箱" },
    { "Light Trial First Left Chest", "光之试炼左一宝箱" },
    { "Light Trial Second Left Chest", "光之试炼左二宝箱" },
    { "Light Trial Third Left Chest", "光之试炼左三宝箱" },
    { "Light Trial First Right Chest", "光之试炼右一宝箱" },
    { "Light Trial Second Right Chest", "光之试炼右二宝箱" },
    { "Light Trial Third Right Chest", "光之试炼右三宝箱" },
    { "Light Trial Invisible Enemies Chest", "光之试炼隐形敌人宝箱" },
    { "Light Trial Lullaby Chest", "光之试炼摇篮曲宝箱" },
    { "Spirit Trial Crystal Switch Chest", "灵之试炼水晶开关宝箱" },
    { "Spirit Trial Invisible Chest", "灵之试炼隐形宝箱" },
    { "Compass Chest", "指南针宝箱" },
    { "Iron Boots Chest", "铁靴宝箱" },
    { "Lobby Left Chest", "大厅左侧宝箱" },
    { "Lobby Right Chest", "大厅右侧宝箱" },
    { "Stalfos Chest", "骷髅兵宝箱" },
    { "Before Heavy Block Chest", "重物方块前宝箱" },
    { "Heavy Block First Chest", "重物方块第一宝箱" },
    { "Heavy Block Second Chest", "重物方块第二宝箱" },
    { "Heavy Block Third Chest", "重物方块第三宝箱" },
    { "Heavy Block Fourth Chest", "重物方块第四宝箱" },
    { "Eye Statue Chest", "眼之雕像宝箱" },
    { "Near Scarecrow Chest", "稻草人附近宝箱" },
    { "Hammer Room Clear Chest", "锤房清空宝箱" },
    { "Hammer Room Switch Chest", "锤房开关宝箱" },
    { "Spike Walls Left Chest", "尖刺墙左侧宝箱" },
    { "Boss Key Chest", "Boss 钥匙宝箱" },
    { "Invisible Floormaster Chest", "隐形楼板怪宝箱" },
    { "Bongo Bongo Heart Container", "邦哥邦哥心之容器" },
    { "Front Left Fake Wall Chest", "左前方假墙宝箱" },
    { "Front Center Bombable Chest", "中前方可炸宝箱" },
    { "Back Left Bombable Chest", "左后方可炸宝箱" },
    { "Underwater Left Chest", "水下左侧宝箱" },
    { "Freestanding Key", "独立钥匙" },
    { "Center Skulltula Chest", "中央金骷髅宝箱" },
    { "Right Bottom Fake Wall Chest", "右下方假墙宝箱" },
    { "Fire Keese Chest", "火蝙蝠宝箱" },
    { "Like Like Chest", "莱克莱克宝箱" },
    { "Map Chest", "地图宝箱" },
    { "Underwater Front Chest", "水下前方宝箱" },
    { "Invisible Chest", "隐形宝箱" },
    { "Lens of Truth Chest", "真实之镜宝箱" },
    { "Maze Right Central Chest", "迷宫右侧中央宝箱" },
    { "Maze Right Side Chest", "迷宫右侧宝箱" },
    { "Underwater Silver Rupee Chest", "水下银卢比宝箱" },
    { "Beamos Chest", "光束炮宝箱" },
    { "Near Boss Chest", "近 Boss 宝箱" },
    { "Flare Dancer Chest", "火焰舞者宝箱" },
    { "Big Lava Room Lower Open Door Chest", "大熔岩房下层开门宝箱" },
    { "Big Lava Room Blocked Door Chest", "大熔岩房堵门宝箱" },
    { "Boulder Maze Lower Chest", "巨石迷宫下层宝箱" },
    { "Boulder Maze Side Room Chest", "巨石迷宫侧室宝箱" },
    { "Boulder Maze Shortcut Chest", "巨石迷宫捷径宝箱" },
    { "Boulder Maze Upper Chest", "巨石迷宫上层宝箱" },
    { "Scarecrow Chest", "稻草人宝箱" },
    { "Megaton Hammer Chest", "百万吨锤宝箱" },
    { "Highest Goron Chest", "最高格雷宝箱" },
    { "Volvagia Heart Container", "沃沃基亚心之容器" },
    { "First Room Chest", "第一房间宝箱" },
    { "First Stalfos Chest", "第一骷髅兵宝箱" },
    { "Raised Island Courtyard Chest", "高岛庭院宝箱" },
    { "Slingshot Room Side Chest", "弹弓房间侧室宝箱" },
    { "Slingshot Chest", "弹弓宝箱" },
    { "Compass Room Side Chest", "指南针房间侧室宝箱" },
    { "Basement Chest", "地下室宝箱" },
    { "Queen Gohma Heart Container", "戈玛女王心之容器" },
    { "Bomb Flower Platform Chest", "炸弹花平台宝箱" },
    { "Bomb Bag Chest", "炸弹袋宝箱" },
    { "End Of Bridge Chest", "桥端宝箱" },
    { "Boss Room Chest", "Boss 房间宝箱" },
    { "King Dodongo Heart Container", "多东哥王心之容器" },
    { "Boomerang Chest", "飞旋镖宝箱" },
    { "Barinade Heart Container", "巴里纳德心之容器" },
    { "Well Chest", "井宝箱" },
    { "Eye Switch Chest", "眼之开关宝箱" },
    { "Floormaster Chest", "楼板怪宝箱" },
    { "Red Poe Chest", "红幽灵宝箱" },
    { "Bow Chest", "弓宝箱" },
    { "Blue Poe Chest", "蓝幽灵宝箱" },
    { "Falling Ceiling Room Chest", "落顶房间宝箱" },
    { "Phantom Ganon Heart Container", "幻影盖侬心之容器" },
    { "Hover Boots Chest", "悬浮靴宝箱" },
    { "Early Silver Rupee Chest", "初期银卢比宝箱" },
    { "Invisible Blades Visible Chest", "隐形刀片可见宝箱" },
    { "Invisible Blades Invisible Chest", "隐形刀片隐形宝箱" },
    { "Falling Spikes Lower Chest", "下落尖刺下层宝箱" },
    { "Falling Spikes Upper Chest", "下落尖刺上层宝箱" },
    { "Falling Spikes Switch Chest", "下落尖刺开关宝箱" },
    { "Invisible Spikes Chest", "隐形尖刺宝箱" },
    { "Wind Hint Chest", "风之提示宝箱" },
    { "After Wind Enemy Chest", "风后敌人宝箱" },
    { "After Wind Hidden Chest", "风后隐藏宝箱" },
    { "Child Bridge Chest", "儿童桥宝箱" },
    { "Child Early Torches Chest", "儿童早期火炬宝箱" },
    { "Child Climb North Chest", "儿童攀爬北宝箱" },
    { "Child Climb East Chest", "儿童攀爬东宝箱" },
    { "Sun Block Room Chest", "太阳方块房宝箱" },
    { "Silver Gauntlets Chest", "银手套宝箱" },
    { "Early Adult Right Chest", "早期成人右侧宝箱" },
    { "First Mirror Left Chest", "第一镜子左侧宝箱" },
    { "First Mirror Right Chest", "第一镜子右侧宝箱" },
    { "Statue Room Northeast Chest", "雕像房东北宝箱" },
    { "Statue Room Hand Chest", "雕像房手掌宝箱" },
    { "Near Four Armos Chest", "四只阿莫斯附近宝箱" },
    { "Hallway Right Invisible Chest", "走廊右侧隐形宝箱" },
    { "Hallway Left Invisible Chest", "走廊左侧隐形宝箱" },
    { "Mirror Shield Chest", "镜盾宝箱" },
    { "Topmost Chest", "最高处宝箱" },
    { "Twinrova Heart Container", "双生巫婆心之容器" },
    { "Cracked Wall Chest", "裂缝墙宝箱" },
    { "Torches Chest", "火炬宝箱" },
    { "Central Pillar Chest", "中央柱子宝箱" },
    { "Central Bow Target Chest", "中央弓靶宝箱" },
    { "Longshot Chest", "长钩宝箱" },
    { "River Chest", "河流宝箱" },
    { "Dragon Chest", "龙宝箱" },
    { "Morpha Heart Container", "摩法心之容器" },
    { "Frogs in the Rain", "雨中青蛙" },
    { "Frogs Ocarina Game", "青蛙陶笛游戏" },
    { "Near Open Grotto Freestanding PoH", "露天洞穴附近独立 PoH" },
    { "Near Domain Freestanding PoH", "领地附近独立 PoH" },
    { "Diving Minigame", "潜水小游戏" },
    { "King Zora Thawed", "卓拉王解冻" },
    { "Iceberg Freestanding PoH", "冰山独立 PoH" },
    { "Bottom Freestanding PoH", "底层独立 PoH" },
    { "Bush 1", "灌木1" },
    { "Bush 2", "灌木2" },
    { "Bush 3", "灌木3" },
    { "Bush 4", "灌木4" },
    { "Bush 5", "灌木5" },
    { "Bush 6", "灌木6" },
    { "Talons Chickens", "塔隆的鸡" },
    { "Dampe Gravedigging Tour", "丹培掘墓之旅" },
    { "Hookshot Chest", "钩索宝箱" },
    { "Dampe Race Freestanding PoH", "丹培赛跑独立 PoH" },
    { "Trade Claim Check", "交易凭证" },
    { "Darunias Joy", "达鲁尼亚的喜悦" },
    { "Pot Freestanding PoH", "罐子独立 PoH" },
    { "Rolling Goron as Child", "童年滚动格雷" },
    { "Rolling Goron as Adult", "成人滚动格雷" },
    { "Maze Left Chest", "迷宫左侧宝箱" },
    { "Maze Right Chest", "迷宫右侧宝箱" },
    { "Maze Center Chest", "迷宫中央宝箱" },
    { "Volcano Freestanding PoH", "火山独立 PoH" },
    { "Wall Freestanding PoH", "墙边独立 PoH" },
    { "Upper Grotto Chest", "上层洞穴宝箱" },
    { "Shield Grave Chest", "盾牌墓穴宝箱" },
    { "Heart Piece Grave Chest", "心之碎片墓穴宝箱" },
    { "Royal Family's Tomb Chest", "皇室之墓宝箱" },

    { "Invalid", "无效" },

    // ---- Randomizer Tricks: difficulty tag names ----
    { "Novice", "新手" },
    { "Intermediate", "中级" },
    { "Advanced", "高级" },
    { "Expert", "专家" },
    { "Extreme", "极限" },
    { "Experimental", "实验性" },
    { "Glitch", "故障" },

    // ---- Randomizer Tricks: trick descriptions ----
    { "Allows ignoring visible barriers and objects that do not actually stop Link from walking, climbing or "
      "hitting things, without clipping.\n\n"
      "This notably allows for walking through Kak's gate backwards, climb into the back of Impa's house as "
      "Adult from the coop,"
      "and hitting Rusted Switches or boulders through Blocks, Ice and Walls.\n\n"
      "This trick only applies to case where doing the thing is trivial, instances where it only works from "
      "certain angles are not part of this trick,"
      "niether are any form of clips, including clipping Link's hitbox inside boulders with jumpslash.",
      "允许忽略可见障碍，以及实际不会阻止林克行走、攀爬或攻击的物体，且无需穿模。\n\n"
      "典型例子：可倒着走过卡卡利科大门、成年林克从鸡舍爬进英帕家后院、隔着方块/冰/墙击中生锈开关或巨石。\n\n"
      "此技巧仅适用于操作本身轻而易举的情况；仅从特定角度才能完成的情形不在此列，任何穿模（包括以跳跃斩将林克判定框卡入巨石）也不在此列。" },

    { "Allows entering hidden grottos without the Stone of Agony.",
      "允许无需振动石进入隐藏洞穴。" },
    { "Normally the only hot area logic expects you to navigate without a Goron Tunic is Death Mountain Crater\n"
       "and you are not expected to navigate underwater sections without a Zora Tunic.\n\n"
       "With this trick you are expected to do any underwater area except Central Pillar,\n"
       "any hot area except Volvagia and the Block lift room in Fire Temple\n"
       "and the health needed to logically navigate Crater is decreased.",
      "通常情况下，仅有死亡山脉火山口这类高温区域的逻辑会要求你不穿格雷外衣也能通过，且水下区域不会要求你不穿卓拉外衣。\n\n开启此技巧后，除中央柱外的所有水下区域、除沃沃基亚与火之神殿方块升降房外的所有高温区域，都预期你可在不穿对应外衣的情况下通过，且火山口所需的逻辑血量也会降低。" },
    { "Many ledges can be overcome with particular jumps which are simple to execute without items.\n"
              "This includes jumping from heights to dive deeper without scales,\n"
              "though this trick doesn't cover Water Temple's Dragon Room.",
      "许多凸台可通过特定跳跃越过，且无需道具即可轻松完成。\n其中包括从高处跳下以无鳞片潜得更深，\n但本技巧不包含水之神殿的龙之房。" },
    { "Fire Rings can be run into while Link is invincible from having taken damage,"
              "letting you interact with some objects inside them such as large chests",
      "当林克因受伤处于无敌状态时，可冲入火焰环，\n从而与其中的部分物体互动，例如大宝箱。" },
    { "Allows damage boosts in order to reach further locations. Can be combined with \"Simple hover boosts\" "
              "for reaching far distances.",
      "允许利用受伤击退到达更远地点。可与\"简易悬浮增益\"组合以抵达极远距离。" },
    { "Allows equipping of hover boots when Link is moving at high speeds to extend distance covered, often "
              "after recoil. Can be combined with \"Simple damage boosts\" for greater uses.",
      "允许在林克高速移动时（常为受击后退后）装备悬浮靴以延长移动距离。可与\"简易受伤增益\"组合使用，效果更佳。" },
    { "Allows exploding beehives with Bombchus.",
      "允许用炸弹鼠炸开蜂巢。" },
    { "You can skip climb for hookshottable ladders can be skipped by hookshotting the top of the ladder from "
              "the correct distance and angle.\n"
              "This is more difficult for some ladders than others, and a few are not possible.\n"
              "Hookshotting climbable walls in the same way is not a trick, as it is trivial to get an angle that "
              "correctly ledge grabs.",
      "可跳过攀爬：从合适的距离与角度用钩绳钩住梯子顶端，即可略过攀爬。\n部分梯子难度更高，少数则无法做到。\n以同样方式用钩绳钩可攀爬的墙壁不算技巧，因为很容易找到能正确抓边的角度。" },
    { "Use Blue Fire to break mud walls, detonate bomb flowers, and break floor to King Dodongo.\nDoes not "
              "apply to MQ Dead Hand bomb flowers.\nUsing blue fire on bombflower to stop rolling goron also requires "
              "\"Stop Link the Goron with Din's Fire\".\nUsing blue fire arrows to break floor in King Dodongo's "
              "chamber also requires \"Dodongo's Cavern Smash the Boss Lobby Floor\".",
      "用蓝焰击碎泥墙、引爆炸弹花，并破坏通往多东哥王的道路。\n不适用于 MQ 死手处的炸弹花。\n用蓝焰引爆炸弹花以阻止滚格雷，还需\"用戴因之火阻止格雷林克\"。\n用蓝焰箭破坏多东哥王房间的地面，还需\"多东哥洞窟砸碎 Boss 前厅地板\"。" },
    { "Underwater chests can be opened by wearing iron boots and hookshotting the chest.",
      "穿上铁靴并用钩绳钩住宝箱，即可开启水下宝箱。" },
    { "From afar boulder collision is disabled, allowing projectiles to pass through them.",
      "远处会禁用巨石碰撞，使投射物可穿过它们。" },
    { "Slightly extends the range of projectiles such as Hookshot, Bow or Slingshot. Also allows clipping "
              "projectile past collision. Used for:\n"
              "- Crossing Gerudo Valley with Hookshot\n"
              "- Retrieving DMT Gold Skulltula beside bomb flower\n"
              "- Hitting switch through wall in Spirit Temple's big mirror room with Bow, Slingshot, or Hookshot\n"
              "- Hitting switch through wall in Spirit Trial with Bow or Slingshot\n"
              "- Hitting switch through gate in Shadow Temple MQ with Bow or Slingshot",
      "略微延长钩绳、弓或弹弓等投射物的射程，并允许投射物穿过碰撞。用于：\n- 用钩绳跨越格鲁德大峡谷\n- 拾取炸弹花旁的死亡山脉金色骷髅\n- 在魂之神殿大镜房用弓、弹弓或钩绳隔墙击中开关\n- 在灵之试炼用弓或弹弓隔墙击中开关\n- 在暗之神殿 MQ 用弓或弹弓隔门击中开关" },
    { "Pausing while a big skulltula is bobbing upwards slightly lifts it,\n"
              "eventually allowing passage without any items.",
      "当大骷髅蜘蛛微微上浮时暂停，会将其稍微抬起，\n最终无需任何道具即可通过。" },
    { "Enables requiring ground jumps.",
      "开启后，逻辑会预期你能够完成地面跳。" },
    { "Enables ground jumps which require some precision outside of setting up jump,\n"
              "such as needing extra height with jumpslash or jumping while running with hover boots.",
      "启用需要一定精度的地面跳（除起跳准备外），\n例如需用跳跃斩获得额外高度，或穿悬浮靴奔跑时起跳。" },
    { "Running forward while sliding sideways on ice can be used to jump on platforms.",
      "在冰面上侧滑的同时向前奔跑，可借此跳上平台。" },

    { "Can be obtained without Hookshot by using the Hover Boots off of one of the roots.",
      "利用某条树根，穿悬浮靴即可无需钩绳获取。" },
    { "With very precise movement it's possible for adult to jump onto the bridge without needing Longshot, "
              "Hover Boots, or Bean.",
      "成年林克凭借极其精准的操作，无需远钩、悬浮靴或魔豆，即可跳上迷失森林桥。" },
    { "With a specific position and angle, you can backflip over Mido.",
      "在特定的位置与角度下，你可用后空翻越过米多。" },
    { "You need Deku Sticks or Kokiri Sword to dive with Navi for entering Zora's River.",
      "需要德库木棒或科克里之剑，借助娜薇俯冲进入卓拉河。" },
    { "You can collect the token with a precise Hookshot use, as long as you can kill the Skulltula somehow "
              "first. It can be killed using Longshot, Bow, Bombchus or Din's Fire.",
      "只要你能先设法击杀骷髅蜘蛛，便能凭借精准的钩绳使用拾取代币。可用远钩、弓、炸弹鼠或戴因之火将其击杀。" },
    { "With precise throws, the Boomerang alone can kill the Skulltula and collect the token, without first "
              "needing to blow up the wall.",
      "凭借精准的投掷，仅凭飞旋镖即可击杀骷髅蜘蛛并拾取代币，无需先炸开墙壁。" },
    { "Big Poes have a chance of appearing without Epona, you can shoot them quickly with only bow.",
      "大波克有一定几率在没骑伊波纳时也出现，你可仅凭弓迅速将其射落。" },
    { "Climb the tower as high as you can without touching the Gold Skulltula, then let go and jumpslash "
              "immediately. By jump-slashing from as low on the ladder as possible to still hit the Skulltula, this "
              "trick can be done without taking fall damage.",
      "尽量不碰到金骷髅地爬到塔的最高处，然后松手并立即跳跃斩。只要从尽可能低的梯级起跳仍能击中金骷髅，本技巧便可在不受到坠落伤害的情况下完成。" },
    { "Can jump up to the spinning platform from below as child with a precise jumpslash timed with the "
              "platforms rotation.",
      "儿童可凭借与旋转平台同步的精准跳跃斩，从下方跳上旋转平台。" },
    { "Take the Hover Boots from the entrance to Impa's House over to the rooftop of Skulltula House. From there, a "
        "precise Hover Boots backwalk with backflip can be used to get onto a hill above the side of the village. And "
        "then from there you can Hover onto Impa's rooftop to kill the Skulltula and backflip into the token.",
      "从英帕家入口处取悬浮靴，带到骷髅蜘蛛之屋的屋顶。由此，可借助精准的悬浮靴后退接后空翻，登上村庄一侧上方的小山。随后从那里悬浮至英帕家屋顶，击杀金骷髅并后空翻入代币。" },
    { "Using a precise moving setup you can obtain the Piece of Heart by having the Boomerang interact with it "
              "along the return path.",
      "利用精准的移动设置，让飞旋镖在回程路径上与心之碎片互动，即可获取。" },
    { "It is possible to complete the second dampe race as child in under a minute, but it is a strict time limit.",
      "儿童可在不到一分钟内完成第二次达培赛跑，但时限非常严苛。" },
    { "It is possible to light all of the torches to open the Shadow Temple entrance with just Fire Arrows, "
              "but you must be very quick, precise, and strategic with how you take your shots.",
      "仅凭火焰箭即可点燃所有火把、开启暗之神殿入口，但你必须在射击的时机、精度与策略上极为迅捷精准。" },
    { "Child can make it past the eruption to reach DMT Summit without a Hylian Shield or Nayru's Love"
              "by backwalking or simply taking damage.",
      "儿童可经后退走位或干脆承受伤害，在不使用海利亚之盾或娜如之爱的情况下，越过喷发抵达死亡山脉山顶。" },
    { "Bugs will go into the soft soil even while the boulder is still blocking the entrance. Then, using a "
              "precise moving setup you can kill the Gold Skulltula and obtain the token by having the Boomerang "
              "interact with it along the return path.",
      "即便巨石仍堵住入口，虫子也会钻入松软的土壤。随后利用精准的移动设置，让飞旋镖在回程路径上与其互动，即可击杀金色骷髅并拾取代币。" },
    { "Child Link can blow up the wall using a nearby bomb flower. You must backwalk with the flower and then "
              "quickly throw it toward the wall.",
      "儿童林克可用附近的炸弹花炸开墙壁。你需带着炸弹花后退走位，再迅速将其掷向墙壁。" },
    { "After killing the Skulltula, the token can be collected without needing to destroy the rock by "
              "backflipping down onto it with the Hover Boots. First use the Hover Boots to stand on a nearby fence, "
              "and go for the Skulltula Token from there.",
      "击杀骷髅蜘蛛后，无需破坏岩石，穿悬浮靴后空翻落到代币上即可拾取。先穿悬浮靴站上附近的栅栏，再从那里去获取金骷髅代币。" },

    { "After killing the Skulltula, the token can be collected without needing to destroy the rock by jumping "
              "down onto it from the bean plant, midflight, with precise timing and positioning.",
      "击杀骷髅蜘蛛后，无需破坏岩石：借助魔豆植株，在半空中以精准的时机与位置跳落到代币上即可拾取。" },
    { "After killing the Skulltula, the token can be collected without needing to destroy the rock by jump "
              "slashing from a precise angle.",
      "击杀骷髅蜘蛛后，无需破坏岩石：从精准的角度跳跃斩即可拾取代币。" },
    { "It is possible to use the Hover Boots to bypass needing to destroy the boulders blocking the path to "
              "the top of Death Mountain.",
      "可借助悬浮靴，省去破坏挡路的巨石，直接抵达死亡山脉山顶。" },
    { "After killing the Skulltula, the token can be collected by backflipping into the rock at the correct "
              "angle.",
      "击杀骷髅蜘蛛后，以正确的角度后空翻撞入岩石，即可拾取代币。" },
    { "A Bombchu can be used to stop the spinning pot, but it can be quite finicky to get it to work.",
      "可用炸弹鼠停住旋转壶，但要让它生效颇为挑剔。" },
    { "Allows for stopping the Goron City Spinning Pot using a Bomb Flower alone, requiring strength in lieu "
              "of inventory explosives.",
      "允许仅凭炸弹花停住格雷城旋转壶，以力量代替背包中的爆炸物。" },
    { "Use the Bomb Flower on the stairs or near Medigoron. Timing is tight, especially without backwalking.",
      "在楼梯上或梅迪格雷附近使用炸弹花。时机很紧，尤其是不后退走位时。" },
    { "A precise backwalk starting from on top of the crate and ending with a precisely-timed backflip can "
              "reach this chest without needing either the Hammer or Silver Gauntlets.",
      "从板条箱顶起步、以精准时机后空翻收尾的精确后退走位，可在无需锤子或银护腕的情况下够到该宝箱。" },
    { "It is possible to reach the Goron City Grotto by quickly using the Hookshot while in the midst of "
              "taking damage from the lava floor.",
      "可在受到熔岩地面伤害的过程中迅速使用钩绳，从而到达格雷城洞穴。" },
    { "The timing is quite awkward.",
      "时机相当刁钻。" },
    { "Hover from the base of the bridge near Goron City and walk up the very steep slope.",
      "从格雷城附近桥墩底部悬浮，再走上那段极陡的斜坡。" },
    { "As Adult, using a shield to drop a pot while you have the perfect speed and position, the pot can push "
              "you that little extra distance you need to jump across the gap in the bridge.",
      "成年后，在你拥有完美速度与站位时，用盾丢出一个罐子，罐子能将你多推那一点距离，正好越过桥面缺口。" },
    { "With the Hammer, you can jumpslash the rock twice in the same jump in order to destroy it before you "
              "fall into the lava.",
      "持锤时，可在同一跳中跳跃斩岩石两次，赶在坠入熔岩前将其破坏。" },
    { "As adult, With careful positioning, you can jump to the ledge where the boulder is, then use repeated "
              "ledge grabs to shimmy to a climbable ledge. This trick supersedes \"Death Mountain Crater Upper to "
              "Lower with Hammer\".",
      "成年后，凭借谨慎的站位，你可跳到巨石所在的凸台，再反复抓边挪到可攀爬的凸台。本技巧取代了\"死亡山脉火山口上层到下层用锤子\"。" },
    { "Adult can reach this PoH with a precise jump, no Hover Boots required.",
      "成年林克凭借精准跳跃即可到达该心之碎片，无需悬浮靴。" },
    { "Adult can reach this PoH with a precise jump, no Hover Boots required.",
      "成年林克凭借精准跳跃即可到达该心之碎片，无需悬浮靴。" },
    { "Can hover behind the waterfall as adult.",
      "成年后可悬浮至瀑布后方。" },
    { "You can fly behind the waterfall with a Cucco as child.",
      "儿童可抱着鸡飞到瀑布后方。" },
    { "With a precise jump as adult, it is possible to get on the fence next to King Zora from the front to "
              "access Zora's Fountain.",
      "成年后凭借精准跳跃，可从正面跳上卓拉王旁的栅栏，从而进入卓拉之泉。" },
    { "A precise jumpslash can kill the Skulltula and recoil back onto the top of the frozen waterfall. To "
              "kill it, the logic normally guarantees one of Hookshot, Bow, or Magic.",
      "精准的跳跃斩可击杀金骷髅并回弹到冰冻瀑布顶端。逻辑上通常会保证你拥有钩绳、弓或魔法三者之一来击杀它。" },
    { "It's possible to use silver gauntlets to pick up the silver rock and hammer to break the rock below "
              "it, allowing you to ledge grab the edge of the hole and get past the breakable wall (hammer can't "
              "break the wall itself).",
      "可用银护腕举起银岩，再用锤子砸碎其下方的岩石，从而抓边够到洞口边缘、越过可破坏的墙壁（锤子无法破坏墙壁本身）。" },
    { "The jumpslash to actually collect the token is somewhat precise.",
      "实际用于拾取代币的跳跃斩需要一定的精度。" },
    { "Remove the Iron Boots in the midst of Hookshotting the underwater crate.",
      "在钩绳钩住水下板条箱的瞬间脱掉铁靴。" },

    { "When entering Water Temple using Gold Scale instead of Iron Boots, the Longshot is usually used to be "
              "able to hit the switch and open the gate. But, by standing in a particular spot, the switch can be hit "
              "with only the reach of the Hookshot.",
      "进入水之神殿时若用黄金鳞片代替铁靴，通常需用远钩击中开关并开门。但站在特定位置，仅用钩绳的触及范围即可击中开关。" },
    { "From the far side of Gerudo Valley, a precise Hover Boots movement and jump-slash recoil can allow "
              "adult to reach the ledge with the crate PoH without needing Longshot. You will take fall damage.",
      "从格鲁德大峡谷对岸，成年林克可凭精准的悬浮靴移动与跳跃斩回弹，无需远钩即够到板条箱心之碎片的凸台。你会受到坠落伤害。" },
    { "The loading zone for Carpenter's Tent is accessible to child.",
      "儿童可进入木匠帐篷的读盘区。" },
    { "Using cucco as child, it's possible to jumpslash over the gate.",
      "儿童抱鸡可跳跃斩越过栅栏。" },
    { "Using Hookshot Extension and a precise setup, you can cross the broken bridge in Gerudo Valley with "
              "only a Hookshot.",
      "利用钩绳延展与精准布置，可仅凭钩绳跨越格鲁德大峡谷的断桥。" },
    { "The logic normally guarantees Bow or Hookshot to stun them from a distance,"
              "but every moving guard can be passed with basic movement and AI manipulation",
      "逻辑上通常会保证你有弓或钩绳从远处将其击晕，但每个移动的守卫都可通过基础走位与 AI 操纵绕过。" },
    { "You can sidehop out of bounds from the tower, then sidehop again on the other side of the gate.\n\n"
              "This is easiest and most useful for Child, but Adult can also do this to skip the Gerudo Jabber Nut.",
      "可从塔上侧跳越界，再在门的另一侧再次侧跳。\n\n对儿童最轻松也最实用，但成年林克也可借此跳过格鲁德胡桃。" },
    { "As adult a precise jumpslash out of bounds with hoverboots from above the jail can be used to get past "
              "the gate.\n\n"
              "This can also be used to reach the tower and lower the gate for child without climb.",
      "成年后，从监狱上方穿悬浮靴、以精准的跳跃斩越界，即可越过该门。\n\n此技巧也可用于到达塔楼，并在无需攀爬的情况下为儿童降下大门。" },
    { "Warriors can be defeated with Slingshot or Bombchus.",
      "守卫可用弹弓或炸弹鼠击败。" },
    { "Adult Link can use a ledge clip to enter Gerudo Training Ground without Gerudo Card.",
      "成年林克可用凸台穿模，在无格鲁德卡片的情况下进入格鲁德训练场。" },
    { "You can beat the quicksand by backwalking across it in a specific way. Note that jumping to the carpet "
              "merchant as child typically requires a fairly precise jumpslash.",
      "你可用特定的后退走位穿过流沙。注意：儿童跳向地毯商通常需相当精准的跳跃斩。" },
    { "By memorizing the path, you can travel through the Wasteland without using the Lens of Truth to see the "
              "Poe. The equivalent trick for going in reverse through the Wasteland is \"Reverse Wasteland\".",
      "记住路线后，无需使用真实之镜显示波克即可穿过荒野。反向穿过荒野的对应技巧是\"反向荒野\"。" },
    { "By memorizing the path, you can travel through the Wasteland in reverse. Note that jumping to the carpet "
              "merchant as child typically requires a fairly precise jumpslash. The equivalent trick for going forward "
              "through the Wasteland is \"Lensless Wasteland\". To cross the river of sand with no additional items, be "
              "sure to also enable \"Wasteland Crossing without Hover Boots or Longshot\". Unless all overworld "
              "entrances are randomized, Child Link will not be expected to do anything at Gerudo's Fortress.",
      "记住路线后，可反向穿过荒野。注意：儿童跳向地毯商通常需相当精准的跳跃斩。正向穿过荒野的对应技巧是\"无真实之镜荒野\"。若要以无额外道具越过沙之河，务必同时开启\"无悬浮靴或远钩穿越荒野\"。除非所有地面世界入口都被随机化，否则不会要求儿童在格鲁德要塞做任何事。" },
    { "Somewhat precise. If you kill enough Leevers you can get enough of a break to take some time to aim "
              "more carefully.",
      "需要一定精度。若击杀足够多的利弗，可获得足够空隙更仔细地瞄准。" },
    { "Can be defeated by doing a precise jumpslash.",
      "凭借精准的跳跃斩即可击败。" },
    { "A precise jump can be used to skip needing to use the Slingshot to go around B1 of the Deku Tree. If "
              "used with the \"Closed Forest\" setting, a Slingshot will not be guaranteed to exist somewhere inside "
              "the Forest. This trick applies to both Vanilla and Master Quest.",
      "可凭精准跳跃，省去用弹弓绕行德库树 B1。若与\"封闭森林\"设置并用，则不保证森林某处会存在弹弓。本技巧同时适用于原版与大师任务。" },
    { "All spider web walls in the Deku Tree basement can be burnt as adult with just a bow by shooting "
              "through torches. This trick only applies to the circular web leading to Gohma; the two vertical webs "
              "are always in logic. Backflip onto the chest near the torch at the bottom of the vine wall. With "
              "precise positioning you can shoot through the torch to the right edge of the circular web. This allows "
              "completion of adult Deku Tree with no fire source.",
      "德库树地下所有蛛网墙，成年后仅凭弓射穿火把即可烧除。本技巧仅适用于通往哥马的环形网；两道竖直网始终算作可达。后空翻落到藤蔓墙底部火把旁的宝箱上，再凭精准站位射穿火把、命中环形网右缘，即可在无火源的情况下完成成年德库树。" },
    { "Allows backflipping over the spiked log in the Deku Tree basement in Vanilla. Only relevant if "
              "\"Shuffle Swim\" is enabled.",
      "允许在原版中后空翻越过德库树地下的尖刺木。仅当开启\"洗牌游泳\"时相关。" },
    { "Climb to the top of the vines, then let go and jumpslash immediately to destroy the boulders using the "
              "Hammer, without needing to spawn a Song of Time block.",
      "爬到藤蔓顶端，松手后立即跳跃斩，用锤子破坏巨石，无需生成时间之歌方块。" },
    { "You can get past the spiked log by rolling to briefly shrink your hitbox. As adult, the timing is a bit "
              "more precise.",
      "滚地可短暂缩小判定框，从而越过尖刺木。成年后时机需更精准一些。" },
    { "You can jump off an Armos Statue to reach the alcove with the Gold Skulltula. It takes quite a long "
              "time to pull the statue the entire way. The jump to the alcove can be a bit picky when done as child.",
      "你可跳上阿摩斯雕像，抵达藏有金色骷髅的壁龛。将雕像整个拖到位相当费时。儿童起跳到壁龛时可能有些挑剔。" },

    { "The vines upon which this Skulltula rests are one-sided collision. You can use the Longshot to get it "
              "from below, by shooting it through the vines, bypassing the need to lower the staircase.",
      "这只骷髅蜘蛛所栖的藤蔓是单向碰撞。可借远钩透过藤蔓将其射下，省去降下楼梯的必要。" },
    { "The Bow can be used to knock down the stairs with two well-timed shots.",
      "可用弓以两次时机精准的射击击落楼梯。" },
    { "With precise platforming, child can cross the platforms while the flame circles are there. When "
              "enabling this trick, it's recommended that you also enable the Adult variant: \"Dodongo's Cavern Spike "
              "Trap Room Jump without Hover Boots\".",
      "凭借精准的踩台，儿童可在火焰环存在时跨越平台。开启此技巧时，建议同时开启成年版：\"多东哥洞窟尖刺陷阱房跳跃（无悬浮靴）\"。" },
    { "With help from a conveniently-positioned block, Adult can quickly carry a Bomb Flower over to destroy "
              "the mud wall blocking the room with two Deku Scrubs.",
      "借助一处位置便利的方块，成年林克可迅速搬来炸弹花，炸开挡住两德库商人房间的泥墙。" },
    { "The bombable floor before King Dodongo can be destroyed with Hammer if hit in the very center. This is "
              "only relevant with Shuffle Boss Entrances or if Dodongo's Cavern is MQ and either variant of "
              "\"Dodongo's Cavern MQ Light the Eyes with Strength\" is on.",
      "多东哥王前的可炸地面，若击中正中心，可用锤子破坏。此技巧仅在与「洗牌 Boss 入口」并用、或洞窟为 MQ 且「多东哥洞窟 MQ 以力量点亮眼睛」任一变体开启时相关。" },
    { "With precise timing you can feed King Dodongo a bombchu during a backflip",
      "凭借精准时机，可在后空翻过程中投喂多东哥王一颗炸弹鼠。" },
    { "Taking a bomb from the back can be used to lower stairs without using stick to drop bomb from wall.",
      "从后方取炸弹，可在不借助木棒从墙上丢炸弹的情况下降下楼梯。" },
    { "With a precise jumpslash from above, you can reach the Bomb Bag area as only child without needing a "
              "Slingshot. You will take fall damage.",
      "从上方精准跳跃斩，仅儿童即可到达炸弹袋区，无需弹弓。你会受到坠落伤害。" },
    { "If you move very quickly, it is possible to use the bomb flower at the top of the room to light the "
              "eyes. To perform this trick as child is significantly more difficult than adult. The player is also "
              "expected to complete the DC back area without explosives, including getting past the Armos wall to the "
              "switch for the boss door.",
      "若移动极快，可用房间顶部的炸弹花点亮眼睛。儿童完成此技巧远比成年困难。同时预期你能在无爆炸物的情况下完成洞窟后方区域，包括越过阿摩斯墙去触发 Boss 门的开关。" },
    { "If you move very quickly, it is possible to use the bomb flower at the top of the room to light the eyes.",
      "若移动极快，可用房间顶部的炸弹花点亮眼睛。" },
    { "You can light the dodongo head's eyes with bombchus from the main room, allowing instant access to the end "
              "of the dungeon.",
      "可从主厅用炸弹鼠点亮多东哥头像的眼睛，从而立即抵达地牢尽头。" },
    { "A box for the blue switch can be carried over by backwalking with one while the elevator is at its "
              "peak. Alternatively, you can skip transporting a box by quickly rolling from the switch and opening the "
              "door before it closes. However, the timing for this is very tight.",
      "当电梯位于顶端时，可一边后退走位一边搬着蓝色开关的箱子过去。或者，从开关处迅速滚身、在门关上前将其打开，从而省去搬运箱子。不过此时机非常紧。" },
    { "Vanilla Jabu: From near the entrance into the room, you can hit the switch that opens the door to the boss "
              "room using a precisely-aimed use of the Slingshot, Bow, or Longshot. As well, if you climb to the top of the "
              "vines you can stand on the right edge of the platform and shoot around the glass. From this distance, even "
              "the Hookshot can reach the switch. This trick is only relevant if \"Shuffle Boss Entrances\" is enabled. MQ "
              "Jabu: A Gold Skulltula Token can be collected with Longshot using the same methods as hitting the switch in "
              "Vanilla.",
      "原版加卜：从靠近房间入口处，可用精准瞄准的弹弓、弓或远钩击中开启 Boss 房门的开关。此外，若爬到藤蔓顶端，可站在平台右缘、绕过玻璃射击。如此距离下，连钩绳都能击中开关。此技巧仅当「洗牌 Boss 入口」开启时相关。MQ 加卜：可用与击中原版开关相同的方法、以远钩拾取金色骷髅代币。" },
    { "You can hit the switch that opens the door to the boss room using a precisely-aimed Bombchu. Also, "
              "using the Hover Boots, adult can throw a Bomb at the switch. This trick is only relevant if \"Shuffle "
              "Boss Entrances\" is enabled.",
      "可用精准瞄准的炸弹鼠击中开启 Boss 房门的开关。此外，成年林克可穿悬浮靴向开关投掷炸弹。此技巧仅当「洗牌 Boss 入口」开启时相关。" },
    { "It's possible reach pots past cube with only hover boots.",
      "仅凭悬浮靴即可越过方块够到罐子。" },
    { "Removes the requirements for the Lens of Truth in Jabu MQ.",
      "去除 MQ 加卜对真实之镜的需求。" },
    { "Boomerang can reach the cow switch to spawn the chest by targeting the cow, jumping off of the ledge "
              "where the chest spawns, and throwing the Boomerang in midair.",
      "飞旋镖可锁定牛、从宝箱生成所在的凸台边缘跳下，并在半空投掷，从而触发牛开关生成宝箱。" },
    { "Allow the Boomerang to return to you through the Song of Time block to grab the token.",
      "允许飞旋镖穿过时间之歌方块飞回你手中，从而拾取代币。" },
    { "Barinade can be damaged with pots, requiring only boomerang to defeat.",
      "巴拉纳德可被罐子伤害，仅需飞旋镖即可击败。" },
    { "Removes the requirements for the Lens of Truth in Bottom of the Well.",
      "去除井底对真实之镜的需求。" },
    { "You need Deku Sticks or Kokiri Sword to dive with Navi for entering Bottom of the Well.",
      "需要德库木棒或科克里之剑，借助娜薇俯冲进入井底。" },

    { "Requires 9 sticks or 5 jumpslashes.",
      "需要 9 根木棒或 5 次跳跃斩。" },
    { "The chest in the basement can be reached with strength by doing a jumpslash with a lit stick to access "
              "the Bomb Flowers.",
      "可借点燃的木棒跳跃斩、够到炸弹花，从而以力量到达地下室的宝箱。" },
    { "While the pits in Bottom of the Well don't allow you to jump just by running straight at them, you can "
              "still get over them by side-hopping or backflipping across. With explosives, this allows you to access "
              "the central areas without Zelda's Lullaby. With Zelda's Lullaby, it allows you to access the west inner "
              "room without explosives.",
      "井底的坑虽不能靠直冲跳越，但可借侧跳或后空翻跨越。有爆炸物时，可无需塞尔达的摇篮曲进入中央区域；有摇篮曲时，可无需爆炸物进入西侧内室。" },
    { "Boomerang can fish the item out of the rubble without needing explosives to blow it up.",
      "飞旋镖可直接从瓦砾中钩出该道具，无需爆炸物炸开。" },
    { "Allows killing this Skulltula with Sword or Sticks by jumpslashing it as you let go from the vines. "
              "You can avoid taking fall damage by recoiling onto the tree. Also allows killing it as Child with a "
              "Bomb throw. It's much more difficult to use a Bomb as child due to Child Link's shorter height.",
      "允许从藤蔓松手时跳跃斩，以剑或木棒击杀这只骷髅蜘蛛。可借回弹到树上避免坠落伤害。也允许儿童投炸弹将其击杀。但儿童身高较矮，用炸弹难度大得多。" },
    { "Precise Boomerang throws can allow child to kill the Skulltula and collect the token.",
      "精准的飞旋镖投掷可让儿童击杀骷髅蜘蛛并拾取代币。" },
    { "The vines in Forest Temple leading to where the well drain switch is in the standard form can be barely "
              "reached with just the Hookshot. Applies to MQ also.",
      "森林神殿中通往标准形态下水井排水开关的藤蔓，仅靠钩绳勉强够到。MQ 同样适用。" },
    { "With precise Hover Boots movement you can fall down to this ledge from upper balconies. If done "
              "precisely enough, it is not necessary to take fall damage. In MQ, this skips a Longshot requirement. In "
              "Vanilla, this can skip a Hookshot requirement in entrance randomizer.",
      "凭借精准的悬浮靴移动，可从上层阳台落到此凸台。若足够精准，无需承受坠落伤害。MQ 中可省去远钩需求；原版中可在入口随机时省去钩绳需求。" },
    { "A precise Hover Boots movement from the upper balconies in this courtyard can be used to get on top of "
              "the door frame. Applies to both Vanilla and Master Quest. In Vanilla, from on top the door frame you "
              "can summon Pierre, allowing you to access the falling ceiling room early. In Master Quest, this allows "
              "you to obtain the GS on the door frame as adult without Hookshot or Song of Time.",
      "从该院子上层阳台精准移动悬浮靴，可登上门框顶端。原版与大师任务均适用。原版中，站在门框顶端可召唤皮埃尔，提前进入落顶房；大师任务中，可让成年林克无需钩绳或时间之歌即取得门框上的金骷髅。" },
    { "A jumpslash recoil can be used to reach the ledge in the block puzzle room that leads to the west "
              "courtyard. This skips a potential Hover Boots requirement in Vanilla, and it can sometimes apply in MQ "
              "as well. This trick can be performed as both ages.",
      "跳跃斩回弹可够到方块谜题房中通往西侧院子的凸台。原版中可省去可能的悬浮靴需求，MQ 有时也适用。两个年龄均可完成。" },
    { "A well aimed boomerang from the water's edge can reach the hearts from ground level. If unable to swim, "
              "you can back away from the water while the boomerang is returning so the hearts land on the ground.",
      "从水边精准投掷飞旋镖，可从地面够到心。若不会游泳，可在飞旋镖回程时从水边后退，使心落于地面。" },
    { "Shoot the vines in the well as low and as far to the right as possible, and then immediately swim under "
              "the ceiling to the right. This is usually only useful in Master Quest.",
      "尽量低、尽量靠右地射中水井中的藤蔓，随即立刻潜入天花板下方向右游。通常仅在大师任务中有用。" },
    { "Send the Bombchu straight up the center of the wall directly to the left upon entering the room.",
      "进入房间后，将炸弹鼠沿正左方墙壁中央笔直向上送出。" },
    { "The switch to twist the hallway can be hit with a jumpslash through the glass block. To get in front "
              "of the switch, either use the Hover Boots or hit the shortcut switch at the top of the room and jump "
              "from the glass blocks that spawn. Sticks can be used as child, but the Kokiri Sword is too short to "
              "reach through the glass.",
      "扭动走廊的开关可借穿过玻璃块的跳跃斩击中。要站到开关前，要么用悬浮靴，要么击中房间顶部的捷径开关、从生成的玻璃块上跳起。儿童可用木棒，但科克里之剑太短、穿不过玻璃。" },
    { "There's a very small gap between the glass block and the wall. Through that gap you can hookshot the "
              "target on the ceiling.",
      "玻璃块与墙壁之间有一道极窄的缝隙。可透过缝隙用钩绳钩中天花板上的目标。" },
    { "The Boomerang can return to Link through walls, allowing child to hit the hallway switch. This can be "
              "used to allow adult to pass through later, or in conjunction with \"Forest Temple Outside Backdoor with "
              "Jumpslash\".",
      "飞旋镖可穿墙飞回林克手中，让儿童击中走廊开关。借此可让成年林克稍后通过，或与\"森林神殿外后门跳跃斩\"并用。" },
    { "If Adult burns the courtyard webbing with Fire Arrows (which is a permanent flag in Ship Rando) "
              "then Child can climb up to the balconies and jump to the SoT block from the railing, "
              "and from there either roll jump or jump against the wall to reach the doorframe.\n"
              "From there, The GS can be killed with a crouchstab, explosives or other ranged weapon "
              "and collected by climbing down.",
      "若成年林克用火焰箭烧掉院子的蛛网（在 Ship 随机中这是永久标记），儿童便可爬上阳台、从栏杆跳到时间之歌方块，再从那里滚跳或贴墙跳抵达门框。\n从此处，金骷髅可用蹲刺、爆炸物或其他远程武器击杀，并爬下拾取。" },
    { "A precise jump can be used to reach this room.",
      "可凭精准跳跃到达该房间。" },
    { "A precise jump can be used to skip pushing the block.",
      "可凭精准跳跃省去推方块。" },
    { "Also known as \"Pixelshot\". The Longshot can reach the target on the elevator itself, allowing you to "
              "skip needing to spawn the scarecrow.",
      "亦称\"像素射击\"。远钩可钩中电梯本身上的目标，从而省去生成稻草人。" },

    { "If you move quickly you can sneak past the edge of a flame wall before rises up to block you. To "
              "do it without taking damage is more precise. Allows progress without needing either a Small Key or "
              "Hover Boots. In MQ if either \"Fire Temple MQ Lower to Upper Lizalfos Maze with Hover Boots\" or "
              "\"with Precise Jump\" are enabled, this also allows progress deeper into the dungeon without Hookshot.\n"
              "Child can sidehop past fire wall in MQ lobby.",
      "若移动迅速，可在火焰墙升起挡路前从其边缘溜过。要做到不受伤则更需精准。无需小钥匙或悬浮靴即可推进。在 MQ 中，若开启「火之神殿 MQ 下层到上层蜥蜴迷宫用悬浮靴」或「精准跳跃」之一，还可无需钩绳深入地牢。\n儿童可在 MQ 大厅侧跳越过火焰墙。" },
    { "The hitbox for the torch extends a bit outside of the crate. Shoot a flaming arrow at the side of the "
              "crate to light the torch without needing to get over there and break the crate.",
      "火把的判定框略微伸出板条箱外。从板条箱侧面射火焰箭即可点亮火把，无需过去打碎箱子。" },
    { "There is a gap between the hitboxes of the flame wall in the big lava room. If you know where this gap "
              "is located, you can jump through it and skip needing to use the Hookshot. To do this without taking "
              "damage is more precise.",
      "大岩浆房中，火焰墙的判定框之间存在缝隙。若知晓缝隙位置，可跳穿过去、省去钩绳。要做到不受伤则更需精准。" },
    { "It is possible to light both of the timed torches to unbar the door to the boss key chest's room with just "
              "Din's Fire if you move very quickly between the two torches. It is also possible to unbar the door with just "
              "Din's Fire by abusing an oversight in the way the game counts how many torches have been lit.",
      "若在两支定时火把间移动极快，仅凭戴因之火即可点亮二者、解除 Boss 钥匙宝箱房的门闩。也可利用游戏统计已点火把数量的疏漏，仅凭戴因之火解除门闩。" },
    { "You can use the Hover Boots to hover around to the climbable wall, skipping the need to use a fire "
              "source and spawn a Hookshot target.",
      "可穿悬浮靴悬浮绕到可攀爬的墙壁，省去火源并生成钩绳目标。" },
    { "You can walk from the blue switch to the door and quickly open the door before the bars reclose. This "
              "skips needing to reach the upper sections of the maze to get a box to place on the switch.",
      "可从蓝色开关走到门边、在栅栏重新关闭前迅速开门。这省去了为取得放在开关上的箱子而攀爬迷宫上层。" },
    { "Use the Hover Boots off of a crate to climb to the upper maze without needing to spawn and use the "
              "Hookshot targets.",
      "从板条箱借悬浮靴，可攀上迷宫上层，无需生成并使用钩绳目标。" },
    { "A precise jump off of a crate can be used to climb to the upper maze without needing to spawn and use "
              "the Hookshot targets. This trick supersedes both \"Fire Temple MQ Lower to Upper Lizalfos Maze with "
              "Hover Boots\" and \"Fire Temple MQ Lizalfos Maze Side Room without Box\".",
      "从板条箱精准起跳，可攀上迷宫上层，无需生成并使用钩绳目标。本技巧同时取代「火之神殿 MQ 下层到上层蜥蜴迷宫用悬浮靴」与「火之神殿 MQ 蜥蜴迷宫侧室无箱」。" },
    { "The floor of the room that contains this Skulltula is only solid from above. From the maze below, the "
              "Longshot can be shot through the ceiling to obtain the token with two fewer small keys than normal.",
      "容纳这只骷髅蜘蛛的房间地面仅从上方为实体。从下方迷宫，可射远钩穿天花板取得代币，比通常少用两把小钥匙。" },
    { "Stand on the eastern side of the central pillar and longshot the torches on the bottom level. Swim "
              "through the corridor and float up to the top level. This allows access to this area and lower water "
              "levels without Iron Boots. The majority of the tricks that allow you to skip Iron Boots in the Water "
              "Temple are not going to be relevant unless this trick is first enabled.",
      "站在中央柱东侧，用远钩击中底层的火把。游过走廊、浮升至顶层。如此可在无铁靴的情况下进入该区域并降低水位。水之神殿中多数省去铁靴的技巧，唯有先开启本技巧才相关。" },
    { "With a midair side-hop while wearing the Hover Boots, you can reach the cracked wall without needing to "
              "raise the water up to the middle level.",
      "穿悬浮靴在空中侧跳，可在无需将水位升至中层的情况下到达裂墙。" },
    { "A precise jumpslash (among other methods) will get you to the cracked wall without needing the Hover "
              "Boots or to raise the water to the middle level. This trick supersedes \"Water Temple Cracked Wall with "
              "Hover Boots\".",
      "精准跳跃斩（及其他方法）可在无需悬浮靴或升水位至中层的情况下到达裂墙。本技巧取代「水之神殿裂墙用悬浮靴」。" },
    { "With precise Hover Boots movement it is possible to reach the boss key chest's region without needing "
              "the Longshot. It is not necessary to take damage from the spikes. The Gold Skulltula Token in the "
              "following room can also be obtained with just the Hover Boots.",
      "凭精准的悬浮靴移动，可在无需远钩的情况下到达 Boss 钥匙宝箱所在区域。无需承受尖刺伤害。下一房间中的金色骷髅代币也可仅凭悬浮靴取得。" },
    { "In the northern basement there's a ledge from where, in Vanilla Water Temple, boulders roll out into "
              "the room. Normally to jump directly to this ledge logically requires the Hover Boots, but with precise "
              "jump, it can be done without them. This trick applies to both Vanilla and Master Quest.",
      "在北侧地下室有一处凸台，在原版水之神殿中巨石会从那里滚入房间。通常逻辑上直接跳上此凸台需悬浮靴，但凭精准跳跃可无需它完成。原版与大师任务均适用。" },
    { "If you set Farore's Wind inside the central pillar and then return to that warp point after raising the "
              "water to the highest level, you can obtain this Skulltula Token with Hookshot or Boomerang.",
      "若在中央柱内设下花柔之风，待升至最高水位后再返回该传送点，即可用钩绳或飞旋镖取得这只金骷髅代币。" },
    { "After opening the middle water level door into the central pillar, the door will stay unbarred so long as you "
              "do not leave the room, even if you were to raise the water up to the highest level. With the Iron Boots to go "
              "through the door after the water has been raised, you can obtain the Skulltula Token with the Hookshot.",
      "打开中层水位的门进入中央柱后，只要不离房，门闩会保持开启——即便你将水位升至最高。水位升高后穿铁靴穿门而过，即可用钩绳取得金骷髅代币。" },
    { "A very precise Bow shot can hit the eye switch from the floor above. Then, you can jump down into the "
              "hallway and make through it before the gate closes. It can also be done as child, using the Slingshot "
              "instead of the Bow.",
      "从上层地面极精准的弓射可击中眼形开关。随后跳入走廊，在门关上前穿过。儿童也可完成，以弹弓代替弓。" },
    { "If you stand on the very edge of the platform, this Gold Skulltula can be obtained with only the Hookshot.",
      "若站在平台最边缘，这只金色骷髅仅凭钩绳即可取得。" },
    { "If you stand on the very edge of the platform, this Gold Skulltula can be obtained with only the Boomerang.",
      "若站在平台最边缘，这只金色骷髅仅凭飞旋镖即可取得。" },

    { "Standing on the exposed ground toward the end of the river, a precise Longshot use can obtain the "
              "token. The Longshot cannot normally reach far enough to kill the Skulltula, however. You'll first have "
              "to find some other way of killing it.",
      "站在河流尽头裸露的地面上，精准使用远钩即可取得代币。不过远钩通常射程不足以击杀骷髅蜘蛛，你得先另想办法将其击杀。" },
    { "If you come into the dragon statue room from the serpent river, you can sidehop down from above and get "
              "into the tunnel without needing either Iron Boots or a Scale. This trick applies to both Vanilla and "
              "Master Quest. In Vanilla, you must shoot the switch from above with the Bow, and then quickly get "
              "through the tunnel before the gate closes.",
      "若从蛇形河进入龙像房，可自上方侧跳落入、进入隧道，无需铁靴或鳞片。原版与大师任务均适用。原版中，须从上方用弓击中开关，再在门关上前迅速穿过隧道。" },
    { "Normally you need both Hookshot and Iron Boots to hit the switch and swim through the tunnel to get to "
              "the chest. But by hitting the switch from dry land, using one of Bombchus, Hookshot, or Bow, it is "
              "possible to skip one or both of those requirements. After the gate has been opened, besides just using "
              "the Iron Boots, a well-timed dive with at least the Silver Scale could be used to swim through the "
              "tunnel. If coming from the serpent river, a jump dive can also be used to get into the tunnel.",
      "通常需钩绳与铁靴击中开关、游过隧道才能到达宝箱。但从干地用炸弹鼠、钩绳或弓之一击中开关，便可省去其中一项或两项需求。门开启后，除铁靴外，至少持银鳞片的精准俯冲也可游过隧道。若从蛇形河来，跳跃俯冲亦能进入隧道。" },
    { "It is possible for child to hit the switch from dry land using one of Bombchus, Slingshot or Boomerang. "
              "Then, to get to the chest, child can dive through the tunnel using at least the Silver Scale. The "
              "timing and positioning of this dive needs to be perfect to actually make it under the gate, and it all "
              "needs to be done very quickly to be able to get through before the gate closes. Be sure to enable "
              "\"Water Temple Dragon Statue Switch from Above the Water as Adult\" for adult's variant of this trick.",
      "儿童可用炸弹鼠、弹弓或飞旋镖之一从干地击中开关。随后为到达宝箱，儿童可持至少银鳞片俯冲穿过隧道。此俯冲的时机与站位须完美，方能真正从门下通过，且须极快完成、赶在关门前穿过。务必同时开启「水之神殿龙像开关（水上·成年）」以启用成年版。" },
    { "Slanted torches have misleading hitboxes. Whenever you see a slanted torch jutting out of the wall, you "
              "can expect most or all of its hitbox is actually on the other side that wall. This can make slanted "
              "torches very finicky to light when using arrows. The torches in the central pillar of MQ Water Temple "
              "are a particularly egregious example. Logic normally expects Din's Fire and Song of Time.",
      "斜插的火把判定框会误导人。只要看到从墙中斜伸出的火把，其基本或全部的判定框其实在墙的另一侧。这使得用箭射击斜火把时极为挑剔。MQ 水之神殿中央柱的火把便是尤其过分的例子。逻辑上通常预期需戴因之火与时间之歌。" },
    { "Diving in front of ledge tapping B to swim up faster, then equipping iron boots while surfacing allows you to "
              "ledge grab to the higher ground. This can be used to reach ledge to boss door and vanilla compass chest, or "
              "MQ storage room",
      "在凸台前下潜、连按 B 加速上浮，再在浮出水面时装备铁靴，即可抓边登上更高处。可用于到达 Boss 门前的凸台与原版指南针宝箱，或 MQ 储藏室。" },
    { "Invisible hookshot geometry can be used in MQ to get over the gate that blocks you from going to this "
              "Skulltula early, skipping a small key as well as needing Hovers or Scarecrow to reach the locked door.\n"
              "In vanilla this can be used to get past without bronze scale.",
      "MQ 中可利用隐形钩绳几何，越过挡住你提前到此金骷髅的闸门，省去一把小钥匙，也无需悬浮靴或稻草人抵达上锁的门。\n原版中可借此在无需青铜鳞片的情况下通过。" },
    { "It is possible to slash at Morpha without hookshot.",
      "可无需钩绳、直接挥砍摩法。" },
    { "Removes the requirements for the Lens of Truth in Shadow Temple for most areas in the dungeon except "
              "for crossing the moving platform in the huge pit room and for fighting Bongo Bongo.",
      "去除暗之神殿中多数区域对真实之镜的需求，但跨越巨坑房移动平台以及对战邦哥邦哥除外。" },
    { "Removes the requirements for the Lens of Truth in Shadow Temple to cross the invisible moving platform "
              "in the huge pit room in either direction.",
      "去除暗之神殿中、任意方向穿越巨坑房隐形移动平台对真实之镜的需求。" },
    { "Bongo Bongo can be defeated without the use of Lens of Truth, as the hands give a pretty good idea of "
              "where the eye is.",
      "无需真实之镜即可击败邦哥邦哥，因为双手已相当明确地指示了眼睛的位置。" },
    { "A very precise Hover Boots movement from off of the lower chest can get you on top of the falling "
              "spikes without needing to pull the block. Applies to both Vanilla and Master Quest.",
      "从下层宝箱处极精准地移动悬浮靴，可登上落刺顶端，无需拉动方块。原版与大师任务均适用。" },
    { "Backflipping as the falling spikes fall clips above without needing any other requirements. "
              "Applies to both Vanilla and Master Quest.",
      "在落刺下落时后空翻，可无需求地穿模到上方。原版与大师任务均适用。" },
    { "After killing the Skulltula, a very precise Hover Boots movement from off of the lower chest can get "
              "you on top of the falling spikes without needing to pull the block. From there, another very precise "
              "Hover Boots movement can be used to obtain the token without needing the Hookshot. Applies to both "
              "Vanilla and Master Quest.",
      "击杀骷髅蜘蛛后，从下层宝箱处极精准地移动悬浮靴，可登上落刺顶端、无需拉动方块。由此，再凭另一次极精准的悬浮靴移动，即可无需钩绳取得代币。原版与大师任务均适用。" },
    { "Release the Bombchu with good timing so that it explodes near the bottom of the pot.",
      "把握时机放出炸弹鼠，使其在大壶底部附近爆炸。" },
    { "By sending a Bombchu around the edge of the gorge, you can knock down the statue without needing a Bow. "
              "Applies in both Vanilla and MQ Shadow.",
      "沿峡谷边缘送出炸弹鼠，即可无需弓将雕像击落。原版与 MQ 暗之神殿均适用。" },
    { "Using precise sword slashes, Bongo Bongo can be defeated without using projectiles. This is only "
              "relevant in conjunction with Shadow Temple dungeon shortcuts or shuffled boss entrances.",
      "凭借精准的剑斩，无需投射物即可击败邦哥邦哥。此技巧仅在与暗之神殿地牢捷径或洗牌 Boss 入口并用时相关。" },
    { "Removes the requirements for the Lens of Truth in Shadow Temple MQ for most areas in the dungeon. See "
              "\"Shadow Temple MQ Invisible Moving Platform without Lens of Truth\", \"Shadow Temple MQ Invisible "
              "Blades Silver Rupees without Lens of Truth\", \"Shadow Temple MQ 2nd Dead Hand without Lens of Truth\", "
              "and \"Shadow Temple Bongo Bongo without Lens of Truth\" for exceptions.",
      "去除 MQ 暗之神殿中多数区域对真实之镜的需求。例外见「MQ 暗之神殿隐形移动平台无需真实之镜」「MQ 暗之神殿隐形刃银卢比无需真实之镜」「MQ 暗之神殿第 2 个死手无需真实之镜」与「无需真实之镜击败邦哥邦哥」。" },
    { "Removes the requirement for the Lens of Truth or Nayru's Love in Shadow Temple MQ for the Invisible "
              "Blades room Silver Rupee collection.",
      "去除 MQ 暗之神殿隐形刃房收集银卢比对真实之镜或娜如之爱的需求。" },

    { "Removes the requirements for the Lens of Truth in Shadow Temple MQ to cross the invisible moving "
              "platform in the huge pit room in either direction.",
      "去除 MQ 暗之神殿中、任意方向穿越巨坑房隐形移动平台对真实之镜的需求。" },
    { "Dead Hand spawns in a random spot within the room. Having Lens removes the hassle of having to comb the "
              "room looking for his spawn location.",
      "死手会在房间内随机位置生成。拥有真实之镜可免去在房间中搜寻其生成点的麻烦。" },
    { "You can Longshot a torch and jump-slash recoil onto the tongue. It works best if you Longshot the right "
              "torch from the left side of the room.",
      "可射远钩击中火把，再以跳跃斩回弹到舌状物上。若从房间左侧射中右侧火把，效果最佳。" },
    { "The Like Like can be used to boost you into the Silver Rupee or Recovery Hearts that normally require Song of "
              "Time. This cannot be performed on OHKO since the Like Like does not boost you high enough if you die.",
      "可用莱克莱克将你顶入通常需时间之歌的银卢比或回复心处。OHKO 下无法完成，因为死亡时莱克莱克顶起的高度不足。" },
    { "Normally a frozen eye switch spawns some platforms that you can use to climb down, but there's actually "
              "a small piece of ground that you can stand on that you can just jump down to.",
      "通常冰冻眼开关会生成若干平台供你攀爬而下，但其实有一小块可站立的地面，直接跳下去即可。" },
    { "It is possible to jump from the alcove in the windy hallway to the middle platform. There are two methods: "
              "wait out the fan opposite the door and hold forward, or jump to the right to be pushed by the fan there "
              "towards the platform ledge. Note that jumps of this distance are inconsistent, but still possible.",
      "可从风之大道壁龛跳到中央平台。两种方法：在门对面的风扇前等候并一直向前，或向右跳、被该处风扇推往平台凸台。注意此距离跳跃并不稳定，但仍可行。" },
    { "Removes the requirements for the Lens of Truth in Spirit Temple.",
      "去除魂之神殿对真实之镜的需求。" },
    { "A carefully-timed Bombchu can hit the switch.",
      "把握时机放出炸弹鼠可击中开关。" },
    { "By carefully walking onto the upper arm of the statue, it's possible to get a good angle on the "
              "Gold Skulltula (In Vanilla) and the farthest pot (In MQ) to collect the checks with Boomerang. "
              "The nearest pot in MQ can be reached from the forearm and is always in logic.",
      "谨慎走上雕像的上臂，即可对金骷髅（原版）与最远罐子（MQ）取得良好角度，以飞旋镖收取。MQ 中最近的罐子可从前臂够到，始终算作可达。" },
    { "A bomb can be used to hit the switch on the ceiling, but it must be thrown from a particular distance "
              "away and with precise timing.",
      "可用炸弹击中天花板上的开关，但须从特定距离、以精准时机投出。" },
    { "A precise jump to obtain the following as adult without needing one of Hover Boots, or Hookshot (in Vanilla) "
              "or Song of Time (in MQ): - Spirit Temple Statue Room Northeast Chest - Spirit Temple GS Lobby - Spirit Temple "
              "MQ Central Chamber Top Left Pot (Left) - Spirit Temple MQ Central Chamber Top Left Pot (Right)",
      "成年林克凭精准跳跃即可取得以下项目，无需悬浮靴，也无需钩绳（原版）或时间之歌（MQ）：- 魂之神殿雕像房东北宝箱 - 魂之神殿金骷髅大厅 - MQ 魂之神殿中央室左上罐（左）- MQ 魂之神殿中央室左上罐（右）" },
    { "To get a line of sight from the upper torch to the map chest torches, you must pull an Armos statue all "
              "the way up the stairs.",
      "要为上层火把与地图宝箱火把之间取得视线，须将阿摩斯雕像一路拉上楼梯。" },
    { "Using the blocks in the room as platforms you can get lines of sight to all three torches. The timer on "
              "the torches is quite short so you must move quickly in order to light all three.\n"
              "A backflip can be used instead to light torches without pushing blocks.",
      "以房间中的方块为平台，可对三支火把取得视线。火把计时很短，须迅速移动才能点亮全部三支。\n也可改用后空翻点亮火把，省去推方块。" },
    { "Logic normally guarantees a way of dealing with both the Beamos and the Walltula before climbing the wall.",
      "逻辑上通常保证你在攀爬墙壁前，已有应对比莫斯与墙蛛的办法。" },
    { "Removes the requirements for the Lens of Truth in Spirit Temple MQ.",
      "去除 MQ 魂之神殿对真实之镜的需求。" },
    { "While adult can easily jump directly to the switch that unbars the door to the sun block room, child "
              "Link cannot make the jump without spawning a Song of Time block to jump from. You can skip this by "
              "throwing the crate down onto the switch from above, which does unbar the door, however the crate "
              "immediately breaks, so you must move quickly to get through the door before it closes back up.",
      "成年林克可轻松直接跳到解除太阳方块房门闩的开关，但儿童林克若不生成时间之歌方块作起跳点便跳不过去。你可改为从上方将板条箱掷到开关上，同样能解除门闩；但箱子会立刻碎裂，须迅速移动、在门重新关上前穿过。" },
    { "Throw the Boomerang in such a way that it curves through the side of the glass block to hit the Gold Skulltula.",
      "投出飞旋镖，使其绕过玻璃块侧面、命中金骷髅。" },
    { "By standing in a precise position it is possible to light two of the torches with a single use of "
              "Din\'s Fire. This saves enough time to be able to light all three torches with only Din\'s Fire.",
      "站在精准位置，可凭一次戴因之火点亮两支火把。这节省的时间足以让你仅用戴因之火便点亮全部三支。" },
    { "You can melt the ice by shooting an arrow through a torch. The only way to find a line of sight for "
              "this shot is to first spawn a Song of Time block, and then stand on the very edge of it.",
      "可射箭穿火把融冰。要为此射击取得视线，唯一办法是先生成时间之歌方块，再站到它的极边缘。" },
    { "Most stalagmites blocking path in Ice Cavern can be clipped past with basic movement. Also applies to "
              "Water Trial.",
      "冰之洞窟中多数挡路的石笋可借基础移动穿模越过。水之试炼同样适用。" },
    { "Shooting stalagmites with hookshot in the right way also breaks them. Also applies to Water Trial.",
      "以正确方式用钩绳射击石笋也能击碎。水之试炼同样适用。" },

    { "The Hover Boots can be used to get in front of the Skulltula to kill it with a jumpslash. Then, the "
              "Hover Boots can again be used to obtain the Token, all without Hookshot or Boomerang.",
      "可穿悬浮靴站到骷髅蜘蛛前，以跳跃斩将其击杀。随后可再次用悬浮靴取得代币，全程无需钩绳或飞旋镖。" },
    { "If you side-hop into the perfect position, you can briefly stand on the platform with the red ice just "
              "long enough to dump some blue fire.",
      "若侧跳到完美位置，你可在红冰平台上短暂站立，恰好够时间倒些蓝焰。" },
    { "Removes the requirements for the Lens of Truth in Gerudo Training Ground.",
      "去除格鲁德训练场对真实之镜的需求。" },
    { "After collecting the rest of the Silver Rupees in the room, you can reach the final Silver Rupee on the "
              "ceiling by being pulled up into it after getting grabbed by the Wallmaster. Then, you must also reach "
              "the exit of the room without the use of the Hookshot. If you move quickly you can sneak past the edge "
              "of a flame wall before it can rise up to block you. To do so without taking damage is more precise.",
      "收齐房间中其余银卢比后，被墙之主宰抓走、被拉入天花板时，可够到天花板上的最后一颗银卢比。随后还须在不使用钩绳的情况下到达房间出口。若移动迅速，可在火焰墙升起挡路前从其边缘溜过。要做到不受伤则更需精准。" },
    { "A precise Hover Boots use from the top of the chest can allow you to grab the ledge without needing the "
              "usual requirements. In Master Quest, this always skips a Song of Time requirement. In Vanilla, this "
              "skips a Hookshot requirement, but is only relevant if \"Gerudo Training Ground Left Side Silver Rupees "
              "without Hookshot\" is enabled.",
      "从宝箱顶端精准使用悬浮靴，可在无需常规需求的情况下抓住凸台。大师任务中，这总能省去时间之歌需求；原版中可省去钩绳需求，但仅当开启「格鲁德训练场左侧银卢比（无钩绳）」时相关。" },
    { "A precise rolling jump can be used to jump between all but the furthest platforms in the lava room.",
      "在岩浆房中，可凭精准的滚跳跨越除最远平台外的所有平台。" },
    { "Removes the requirements for the Lens of Truth in Gerudo Training Ground MQ.",
      "去除格鲁德训练场 MQ 对真实之镜的需求。" },
    { "The highest Silver Rupee can be obtained by hookshooting the target and then immediately jumpslashing "
              "toward the Rupee.",
      "可射钩绳击中目标，随即朝银卢比方向跳跃斩，从而取得最高的银卢比。" },
    { "After collecting the rest of the Silver Rupees in the room, you can reach the final Silver Rupee on the "
              "ceiling by being pulled up into it after getting grabbed by the Wallmaster. The Wallmaster will not "
              "track you to directly underneath the rupee. You should take the last step to be under the rupee after "
              "the Wallmaster has begun its attempt to grab you. Also included with this trick is that fact that the "
              "switch that unbars the door to the final chest of GTG can be hit without a projectile, using a precise "
              "jumpslash. This trick supersedes \"Gerudo Training Ground MQ Left Side Silver Rupees with Hookshot\".",
      "收齐房间中其余银卢比后，被墙之主宰抓走、被拉入天花板时，可够到天花板上的最后一颗银卢比。墙之主宰不会追踪到你、让你直接位于卢比正下方；你应在墙之主宰开始抓你之后、最后一步站到卢比下方。本技巧亦包含：解除 GTG 最后宝箱门闩的开关，可凭精准跳跃斩、无需投射物击中。本技巧取代「格鲁德训练场 MQ 左侧银卢比（有钩绳）」。" },
    { "Removes the requirements for the Lens of Truth in Ganon's Castle.",
      "去除盖侬城堡对真实之镜的需求。" },
    { "The highest rupee can be obtained as adult by performing a precise jump and a well-timed jumpslash "
              "off of an Armos.",
      "成年林克可借精准跳跃、从阿摩斯身上及时跳跃斩，取得最高的卢比。" },
    { "Removes the requirements for the Lens of Truth in Ganon's Castle MQ.",
      "去除盖侬城堡 MQ 对真实之镜的需求。" },
    { "It's possible to hook the target at the end of fire trial with just Hookshot, but it requires precise "
              "aim and perfect positioning. The main difficulty comes from getting on the very corner of the obelisk "
              "without falling into the lava.",
      "仅用钩绳即可钩中火之试炼尽头的靶，但需精准瞄准与完美站位。主要难点在于要站上方尖碑的极边缘、又不坠入岩浆。" },
    { "You can light the torch in this room without a fire source by shooting an arrow through the lit torch "
              "at the beginning of the room. Because the room is so dark and the unlit torch is so far away, it can be "
              "difficult to aim the shot correctly.",
      "可射箭穿过房间起始处的已燃火把，从而在无火源的情况下点亮本房火把。由于房间极暗、未燃火把又极远，要正确瞄准这一射颇为困难。" },
    { "If you move quickly you can sneak past the edge of a flame wall before it can rise up to block you. In "
              "this case to do it without taking damage is especially precise.",
      "若移动迅速，可在火焰墙升起挡路前从其边缘溜过。此情形下要做到不受伤则格外精准。" },

    // ---- Randomizer Tricks: trick names (A) ----
    { "Acute angle clip", "锐角穿墙" },
    { "Adult Kokiri Forest GS with Hover Boots", "成人用悬浮靴获取科克里森林金骷髅" },
    { "Advanced clips", "高级穿墙" },
    { "Backflip over Mido as Adult", "成人用后空翻越过米多" },
    { "Big Poe without Epona", "无需伊波纳获取大波克" },
    { "Blank A", "空 A 键" },
    { "Blue Fire Beyond Red Ice", "越过红冰获取蓝火焰" },
    { "Bombchu Beehives", "炸弹鼠蜂巢" },
    { "Bottom of the Well Map Chest with Strength & Sticks", "以力量与木棒获取井底地图宝箱" },
    { "Bottom of the Well MQ Dead Hand Freestanding Key with Boomerang", "以飞旋镖获取井底 MQ 死手独立钥匙" },
    { "Bottom of the Well MQ Jump Over the Pits", "井底 MQ 跳过深坑" },
    { "Bottom of the Well Navi dive", "井底娜薇俯冲" },
    { "Bottom of the Well without Lens of Truth", "无需真实之镜通过井底" },
    { "Bunny Hood", "兔子头巾" },
    { "Child Dead Hand without Kokiri Sword", "儿童无需科克里之剑击败死手" },
    { "Colossus Hill GS with Hookshot", "以钩绳获取巨像山丘金骷髅" },
    { "Death Mountain Crater Jump to Bolero", "死亡山脉火山口跳向波丽罗" },
    { "Death Mountain Crater Upper to Lower Boulder Skip", "死亡山脉火山口上层跳下巨石" },
    { "Death Mountain Crater Upper to Lower with Hammer", "以锤子从火山口上层到下层" },
    { "Death Mountain Trail Chest with Strength", "以力量获取死神山径宝箱" },
    { "Death Mountain Trail Child Climb Without Shield", "儿童无需盾攀爬死神山径" },
    { "Death Mountain Trail Climb with Hover Boots", "以悬浮靴攀爬死神山径" },
    { "Death Mountain Trail Lower Red Rock GS with Hover Boots", "以悬浮靴获取下层红岩金骷髅" },
    { "Death Mountain Trail Lower Red Rock GS with Jumpslash", "以跳跃斩获取下层红岩金骷髅" },
    { "Death Mountain Trail Lower Red Rock GS with Magic Bean", "以魔法魔豆获取下层红岩金骷髅" },
    { "Death Mountain Trail Soil GS without Destroying Boulder", "不破坏巨石获取死神山径土堆金骷髅" },
    { "Death Mountain Trail Upper Red Rock GS with Backflip", "以後空翻获取上层红岩金骷髅" },
    { "Deku Tree Basement Backflip over Spiked Log", "德库树地下室後空翻越过尖刺木" },
    { "Deku Tree Basement Vines GS with Jumpslash", "以跳跃斩获取德库树地下室藤蔓金骷髅" },
    { "Deku Tree Basement Web to Gohma with Bow", "以弓从蛛网到哥马" },
    { "Deku Tree Basement without Slingshot", "无需弹弓通过德库树地下室" },
    { "Deku Tree MQ Compass Room GS Boulders with Just Hammer", "仅以锤子处理德库树 MQ 指南针房巨石金骷髅" },
    { "Deku Tree MQ Roll Under the Spiked Log", "德库树 MQ 从尖刺木下滚过" },
    { "Deliver Eye Drops with Bolero of Fire", "以炎之波丽罗送达眼药水" },
    { "Distant Boulder Collision", "远距离巨石碰撞" },
    { "Doom Jump", "末日跳" },
    { "EPG", "EPG（入口点故障）" },
    { "Equip Swap", "装备交换" },
    { "Fewer Tunic Requirements", "减少外衣需求" },
    { "Fire Ring", "火焰环" },
    { "Fire Temple Climb without Strength", "无需力量攀爬火之神殿" },
    { "Fire Temple MQ Above Flame Wall Maze GS from Below with Longshot", "以远钩从下方获取火之神殿 MQ 火焰墙迷宫上方金骷髅" },
    { "Fire Temple MQ Big Lava Room Blocked Door without Hookshot", "无需钩绳通过火之神殿 MQ 大岩浆房封锁门" },
    { "Fire Temple MQ Boss Key Chest without Bow", "无需弓获取火之神殿 MQ Boss 钥匙宝箱" },
    { "Fire Temple MQ Chest Near Boss without Breaking Crate", "不破坏木箱获取火之神殿 MQ Boss 附近宝箱" },
    { "Fire Temple MQ Climb without Fire Source", "无需火源攀爬火之神殿 MQ" },
    { "Fire Temple MQ Lizalfos Maze Side Room without Box", "无需箱子进入火之神殿 MQ 蜥蜴战士迷宫侧室" },
    { "Fire Temple MQ Lower to Upper Lizalfos Maze with Hover Boots", "以悬浮靴从火之神殿 MQ 蜥蜴迷宫下层到上层" },
    { "Fire Temple MQ Lower to Upper Lizalfos Maze with Precise Jump", "以精准跳跃从火之神殿 MQ 蜥蜴迷宫下层到上层" },
    { "Fire Temple Skip Flame Walls", "火之神殿跳过火焰墙" },
    { "Fire Temple Song of Time Room GS without Song of Time", "无需时间之歌获取火之神殿时间之歌房金骷髅" },
    { "Fire Trial MQ with Hookshot", "以钩绳通过火焰试炼 MQ" },
    { "Flame Storage", "火焰存储" },
    { "Forest Temple Courtyard Hearts with Boomerang", "以飞旋镖获取森林神殿庭院心之碎片" },
    { "Forest Temple East Courtyard Door Frame with Hover Boots", "以悬浮靴登森林神殿东庭院门框" },
    { "Forest Temple East Courtyard GS with Boomerang", "以飞旋镖获取森林神殿东庭院金骷髅" },
    { "Forest Temple East Courtyard Vines with Hookshot", "以钩绳获取森林神殿东庭院藤蔓" },
    { "Forest Temple First Room GS with Difficult-to-Use Weapons", "以难用武器获取森林神殿第一房金骷髅" },
    { "Forest Temple MQ Doorframe GS as Child without Boomerang", "儿童无需飞旋镖获取森林神殿 MQ 门框金骷髅" },
    { "Forest Temple MQ Twisted Hallway Switch with Boomerang", "以飞旋镖触发森林神殿 MQ 扭曲走廊开关" },
    { "Forest Temple MQ Twisted Hallway Switch with Hookshot", "以钩绳触发森林神殿 MQ 扭曲走廊开关" },
    { "Forest Temple MQ Twisted Hallway Switch with Jumpslash", "以跳跃斩触发森林神殿 MQ 扭曲走廊开关" },
    { "Forest Temple NE Courtyard Ledge with Hover Boots", "以悬浮靴登森林神殿东北庭院凸台" },
    { "Forest Temple Outside Backdoor with Jumpslash", "以跳跃斩从森林神殿外后门进入" },
    { "Gerudo Training Ground Left Side Silver Rupees without Hookshot", "无需钩绳获取格鲁德训练场左侧银卢比" },
    { "Gerudo Training Ground MQ Left Side Silver Rupees with Hookshot", "以钩绳获取格鲁德训练场 MQ 左侧银卢比" },
    { "Gerudo Training Ground MQ Left Side Silver Rupees without Hookshot", "无需钩绳获取格鲁德训练场 MQ 左侧银卢比" },
    { "Gerudo Training Ground MQ without Lens of Truth", "无需真实之镜通过格鲁德训练场 MQ" },
    { "Gerudo Training Ground without Lens of Truth", "无需真实之镜通过格鲁德训练场" },
    { "Gerudo Training Grounds Itemless Lava Room Jump", "无道具跳跃通过格鲁德训练场岩浆房" },
    { "Gerudo Valley Bridge with only Hookshot", "仅以钩绳过格鲁德大峡谷大桥" },
    { "Gerudo Valley Crate PoH as Adult with Hover Boots", "成人以悬浮靴用木箱到达 PoH" },
    { "Gerudo Valley Enter Carpenter's Tent as Child", "儿童进入木匠帐篷" },
    { "Gerudo Valley Jump Fence with Cucco", "以鸡跳过格鲁德大峡谷栅栏" },
    { "Goron City Grotto with Hookshot While Taking Damage", "受伤时用钩绳进入格雷城洞穴" },
    { "Goron City Maze Left Chest with Hover Boots", "以悬浮靴获取格雷城迷宫左侧宝箱" },
    { "Goron City Spinning Pot PoH with Bombchu", "以炸弹鼠用旋转壶到达 PoH" },
    { "Goron City Spinning Pot PoH with Strength", "以力量用旋转壶到达 PoH" },
    { "Graveyard Freestanding PoH with Boomerang", "以飞旋镖获取墓地独立 PoH" },
    { "Ground Clip", "地面穿模" },
    { "Ground Jump", "地面跳" },
    { "Hard Ground Jumps", "高难度地面跳" },
    { "HESS", "HESS（超级延展滑行）" },
    { "Hidden Grottos without Stone of Agony", "无需振动石进入隐藏洞穴" },
    { "Hookshot Clip", "钩绳穿墙" },
    { "Hookshot Jump", "钩绳跳" },
    { "Hookshot Ladders", "钩绳梯子" },
    { "Hyrule Castle Storms Grotto GS with Just Boomerang", "仅以飞旋镖获取海拉鲁城堡风暴洞穴金骷髅" },
    { "Ice Cavern Block Room GS with Hover Boots", "以悬浮靴获取冰之洞窟方块房金骷髅" },
    { "Ice Cavern MQ Red Ice GS without Song of Time", "无需时间之歌获取冰之洞窟 MQ 红冰金骷髅" },
    { "Ice Cavern Stalagmite Clips", "冰之洞窟石笋穿模" },
    { "Ice Cavern Stalagmites with Hookshot", "以钩绳获取冰之洞窟石笋" },
    { "Ignore Visible Collision", "忽略可见碰撞" },
    { "ISG", "ISG（无限剑故障）" },
    { "Item Extension", "道具延展" },
    { "Jabu B1 Pass Cube with Hover Boots", "以悬浮靴通过加卜 B1 方块" },
    { "Jabu Barinade with Pots", "以罐子击败加卜巴拉纳德" },
    { "Jabu MQ Compass Chest with Boomerang", "以飞旋镖获取加卜 MQ 指南针宝箱" },
    { "Jabu MQ Song of Time Block GS with Boomerang", "以飞旋镖获取加卜 MQ 时间之歌方块金骷髅" },
    { "Jabu MQ without Lens of Truth", "无需真实之镜通过加卜 MQ" },
    { "Jabu Near Boss Ceiling Switch with Explosives", "以爆炸物触发加卜 Boss 附近天花板开关" },
    { "Jabu Near Boss Ceiling Switch/GS without Boomerang or Explosives", "无需飞旋镖或爆炸物触发加卜 Boss 附近天花板开关/金骷髅" },
    { "Jabu Near Boss Room with Hover Boots", "以悬浮靴进入加卜 Boss 附近房间" },
    { "Jump onto the Lost Woods Bridge as Adult with Nothing", "成人空手跳上迷失森林桥" },
    { "Kakariko Rooftop GS with Hover Boots", "以悬浮靴获取卡卡利科屋顶金骷髅" },
    { "Kakariko Tower GS with Jumpslash", "以跳跃斩获取卡卡利科塔金骷髅" },
    { "Lake Hylia Lab Dive without Gold Scale", "无需黄金鳞片潜入海拉鲁湖研究所" },
    { "Lake Hylia Lab Wall GS with Jumpslash", "以跳跃斩获取海拉鲁湖研究所墙金骷髅" },
    { "Ledge Clip into Training Ground", "凸台穿模进入训练场" },
    { "Lensless Wasteland", "无真实之镜通过荒原" },

    // ---- Randomizer Tricks: trick names (B) ----
    { "Light Trial MQ without Hookshot", "无需钩绳通过光之试炼 MQ" },
    { "Lost Woods Adult GS without Bean", "成人无需魔豆获取迷失森林金骷髅" },
    { "Lost Woods Navi dive", "迷失森林娜薇俯冲" },
    { "Open Underwater Chests", "开启水下宝箱" },
    { "Reach Gerudo Training Ground Fake Wall Ledge with Hover Boots", "以悬浮靴到达格鲁德训练场假墙凸台" },
    { "Reverse Wasteland", "反向荒原" },
    { "Rolling Goron (Hot Rodder Goron) as Child with Strength", "儿童以力量推动滚格雷（飙车格雷）" },
    { "Second Dampe Race as Child", "儿童参加第二次达培赛跑" },
    { "Shadow Temple Bongo Bongo without Lens of Truth", "无需真实之镜击败暗之神殿邦哥邦哥" },
    { "Shadow Temple Bongo Bongo without projectiles", "无需投射物击败暗之神殿邦哥邦哥" },
    { "Shadow Temple Entry with Fire Arrows", "以火焰箭进入暗之神殿" },
    { "Shadow Temple Falling Spikes GS with Hover Boots", "以悬浮靴获取暗之神殿落刺金骷髅" },
    { "Shadow Temple Freestanding Key with Bombchu", "以炸弹鼠获取暗之神殿独立钥匙" },
    { "Shadow Temple Invisible Moving Platform without Lens of Truth", "无需真实之镜通过暗之神殿隐形移动平台" },
    { "Shadow Temple MQ 2nd Dead Hand without Lens of Truth", "无需真实之镜通过暗之神殿 MQ 第二个死手" },
    { "Shadow Temple MQ Invisible Blades Silver Rupees without Lens of Truth", "无需真实之镜获取暗之神殿 MQ 隐形刃银卢比" },
    { "Shadow Temple MQ Invisible Blades without Song of Time", "无需时间之歌通过暗之神殿 MQ 隐形刃" },
    { "Shadow Temple MQ Invisible Moving Platform without Lens of Truth", "无需真实之镜通过暗之神殿 MQ 隐形移动平台" },
    { "Shadow Temple MQ Lower Huge Pit without Fire Source", "无需火源通过暗之神殿 MQ 下层巨坑" },
    { "Shadow Temple MQ Stationary Objects without Lens of Truth", "无需真实之镜通过暗之神殿 MQ 静止物体" },
    { "Shadow Temple MQ Truth Spinner Gap with Longshot", "以远钩跨越暗之神殿 MQ 真实纺车缺口" },
    { "Shadow Temple MQ Windy Walkway Reverse without Hover Boots", "无需悬浮靴反向通过暗之神殿 MQ 风之大道" },
    { "Shadow Temple River Statue with Bombchu", "以炸弹鼠处理暗之神殿河之雕像" },
    { "Shadow Temple Stationary Objects without Lens of Truth", "无需真实之镜通过暗之神殿静止物体" },
    { "Shadow Temple Stone Umbrella Clip", "暗之神殿石伞穿模" },
    { "Shadow Temple Stone Umbrella Skip", "暗之神殿石伞跳过" },
    { "Shadow Trial MQ Torch with Bow", "以弓点燃暗之试炼 MQ 火把" },
    { "Simple damage boosts", "简单伤害增益" },
    { "Simple hover boosts", "简单悬浮增益" },
    { "Skip Forest Temple MQ Block Puzzle with Bombchu", "以炸弹鼠跳过森林神殿 MQ 方块谜题" },
    { "Skip King Zora as Adult with Nothing", "成人空手跳过卓拉王" },
    { "Sliding Jumps", "滑行跳" },
    { "Sneak Past Moving Gerudo Guards with No Items", "无道具潜过移动格鲁德守卫" },
    { "Spirit Temple Child Side Bridge with Bombchu", "以炸弹鼠过魂之神殿儿童侧桥" },
    { "Spirit Temple Lower Adult Switch with Bombs", "以炸弹触发魂之神殿下层成人开关" },
    { "Spirit Temple Main Room Hookshot to Boss Platform", "以钩绳从魂之神殿主厅到 Boss 平台" },
    { "Spirit Temple Map Chest with Bow", "以弓获取魂之神殿地图宝箱" },
    { "Spirit Temple MQ Frozen Eye Switch without Fire", "无需火触发魂之神殿 MQ 冰冻眼开关" },
    { "Spirit Temple MQ Lower Adult without Fire Arrows", "无需火焰箭通过魂之神殿 MQ 下层成人区" },
    { "Spirit Temple MQ Sun Block Room as Child without Song of Time", "儿童无需时间之歌进入魂之神殿 MQ 太阳方块房" },
    { "Spirit Temple MQ Sun Block Room GS with Boomerang", "以飞旋镖获取魂之神殿 MQ 太阳方块房金骷髅" },
    { "Spirit Temple MQ without Lens of Truth", "无需真实之镜通过魂之神殿 MQ" },
    { "Spirit Temple Shifting Wall with No Additional Items", "无需额外道具通过魂之神殿移动墙" },
    { "Spirit Temple Statue Room Jump from Hands to Upper Ledges", "从手跳到魂之神殿雕像房上层凸台" },
    { "Spirit Temple Statue Room West Ledge Checks with Boomerang", "以飞旋镖检查魂之神殿雕像房西凸台" },
    { "Spirit Temple Sun Block Room Chest with Bow", "以弓获取魂之神殿太阳方块房宝箱" },
    { "Spirit Temple without Lens of Truth", "无需真实之镜通过魂之神殿" },
    { "Spirit Trial without Hookshot", "无需钩绳通过灵之试炼" },
    { "Swim Through Forest Temple Well with Hookshot", "以钩绳游过森林神殿水井" },
    { "Unintuitive Jumps", "反直觉跳跃" },
    { "Wasteland Crossing with Bunny Hood", "戴兔子头巾穿越荒原" },
    { "Wasteland Crossing without Hover Boots or Longshot", "无需悬浮靴或远钩穿越荒原" },
    { "Water Temple Boss Key Region with Hover Boots", "以悬浮靴到达水之神殿 Boss 钥匙区" },
    { "Water Temple Central Bow Target without Longshot or Hover Boots", "无需远钩或悬浮靴射击水之神殿中央弓靶" },
    { "Water Temple Central Pillar GS with Iron Boots", "以铁靴获取水之神殿中央柱金骷髅" },
    { "Water Temple Cracked Wall with Hover Boots", "以悬浮靴处理水之神殿裂墙" },
    { "Water Temple Cracked Wall with No Additional Items", "无需额外道具处理水之神殿裂墙" },
    { "Water Temple Dragon Statue Jump Dive", "水之神殿龙像跳跃俯冲" },
    { "Water Temple Dragon Statue Switch from Above the Water as Adult", "成人从水上触发水之神殿龙像开关" },
    { "Water Temple Dragon Statue Switch from Above the Water as Child", "儿童从水上触发水之神殿龙像开关" },
    { "Water Temple Entry without Iron Boots using Hookshot", "以钩绳无铁靴进入水之神殿" },
    { "Water Temple Falling Platform Room GS with Boomerang", "以飞旋镖获取水之神殿落台房金骷髅" },
    { "Water Temple Falling Platform Room GS with Hookshot", "以钩绳获取水之神殿落台房金骷髅" },
    { "Water Temple Invisible Hookshot Target", "水之神殿隐形钩绳目标" },
    { "Water Temple Ledge Grab While Surfacing with Iron Boots", "以铁靴在浮出水面时抓凸台" },
    { "Water Temple Morpha without Hookshot", "无需钩绳击败水之神殿摩法" },
    { "Water Temple MQ Central Pillar with Fire Arrows", "以火焰箭处理水之神殿 MQ 中央柱" },
    { "Water Temple North Basement Ledge with Precise Jump", "以精准跳跃登水之神殿北部 basement 凸台" },
    { "Water Temple River GS without Iron Boots", "无需铁靴获取水之神殿河流金骷髅" },
    { "Water Temple Torch Longshot", "水之神殿火把远钩" },
    { "Windmill PoH as Child with Precise Jumpslash", "儿童以精准跳跃斩在风车到达 PoH" },
    { "Dodongo's Cavern Scarecrow GS with Armos Statue", "多东哥洞窟以阿摩斯雕像获取稻草人金骷髅" },
    { "Dodongo's Cavern Vines GS from Below with Longshot", "多东哥洞窟以远钩从下方获取藤蔓金骷髅" },
    { "Dodongo's Cavern Stairs with Bow", "多东哥洞窟以弓降下楼梯" },
    { "Dodongo's Cavern Child Slingshot Skips", "多东哥洞窟儿童弹弓跳跃" },
    { "Dodongo's Cavern Two Scrub Room with Strength", "多东哥洞窟以力量进入双商人房" },
    { "Dodongo's Cavern Smash the Boss Lobby Floor", "多东哥洞窟砸碎 Boss 前厅地板" },
    { "Dodongo's Cavern MQ Stairs With Only Strength", "多东哥洞窟 MQ 仅以力量降下楼梯" },
    { "Dodongo's Cavern MQ Early Bomb Bag Area as Child", "多东哥洞窟 MQ 儿童提前到达炸弹袋区" },
    { "Dodongo's Cavern MQ Light the Eyes with Strength as Child", "多东哥洞窟 MQ 儿童以力量点亮眼睛" },
    { "Dodongo's Cavern MQ Light the Eyes with Strength as Adult", "多东哥洞窟 MQ 成人以力量点亮眼睛" },
    { "Dodongo's Cavern Dodongo with Only Bombchus", "多东哥洞窟仅以炸弹鼠击败多东哥" },
    { "Dodongo's Cavern Light the Eyes with Bombchus", "多东哥洞窟以炸弹鼠点亮眼睛" },
    { "Lift Big Skulltulas with Pausing", "通过暂停抬起大骷髅蜘蛛" },
    { "Gerudo's Fortress Gate Skip with Sidehop", "通过侧跳跳过格鲁德要塞大门" },
    { "Gerudo's Fortress Skip Wasteland Gate as Adult", "成人跳过格鲁德要塞荒原大门" },
    { "Gerudo's Fortress Warriors with Difficult Weapons", "用困难武器通过格鲁德要塞战士" },
    { "Stop Link the Goron with Din's Fire", "用丁火阻止林克格雷" },
    { "Crater's Bean PoH with Hover Boots", "用悬浮靴到达火山口魔豆 PoH" },
    { "Zora's River Lower Freestanding PoH as Adult with Nothing", "成人空手到达卓拉之河下层独立 PoH" },
    { "Zora's River Upper Freestanding PoH as Adult with Nothing", "成人空手到达卓拉之河上层独立 PoH" },
    { "Zora's Domain Entry with Hover Boots", "用悬浮靴进入卓拉领地" },
    { "Zora's Domain Entry with Cucco", "用鸡进入卓拉领地" },
    { "Zora's Domain GS with No Additional Items", "无额外道具获取卓拉领地金骷髅" },
    { "Zora's Fountain Great Fairy without Explosives", "无爆炸物到达卓拉之泉大精灵" },
    { "Fire Temple East Tower without Scarecrow's Song", "无需稻草人之歌通过火之神殿东塔" },
    { "Water Temple Central Pillar GS with Farore's Wind", "用法鲁风到达水之神殿中央柱金骷髅" },
    { "Ganon's Castle without Lens of Truth", "无需真实之镜通过盖侬城堡" },
    { "Ganon's Castle MQ without Lens of Truth", "无需真实之镜通过盖侬城堡 MQ" },
    
    // ---- Randomizer option descriptions (1/?) ----
    { "Determines if Kokiri forest can be left for the Lost Woods bridge or the Deku Tree.\n"
      "\n"
      "On - Kokiri Sword & Deku Shield are required to access "
      "the Deku Tree, and completing the Deku Tree is required to "
      "access the Lost Woods Bridge Exit.\n"
      "\n"
      "Deku Only - Kokiri boy no longer blocks the path to the Bridge "
      "but Mido still requires the Kokiri Sword and Deku Shield "
      "to access the tree.\n"
      "\n"
      "Off - Mido no longer blocks the path to the Deku Tree. Kokiri "
      "boy no longer blocks the path out of the forest.",
      "决定能否离开科克里森林前往迷失森林桥或德库树。\n"
      "\n"
      "开启 - 需要科克里之剑与德库盾才能进入德库树，且完成德库树才能\n"
      "进入迷失森林桥出口。\n"
      "\n"
      "仅德库 - 科克里男孩不再挡住通往桥的路，但米多仍需要科克里之剑\n"
      "与德库盾才能进入德库树。\n"
      "\n"
      "关闭 - 米多不再挡住通往德库树的路，科克里男孩也不再挡住\n"
      "离开森林的路。" },
    { "Closed - The gate will remain closed until Zelda's Letter "
      "is shown to the guard.\n"
      "\n"
      "Open - The gate is always open. The Happy Mask Shop "
      "will open immediately after obtaining Zelda's Letter.",
      "关闭 - 在向守卫出示塞尔达的信之前，大门保持关闭。\n"
      "\n"
      "开放 - 大门始终开放。获得塞尔达的信后，快乐面具店\n"
      "会立即开门。" },
    { "Closed - The Ocarina of Time, the Song of Time and all "
      "three Spiritual Stones are required to open the Door of Time.\n"
      "\n"
      "Song only - Play the Song of Time in front of the Door of "
      "Time to open it.\n"
      "\n"
      "Open - The Door of Time is permanently open with no requirements.",
      "关闭 - 需要时之陶笛、时间之歌以及全部三枚精神石才能\n"
      "打开时之门。\n"
      "\n"
      "仅歌曲 - 在时之门前演奏时间之歌即可打开。\n"
      "\n"
      "开放 - 时之门永久敞开，无任何条件。" },
    { "Closed - King Zora obstructs the way to Zora's Fountain. "
      "Ruto's Letter must be shown as child Link in order to move "
      "him in both time periods.\n"
      "\n"
      "Closed as child - Ruto's Letter is only required to move King Zora "
      "as child Link. Zora's Fountain starts open as adult.\n"
      "\n"
      "Open - King Zora has already mweeped out of the way in both "
      "time periods. Ruto's Letter is removed from the item pool.",
      "关闭 - 卓拉王挡住通往卓拉之泉的路。需以儿童林克出示\n"
      "茹特的信，才能在两个时期移动他。\n"
      "\n"
      "儿童时期关闭 - 仅需在儿童时期出示茹特的信移动卓拉王。\n"
      "成人时期卓拉之泉初始即为开放。\n"
      "\n"
      "开放 - 两个时期卓拉王都已让开道路。茹特的信从道具池移除。" },
    { "Closed - Sleeping Waterfall obstructs the entrance to Zora's "
      "Domain. Zelda's Lullaby must be played in order to open it "
      "(but only once; then it stays open in both time periods).\n"
      "\n"
      "Open - Sleeping Waterfall is always open. "
      "Link may always enter Zora's Domain.",
      "关闭 - 沉睡瀑布挡住卓拉领地的入口。需演奏塞尔达的摇篮曲\n"
      "才能打开（但只需一次；之后两个时期都保持开放）。\n"
      "\n"
      "开放 - 沉睡瀑布始终开放。林克可随时进入卓拉领地。" },
    { "Closed - A fish is required to open Jabu-Jabu's mouth.\n\n"
      "Open - Jabu-Jabu's mouth opens without the need for a fish.",
      "关闭 - 需要一条鱼才能打开加卜加卜之口。\n\n"
      "开放 - 无需鱼，加卜加卜之口自动打开。" },
    { "Add locks to all wooden overworld doors, requiring specific small keys to open them",
      "为所有地面世界的木门加上锁，需要特定的小钥匙才能打开" },
    { "Choose which age Link will start as.\n\n"
      "Starting as adult means you start with the Master Sword in your inventory.\n"
      "The child option is forcefully set if it would conflict with other options.",
      "选择林克起始的年龄。\n\n"
      "以成人开始意味着背包中初始携带大师之剑。\n"
      "若与其它选项冲突，则会强制设为儿童。" },
    { "Sets the state of the carpenters captured by Gerudo "
      "in Gerudo Fortress, and with it the number of guards that spawn.\n"
      "\n"
      "Normal - All 4 carpenters are required to be saved.\n"
      "\n"
      "Fast - Only the bottom left carpenter requires rescuing.\n"
      "\n"
      "Free - The bridge is repaired from the start, and Nabooru cannot spawn.\n"
      "If the Gerudo Membership Card isn't shuffled, you start with it.\n"
      "\n"
      "Only \"Normal\" is compatible with Gerudo Fortress Key Rings.",
      "设定被格鲁德俘虏的木匠状态，以及由此生成的守卫数量。\n"
      "\n"
      "普通 - 需要救出全部 4 名木匠。\n"
      "\n"
      "快速 - 只需救援左下角的木匠。\n"
      "\n"
      "自由 - 桥从一开始就已修复，娜薇（Nabooru）不会出现。\n"
      "若格鲁德会员卡未被洗牌，则初始即持有。\n"
      "\n"
      "只有\"普通\"与格鲁德要塞钥匙环兼容。" },
    { "Alters the requirements to open the bridge to Ganon's Castle.\n"
      "\n"
      "Vanilla - Obtain the Shadow Medallion, Spirit Medallion and Light Arrows.\n"
      "\n"
      "Always open - No requirements.\n"
      "\n"
      "Stones - Obtain the specified amount of Spiritual Stones.\n"
      "\n"
      "Medallions - Obtain the specified amount of medallions.\n"
      "\n"
      "Dungeon rewards - Obtain the specified total sum of Spiritual "
      "Stones or medallions.\n"
      "\n"
      "Dungeons - Complete the specified amount of dungeons. Dungeons "
      "are considered complete after stepping in to the blue warp after "
      "the boss.\n"
      "\n"
      "Tokens - Obtain the specified amount of Skulltula tokens.\n"
      "\n"
      "Greg - Find Greg the Green Rupee.",
      "改变打开通往盖侬城堡的桥所需的条件。\n"
      "\n"
      "原版 - 获得暗之徽章、灵之徽章与光之箭。\n"
      "\n"
      "始终开放 - 无要求。\n"
      "\n"
      "石 - 获得指定数量的精神石。\n"
      "\n"
      "徽章 - 获得指定数量的徽章。\n"
      "\n"
      "地牢奖励 - 获得指定总数的精神石或徽章。\n"
      "\n"
      "地牢 - 完成指定数量的地牢。在 Boss 后踏入蓝色传送点\n"
      "即视为完成。\n"
      "\n"
      "令牌 - 获得指定数量的骷髅令牌。\n"
      "\n"
      "格雷格 - 找到绿色卢比格雷格。" },
    { "Standard Rewards - Greg does not change logic, Greg does not help open the bridge, max "
      "number of rewards on slider does not change.\n"
      "\n"
      "Greg as Reward - Greg does change logic (can be part of expected path for opening "
      "bridge), Greg helps open bridge, max number of rewards on slider increases by 1 to "
      "account for Greg. \n"
      "\n"
      "Greg as Wildcard - Greg does not change logic, Greg helps open the bridge, max number of "
      "rewards on slider does not change.",
      "标准奖励 - 格雷格不改变逻辑，格雷格不帮助开启桥，滑块上的\n"
      "最大奖励数量不变。\n"
      "\n"
      "格雷格作为奖励 - 格雷格会改变逻辑（可能是开启桥的预期路径之一），\n"
      "格雷格帮助开启桥，滑块最大奖励数量加 1 以计入格雷格。\n"
      "\n"
      "格雷格作为万能替换 - 格雷格不改变逻辑，但帮助开启桥，\n"
      "滑块最大奖励数量不变。" },
    { "Sets the number of Ganon's Trials required to dispel the barrier.\n"
      "\n"
      "Skip - No Trials are required and the barrier is already dispelled.\n"
      "\n"
      "Set Number - Select a number of trials that will be required from the "
      "slider below. Which specific trials you need to complete will be random.\n"
      "\n"
      "Random Number - A random number and set of trials will be required.",
      "设定驱散屏障所需的盖侬试炼数量。\n"
      "\n"
      "跳过 - 无需试炼，屏障已解除。\n"
      "\n"
      "设定数量 - 从下方滑块选择所需的试炼数量。具体需要完成\n"
      "哪些试炼将是随机的。\n"
      "\n"
      "随机数量 - 需要随机数量与组合的试炼。" },
    { "Set the number of trials required to enter Ganon's Tower.",
      "设定进入盖侬塔所需的试炼数量。" },
    { "Doors to trials will be barred until their corresponding medallion is acquired.",
      "在获得相应徽章之前，试炼之门保持封闭。" },
    { "Sets the number of Master Quest Dungeons that are shuffled into the pool.\n"
      "\n"
      "None - All Dungeons will be their Vanilla versions.\n"
      "\n"
      "Set Number - Select a number of dungeons that will be their Master Quest versions "
      "using the slider below. Which dungeons are set to be the Master Quest variety will be random.\n"
      "\n"
      "Random Number - A random number and set of dungeons will be their Master Quest varieties.\n"
      "\n"
      "Selection Only - Specify which dungeons are Vanilla, Master Quest or a 50/50 between the two.\n"
      "Differs from Random Number in that they are rolled individually, making the exact total a bell curve.",
      "设定被洗牌进入池中的大师任务地牢数量。\n"
      "\n"
      "无 - 所有地牢均为原版版本。\n"
      "\n"
      "设定数量 - 用下方滑块选择成为大师任务版本的地牢数量。\n"
      "具体哪些地牢为大师任务版本将是随机的。\n"
      "\n"
      "随机数量 - 随机数量与组合的地牢为大师任务版本。\n"
      "\n"
      "仅选择 - 指定哪些地牢是原版、大师任务，或两者五五开。\n"
      "与随机数量不同，它们各自独立判定，使总数呈钟形曲线。" },
    { "Choose specific Dungeons to be Master Quest or Vanilla.\n"
      "\n"
      "If Master Quest Dungeons is set to Set Number or Random, the dungeons chosen "
      "to be Master Quest here will count towards that total. Any Dungeons set to Vanilla "
      "here will be guaranteed to be Vanilla. If Set Number is higher than the amount of dungeons "
      "set to either MQ or Random here, you will have fewer MQ Dungeons than the number you "
      "set.",
      "选择特定地牢为大师任务或原版。\n"
      "\n"
      "若\"大师任务地牢\"设为设定数量或随机，则此处选为大师任务的\n"
      "地牢将计入该总数。此处设为原版的地牢保证为原版。若设定数量\n"
      "高于此处设为 MQ 或随机的地牢数量，则实际 MQ 地牢数量将少于你所设的数值。" },

    // ---- Randomizer option descriptions (2/?) ----
    { "Pieces of the Triforce of Courage have been scattered across the world. Find them all to finish the game!\n"
      "\n"
      "If set to Win: the game is saved and the credits roll, though you can load back in to receive Ganon's "
      "Castle Boss Key. Keep in mind that Ganon might not be logically reachable when \"All Locations Reachable\" "
      "is disabled.",
      "勇气三角力量的碎片已散落世界各地。找齐它们即可通关！\n"
      "\n"
      "若设为胜利：游戏会存档并播放制作人员名单，但你可重新载入以\n"
      "获得盖侬城堡的 Boss 钥匙。注意当\"所有地点可达\"关闭时，\n"
      "盖侬可能在逻辑上无法到达。" },
    { "The amount of Triforce pieces that will be placed in the world. "
      "Keep in mind seed generation can fail if more pieces are placed than there are junk items in the item pool.",
      "将放置于世界中的三角力量碎片数量。注意若放置的碎片数量\n"
      "超过道具池中的垃圾道具数量，种子生成可能失败。" },
    { "The amount of Triforce pieces required to win the game.",
      "通关游戏所需的三角力量碎片数量。" },
    { "Shuffle the pool of dungeon entrances, including Bottom of the Well, Ice Cavern and Gerudo Training Ground.\n"
      "\n"
      "Shuffling Ganon's Castle can be enabled separately.\n"
      "\n"
      "Additionally, the entrances of Deku Tree, Fire Temple, Bottom of the Well and Gerudo Training Ground are "
      "opened for both child and adult.\n"
      "\n"
      "- Deku Tree will be open for adult after Mido has seen child Link with a sword and a shield.\n"
      "- Bottom of the Well will be open for adult after playing Song of Storms to the Windmill guy as child.\n"
      "- Gerudo Training Ground will be open for child after adult has paid to open the gate once.",
      "洗牌地牢入口池，包括井底、冰之洞窟与格鲁德训练场。\n"
      "\n"
      "盖侬城堡的洗牌可单独开启。\n"
      "\n"
      "此外，德库树、火之神殿、井底与格鲁德训练场的入口\n"
      "对儿童和成人都开放。\n"
      "\n"
      "- 儿童林克持剑与盾被米多见过后，德库树对成人开放。\n"
      "- 儿童向风车老人演奏风暴之歌后，井底对成人开放。\n"
      "- 成人付费开过一次门后，格鲁德训练场对儿童开放。" },
    { "Shuffle the pool of dungeon boss entrances. This affects the boss rooms of all stone and medallion dungeons.\n"
      "\n"
      "Age Restricted - Shuffle the entrances of child and adult boss rooms separately.\n"
      "\n"
      "Full - Shuffle the entrances of all boss rooms together. Child may be expected to defeat Phantom Ganon and/or "
      "Bongo Bongo.",
      "洗牌地牢 Boss 入口池。这影响所有石之与徽章地牢的 Boss 房间。\n"
      "\n"
      "年龄限制 - 儿童与成人 Boss 房间入口分别洗牌。\n"
      "\n"
      "完整 - 所有 Boss 房间入口一起洗牌。可能要求儿童击败幻影盖侬和/或\n"
      "邦哥邦哥。" },
    { "Shuffle the entrance from Ganon's Castle to Ganon's Tower into the pool of boss entrances.",
      "将盖侬城堡到盖侬塔的入口洗入 Boss 入口池。" },
    { "Shuffle the pool of Overworld entrances, which corresponds to almost all loading zones between overworld "
      "areas.\n"
      "\n"
      "Some entrances are unshuffled to avoid issues:\n"
      "- Hyrule Castle Courtyard and Garden entrance\n"
      "- Both Market Back Alley entrances\n"
      "- Gerudo Valley to Lake Hylia (unless entrances are decoupled)",
      "洗牌地面世界入口池，对应地面世界各区域间几乎所有载入点。\n"
      "\n"
      "为避免问题，部分入口不参与洗牌：\n"
      "- 海拉鲁城堡庭院与花园入口\n"
      "- 市场后巷的两个入口\n"
      "- 格鲁德大峡谷到海拉鲁湖（除非入口解耦）" },
    { "Shuffle the pool of interior entrances which contains most Houses and all Great Fairies.\n"
      "\n"
      "All - An extended version of 'Simple' with some extra places:\n"
      "- Windmill\n"
      "- Link's House\n"
      "- Temple of Time\n"
      "- Kakariko Potion Shop",
      "洗牌室内入口池，包含大多数房屋与所有大精灵。\n"
      "\n"
      "全部 - \"简单\"的扩展版，含额外地点：\n"
      "- 风车\n"
      "- 林克之家\n"
      "- 时之殿\n"
      "- 卡卡利科药水店" },
    { "Shuffle the pool of entrances between Gerudo Fortress & Thieves' Hideout.",
      "洗牌格鲁德要塞与盗贼藏身处之间的入口池。" },
    { "Shuffle the pool of grotto entrances, including all graves, small Fairy fountains and the Deku Theatre.",
      "洗牌洞穴入口池，包括所有墓穴、小型精灵泉与德库剧场。" },
    { "Randomize where Kaepora Gaebora (the Owl) drops you at when you talk "
      "to him at Lake Hylia or at the top of Death Mountain Trail.",
      "随机化卡波拉·盖波拉（猫头鹰）在湖之祝福或死神山径顶端\n"
      "与你对话后把你放下的地点。" },
    { "Randomize where each of the 6 warp songs leads to.",
      "随机化 6 首传送歌曲各自的目的地。" },
    { "Randomize where you start as Child or Adult when loading a save in the Overworld. This "
      "means you may not necessarily spawn inside Link's House or Temple of Time.\n"
      "\n"
      "This stays consistent after saving and loading the game again.\n"
      "\n"
      "Keep in mind you may need to temporarily disable the \"Remember Save Location\" time saver to "
      "be able use the spawn positions, especially if they are the only logical way to get to certain areas.",
      "随机化在地面世界载入存档时儿童或成人的初始位置。这意味着你\n"
      "不一定在林克之家或时之殿出生。\n"
      "\n"
      "保存并再次载入游戏后，该位置保持一致。\n"
      "\n"
      "注意你可能需要暂时关闭\"记住存档位置\"这一省时功能才能使用\n"
      "这些出生点，尤其是当它们是到达某些区域的唯一逻辑路径时。" },
    { "Decouple entrances when shuffling them. This means you are no longer guaranteed "
      "to end up back where you came from when you go back through an entrance.\n"
      "\n"
      "This also adds the one-way entrance from Gerudo Valley to Lake Hylia in the pool of "
      "overworld entrances when they are shuffled.",
      "洗牌入口时解耦它们。这意味着你从入口返回时不再保证\n"
      "回到原处。\n"
      "\n"
      "这还会在地面世界入口被洗牌时，把格鲁德大峡谷到海拉鲁湖的\n"
      "单向入口加入池中。" },
    { "Shuffle entrances into a mixed pool instead of separate ones. Has no effect on pools whose "
      "entrances aren't shuffled, and \"Shuffle Boss Entrances\" must be set to \"Full\" to include them.\n"
      "\n"
      "For example, enabling the settings to shuffle grotto, dungeon, and overworld entrances and "
      "selecting grotto and dungeon entrances here will allow a dungeon to be inside a grotto or "
      "vice versa, while overworld entrances are shuffled in their own separate pool and indoors stay vanilla.",
      "将入口洗入混合池而非分立池。对未洗牌的入口池无效，且\n"
      "需将\"洗牌 Boss 入口\"设为\"完整\"才会包含它们。\n"
      "\n"
      "例如，开启洞穴、地牢、地面世界入口洗牌并在此选择洞穴与地牢入口，\n"
      "将允许地牢位于洞穴内或反之，而地面世界入口在各自独立池中洗牌，室内保持原版。" },
    { "Dungeon entrances will be part of the mixed pool.",
      "地牢入口将成为混合池的一部分。" },
    { "Boss entrances will be part of the mixed pool.",
      "Boss 入口将成为混合池的一部分。" },
    { "Overworld entrances will be part of the mixed pool.",
      "地面世界入口将成为混合池的一部分。" },
    { "Interior entrances will be part of the mixed pool.",
      "室内入口将成为混合池的一部分。" },
    { "Grotto entrances will be part of the mixed pool.",
      "洞穴入口将成为混合池的一部分。" },
    { "Off - Songs will appear at their vanilla locations.\n"
      "\n"
      "Song locations - Songs will only appear at locations that normally teach songs.\n"
      "\n"
      "Dungeon rewards - Songs appear after beating a major dungeon boss.\n"
      "The 4 remaining songs are located at:\n"
      "  - Zelda's Lullaby location\n"
      "  - Ice Cavern's Serenade of Water location\n"
      "  - Bottom of the Well Lens of Truth location\n"
      "  - Gerudo Training Ground's Ice Arrows location\n"
      "\n"
      "Anywhere - Songs can appear at any location.",
      "关闭 - 歌曲出现在原版位置。\n"
      "\n"
      "歌曲地点 - 歌曲只出现在通常教授歌曲的地点。\n"
      "\n"
      "地牢奖励 - 歌曲在击败主要地牢 Boss 后出现。其余 4 首位于：\n"
      "  - 塞尔达的摇篮曲位置\n"
      "  - 冰之洞窟水之小夜曲位置\n"
      "  - 井底真实之镜位置\n"
      "  - 格鲁德训练场冰之箭位置\n"
      "\n"
      "任意地点 - 歌曲可出现在任何位置。" },
    { "Shuffles Golden Skulltula Tokens into the item pool. This means "
      "Golden Skulltulas can contain other items as well.\n"
      "\n"
      "Off - GS tokens will not be shuffled.\n"
      "\n"
      "Dungeons - Only shuffle GS tokens that are within dungeons.\n"
      "\n"
      "Overworld - Only shuffle GS tokens that are outside of dungeons.\n"
      "\n"
      "All Tokens - Shuffle all 100 GS tokens.",
      "将金色骷髅令牌洗入道具池。这意味着金色骷髅也可能包含其它道具。\n"
      "\n"
      "关闭 - 金骷髅令牌不被洗牌。\n"
      "\n"
      "地牢 - 仅洗牌地牢内的金骷髅令牌。\n"
      "\n"
      "地面世界 - 仅洗牌地牢外的金骷髅令牌。\n"
      "\n"
      "所有令牌 - 洗牌全部 100 枚金骷髅令牌。" },
    { "All Golden Skulltulas that require nighttime to appear will only be "
      "expected to be collected after getting Sun's Song.",
      "所有需要夜晚才会出现的金色骷髅，都预期在获得太阳之歌后\n"
      "才能被收集。" },
    { "Shuffles the Kokiri Sword into the item pool.\n"
      "\n"
      "This will require the use of sticks until the Kokiri Sword is found.",
      "将科克里之剑洗入道具池。\n"
      "\n"
      "在找到科克里之剑之前，需使用木棒战斗。" },
    { "Shuffles the Master Sword into the item pool.\n"
      "\n"
      "Adult Link will start with a second free item instead of the Master Sword.\n"
      "If you haven't found the Master Sword before facing Ganon, you won't receive it during the fight.",
      "将大师之剑洗入道具池。\n"
      "\n"
      "成人林克将以第二件免费道具起始，而非大师之剑。\n"
      "若在面对盖侬前未找到大师之剑，战斗中也不会获得它。" },
    { "Enabling this shuffles the Child's Wallet into the item pool.\n"
      "\n"
      "You will not be able to carry any rupees until you find a wallet.",
      "开启此选项会将儿童钱包洗入道具池。\n"
      "\n"
      "在找到钱包之前，你将无法携带任何卢比。" },
    { "Enabling this adds an extra Progressive Wallet to the pool and "
      "adds a new 999 capacity tier after Giant's Wallet.\n",
      "开启此选项会向池中加入一个额外进阶钱包，并在巨人钱包之后\n"
      "新增 999 容量的层级。\n" },
    { "Enabling this shuffles the Fairy Ocarina and the Ocarina of Time into the item pool.\n"
      "\n"
      "This will require finding an Ocarina before being able to play songs.",
      "开启此选项会将精灵陶笛与时之陶笛洗入道具池。\n"
      "\n"
      "在找到陶笛之前，将无法演奏歌曲。" },
    { "Enabling this shuffles the Ocarina buttons into the item pool.\n"
      "\n"
      "This will require finding the buttons before being able to use them in songs.",
      "开启此选项会将陶笛按钮洗入道具池。\n"
      "\n"
      "在找到按钮之前，无法在歌曲中使用它们。" },
    { "Shuffles the ability to Swim into the item pool as a progressive upgrade before Silver Scale.\n"
      "The ability to swim has to be found as an item (you can still be underwater with iron boots).\n"
      "\n"
      "If you enter a water entrance without swim you will be respawned on land to prevent infinite death loops.\n"
      "If you void out in Water Temple you will immediately be kicked out to prevent a softlock.",
      "将游泳能力作为银鳞片之前的进阶升级洗入道具池。\n"
      "游泳能力需作为道具找到（穿铁靴仍可潜水）。\n"
      "\n"
      "若无游泳能力而进入水边入口，你会被传送回陆地以防无限死亡循环。\n"
      "若在水源神殿坠空，会立即被踢出以防卡死。" },
    { "Shuffle the ability to grab as a progressive upgrade before Goron Bracelet.",
      "将抓取能力作为格雷手镯之前的进阶升级洗入道具池。" },
    { "Shuffle the ability to climb ladders into the item pool.",
      "将爬梯能力洗入道具池。" },
    { "Shuffles the ability to use crawlspaces into the item pool.",
      "将使用爬行空间的能力洗入道具池。" },
    { "Shuffle ability to speak to NPCs. 6 jabbernuts will be shuffled:\nDeku, Gerudo, Goron, Hylian, Kokiri, "
      "Zora\nKaepora Gaebora speaks any language.",
      "洗牌与 NPC 对话的能力。将洗牌 6 颗喋喋坚果：\n德库、格鲁德、格雷、海拉鲁、科克里、\n卓拉\n卡波拉·盖波拉会说任何语言。" },

    // ---- Randomizer option descriptions (3/?) ----
    { "Shuffles the ability to open chests into the item pool.",
      "将开宝箱能力洗入道具池。" },
    { "Shuffles the Weird Egg from Malon in to the item pool. Enabling "
      "\"Skip Child Zelda\" disables this feature.\n"
      "\n"
      "The Weird Egg is required to unlock several events:\n"
      "  - Zelda's Lullaby from Impa\n"
      "  - Saria's Song in Sacred Forest Meadow\n"
      "  - Epona's Song and chicken minigame at Lon Lon Ranch\n"
      "  - Zelda's Letter for Kakariko gate (if set to closed)\n"
      "  - Happy Mask Shop sidequest\n",
      "将玛隆的奇怪的蛋洗入道具池。开启\"跳过儿童塞尔达\"会\n"
      "禁用此功能。\n"
      "\n"
      "奇怪的蛋是解锁以下事件所必需的：\n"
      "  - 英帕给予塞尔达的摇篮曲\n"
      "  - 神圣森林草甸的萨莉亚之歌\n"
      "  - 隆隆牧场的伊波纳之歌与养鸡小游戏\n"
      "  - 卡卡利科大门的塞尔达的信（若设为关闭）\n"
      "  - 快乐面具店支线\n" },
    { "Shuffles the Gerudo Membership Card into the item pool.\n"
      "\n"
      "The Gerudo Card is required to enter the Gerudo Training Ground, opening "
      "the gate to Haunted Wasteland and the Horseback Archery minigame.",
      "将格鲁德会员卡洗入道具池。\n"
      "\n"
      "进入格鲁德训练场需要格鲁德会员卡，它还会打开通往\n"
      "幻影沙漠与马背射箭小游戏的大门。" },
    { "Pots will drop a randomized item the first time they're broken and collected. This does not include the "
      "flying pots."
      " Pots will have a different appearance when they hold a randomized item.\n"
      "With this option enabled, Ganon's boss key door is moved further up the stairs to\n"
      "allow access to the pots before obtaining Ganon's Boss Key.\n"
      "\n"
      "Off - Pots will not be shuffled.\n"
      "\n"
      "Dungeons - Only shuffle pots that are within dungeons.\n"
      "\n"
      "Overworld - Only shuffle pots that are outside of dungeons.\n"
      "\n"
      "All pots - Shuffle all pots.",
      "陶罐首次被打破并拾取时会掉落随机道具。飞行陶罐不包括在内。"
      "持有随机道具的陶罐外观会不同。\n"
      "开启此选项后，盖侬的 Boss 钥匙门会被移向楼梯更上方，以便在\n"
      "获得盖侬 Boss 钥匙前即可访问这些陶罐。\n"
      "\n"
      "关闭 - 陶罐不被洗牌。\n"
      "\n"
      "地牢 - 仅洗牌地牢内的陶罐。\n"
      "\n"
      "地面世界 - 仅洗牌地牢外的陶罐。\n"
      "\n"
      "所有陶罐 - 洗牌全部陶罐。" },
    { "Crates will drop a randomized item the first time they're broken and collected. "
      "Crates will have a different appearance when they hold a randomized item.\n"
      "\n"
      "Off - Crates will not be shuffled.\n"
      "\n"
      "Dungeons - Only shuffle crates that are within dungeons.\n"
      "\n"
      "Overworld - Only shuffle crates that are outside of dungeons.\n"
      "\n"
      "All Crates - Shuffle all crates.",
      "木箱首次被打破并拾取时会掉落随机道具。持有随机道具的\n"
      "木箱外观会不同。\n"
      "\n"
      "关闭 - 木箱不被洗牌。\n"
      "\n"
      "地牢 - 仅洗牌地牢内的木箱。\n"
      "\n"
      "地面世界 - 仅洗牌地牢外的木箱。\n"
      "\n"
      "所有木箱 - 洗牌全部木箱。" },
    { "Trees will contain randomized items which are dropped the first time the player rolls into one.\n"
      "Trees will have a special appearance when carrying randomized items.\n"
      "\nSome trees are dependant on Link's age, such as some trees in Hyrule Field.\nTwo trees at Hyrule Castle are "
      "only shuffle with No Logic.",
      "树木会在玩家首次撞入时掉落随机道具。携带随机道具的\n"
      "树木会有特殊外观。\n"
      "\n部分树木依赖林克的年龄，例如海拉鲁平原的一些树。\n"
      "海拉鲁城堡的两棵树仅在\"无逻辑\"下被洗牌。" },
    { "Bushes in Hyrule Field & Zora's Fountain will contain randomized items when first walked through.",
      "海拉鲁平原与卓拉之泉的灌木丛在首次穿过时会包含随机道具。" },
    { "Shuffles the fishing pole into the item pool.\n"
      "\n"
      "The fishing pole is required to play the fishing pond minigame.",
      "将钓竿洗入道具池。\n"
      "\n"
      "游玩钓鱼池小游戏需要钓竿。" },
    { "Adds upgrades that hold infinite quantities of items (bombs, arrows, etc.).\n"
      "\n"
      "Progressive - The infinite upgrades are obtained after getting the last normal capacity upgrade.\n"
      "\n"
      "Condensed Progressive - The infinite upgrades are obtained as the first capacity upgrade (doesn't apply to "
      "the infinite wallet or to infinite magic).",
      "新增可持有无限数量道具的升级（炸弹、箭等）。\n"
      "\n"
      "进阶 - 在获得最后一个普通容量升级后获得无限升级。\n"
      "\n"
      "精简进阶 - 作为第一个容量升级获得无限升级（不适用于\n"
      "无限钱包或无限魔法）。" },
    { "Shuffles the Deku Stick bag into the item pool.\n"
      "\n"
      "The Deku Stick bag is required to hold Deku Sticks.",
      "将德库木棒袋洗入道具池。\n"
      "\n"
      "持有德库木棒需要德库木棒袋。" },
    { "Shuffles the Deku Nut bag into the item pool.\n"
      "\n"
      "The Deku Nut bag is required to hold Deku Nuts.",
      "将德库坚果袋洗入道具池。\n"
      "\n"
      "持有德库坚果需要德库坚果袋。" },
    { "Off - All shop items will be the same as vanilla.\n"
      "\n"
      "Specific Count - Vanilla shop items will be shuffled among different shops, and "
      "each shop will contain a specific number (0-7) of non-vanilla shop items.\n"
      "\n"
      "Random - Vanilla shop items will be shuffled among different shops, and "
      "each shop will contain a random number (1-7) of non-vanilla shop items.",
      "关闭 - 所有商店道具与原版相同。\n"
      "\n"
      "指定数量 - 原版商店道具将在不同商店间洗牌，且每个商店\n"
      "会包含指定数量（0-7）的非原版商店道具。\n"
      "\n"
      "随机 - 原版商店道具将在不同商店间洗牌，且每个商店\n"
      "会包含随机数量（1-7）的非原版商店道具。" },
    { "0 Items - Vanilla shop items will be shuffled among different shops.\n"
      "\n"
      "1-7 Items - Vanilla shop items will be shuffled among different shops, and "
      "each shop will contain 1-7 non-vanilla shop items.\n",
      "0 件 - 原版商店道具将在不同商店间洗牌。\n"
      "\n"
      "1-7 件 - 原版商店道具将在不同商店间洗牌，且每个商店\n"
      "会包含 1-7 件非原版商店道具。\n" },
    { "Vanilla - The same price as the item it replaced.\n"
      "Cheap Balanced - Prices will range between 0 to 95 rupees, favoring lower numbers.\n"
      "Balanced - Prices will range between 0 to 300 rupees, favoring lower numbers.\n"
      "Fixed - A fixed number.\n"
      "Range - A random point between specific ranges.\n"
      "Set By Wallet - Set weights that decide the choice of each wallet, and get a random price in that range if "
      "that wallet is chosen.",
      "原版 - 与被替换道具价格相同。\n"
      "廉价均衡 - 价格在 0 至 95 卢比之间，偏向较低数值。\n"
      "均衡 - 价格在 0 至 300 卢比之间，偏向较低数值。\n"
      "固定 - 固定数值。\n"
      "范围 - 指定范围内的随机值。\n"
      "由钱包设定 - 设定权重决定各钱包的选择，若该钱包被选中则在该范围内取随机价格。" },
    { "The price for Shopsanity checks.",
      "商店洗牌检查的价格。" },
    { "The first part of the inclusive range of prices to allow for Shopsanity checks.",
      "商店洗牌检查所允许的价格范围（含端点）的第一部分。" },
    { "The second part of the inclusive range of prices to allow for Shopsanity checks.",
      "商店洗牌检查所允许的价格范围（含端点）的第二部分。" },
    { "The chance for Shopsanity checks to be free.",
      "商店洗牌检查免费的概率。" },
    { "The chance for Shopsanity checks to be purchasable with Child's Wallet (1-99).",
      "商店洗牌检查可用儿童钱包（1-99）购买的概率。" },
    { "The chance for Shopsanity checks to be purchasable with Adult's Wallet (100-200).",
      "商店洗牌检查可用成人钱包（100-200）购买的概率。" },
    { "The chance for Shopsanity checks to be purchasable with Giant's Wallet (201-500).",
      "商店洗牌检查可用巨人钱包（201-500）购买的概率。" },
    { "The chance for Shopsanity checks to be purchasable with Tycoon Wallet (500+).",
      "商店洗牌检查可用大亨钱包（500+）购买的概率。" },
    { "After choosing a price, set it to the affordable amount based on the wallet required.\n\n"
      "Affordable prices per tier: starter = 1, adult = 100, giant = 201, tycoon = 501\n\n"
      "Use this to enable wallet tier locking, but make shop items not as expensive as they could be.",
      "选定价格后，根据所需钱包设为可负担金额。\n\n"
      "各层级可负担价格：起始 = 1，成人 = 100，巨人 = 201，大亨 = 501\n\n"
      "用于启用钱包层级锁定，但让商店道具不至于过于昂贵。" },
    { "Off - Fish will not be shuffled. No changes will be made to fishing behavior.\n\n"
      "Shuffle only Hyrule Loach - Allows you to earn an item by catching the Hyrule Loach at the fishing pond and "
      "giving it to the owner.\n\n"
      "Shuffle Fishing Pond - The fishing pond's fish will be shuffled. Catching a fish in the fishing pond will "
      "grant a reward.\n\n"
      "Shuffle Overworld Fish - Fish in generic grottos and Zora's Domain will be shuffled. Catching a fish in a "
      "bottle will give a reward.\n\n"
      "Shuffle Both - Both overworld fish and fish in the fishing pond will be shuffled.",
      "关闭 - 鱼不被洗牌，钓鱼行为不变。\n\n"
      "仅洗牌海拉鲁泥鳅 - 在钓鱼池捕获海拉鲁泥鳅并交给店主可获得道具。\n\n"
      "洗牌钓鱼池 - 钓鱼池的鱼会被洗牌。在钓鱼池捕到鱼会给予奖励。\n\n"
      "洗牌地面世界鱼 - 普通洞穴与卓拉领地的鱼会被洗牌。在瓶中捕到鱼会给予奖励。\n\n"
      "两者都洗牌 - 地面世界鱼与钓鱼池的鱼都会被洗牌。" },
    { "The number of fish to randomize in the fishing pool.\n\n"
      "If set to maximum, each fish will have a unique check, including a Hyrule Loach which appears only as child, "
      "and "
      "uncaught fish will be given a visual indicator to distinguish from already-caught fish.\n\n"
      "Otherwise, any fish caught in the pond will give a reward, until all rewards have been given.",
      "钓鱼池中要随机化的鱼的数量。\n\n"
      "若设为最大，每条鱼都有独立检查点，包括仅儿童出现的海拉鲁泥鳅，\n"
      "且未捕获的鱼会有视觉标识以区别于已捕获的鱼。\n\n"
      "否则，在钓鱼池捕获任意鱼都会给予奖励，直到所有奖励发放完毕。" },
    { "Enabling this will split the fishing pond fish by age, making fishing pond fish grant different rewards as "
      "child and adult.\n\n"
      "If disabled, then the child pond will be shuffled and shared between both ages.\n\n"
      "Note that, as child, there is a second loach available in the pond!",
      "开启此选项会按年龄分离钓鱼池的鱼，使钓鱼池的鱼在儿童与成人时\n"
      "给予不同奖励。\n\n"
      "若关闭，则儿童池塘会被洗牌并在两个年龄间共享。\n\n"
      "注意：作为儿童时，池塘中还有第二条泥鳅！" },

    // ---- Randomizer option descriptions (4/?) ----
    { "Off - Scrubs will not be shuffled. The 3 Scrubs that give one-time items in the "
      "vanilla game (PoH, Deku Nut capacity, and Deku Stick capacity) will not spawn."
      "\n"
      "One-Time Only - Only the 3 Scrubs that give one-time items in the "
      "vanilla game are shuffled.\n"
      "\n"
      "All - All Scrubs are shuffled.",
      "关闭 - 商人（Scrub）不被洗牌。原版游戏中给予一次性道具的\n"
      "3 个 Scrub（PoH、德库坚果容量、德库木棒容量）不会出现。"
      "\n"
      "仅一次 - 仅原版游戏中给予一次性道具的 3 个 Scrub 被洗牌。\n"
      "\n"
      "全部 - 所有 Scrub 都被洗牌。" },
    { "Vanilla - The same price as the item it replaced.\n"
      "Cheap Balanced - Prices will range between 0 to 95 rupees, favoring lower numbers.\n"
      "Balanced - Prices will range between 0 to 300 rupees, favoring lower numbers.\n"
      "Fixed - A fixed number.\n"
      "Range - A random point between specific ranges.\n"
      "Set By Wallet - Set weights that decide the choice of each wallet, and get a random price in that range if "
      "that wallet is chosen.",
      "原版 - 与被替换道具价格相同。\n"
      "廉价均衡 - 价格在 0 至 95 卢比之间，偏向较低数值。\n"
      "均衡 - 价格在 0 至 300 卢比之间，偏向较低数值。\n"
      "固定 - 固定数值。\n"
      "范围 - 指定范围内的随机值。\n"
      "由钱包设定 - 设定权重决定各钱包的选择，若该钱包被选中则在该范围内取随机价格。" },
    { "The price for Scrub checks.",
      "Scrub 检查的价格。" },
    { "The first part of the inclusive range of prices to allow for Scrub checks.",
      "Scrub 检查所允许的价格范围（含端点）的第一部分。" },
    { "The second part of the inclusive range of prices to allow for Scrub checks.",
      "Scrub 检查所允许的价格范围（含端点）的第二部分。" },
    { "The chance for Scrub checks to be free.",
      "Scrub 检查免费的概率。" },
    { "The chance for Scrub checks to be purchasable with Child's Wallet (1-99).",
      "Scrub 检查可用儿童钱包（1-99）购买的概率。" },
    { "The chance for Scrub checks to be purchasable with Adult's Wallet (100-200).",
      "Scrub 检查可用成人钱包（100-200）购买的概率。" },
    { "The chance for Scrub checks to be purchasable with Giant's Wallet (201-500).",
      "Scrub 检查可用巨人钱包（201-500）购买的概率。" },
    { "The chance for Scrub checks to be purchasable with Tycoon Wallet (500+).",
      "Scrub 检查可用大亨钱包（500+）购买的概率。" },
    { "After choosing a price, set it to the affordable amount based on the wallet required.\n\n"
      "Affordable prices per tier: starter = 1, adult = 100, giant = 201, tycoon = 501\n\n"
      "Use this to enable wallet tier locking, but make scrub items not as expensive as they could be.",
      "选定价格后，根据所需钱包设为可负担金额。\n\n"
      "各层级可负担价格：起始 = 1，成人 = 100，巨人 = 201，大亨 = 501\n\n"
      "用于启用钱包层级锁定，但让 Scrub 道具不至于过于昂贵。" },
    { "Beehives give a randomized item from the pool when broken.",
      "蜂巢被打破时会从池中掉落随机道具。" },
    { "Cows give a randomized item from the pool upon performing Epona's Song in front of them.",
      "在牛面前演奏伊波纳之歌时，牛会从池中给予随机道具。" },
    { "This setting governs if the Bean Salesman, Medigoron, Granny and the Carpet Salesman "
      "sell a random item.\n"
      "Beans Only - Only the Bean Salesman will have a check, and a pack of Magic Beans will be added "
      "to the item pool.\n"
      "All But Beans - Medigoron, Granny and the Carpet Salesman will have checks, "
      "A Giant's Knife and a pack of Bombchus will be added to the item pool, and "
      "one of the bottles will contain a Blue Potion.\n"
      "All - Apply both effects.\n"
      "\n"
      "Granny's item will only be offered after you have traded in the Odd Mushroom when Shuffle Adult Trade is on. "
      "Otherwise when off, you will need to have found the Claim Check to buy her item (simulating the trade quest "
      "is complete).",
      "此设置决定魔豆商人、梅迪戈隆、老奶奶与地毯商人是否出售随机道具。\n"
      "仅魔豆 - 只有魔豆商人会有检查点，且一包魔法魔豆会加入道具池。\n"
      "除魔豆外全部 - 梅迪戈隆、老奶奶与地毯商人会有检查点，一把\n"
      "巨人刀与一包炸弹鼠会加入道具池，且其中一个瓶子会装有蓝色药水。\n"
      "全部 - 同时应用两种效果。\n"
      "\n"
      "当\"洗牌成人交易\"开启时，老奶奶的道具只有在你交付奇异蘑菇后才会提供。"
      "否则（关闭时），你需要找到领取凭证才能购买她的道具（模拟交易任务完成）。" },
    { "Vanilla - The same price as the Check in vanilla, 60 for the Bean Salesman.\n"
      "Cheap Balanced - Prices will range between 0 to 95 rupees, favoring lower numbers.\n"
      "Balanced - Prices will range between 0 to 300 rupees, favoring lower numbers.\n"
      "Fixed - A fixed number.\n"
      "Range - A random point between specific ranges.\n"
      "Set By Wallet - Set weights that decide the choice of each wallet, and get a random price in that range if "
      "that wallet is chosen.",
      "原版 - 与原版检查点价格相同，魔豆商人为 60。\n"
      "廉价均衡 - 价格在 0 至 95 卢比之间，偏向较低数值。\n"
      "均衡 - 价格在 0 至 300 卢比之间，偏向较低数值。\n"
      "固定 - 固定数值。\n"
      "范围 - 指定范围内的随机值。\n"
      "由钱包设定 - 设定权重决定各钱包的选择，若该钱包被选中则在该范围内取随机价格。" },
    { "The price for Merchant checks.",
      "商人检查的价格。" },
    { "The first part of the inclusive range of prices to allow for Merchant checks.",
      "商人检查所允许的价格范围（含端点）的第一部分。" },
    { "The second part of the inclusive range of prices to allow for Merchant checks.",
      "商人检查所允许的价格范围（含端点）的第二部分。" },
    { "The chance for Merchant checks to be free.",
      "商人检查免费的概率。" },
    { "The chance for Merchant checks to be purchasable with Child's Wallet (1-99).",
      "商人检查可用儿童钱包（1-99）购买的概率。" },
    { "The chance for Merchant checks to be purchasable with Adult's Wallet (100-200).",
      "商人检查可用成人钱包（100-200）购买的概率。" },
    { "The chance for Merchant checks to be purchasable with Giant's Wallet (201-500).",
      "商人检查可用巨人钱包（201-500）购买的概率。" },
    { "The chance for Merchant checks to be purchasable with Tycoon Wallet (500+).",
      "商人检查可用大亨钱包（500+）购买的概率。" },
    { "After choosing a price, set it to the affordable amount based on the wallet required.\n\n"
      "Affordable prices per tier: starter = 1, adult = 100, giant = 201, tycoon = 501\n\n"
      "Use this to enable wallet tier locking, but make merchant items not as expensive as they could be.",
      "选定价格后，根据所需钱包设为可负担金额。\n\n"
      "各层级可负担价格：起始 = 1，成人 = 100，巨人 = 201，大亨 = 501\n\n"
      "用于启用钱包层级锁定，但让商人道具不至于过于昂贵。" },
    { "Shuffles 5 Purple Rupees into to the item pool, and allows\n"
      "you to earn items by playing songs at the Frog Choir.\n"
      "\n"
      "This setting does not effect the item earned from playing\n"
      "the Song of Storms and the frog song minigame.",
      "将 5 枚紫色卢比洗入道具池，并允许你在青蛙合唱团处\n"
      "通过演奏歌曲获得道具。\n"
      "\n"
      "此设置不影响演奏风暴之歌与青蛙歌曲小游戏\n"
      "所获得的道具。" },
    { "Adds all of the adult trade quest items into the pool, each of which "
      "can be traded for a unique reward.\n"
      "\n"
      "You will be able to choose which of your owned adult trade items is visible "
      "in the inventory by selecting the item with A and using the control stick or "
      "D-pad.\n"
      "\n"
      "If disabled, only the Claim Check will be found in the pool.",
      "将所有成人交易任务道具加入池中，每一件都可交易换取独特奖励。\n"
      "\n"
      "你可用 A 键选中道具并操作控制杆或十字键，选择自己拥有的\n"
      "成人交易道具中哪一个在背包中显示。\n"
      "\n"
      "若关闭，池中只会找到领取凭证。" },
    { "Shuffle the item the cursed rich man in the House of Skulltula gives when you "
      "have collected all 100 Gold Skulltula Tokens.\n"
      "\n"
      "You can still talk to him multiple times to get Huge Rupees.",
      "当你收集齐全部 100 枚金色骷髅令牌时，洗牌骷髅屋中受诅咒的\n"
      "富人给予的道具。\n"
      "\n"
      "你仍可与他多次对话以获得巨大卢比。" },
    { "Freestanding rupees & hearts are shuffles to random items. "
      "Freestanding heart pieces and small keys are already shuffled by default.\n"
      "\n"
      "Off - freestanding rupees & hearts will not be shuffled.\n"
      "\n"
      "Dungeons - Only freestanding rupees & hearts that are within dungeons.\n"
      "\n"
      "Overworld - Only freestanding rupees & hearts that are outside of dungeons.\n"
      "\n"
      "All Items - Shuffle all freestanding rupees & hearts.",
      "独立的卢比与心之碎片会被洗牌为随机道具。独立的\n"
      "心之碎片与小钥匙默认已被洗牌。\n"
      "\n"
      "关闭 - 独立的卢比与心之碎片不被洗牌。\n"
      "\n"
      "地牢 - 仅洗牌地牢内的独立卢比与心之碎片。\n"
      "\n"
      "地面世界 - 仅洗牌地牢外的独立卢比与心之碎片。\n"
      "\n"
      "所有道具 - 洗牌所有独立卢比与心之碎片。" },
    { "Shuffle fairies in fountain locations. "
      "This includes the sets of fairies found in Ganon's Castle and the Desert Oasis.",
      "洗牌喷泉地点的精灵。包括盖侬城堡与沙漠绿洲中的精灵群。" },
    { "Shuffle fairies from gossip stone locations.",
      "洗牌来自闲话石地点的精灵。" },
    { "Shuffle fairies from magic bean locations.",
      "洗牌来自魔法魔豆地点的精灵。" },
    { "Shuffle fairy spots. These are spots where a big fairy is revealed by a song."
      "\n"
      "This excludes gossip stones and magic bean locations.",
      "洗牌精灵点。这些是由歌曲揭示大精灵的地点。"
      "\n"
      "不包括闲话石与魔法魔豆地点。" },
    { "Grass will drop a randomized item the first time they're cut and collected. "
      "Grass will have a different appearance when they hold a randomized item.\n"
      "\n"
      "Off - Grass will not be shuffled.\n"
      "\n"
      "Dungeons - Only shuffle grass that are within dungeons.\n"
      "\n"
      "Overworld - Only shuffle grass that are outside of dungeons.\n"
      "\n"
      "All Grass - Shuffle all grass.",
      "草丛首次被割下并拾取时会掉落随机道具。持有随机道具的\n"
      "草丛外观会不同。\n"
      "\n"
      "关闭 - 草丛不被洗牌。\n"
      "\n"
      "地牢 - 仅洗牌地牢内的草丛。\n"
      "\n"
      "地面世界 - 仅洗牌地牢外的草丛。\n"
      "\n"
      "所有草丛 - 洗牌所有草丛。" },

    // ---- Randomizer option descriptions (5/?) ----
    { "Shuffles the location of Spiritual Stones and medallions.\n"
      "Vanilla - Spiritual Stones and medallions will be given from their respective boss.\n"
      "\n"
      "End of dungeons - Spiritual Stones and medallions will be given as rewards "
      "for beating major dungeons. Link will always start with one stone or medallion.\n"
      "\n"
      "Any dungeon - Spiritual Stones and medallions can be found inside any dungeon.\n"
      "\n"
      "Overworld - Spiritual Stones and medallions can only be found outside of dungeons.\n"
      "\n"
      "Anywhere - Spiritual Stones and medallions can appear anywhere.",
      "洗牌精神石与徽章的位置。\n"
      "原版 - 精神石与徽章由各自对应的 Boss 给予。\n"
      "\n"
      "地牢末尾 - 精神石与徽章作为击败主要地牢的奖励给予。林克\n"
      "始终以一枚石或徽章起始。\n"
      "\n"
      "任意地牢 - 精神石与徽章可在任意地牢内找到。\n"
      "\n"
      "地面世界 - 精神石与徽章只能在地牢外找到。\n"
      "\n"
      "任意地点 - 精神石与徽章可出现在任何地方。" },
    { "Start with - You will start with Maps & Compasses from all dungeons.\n"
      "\n"
      "Vanilla - Maps & Compasses will appear in their vanilla locations.\n"
      "\n"
      "Own dungeon - Maps & Compasses can only appear in their respective dungeon.\n"
      "\n"
      "Any dungeon - Maps & Compasses can only appear inside of any dungeon.\n"
      "\n"
      "Overworld - Maps & Compasses can only appear outside of dungeons.\n"
      "\n"
      "Anywhere - Maps & Compasses can appear anywhere in the world.",
      "起始携带 - 你将起始携带所有地牢的地图与指南针。\n"
      "\n"
      "原版 - 地图与指南针出现在原版位置。\n"
      "\n"
      "自身地牢 - 地图与指南针只能出现在各自对应的地牢。\n"
      "\n"
      "任意地牢 - 地图与指南针只能出现在任意地牢内。\n"
      "\n"
      "地面世界 - 地图与指南针只能在地牢外出现。\n"
      "\n"
      "任意地点 - 地图与指南针可出现在世界任何地方。" },
    { "Start with - You will start with all Small Keys from all dungeons.\n"
      "\n"
      "Vanilla - Small Keys will appear in their vanilla locations. "
      "You start with 3 keys in Spirit Temple MQ because the vanilla key layout is not beatable in logic.\n"
      "\n"
      "Own dungeon - Small Keys can only appear in their respective dungeon. "
      "If Fire Temple is not a Master Quest dungeon, the door to the Boss Key chest will be unlocked.\n"
      "\n"
      "Any dungeon - Small Keys can only appear inside of any dungeon.\n"
      "\n"
      "Overworld - Small Keys can only appear outside of dungeons.\n"
      "\n"
      "Anywhere - Small Keys can appear anywhere in the world.",
      "起始携带 - 你将起始携带所有地牢的全部小钥匙。\n"
      "\n"
      "原版 - 小钥匙出现在原版位置。魂之神殿 MQ 中你以 3 把钥匙\n"
      "起始，因为原版钥匙布局在逻辑上无法通过。\n"
      "\n"
      "自身地牢 - 小钥匙只能出现在各自对应的地牢。若火之神殿\n"
      "不是大师任务地牢，则通往 Boss 钥匙宝箱的门会解锁。\n"
      "\n"
      "任意地牢 - 小钥匙只能出现在任意地牢内。\n"
      "\n"
      "地面世界 - 小钥匙只能在地牢外出现。\n"
      "\n"
      "任意地点 - 小钥匙可出现在世界任何地方。" },
    { "Keyrings will replace all small keys from a particular dungeon with a single keyring that awards all keys for "
      "its associated dungeon.\n"
      "\n"
      "Off - No dungeons will have their keys replaced with keyrings.\n"
      "\n"
      "Random - A random amount of dungeons (0-8 or 9) will have their keys replaced with keyrings.\n"
      "\n"
      "Count - A specified amount of randomly selected dungeons will have their keys replaced with keyrings.\n"
      "\n"
      "Selection - Hand select which dungeons will have their keys replaced with keyrings\n"
      "(can also be left as random, in which case each one will have a 50% chance of being a keyring).\n"
      "\n"
      "Selecting key ring for dungeons will have no effect if Small Keys are set to Start With or Vanilla.\n"
      "\n"
      "If Gerudo Fortress Carpenters is set to Normal, and Gerudo Fortress Keys is set to anything "
      "other than Vanilla, then the maximum amount of Key Rings that can be selected by Random or "
      "Count will be 9. Otherwise, the maximum amount of Key Rings will be 8.",
      "钥匙环会用一枚钥匙环替换某个特定地牢的全部小钥匙，该钥匙环\n"
      "会授予其关联地牢的所有钥匙。\n"
      "\n"
      "关闭 - 没有地牢的钥匙会被钥匙环替换。\n"
      "\n"
      "随机 - 随机数量（0-8 或 9）的地牢其钥匙会被钥匙环替换。\n"
      "\n"
      "数量 - 指定数量的随机选定地牢其钥匙会被钥匙环替换。\n"
      "\n"
      "选择 - 手动选择哪些地牢的钥匙被钥匙环替换\n"
      "（也可留为随机，此时每个有 50% 概率为钥匙环）。\n"
      "\n"
      "若将小钥匙设为起始携带或原版，则为地牢选择钥匙环无效。\n"
      "\n"
      "若格鲁德要塞木匠设为普通，且格鲁德要塞钥匙设为原版之外的值，\n"
      "则随机或数量可选的最大钥匙环数为 9；否则最大为 8。" },
    { "Vanilla - Thieves' Hideout Keys will appear in their vanilla locations.\n"
      "\n"
      "Any dungeon - Thieves' Hideout Keys can only appear inside of any dungon.\n"
      "\n"
      "Overworld - Thieves' Hideout Keys can only appear outside of dungeons.\n"
      "\n"
      "Anywhere - Thieves' Hideout Keys can appear anywhere in the world.",
      "原版 - 盗贼藏身处的钥匙出现在原版位置。\n"
      "\n"
      "任意地牢 - 盗贼藏身处的钥匙只能出现在任意地牢内。\n"
      "\n"
      "地面世界 - 盗贼藏身处的钥匙只能在地牢外出现。\n"
      "\n"
      "任意地点 - 盗贼藏身处的钥匙可出现在世界任何地方。" },
    { "Start with - You will start with Boss keys from all dungeons.\n"
      "\n"
      "Vanilla - Boss Keys will appear in their vanilla locations.\n"
      "\n"
      "Own dungeon - Boss Keys can only appear in their respective dungeon.\n"
      "\n"
      "Any dungeon - Boss Keys can only appear inside of any dungeon.\n"
      "\n"
      "Overworld - Boss Keys can only appear outside of dungeons.\n"
      "\n"
      "Anywhere - Boss Keys can appear anywhere in the world.",
      "起始携带 - 你将起始携带所有地牢的 Boss 钥匙。\n"
      "\n"
      "原版 - Boss 钥匙出现在原版位置。\n"
      "\n"
      "自身地牢 - Boss 钥匙只能出现在各自对应的地牢。\n"
      "\n"
      "任意地牢 - Boss 钥匙只能出现在任意地牢内。\n"
      "\n"
      "地面世界 - Boss 钥匙只能在地牢外出现。\n"
      "\n"
      "任意地点 - Boss 钥匙可出现在世界任何地方。" },
    { "Vanilla - Ganon's Boss Key will appear in the vanilla location.\n"
      "\n"
      "Own dungeon - Ganon's Boss Key can appear anywhere inside Ganon's Castle.\n"
      "\n"
      "Start with - Places Ganon's Boss Key in your starting inventory."
      "\n"
      "Any dungeon - Ganon's Boss Key Key can only appear inside of any dungeon.\n"
      "\n"
      "Overworld - Ganon's Boss Key Key can only appear outside of dungeons.\n"
      "\n"
      "Anywhere - Ganon's Boss Key Key can appear anywhere in the world.\n"
      "\n"
      "LACS - These settings put the boss key on the Light Arrow Cutscene location, from Zelda in Temple of Time as "
      "adult, with differing requirements:\n"
      "- Vanilla: Obtain the Shadow Medallion and Spirit Medallion\n"
      "- Stones: Obtain the specified amount of Spiritual Stones.\n"
      "- Medallions: Obtain the specified amount of medallions.\n"
      "- Dungeon rewards: Obtain the specified total sum of Spiritual Stones or medallions.\n"
      "- Dungeons: Complete the specified amount of dungeons. Dungeons are considered complete after stepping in to "
      "the blue warp after the boss.\n"
      "- Tokens: Obtain the specified amount of Skulltula tokens.\n"
      "\n"
      "100 GS Reward - Ganon's Boss Key will be awarded by the cursed rich man after you collect 100 Gold Skulltula "
      "Tokens.",
      "原版 - 盖侬的 Boss 钥匙出现在原版位置。\n"
      "\n"
      "自身地牢 - 盖侬的 Boss 钥匙可出现在盖侬城堡内任意位置。\n"
      "\n"
      "起始携带 - 将盖侬的 Boss 钥匙放入起始背包。"
      "\n"
      "任意地牢 - 盖侬的 Boss 钥匙只能出现在任意地牢内。\n"
      "\n"
      "地面世界 - 盖侬的 Boss 钥匙只能在地牢外出现。\n"
      "\n"
      "任意地点 - 盖侬的 Boss 钥匙可出现在世界任何地方。\n"
      "\n"
      "LACS - 这些设置将 Boss 钥匙放在光之箭过场位置，即成人时期\n"
      "时之殿的塞尔达处，条件各不相同：\n"
      "- 原版：获得暗之徽章与灵之徽章\n"
      "- 石：获得指定数量的精神石。\n"
      "- 徽章：获得指定数量的徽章。\n"
      "- 地牢奖励：获得指定总数的精神石或徽章。\n"
      "- 地牢：完成指定数量的地牢。在 Boss 后踏入蓝色传送点即视为完成。\n"
      "- 令牌：获得指定数量的骷髅令牌。\n"
      "\n"
      "100 金骷髅奖励 - 收集齐 100 枚金色骷髅令牌后，受诅咒的富人会授予盖侬的 Boss 钥匙。" },
    { "Standard Rewards - Greg does not change logic, Greg does not help obtain GBK, max "
      "number of rewards on slider does not change.\n"
      "\n"
      "Greg as Reward - Greg does change logic (can be part of expected path for obtaining "
      "GBK), Greg helps obtain GBK, max number of rewards on slider increases by 1 to "
      "account for Greg. \n"
      "\n"
      "Greg as Wildcard - Greg does not change logic, Greg helps obtain GBK, max number of "
      "rewards on slider does not change.",
      "标准奖励 - 格雷格不改变逻辑，格雷格不帮助获得 GBK，滑块上的\n"
      "最大奖励数量不变。\n"
      "\n"
      "格雷格作为奖励 - 格雷格会改变逻辑（可能是获得 GBK 的预期路径之一），\n"
      "格雷格帮助获得 GBK，滑块最大奖励数量加 1 以计入格雷格。\n"
      "\n"
      "格雷格作为万能替换 - 格雷格不改变逻辑，但帮助获得 GBK，\n"
      "滑块最大奖励数量不变。" },
    { "The Poe collector will give a reward for turning in this many Big Poes.",
      "波克收集者会在你交付这么多大波克时给予奖励。" },
    { "The crawlspace into Hyrule Castle goes straight to Zelda, skipping the guards.",
      "通往海拉鲁城堡的爬行空间直接通向塞尔达，跳过守卫。" },
    { "Start with Zelda's Letter and the item Impa would normally give you and skip the sequence up "
      "until after meeting Zelda. Disables the ability to shuffle Weird Egg.",
      "起始携带塞尔达的信以及英帕通常会给你的道具，并跳过\n"
      "直到遇见塞尔达之前的流程。禁用洗牌奇怪的蛋的能力。" },
    { "Epona can be summoned with Epona's Song without needing to race Ingo.",
      "无需与印格赛跑即可用伊波纳之歌召唤伊波纳。" },
    { "How masks are acquired.\n"
      "Vanilla - Mask trade quest.\n"
      "\n"
      "Completed - Once the Happy Mask Shop is opened, all masks will be available to be borrowed.\n"
      "\n"
      "Shuffle - Happy Mask Shop never opens, masks are shuffled with rest of items.",
      "面具的获取方式。\n"
      "原版 - 面具交易任务。\n"
      "\n"
      "已完成 - 快乐面具店一旦开门，所有面具都可借用。\n"
      "\n"
      "洗牌 - 快乐面具店永不开启，面具与其余道具一起被洗牌。" },
    { "Start with the ability to summon Pierre the Scarecrow. Pulling out an Ocarina in the usual locations will "
      "automatically summon him.\n"
      "With \"Shuffle Ocarina Buttons\" enabled, you'll need at least two Ocarina buttons to summon him.",
      "起始即拥有召唤稻草人皮埃尔的能力。在通常地点掏出陶笛会\n"
      "自动召唤他。开启\"洗牌陶笛按钮\"后，你需要至少两个陶笛按钮才能召唤他。" },
    { "Beans will be planted once you find beans.\n"
      "If bean souls are shuffled, you must find soul still.",
      "找到魔豆后会自动种植。若魔豆灵魂被洗牌，仍需找到灵魂。" },
    { "Sets how many major items appear in the item pool.\n"
      "\n"
      "Plentiful - Extra major items are added to the pool.\n"
      "\n"
      "Balanced - Original item pool.\n"
      "\n"
      "Scarce - Some excess items are removed, including health upgrades.\n"
      "\n"
      "Minimal - Most excess items are removed.",
      "设定道具池中出现的主要道具数量。\n"
      "\n"
      "丰富 - 向池中加入额外主要道具。\n"
      "\n"
      "均衡 - 原始道具池。\n"
      "\n"
      "稀少 - 移除部分多余道具，包括生命升级。\n"
      "\n"
      "最少 - 移除大部分多余道具。" },
    { "Sets if ice traps that exist in vanilla are shuffled into the item pool.\n"
      "If this is on, 1 Trap will always be added to the pool,\n"
      "an additional trap will be added if Gerudo Training Grounds\n"
      "is NOT master quest,\n"
      "and 4 more will be added if Ganon's Castle is NOT Master Quest.",
      "设定原版中存在的冰冻陷阱是否洗入道具池。\n"
      "若开启，总会向池中加入 1 个陷阱；\n"
      "若格鲁德训练场不是大师任务，会再增加 1 个；\n"
      "若盖侬城堡不是大师任务，会再增加 4 个。" },
    { "Sets how many more Ice Traps will be added to item pool,\n"
      "assuming there is enough space after placing Progression Items.\n\n"
      "You do not need to have base ice traps on for this setting to work.",
      "设定会向道具池额外加入多少冰冻陷阱，\n"
      "假设在放置进阶道具后仍有足够空间。\n\n"
      "此设置生效无需开启基础冰冻陷阱。" },
    { "If set above 0, each Junk item has that chance of being replaced with an extra Ice Trap.",
      "若设为大于 0，每个垃圾道具有该概率被替换为额外的冰冻陷阱。" },

    // ---- Randomizer option descriptions (6/?) ----
    { "Allows Gossip Stones to provide hints on item locations. Hints mentioning "
      "\"Way of the Hero\" indicate a location that holds an item required to beat "
      "the seed.\n"
      "\n"
      "No hints - No hints will be given at all.\n"
      "\n"
      "Need Nothing - Hints are always available from Gossip Stones.\n"
      "\n"
      "Need Stone of Agony - Hints are only available after obtaining the Stone of Agony.\n"
      "\n"
      "Need Mask of Truth - Hints are only available whilst wearing the Mask of Truth.\n",
      "允许闲话石提供关于道具位置的提示。提及\"英雄之路\"的提示\n"
      "指示持有通关所需道具的地点。\n"
      "\n"
      "无提示 - 完全不给出提示。\n"
      "\n"
      "无需任何条件 - 闲话石始终提供提示。\n"
      "\n"
      "需要振动石 - 仅在获得振动石后提供提示。\n"
      "\n"
      "需要真实面具 - 仅在佩戴真实面具时提供提示。\n" },
    { "Sets the difficulty of hints.\n"
      "\n"
      "Obscure - Hints are unique for each item, but the writing may be cryptic.\n"
      "Ex: Kokiri Sword > a butter knife\n"
      "\n"
      "Ambiguous - Hints are clearly written, but may refer to more than one item.\n"
      "Ex: Kokiri Sword > a sword\n"
      "\n"
      "Clear - Hints are clearly written and are unique for each item.\n"
      "Ex: Kokiri Sword > the Kokiri Sword",
      "设定提示的难度。\n"
      "\n"
      "冷门 - 每个道具的提示都唯一，但措辞可能晦涩。\n"
      "例：科克里之剑 > 一把黄油刀\n"
      "\n"
      "模糊 - 提示表述清晰，但可能指向多个道具。\n"
      "例：科克里之剑 > 一把剑\n"
      "\n"
      "清晰 - 提示表述清晰且每个道具唯一。\n"
      "例：科克里之剑 > 科克里之剑" },
    { "Sets how many hints will be useful.\n"
      "\n"
      "Useless - Only junk hints.\n"
      "\n"
      "Balanced - Recommended hint spread.\n"
      "\n"
      "Strong - More useful hints.\n"
      "\n"
      "Very Strong - Many powerful hints.",
      "设定有多少提示是有用的。\n"
      "\n"
      "无用 - 只有垃圾提示。\n"
      "\n"
      "均衡 - 推荐的提示分布。\n"
      "\n"
      "强 - 更有用的提示。\n"
      "\n"
      "极强 - 许多强力提示。" },
    { "Reading the Temple of Time altar as child will tell you the locations of the Spiritual Stones.\n"
      "Reading the Temple of Time altar as adult will tell you the locations of the medallions, as well as the "
      "conditions for building the Rainbow Bridge and getting the Boss Key for Ganon's Castle.",
      "儿童时期阅读时之殿祭坛会告诉你精神石的位置。成人时期阅读\n"
      "时之殿祭坛会告诉你徽章的位置，以及建造彩虹桥与获得\n"
      "盖侬城堡 Boss 钥匙的条件。" },
    { "Talking to Ganondorf in his boss room will tell you the location of the Light Arrows and Master Sword."
      "If this option is enabled and Ganondorf is reachable without these items, Gossip Stones will never hint the "
      "appropriate items.",
      "在 Boss 房与盖侬道夫对话会告诉你光之箭与大师之剑的位置。"
      "若开启此选项且盖侬道夫无需这些道具即可到达，闲话石将永不提示相应道具。" },
    { "Talking to Sheik inside Ganon's Castle will tell you the location of the Light Arrows."
      "If this option is enabled and Sheik is reachable without Light Arrows, Gossip Stones will never hint the "
      "Light Arrows.",
      "在盖侬城堡内与什克对话会告诉你光之箭的位置。"
      "若开启此选项且什克无需光之箭即可到达，闲话石将永不提示光之箭。" },
    { "Reading the diary of Dampé the gravekeeper as adult will tell you the location of one of the Hookshots.",
      "成人时期阅读守墓人达培的日记会告诉你其中一个钩绳的位置。" },
    { "Talking to the chest game owner after buying a key will tell you the location of Greg the Green Rupee.",
      "购买钥匙后与宝箱游戏店主对话会告诉你绿色卢比格雷格的位置。" },
    { "Talking to the fishing pond owner and asking to talk about something will "
      "tell you what's the reward for the Hyrule Loach.",
      "与钓鱼池店主对话并选择谈论某事，会告诉你海拉鲁泥鳅的奖励是什么。" },
    { "Navi will tell where boss key can be found when prompted at boss door.",
      "在 Boss 门前触发时，娜薇会告诉 Boss 钥匙的位置。" },
    { "Talking to Saria either in person or through Saria's Song will tell you the "
      "location of a progressive magic meter.",
      "亲自或与萨莉亚通过萨莉亚之歌对话，会告诉你进阶魔法槽的位置。" },
    { "Talking to Mido as child will tell you the location of the Kokiri Sword.",
      "儿童时期与米多对话会告诉你科克里之剑的位置。" },
    { "Talking to the fishing pond owner without the fishing pole will tell you its location.",
      "没有钓竿时与钓鱼池店主对话会告诉你钓竿的位置。" },
    { "Sheik in the Temple of Time will tell you the item and song on the Ocarina of Time.",
      "时之殿的什克会告诉你时之陶笛上的道具与歌曲。" },
    { "Standing near the pedestal for the frogs in Zora's River will tell you the "
      "reward for the frogs' Ocarina game.",
      "站在卓拉之河青蛙的基座附近，会告诉你青蛙陶笛游戏的奖励。" },
    { "Talking to Biggoron will tell you the item he will give you in exchange for the Claim Check.",
      "与巨大格雷对话会告诉你他交换领取凭证所给予的道具。" },
    { "Talking to the Poe Collector in the Market Guardhouse while adult will "
      "tell you what you receive for handing in Big Poes.",
      "成人时期在市场警卫室与波克收集者对话，会告诉你交付大波克所获得的奖励。" },
    { "Talking to Anju as a child will tell you the item she will give you for delivering her cuccos to the pen.",
      "儿童时期与安茱对话，会告诉你将她的鸡送回鸡栏后她给予的道具。" },
    { "Talking to Malon as adult will tell you the item on \"Link's cow\", the cow "
      "you win from beating her time on the Lon Lon Obstacle Course.",
      "成人时期与玛隆对话，会告诉你\"林克的牛\"上的道具——即你在\n"
      "隆隆障碍赛击败她的时间后赢得的那头牛。" },
    { "Talking to the Horseback Archery gerudo in Gerudo Fortress, or the nearby sign, will tell you what you win "
      "for scoring 1000 and 1500 points on Horseback Archery.",
      "在格鲁德要塞与马背射箭的格鲁德人对话，或查看附近招牌，会告诉你\n"
      "在马背射箭中得 1000 与 1500 分时的奖励。" },
    { "Playing a warp song will tell you where it leads. (If warp song "
      "destinations are vanilla, this is always enabled.)",
      "演奏传送歌曲会告诉你它的目的地。（若传送歌曲目的地为原版，则此功能始终开启。）" },
    { "Business scrubs will reveal the identity of what they're selling.",
      "商人（Scrub）会透露他们所售道具的身份。" },
    { "Merchants will reveal the identity of what they're selling (Shops are not affected by this setting).",
      "商人会透露他们所售道具的身份（商店不受此设置影响）。" },
    { "Talking to the Cursed Resident in the Skulltula House who is saved after 10 tokens will tell you the reward.",
      "与骷髅屋中收集 10 枚令牌后被解救的受诅咒居民对话，会告诉你奖励。" },
    { "Talking to the Cursed Resident in the Skulltula House who is saved after 20 tokens will tell you the reward.",
      "与骷髅屋中收集 20 枚令牌后被解救的受诅咒居民对话，会告诉你奖励。" },
    { "Talking to the Cursed Resident in the Skulltula House who is saved after 30 tokens will tell you the reward.",
      "与骷髅屋中收集 30 枚令牌后被解救的受诅咒居民对话，会告诉你奖励。" },
    { "Talking to the Cursed Resident in the Skulltula House who is saved after 40 tokens will tell you the reward.",
      "与骷髅屋中收集 40 枚令牌后被解救的受诅咒居民对话，会告诉你奖励。" },
    { "Talking to the Cursed Resident in the Skulltula House who is saved after 50 tokens will tell you the reward.",
      "与骷髅屋中收集 50 枚令牌后被解救的受诅咒居民对话，会告诉你奖励。" },
    { "Talking to the Cursed Resident in the Skulltula House who is saved after 100 tokens will tell you the reward.",
      "与骷髅屋中收集 100 枚令牌后被解救的受诅咒居民对话，会告诉你奖励。" },
    { "Reading the mask shop sign will tell you rewards from showing masks at the Deku Theatre.",
      "阅读面具店招牌会告诉你于德库剧场展示面具的奖励。" },
    { "Start with a full wallet. All wallet upgrades come filled with rupees.",
      "起始即拥有满钱包。所有钱包升级都预装卢比。" },
    { "None - Bombchus have vanilla behavior, any Bombchu requirement is filled by Bomb Bag + a renewable source of "
      "Bombchus.\n\n"
      "Single Bag - Bombchus require their own bag to be found before use. 5 of them are added to the pool "
      "(6 if the Carpet Merchant is shuffled). The first Bombchu Bag you find will be a Bag containing 20 chus, "
      "and subsequent bags will be replaced with Bombchu Ammo refills. Once found, they can be replenished at "
      "shops selling refills, Bombchu Bowling and the carpet merchant. Bombchu Bowling is opened by obtaining "
      "the Bombchu Bag.\n\n"
      "Progressive Bags - 3 Bombchu Bags are added to the pool, the first one will unlock Bombchus with a capacity "
      "of 20. The second one will upgrade this capacity to 30, and the final one will upgrade the capacity to the "
      "usual 50.\n\n"
      "Bombchu Bowling is opened by obtaining the first Bombchu bag.",
      "无 - 炸弹鼠为原版行为，任何炸弹鼠需求由炸弹袋加可再生炸弹鼠来源满足。\n\n"
      "单一袋 - 炸弹鼠需先找到自己的袋子才能使用。其中 5 个加入池中\n"
      "（若地毯商人被洗牌则为 6 个）。你找到的第一个炸弹鼠袋含 20 个鼠，\n"
      "后续袋子会被替换为炸弹鼠弹药补给。找到后可在出售补给的商店、\n"
      "炸弹鼠保龄球与地毯商人处补充。获得炸弹鼠袋即开启炸弹鼠保龄球。\n\n"
      "进阶袋 - 池中加入 3 个炸弹鼠袋，第一个解锁容量 20 的炸弹鼠。\n"
      "第二个将容量升至 30，最后一个升至通常的 50。\n\n"
      "获得第一个炸弹鼠袋即开启炸弹鼠保龄球。" },
    { "Once you obtain a Bombchu Bag, refills will sometimes replace "
      "Bomb drops that would spawn."
      "\n"
      "If you have Bombchu Bag disabled, you will need a Bomb Bag "
      "and existing Bombchus for Bombchus to drop.",
      "一旦获得炸弹鼠袋，补给有时会替换本应生成的炸弹掉落。"
      "\n"
      "若你禁用了炸弹鼠袋，则需要炸弹袋与已有的炸弹鼠，炸弹鼠才会掉落。" },
    { "Ice Arrows act like Blue Fire, making them able to melt red ice. "
      "Item placement logic will respect this option, so it might be required to use this to progress.",
      "冰之箭表现得像蓝火焰，使它们能够融化红冰。道具放置逻辑会\n"
      "尊重此选项，因此可能需要用它来推进进程。" },
    { "Adds a new item called the \"Skeleton Key\", it unlocks every dungeon door locked by a small key.",
      "新增名为\"万能钥匙\"的道具，可解锁所有由小钥匙锁住的地牢门。" },
    { "Light Arrows can be used to light up the sun switches instead of using the Mirror Shield. "
      "Item placement logic will respect this option, so it might be required to use this to progress.",
      "光之箭可用于点亮太阳开关，替代镜盾。道具放置逻辑会\n"
      "尊重此选项，因此可能需要用它来推进进程。" },
    { "Adds Roc's Feather to the item pool. Roc's Feather is a custom item granting the player a jump on demand. "
      "The jump can also be used when already in mid-air. Roc's Feather is not considered by logic.",
      "将洛克的羽毛加入道具池。洛克的羽毛是自定义道具，允许玩家\n"
      "随时起跳，且可在空中时再次使用。逻辑不考量洛克的羽毛。" },
    { "Allows Slingshot and Bow to break beehives when Beehive Shuffle is turned on.",
      "开启蜂巢洗牌时，允许弹弓与弓打破蜂巢。" },
    { "Glitchless - No glitches are required, but may require some minor tricks. Additional tricks may be enabled "
      "and disabled below.\n"
      "\n"
      "No logic - Item placement is completely random. MAY BE IMPOSSIBLE TO BEAT.",
      "无故障 - 无需故障，但可能需要一些小幅技巧。下方可\n"
      "启用或禁用额外技巧。\n"
      "\n"
      "无逻辑 - 道具放置完全随机。可能无法通关。" },
    { "When this option is enabled, the randomizer will "
      "guarantee that every item is obtainable and every "
      "location is reachable. When disabled, only "
      "required items and locations to beat the game "
      "will be guaranteed reachable.",
      "开启此选项时，随机生成器会保证每个道具都可获得、每个\n"
      "地点都可到达。关闭时，仅保证通关所需的道具与地点可达。" },
    { "Shuffle 10 bean souls which must be found to spawn corresponding soil / plant.",
      "洗牌 10 个魔豆灵魂，需找到它们才能生成相应的土壤/植物。" },
    { "Shuffles 8 boss souls (one for each blue warp dungeon). A boss will not appear until you collect its "
      "respective soul."
      "\n\"On + Ganon\" will also hide Ganon and Ganondorf behind a boss soul.",
      "洗牌 8 个 Boss 灵魂（每个蓝色传送地牢一个）。在收集到\n"
      "相应灵魂之前，Boss 不会出现。"
      "\n\"开启 + 盖侬\"还会将盖侬与盖侬道夫也隐藏在 Boss 灵魂之后。" },

    // ---- Randomizer Tricks menu buttons ----
    { "Collapse All##disabled", "全部折叠##disabled" },
    { "Collapse All##enabled", "全部折叠##enabled" },
    { "Disable All", "全部禁用" },
    { "Disable Visible", "禁用可见项" },
    { "Enable All", "全部启用" },
    { "Enable Visible", "启用可见项" },
    { "Open All##disabled", "全部展开##disabled" },
    { "Open All##enabled", "全部展开##enabled" },
    { "Disabled Tricks", "已禁用技巧" },
    { "Enabled Tricks", "已启用技巧" },

    // ---- Item Tracker menu ----
    { "General settings", "通用设置" },
    { "Section settings", "分区设置" },
    { "Window Type", "窗口类型" },
    { "Window", "窗口" },
    { "Floating", "悬浮" },
    { "Main Window", "主窗口" },
    { "Separate", "独立窗口" },
    { "Hidden", "隐藏" },
    { "Misc Window", "杂项窗口" },
    { "Dungeon Rewards", "地牢奖励" },
    { "Icon size : %dpx", "图标尺寸：%d 像素" },
    { "Icon margins : %dpx", "图标间距：%d 像素" },
    { "Text size : %dpx", "文字尺寸：%d 像素" },
    { "Bean Souls", "魔豆之魂" },
    { "Boss Souls", "魔王之魂" },
    { "Jabber Nuts", "喋喋坚果" },
    { "Ocarina Buttons", "陶笛按钮" },
    { "Overworld Keys", "地面世界钥匙" },
    { "Ammo/Capacity Tracking", "弹药/容量追踪" },
    { "Current Capacity", "当前容量" },
    { "Current Ammo", "当前弹药" },
    { "Current Capacity / Max Capacity", "当前容量 / 最大容量" },
    { "Current Ammo / Current Capacity", "当前弹药 / 当前容量" },
    { "No Numbers", "无数字" },
    { "Combo Button Hold", "按住组合键" },
    { "Key Count Tracking", "钥匙计数追踪" },
    { "Collected / Max", "已收集 / 最大" },
    { "Current / Collected / Max", "当前 / 已收集 / 最大" },
    { "Current / Max", "当前 / 最大" },
    { "Personal notes", "个人便签" },
    { "Triforce Piece Count Tracking", "三角神力碎片计数追踪" },
    { "Collected / Required", "已收集 / 所需" },
    { "Collected / Required / Max", "已收集 / 所需 / 最大" },
    { "Show Hookshot Identifiers", "显示钩绳标识符" },

    // ---- Misc missing labels ----
    { "Fix Vanishing Paths", "修复消失的路径" },
    { "Play Zelda's Lullaby to Open Sleeping Waterfall", "演奏塞尔达的摇篮曲以开启沉睡瀑布" },
    { "Skip Feeding Jabu-Jabu", "跳过喂养盖侬加加" },
    { "Time of Day", "时间" },
    { "WWLSepFairy", "其他精灵" },
    { "WWLSepNavi", "娜薇" },

    // ---- Enhancements (second half) & Settings & DevTools tooltips/labels ----
    { "Adds back in a delay after unpausing before the game resumes playing again, where inputs can be held prematurely to be input immediately after the game resumes. This essentially brings back behaviour from console releases which are lost on default because SoH isn't limited to N64 hardware.",
      "在取消暂停、游戏恢复运行之前重新加入一段延迟，期间可提前按住按键，待游戏恢复后立即输入。这实质上是恢复了主机版本的行为，而 SoH 不受 N64 硬件限制，默认情况下该行为已丢失。" },
    { "Allows Child Link to use a Bow with Arrows.\nAllows Adult Link to use a Slingshot with Seeds.\n\nRequires glitches or the 'Timeless Equipment' cheat to equip.",
      "允许童年林克使用弓箭。\n允许成年林克使用种子弹弓。\n\n需要利用漏洞或\"永恒装备\"作弊码才能装备。" },
    { "Allows Link to freely change age by playing the Song of Time.\nTime Blocks can still be used properly.\n\nRequirements:\n - Obtained the Song of Time\n - Obtained the Ocarina of Time (depends on selection)\n - Obtained the Master Sword (depends on selection)\n - Not within range of a Time Block\n - Not within range of Ocarina Playing spots",
      "允许林克通过演奏时光之笛自由切换年龄。\n时间方块仍可正常使用。\n\n要求：\n - 已获得时光之笛\n - 已获得时光之笛乐器（取决于选择）\n - 已获得大师之剑（取决于选择）\n - 不在时间方块范围内\n - 不在演奏乐器点范围内" },
    { "Allows the cursor on the pause menu to be over any slot. Sometimes required in Randomizer to select certain items.",
      "允许暂停菜单的光标停留在任意槽位。在随机化器中，有时需要它来选择特定道具。" },
    { "Allows unequipping items from C-Buttons/D-pad by hovering over an equipped item and pressing the button it's equipped to.",
      "将光标悬停在已装备的道具上，按下其对应的装备按键，即可从 C 键/方向键卸下该道具。" },
    { "Allows you to have \"Link\" as a premade file name.",
      "允许你将林克作为预设文件名。" },
    { "Changes Heart Piece and Heart Container functionality.\n\n - Each Heart Container or full Heart Piece reduces Link's Hearts by 1.\n - Can be enabled retroactively after a File has already started.",
      "改变心之碎片与心之容器的功能。\n\n - 每个心之容器或完整心之碎片会使林克的心数减 1。\n - 可在存档已开始之后追溯启用。" },
    { "Changes the behavior of debug file select creation (creating a save file on slot 1 with debug mode on):\n- Off: The debug save file will be a normal savefile.\n- Vanilla: The debug save file will be the debug save file from the original game.\n- Maxed: The debug save file will be a save file with all of the items & upgrades.",
      "改变调试模式创建存档（在 1 号槽创建开启调试模式的存档）的行为：\n- 关闭：调试存档为一个普通存档。\n- 原版：调试存档为原版游戏中的调试存档。\n- 满级：调试存档为一个拥有全部道具与升级的存档。" },
    { "Configure what happens when starting or resetting the game.\n\nDefault: LUS logo -> N64 logo\nAuthentic: N64 logo only\nFile Select: Skip to file select menu\nDebug Warp Screen: Skip to the debug warp screen\nWarp Point: Skip to active warp point (if set), see Dev Tools -> General",
      "配置开始或重置游戏时发生的行为。\n\n默认：LUS 标志 -> N64 标志\n原版风格：仅 N64 标志\n文件选择：跳转到文件选择菜单\n调试传送屏：跳转到调试传送屏幕\n传送点：跳转到当前传送点（若已设置），见开发工具 -> 通用" },
    { "Disabled: Paths vanish more the higher the resolution (Z-Fighting is based on resolution).\nConsistent: Certain paths vanish the same way in all resolutions.\nNo Vanish: Paths do not vanish, Link seems to sink in to some paths.\nThis might affect other decal effects.",
      "禁用：分辨率越高，路径消失越明显（Z 冲突基于分辨率）。\n一致：特定路径在所有分辨率下以相同方式消失。\n不消失：路径不会消失，林克在某些路径上似乎会下陷。\n这可能影响其它贴花效果。" },
    { "Disables 2D pre-rendered backgrounds. Enable this when using a mod that implements 3D backdrops for these areas.\nRequires Scene Change to alter.",
      "禁用 2D 预渲染背景。当使用为这些区域实现 3D 背景的模组时启用此项。\n需要切换场景才能生效。" },
    { "Disables the sword trail effect when swinging Link's sword. Useful when using mods that replace Link's sword model.",
      "禁用林克挥剑时的剑光拖尾效果。在使用替换林克剑模型的模组时有用。" },
    { "Disables warning text when you don't have on the Goron/Zora Tunic in Hot/Underwater conditions.",
      "当你在高温/水下环境中没有穿上火纹/卓拉外衣时，禁用警告文字。" },
    { "Don't increase crawl speed when exiting glitch-useful crawlspaces.Currently it is only the BOTW crawlspace to locked door",
      "从有利于漏洞的爬行空间中离开时，不提高爬行速度。目前仅适用于通往上锁门的王国之泪爬行空间" },
    { "Don't skip cutscenes that are associated with useful glitches. Currently, it is only the Fire Temple Darunia CS, Forest Temple Poe Sisters CS, Dodongo Boss Door Switch CS, Water Temple Dragon Switch CS, the Box Skip One Point in Jabu, Early Hammer Switch CS in MQ Spirit, and Cow Switch Chest CS in MQ Jabu.",
      "不跳过与有用漏洞相关的过场动画。目前仅包括：火之神殿达鲁尼亚过场、森林神殿 Poe 姐妹过场、多多隆 Boss 门开关过场、水之神殿龙开关过场、 Jabu 中的箱子跳过一点、 MQ 灵魂神殿的早期锤子开关过场，以及 MQ Jabu 中的牛开关宝箱过场。" },
    { "Enables Debug Mode, allowing you to select maps with L + R + Z, noclip with L + D-pad Right, and open the debug menu with L on the pause screen.",
      "启用调试模式，允许你用 L + R + Z 选择地图，用 L + 方向键右键穿墙，并在暂停界面按 L 打开调试菜单。" },
    { "Enables Skulltula Debug, when moving the cursor in the menu above various map icons (boss key, compass, map screen locations, etc.) will set the GS bits in that area.\nUSE WITH CAUTION AS IT DOES NOT UPDATE THE GS COUNT!",
      "启用骷髅蜘蛛调试：当光标在菜单中移动到各种地图图标（ Boss 钥匙、罗盘、地图画面位置等）上方时，会设置该区域的金色骷髅标记位。\n谨慎使用，因为它不会更新金色骷髅计数！" },
    { "Enemies spawned by CrowdControl won't be considered for \"clear enemy rooms\", so they don't need to be killed to complete these rooms.",
      "由 CrowdControl 生成的敌人不会被计入清空敌人房间，因此无需击杀它们即可完成这些房间。" },
    { "Hides most of the UI when not needed.\nNOTE: Doesn't activate until scene transition.",
      "在不需要时隐藏大部分界面。\n注意：直到切换场景后才会激活。" },
    { "Introduces Options for unequipping Link's sword\n\nNone: Only Biggoron's Sword/Giant's Knife can be toggled. Doing so will equip the Master Sword.\n\nChild Toggle: This will allow for completely unequipping any sword as Child link.\n\nBoth Ages: Any sword can be unequipped as either age. This may lead to swordless glitches as adult.",
      "引入卸下林克剑的选项\n\n无：仅可切换大师古剑/巨人刀。切换后会装备大师之剑。\n\n童年切换：允许童年林克完全卸下任意剑。\n\n两个年龄：任意年龄都可卸下任意剑。这可能导致成年林克出现无剑漏洞。" },
    { "Make Deku Nuts explode Bombs, similar to how they interact with Bombchus. This does not affect Bomb Flowers.",
      "使德库坚果像与定时炸弹互动那样引爆炸弹。这不影响炸弹花。" },
    { "Makes Link always kick the chest to open it, instead of doing the longer chest opening animation for major items.",
      "让林克总是用脚踢开宝箱，而不是播放主要道具较长的开箱动画。" },
    { "Matches the color of maps & compasses to the dungeon they belong to. This helps identify maps & compasses from afar and adds a little bit of flair.\n\nThis only applies to seeds with maps & compasses shuffled to \"Any Dungeon\", \"Overworld\", or ",
      "将地图与罗盘的颜色匹配到它们所属的地牢。这有助于从远处辨认地图与罗盘，并增添一点特色。\n\n这仅适用于将地图与罗盘洗入任意地牢、地面世界\"或" },
    { "Modifies damage taken after falling into a void:\n2x: Can survive void damage from the start of the game.\n4x: Cannot survive void damage from the start of the game.\n8x: Can survive void damage twice with max health without double defense.\n16x: Can survive void damage with max health without double defense.\n32x: Can survive void damage with max health and double defense.\n64x: Cannot survive void damage.",
      "修改坠入虚空后受到的伤害：\n2 倍：从游戏开始即可承受虚空伤害。\n4 倍：从游戏开始无法承受虚空伤害。\n8 倍：在满血且无双重防御时可承受两次虚空伤害。\n16 倍：在满血且无双重防御时可承受虚空伤害。\n32 倍：在满血且双重防御时可承受虚空伤害。\n64 倍：无法承受虚空伤害。" },
    { "Resets the Navi timer on scene change. If you have already talked to her, she will try and talk to you again, instead of needing a save warp or death.",
      "在切换场景时重置娜薇计时器。如果你已经和她说过话，她会再次尝试与你交谈，而无需存读档或死亡。" },
    { "Reworks targeting functionality\n- Press Z while locked always untargets (in Toggle mode)\n- Use the configured button combo to switch between targets",
      "重构锁定功能\n- 锁定状态下按 Z 始终取消锁定（切换模式）\n- 使用配置的按键组合在目标间切换" },
    { "Skip the \"Game Saved\" confirmation screen.",
      "跳过\"游戏已保存\"确认画面。" },
    { "Skip the tower escape sequence between Ganondorf and Ganon.",
      "跳过盖侬道夫与盖侬之间的逃脱塔序列。" },
    { "Skips Link's taking breath animation after coming up from water. This setting does not interfere with getting items from underwater.",
      "跳过林克从水中浮出后的呼吸动画。此设置不影响从水下获取道具。" },
    { "Speeds up animation of the pause menu, similar to Majora's Mask",
      "加快暂停菜单的动画速度，类似《Majora 的面具》。" },
    { "Speeds up emptying animation when dumping out the contents of a bottle.",
      "加快从瓶中倒空内容物的动画速度。" },
    { "Speeds up lifting Silver Rocks and Obelisks.",
      "加快举起银色岩石与方尖碑的速度。" },
    { "Speeds up ship in Shadow Temple.",
      "加快 Shadow 神殿中船的速度。" },
    { "Stops masks from automatically unequipping on certain situations:\n- When entering a new scene\n- When not in any C-Button or the D-pad\n- When saving and quitting\n- When dying\n- When traveling through time (if \"Masks Equippable as Adult\" is activated)",
      "阻止面具在特定情况下自动卸下：\n- 进入新场景时\n- 不在任何 C 键或方向键上时\n- 保存并退出时\n- 死亡时\n- 穿越时间时（若已启用\"面具可在成年装备\"）" },
    { "This option is disabled because \"Customize Behavior\" is turned off or \"Unlimited Playback Time\" is on.",
      "此选项已禁用，因为\"自定义行为\"已关闭或\"无限回放时间\"已开启。" },
    { "This setting is forcefully enabled because a randomized save file with the option \"Skip Scarecrow's Song\" is currently loaded.",
      "此设置被强制启用，因为当前载入的随机化存档启用了\"跳过稻草人之歌\"选项。" },
    { "Pierre appears when an Ocarina is pulled out. Requires learning the Scarecrow's Song first.\n"
      "Without the randomizer option \"Skip Scarecrow's Song\" enabled for a seed, this still requires you "
      "to teach the scarecrow the song as both ages before summoning.",
      "拿出陶笛时皮埃尔会出现。需要先学会稻草人之歌。\n"
      "若种子未启用随机化选项\"跳过稻草人之歌\"，你仍需分别以两个年龄阶段将此歌教给稻草人后方可召唤。" },
    { "Stops the game from freezing the player when picking up Gold Skulltula Tokens. Does not "
      "apply in randomizer savefiles.",
      "拾取金蜘蛛纹章时不再冻结玩家的动作。此设置在随机化存档中不生效。" },
    { "Makes Gold Skulltulas come out of bean patches faster after bugs dig into center.",
      "在虫子钻入豆田中心后，让金蜘蛛更快地从豆田中出现。" },
    { "This setting is forcefully enabled because a randomized savefile with \"Blue Fire Arrows\" is currently loaded.",
      "此设置被强制启用，因为当前载入的随机化存档包含\"蓝色火焰箭\"。" },
    { "This setting is forcefully enabled because a randomized savefile with \"Sunlight Arrows\" enabled is currently loaded.",
      "此设置被强制启用，因为当前载入的随机化存档启用了\"阳光箭\"。" },
    { "This setting is forcefully enabled because a randomizer savefile with \"Sleeping Waterfall: Open\" is loaded.",
      "此设置被强制启用，因为当前载入的随机化存档包含\"沉睡瀑布：开启\"。" },
    { "Turns the Static Image of Link in the Pause Menu's Equipment Subscreen into a model cycling through his idle animations.",
      "将暂停菜单装备子画面中林克的静态图像变为循环播放待机动画的模型。" },
    { "Wearing the Bunny Hood grants a speed and jump boost like in Majora's Mask.\nCan also be limited to only the speed boost.\nThe effects of either option are not accounted for in Randomizer logic.\nAlso disables NPC's reactions to wearing the Bunny Hood.",
      "佩戴兔子帽可获得类似《Majora 的面具》中的速度与跳跃加成。\n也可仅限制为速度加成。\n随机化器逻辑不会考虑任一选项的效果。\n同时禁用 NPC 对佩戴兔子帽的反应。" },
    { "(Select \"Off\" to disable.)",
      "（选择\"关闭\"以禁用。）" },
    { "Allows Link to bounce off walls when linear velocity is high enough, this is relevant when frequently being knocked back by traps, CC, or in Anchor.",
      "当线速度足够高时，允许林克从墙壁弹开。在频繁被陷阱、CC 或 Anchor 击退时相关。" },
    { "Buttons that activate Speed Modifier 1.\n\nIf \"Toggle modifier instead of holding\" is off, hold this combo to apply the modifier.\nIf it is on, tap this combo to toggle the modifier on/off.",
      "激活速度修正器 1 的按键。\n\n若\"切换修正而非按住\"关闭，按住此组合键以应用修正。\n若开启，轻按此组合键以开关修正。" },
    { "Causes your Wallet to fill and empty faster when you gain or lose money.",
      "使你获得或失去金钱时，钱包的填充与清空速度更快。" },
    { "Click to disable N64 mode",
      "点击以禁用 N64 模式" },
    { "Click to reenable aspect correction.",
      "点击以重新启用宽高比校正。" },
    { "Click to reset a console variable that may be causing this.",
      "点击以重置可能导致此问题的控制台变量。" },
    { "Click to resolve",
      "点击以解决" },
    { "Creates a new random seed value to be used when generating a randomizer",
      "创建用于生成随机化器的新随机种子值。" },
    { "Don't scale image to fill window.",
      "不缩放图像以填充窗口。" },
    { "Force aspect ratio:",
      "强制宽高比：" },
    { "Holding down B skips text.",
      "按住 B 键可跳过文本。" },
    { "Prevent forced conversations with Navi and/or other NPCs.",
      "防止娜薇和/或其它 NPC 强制对话。" },
    { "Skip Pickup Messages for Bottle Swipes.",
      "跳过瓶装挥动的拾取提示。" },
    { "Skip Pickup Messages for new Consumable Items.",
      "跳过新消耗品道具的拾取提示。" },

    // ---- Resolution Editor ----
    { "AspectSep", "宽高比" },
    { "AspectRatioCustom", "宽高比自定义" },
    { "MoreResolutionSettings", "更多分辨率设置" },
    { "Enable advanced settings.",
      "启用高级设置。" },
    { "Internal resolution: {} x {}",
      "内部分辨率：{} x {}" },
    { "Viewport dimensions: {} x {}",
      "视口尺寸：{} x {}" },
    { "Original (4:3)", "原版 (4:3)" },
    { "Widescreen (16:9)", "宽屏 (16:9)" },
    { "Nintendo 3DS (5:3)", "任天堂 3DS (5:3)" },
    { "16:10 (8:5)", "16:10 (8:5)" },
    { "Ultrawide (21:9)", "超宽屏 (21:9)" },
    { "Don't scale image to fill window.",
      "不缩放图像以填充窗口。" },
    { "Automatically sets scale factor to fit window. Only available in Pixel Perfect Mode.",
      "自动设置缩放因子以适应窗口。仅在点阵完美模式下可用。" },
    { "Integer scales the image. Only available in Pixel Perfect Mode.",
      "以整数倍缩放图像。仅在点阵完美模式下可用。" },
    { "Override the resolution scale slider and use the settings below, irrespective of window size.",
      "覆盖分辨率缩放滑块，并使用下面的设置，不受窗口大小影响。" },
    { "Prevents integer scaling factor from exceeding screen bounds.\n\nEnabled: Will clamp the scaling factor and display a gentle warning in the resolution editor.\nDisabled: Will allow scaling to exceed screen bounds, for users who want to crop overscan.\n\n  Please note that exceeding screen bounds may show a scroll bar on-screen.",
      "防止整数缩放因子超出屏幕边界。\n\n开启：将限制缩放因子并在分辨率编辑器中显示温和警告。\n关闭：允许缩放超出屏幕边界，供想要裁切过扫描的用户使用。\n\n  请注意，超出屏幕边界可能会在屏幕上显示滚动条。" },
    { "Activates MSAA (multi-sample anti-aliasing) from 2x up to 8x, to smooth the edges of rendered geometry.\nHigher sample count will result in smoother edges on models, but may reduce performance.",
      "启用 2 倍至 8 倍的 MSAA（多重采样抗锯齿），以平滑渲染几何体的边缘。\n采样数越高，模型边缘越平滑，但可能降低性能。" },
    { "Multiplies your output resolution by the value inputted, as a more intensive but effective form of anti-aliasing.",
      "将输出分辨率乘以输入的值，作为一种更耗费资源但有效的抗锯齿形式。" },

    // ---- Misc (Resolution Editor widgets & Randomizer dynamic text) ----
    { "Pixel Count Presets", "像素数量预设" },
    { "Aspect ratio: %.2f:1", "宽高比：%.2f:1" },
    { "Remove this button from the combination", "从组合中移除该按钮" },
    { "Requires Logic Turned On.", "需要开启逻辑。" },
    { "Spoiler File: %s", "剧透文件：%s" },

    // ---- Resolution Editor: graphics/advanced-resolution panel (dynamic & direct-call strings) ----
    { "Aspect Ratio", "宽高比" },
    { "Off", "关闭" },
    { "Custom", "自定义" },
    { "(Select \"Off\" to disable.)", "（选择\"关闭\"以禁用。）" },
    { "Set fixed vertical resolution (disables resolution slider)",
      "设置固定垂直分辨率（禁用分辨率滑块）" },
    { "Horiz. Pixel Count", "水平像素数" },
    { "Vertical Pixel Count", "垂直像素数" },
    { "Integer Scaling Settings", "整数缩放设置" },
    { "Pixel Perfect Mode", "像素完美模式" },
    { "Integer scale factor: {}", "整数缩放倍数：{}" },
    { "Automatically scale image to fit viewport", "自动缩放图像以适应视口" },
    { "Show a horizontal resolution field, instead of aspect ratio.",
      "显示水平分辨率字段，而非宽高比。" },
    { "Prevent integer scaling from exceeding screen bounds.\n(Makes screen bounds take priority over specified factor.)",
      "防止整数缩放超出屏幕边界。\n（使屏幕边界优先于指定倍数。）" },
    { "Allow integer scale factor to go +1 above maximum screen bounds.",
      "允许整数缩放倍数超出最大屏幕边界 1 倍。" },
    { "Click to resolve", "点击以修复" },
    { "Click to reenable aspect correction.", "点击以重新启用宽高比校正。" },
    { "Click to disable N64 mode", "点击以关闭 N64 模式" },
    { "A scroll bar may become visible if screen bounds are exceeded.",
      "如果超出屏幕边界，可能会出现滚动条。" },
    { "Click to reset a console variable that may be causing this.",
      "点击以重置可能导致此问题的控制台变量。" },
    { "Native N64 (240p)", "原生 N64 (240p)" },
    { "2x (480p)", "2 倍 (480p)" },
    { "3x (720p)", "3 倍 (720p)" },
    { "4x (960p)", "4 倍 (960p)" },
    { "5x (1200p)", "5 倍 (1200p)" },
    { "6x (1440p)", "6 倍 (1440p)" },
    { "Full HD (1080p)", "全高清 (1080p)" },
    { "4K (2160p)", "4K (2160p)" },
    // Icon-prefixed warning/info messages (icons must be preserved in both key and value).
    { ICON_FA_EXCLAMATION_TRIANGLE " Significant frame rate (FPS) drops may be occuring.",
      ICON_FA_EXCLAMATION_TRIANGLE " 帧率（FPS）可能出现显著下降。" },
    { ICON_FA_QUESTION_CIRCLE " \"Force aspect ratio\" required.",
      ICON_FA_QUESTION_CIRCLE " 需要\"强制宽高比\"。" },
    { ICON_FA_QUESTION_CIRCLE " If the image is stretched and you don't know why, click this.",
      ICON_FA_QUESTION_CIRCLE " 如果画面被拉伸且不知道原因，请点击此处。" },
    { ICON_FA_QUESTION_CIRCLE " \"N64 Mode\" is overriding these settings.",
      ICON_FA_QUESTION_CIRCLE " \"N64 模式\"正在覆盖这些设置。" },
    { " " ICON_FA_INFO_CIRCLE " A scroll bar may become visible if screen bounds are exceeded.",
      " " ICON_FA_INFO_CIRCLE " 如果超出屏幕边界，可能会出现滚动条。" },

    // ===== Cosmetics Editor : tooltips (auto-wrapped via WrappedText) =====
    { "Revert every element to use their original position and no margins",
      "将所有元素恢复为使用其原始位置且不含边距" },
    { "Using this allow you move the element with General margins sliders",
      "使用此选项可通过通用边距滑块移动元素" },
    { "This will use original intended elements position",
      "这将使用元素的原始预期位置" },
    { "This will make your elements follow the left side of your game window",
      "这将使你的元素贴附在游戏窗口的左侧" },
    { "This will make your elements follow the right side of your game window",
      "这将使你的元素贴附在游戏窗口的右侧" },
    { "This will make your elements to not follow any side\nBetter used for center elements",
      "这将使你的元素不贴附任何一侧\\n更适合居中元素" },
    { "This will make your elements hidden",
      "这将隐藏你的元素" },
    { "This slider is used to move Up and Down your elements.",
      "此滑块用于上下移动你的元素。" },
    { "This slider is used to move Left and Right your elements.",
      "此滑块用于左右移动你的元素。" },
    { "This will set the length of a row of hearts. Set to 0 for unlimited length.",
      "这将设置一行心心的长度。设为 0 表示长度不限。" },
    { "This will make your elements follow the bottom of the life meter",
      "这将使你的元素贴附在生命计量表的底部" },
    { "This will use enemy on screen position",
      "这将使用敌人屏幕上的位置" },
    { "This will make your elements follow the top edge of your game window",
      "这将使你的元素贴附在游戏窗口的上边缘" },
    { "This will make your elements follow the bottom edge of your game window",
      "这将使你的元素贴附在游戏窗口的下边缘" },
    { "This will change the width of the health bar",
      "这将改变生命条的宽度" },
    { "Makes snow fall for December holidays.\nWill reset on restart outside of December 23-25.",
      "让十二月假期时下雪。\\n在 12 月 23–25 日之外重启时将重置。" },
    { "Set when the cosmetics is automaticly randomized:\n- Manual: Manually randomize cosmetics by pressing the 'Randomize all' button\n- On New Scene : Randomizes when you enter a new scene.\n- On Rando Gen Only: Randomizes only when you generate a new randomizer.\n- On File Load: Randomizes on File Load.\n- On File Load (Seeded): Randomizes on file load based on the current randomizer seed/file.",
      "设置外观道具何时被自动随机化：\\n- 手动：按\"全部随机化\"按钮手动随机化外观\\n- 进入新场景：进入新场景时随机化\\n- 仅随机生成时：仅在你生成新的随机种子时随机化\\n- 读取存档时：读取存档时随机化\\n- 读取存档时（带种子）：根据当前随机种子/存档在读取存档时随机化。" },
    { "Some cosmetic options may not apply if you have any mods that provide custom models for the cosmetic option.\n\nFor example, if you have custom Link model, then the Link's Hair color option will most likely not apply.",
      "如果你安装了为某项外观选项提供自定义模型的模组，部分外观选项可能不生效。\\n\\n例如，如果你使用了自定义林克模型，那么林克的发色选项很可能不会生效。" },

    // ===== Audio Editor : tooltips (auto-wrapped via WrappedText) =====
    { "Stop Preview", "停止预览" },
    { "Play Preview", "播放预览" },
    { "Reset to default", "恢复默认" },
    { "Randomize this sound", "随机化此音效" },
    { "Randomizes all unlocked music and sound effects across tab groups",
      "随机化所有标签页组中已解锁的音乐与音效" },
    { "Resets all unlocked music and sound effects across tab groups",
      "重置所有标签页组中已解锁的音乐与音效" },
    { "Locks all music and sound effects across tab groups",
      "锁定所有标签页组中已解锁的音乐与音效" },
    { "Unlocks all music and sound effects across tab groups",
      "解锁所有标签页组中的音乐与音效" },
    { "Disable the low HP beeping sound.",
      "禁用低血量时的嘀嘀声。" },
    { "Disables the voice audio when Navi calls you.",
      "禁用娜薇呼叫你时的语音音效。" },
    { "Sound locked", "音效已锁定" },
    { "Sound unlocked", "音效已解锁" },
    { "Disables the music change when getting close to enemies. Useful for hearing your custom music for each scene more often.",
      "靠近敌人时禁用音乐切换。便于更频繁地听到你为每个场景自定义的配乐。" },
    { "Plays the battle music when getting close to a Leever, like in Majora's Mask.",
      "靠近 Leever 时播放战斗音乐，如同《Majora 的面具》中那样。" },
    { "Disables the volume shifting in the Lost Woods. Useful for hearing your custom music in the Lost Woods if you don't need the navigation assitance the volume changing provides. If toggling this while in the Lost Woods, reload the area for the effect to kick in.",
      "禁用迷失森林中的音量变化。若你不需要音量变化所提供的导航辅助，便可更清楚地听到你在迷失森林中的自定义配乐。若在迷失森林中切换此选项，请重新加载该区域以使效果生效。" },
    { "Emits a notification with the current song name whenever it changes. (does not apply to fanfares or enemy BGM).",
      "每当当前曲目名称变化时发出通知。（不适用于号角声或敌人 BGM。）" },
    { "Set when the music and sound effects is automaticly randomized:\n- Manual: Manually randomize music or sound effects by pressing the 'Randomize all Groups' button\n- On New Scene : Randomizes when you enter a new scene.\n- On Rando Gen Only: Randomizes only when you generate a new randomizer.\n- On File Load: Randomizes on File Load.\n- On File Load (Seeded): Randomizes on file load based on the current randomizer seed/file.",
      "设置音乐与音效何时被自动随机化：\\n- 手动：按\"随机化所有分组\"按钮手动随机化音乐或音效\\n- 进入新场景：进入新场景时随机化\\n- 仅随机生成时：仅在你生成新的随机种子时随机化\\n- 读取存档时：读取存档时随机化\\n- 读取存档时（带种子）：根据当前随机种子/存档在读取存档时随机化。" },
    { "Some custom sequences may have notes that are too high for the game's audio engine to play. Enabling this checkbox will cause these notes to drop a couple of octaves so they can still harmonize with the other notes of the sequence.",
      "部分自定义音序可能含有游戏音频引擎无法播放的过高音符。启用此选项将使这些音符降低几个八度，从而仍能与该音序的其它音符和谐共鸣。" },

    // ===== Gameplay Stats : tooltips (auto-wrapped via WrappedText) =====
    { "Keep track of the timer as an in-game HUD element. The position of the timer can be changed in the Cosmetics Editor.",
      "在游戏内 HUD 元素上记录计时器。计时器的位置可在外观编辑器中更改。" },
    { "Allows a more in-depth perspective of time spent in a certain map.",
      "以更深入的视角查看在特定地图中所花费的时间。" },
    { "Timestamps are relative to starting timestamp rather than in game time, usually necessary for races/speedruns.\n\nStarting timestamp is on first non-C-up input after intro cutscene.\n\nNOTE: THIS NEEDS TO BE SET BEFORE CREATING A FILE TO TAKE EFFECT",
      "时间戳相对于起始时间戳，而非游戏内时间，通常竞速/速通所必需。\\n\\n起始时间戳为过场动画后第一次非 C 上键的输入。\\n\\n注意：必须在创建存档之前设置此项才会生效" },

    // ===== Cosmetics Editor : setting names / slider labels (covered by central label wrap) =====
    { "Let It Snow", "让它下雪" },
    { "Link Body Size", "林克身体尺寸" },
    { "Unfix Goron Spin", "解除格雷旋转锁定" },
    { "Faries Size", "仙女尺寸" },
    { "N64 Logo Spin Speed", "N64 标志旋转速度" },
    { "Moon Size", "月亮尺寸" },
    { "Kak Windmill Speed", "卡卡利科风车速度" },
    { "Color Scheme", "配色方案" },
    { "Sync Rainbow colors", "同步彩虹色" },
    { "Rainbow Speed", "彩虹速度" },
    { "Automatically Randomize All Cosmetics", "自动随机化所有外观" },
    { "Advanced Mode", "高级模式" },
    { "Advanced mode", "高级模式" },
    { "Link Head Scale", "林克头部缩放" },
    { "Link Sword Scale", "林克剑缩放" },
    { "Bunny Hood Length", "兔子帽长度" },
    { "Bunny Hood Spread", "兔子帽展开" },
    { "Goron Neck Length", "格雷颈部长度" },
    { "Randomize All", "全部随机化" },
    { "Reset All", "全部重置" },
    { "Lock All", "全部锁定" },
    { "Unlock All", "全部解锁" },
    { "Rainbow All", "全部彩虹" },
    { "Un-Rainbow All", "全部取消彩虹" },
    { "Give all keys dungeon-specific colors", "为所有钥匙赋予对应迷宫的颜色" },
    { "Reset##EnemyHealthBarWidth", "重置##EnemyHealthBarWidth" },
    { "Reset##Link_BodySize", "重置##Link_BodySize" },
    { "Trails Duration: %d", "拖尾持续时间：%d" },
    { "Reset all positions", "重置所有位置" },
    { "Up <-> Down : %d", "上 <-> 下：%d" },
    { "Left <-> Right : %d", "左 <-> 右：%d" },
    { "Top: %d", "顶部：%d" },
    { "Left: %d", "左侧：%d" },
    { "Right: %d", "右侧：%d" },
    { "Bottle: %d", "底部：%d" },
    { "Heart line length : %d", "心心行长度：%d" },
    { "Health Bar Width: %d", "生命条宽度：%d" },

    // ===== Audio Editor : setting names / slider labels (covered by central label wrap) =====
    { "Mute Low HP Alarm", "静音低血量警报" },
    { "Disable Navi Call Audio", "禁用娜薇呼叫音效" },
    { "Disable Enemy Proximity Music", "禁用敌人接近音乐" },
    { "Enable Enemy Proximity Music for Leever", "为 Leever 启用敌人接近音乐" },
    { "Disable Leading Music in Lost Woods", "禁用迷失森林中的引导音乐" },
    { "Display Sequence Name in Notifications", "在通知中显示音序名称" },
    { "Sequence Notification Duration: %d seconds", "音序通知持续时间：%d 秒" },
    { "Link's Voice Pitch Multiplier", "林克语音音高倍率" },
    { "Automatically Randomize All Music and Sound Effects", "自动随机化所有音乐与音效" },
    { "Lower Octaves of Unplayable High Notes", "降低无法播放的高音符八度" },
    { "Randomize All Groups", "随机化所有分组" },
    { "Reset All Groups", "重置所有分组" },
    { "Lock All Groups", "锁定所有分组" },
    { "Unlock All Groups", "解锁所有分组" },
    { "Exclude All", "全部排除" },
    { "Include All", "全部包含" },
    { "Reset##linkVoiceFreqMultiplier", "重置##linkVoiceFreqMultiplier" },

    // ===== Gameplay Stats : setting names (covered by central label wrap) =====
    { "Show in-game total timer", "显示游戏内总计时器" },
    { "Show latest timestamps on top", "在顶部显示最新时间戳" },
    { "Room Breakdown", "按房间细分" },
    { "RTA Timing on new files", "新存档使用 RTA 计时" },
    { "Show additional detail timers", "显示额外详细计时器" },
    { "Show Debug Info", "显示调试信息" },

    // ===== Direct ImGui static text (wrapped at call site) =====
    { "Move %s", "移动 %s" },
    { "Set Tokens", "设置代币" },
    { "Window Options", "窗口选项" },
    { "Split List Management", "分段列表管理" },
    { "New List Name: ", "新列表名称：" },
    { "Select List to Load: ", "选择要加载的列表：" },
    { "No Enabled Timers...", "没有已启用的计时器……" },
    { "Display Gameplay Timer", "显示游戏内计时器" },
    { "Display Time of Day", "显示当前时间" },
    { "Display Conditional Timer", "显示条件计时器" },
    { "Display Navi Timer", "显示娜薇计时器" },
    { "Platform: Windows", "平台：Windows" },
    { "Platform: iOS", "平台：iOS" },
    { "Platform: macOS", "平台：macOS" },
    { "Platform: Linux", "平台：Linux" },
    { "Platform: Unknown", "平台：未知" },
    { "Status: %0.3f ms/frame (%0.1f FPS)", "状态：%0.3f 毫秒/帧（%0.1f FPS）" },
    { "Note: Gameplay stats are saved to the current file and will be\nlost if you quit without saving.",
      "注意：游戏统计会保存到当前存档，若你未保存就退出将会\\n丢失。" },
    { "General Margins Settings", "通用边距设置" },
    { "Hearts count position", "心心计数位置" },
    { "Magic Meter position", "魔法计量表位置" },
    { "Visual stone of agony position", "痛苦视觉石位置" },
    { "DPad items position", "十字键道具位置" },
    { "Enemy Health Bar position", "敌人生命条位置" },
    { "Lock All Advanced", "锁定全部高级选项" },
    { "Unlock All Advanced", "解锁全部高级选项" },

    // ===== Mod Menu (mod_menu.cpp) =====
    { "Edit", "编辑" },
    { "Cancel", "取消" },
    { "Clear List", "清空列表" },
    { "Enabled Mods", "已启用模组" },
    { "Toggle mods. For graphics mods, this means toggling between default and mod graphics.",
      "切换模组。对于图形模组，即默认图形与模组图形之间的切换。" },
    { "Allows pressing the Tab key to toggle mods", "允许按下 Tab 键来切换模组" },
    { "Disabled because of race lockout", "因竞速锁定已禁用" },

    // ===== Presets (Presets/Presets.cpp) =====
    { "Presets", "预设" },
    { "No presets with rando options. Make some in Settings -> Presets",
      "没有带随机选项的预设。请在「设置 → 预设」中创建。" },
    { "Preset Name", "预设名称" },
    { "Save Settings", "保存设置" },
    { "Save Enhancements", "保存增强" },
    { "Save Audio", "保存音频" },
    { "Save Cosmetics", "保存外观" },
    { "Save Rando Settings", "保存随机设置" },
    { "Save Trackers", "保存追踪器" },
    { "Save Network", "保存网络" },
    { "New Preset", "新建预设" },
    { "Hide built-in presets", "隐藏内置预设" },
    { "No presets found.", "未找到预设。" },
    { "Apply", "应用" },
    { "Apply Preset", "应用预设" },
    // 内置预设名称
    { "Enhancements - Curated First Time Vanilla", "增强 - 精选首次原版体验" },
    { "Enhancements - Curated Randomizer", "增强 - 精选随机化" },
    { "Enhancements - Curated Returning Vanilla", "增强 - 精选重玩原版" },
    { "Enhancements - Reset to Default", "增强 - 恢复默认" },
    { "Rando Seed Settings - Advanced", "随机种子设置 - 进阶" },
    { "Rando Seed Settings - Beginner", "随机种子设置 - 新手" },
    { "Rando Seed Settings - Hell Mode", "随机种子设置 - 地狱模式" },
    { "Rando Seed Settings - Reset to Default", "随机种子设置 - 恢复默认" },
    { "Rando Seed Settings - Standard", "随机种子设置 - 标准" },


    // ===== Message Viewer (debugger/MessageViewer.cpp) =====
    { "Table ID", "表 ID" },
    { "Text ID", "文本 ID" },
    { "Hexadecimal", "十六进制" },
    { "Decimal", "十进制" },
    { "Which language to load from the selected text ID", "从所选文本 ID 加载的语言" },
    { "Language", "语言" },
    { "Display Message##ExistingMessage", "显示消息##ExistingMessage" },
    { "Custom Message", "自定义消息" },
    { "Display Message##CustomMessage", "显示消息##CustomMessage" },
    { "Leave blank for vanilla table", "留空则使用原版表" },
    { "Decimal Text ID of the message to load. Decimal digits only (0-9).",
      "要加载消息的十进制文本 ID。仅限十进制数字（0-9）。" },
    { "Hexadecimal Text ID of the message to load. Hexadecimal digits only (0-9/A-F).",
      "要加载消息的十六进制文本 ID。仅限十六进制数字（0-9/A-F）。" },

    // ===== Anchor Room (Network/Anchor/AnchorRoomWindow.cpp) =====
    { "Players Online: %d", "在线玩家：%d" },
    { "Incompatible version! Will not work together!", "版本不兼容！无法一起游玩！" },
    { "Yours: %s", "你的版本：%s" },
    { "Theirs: %s", "对方的版本：%s" },
    { "Seed mismatch! Continuing will break things!", "种子不匹配！继续将导致问题！" },
    { "Yours: %u", "你的种子：%u" },
    { "Theirs: %u", "对方的种子：%u" },

    // ===== Enemy Randomizer (ExtraModes/EnemyRandomizer.cpp) =====
    { "Enemy Randomizer", "敌人随机化" },
    { "Replaces fixed enemies throughout the game with a random enemy. Bosses, Mini-Bosses and a "
      "few specific regular enemies are excluded.\n"
      "Enemies that need more than Deku Nuts & either Deku Sticks or a sword to kill are excluded "
      "from spawning in \"clear enemy\" rooms.\n\n"
      "- Random: Enemies are randomized every time you load a room.\n"
      "- Random (Seeded): Enemies are randomized based on the current randomizer seed/file.\n",
      "用随机敌人替换游戏中固定的敌人。头目、迷你头目以及少数特定普通敌人除外。\n"
      "需要超过德库核桃且德库木棒或剑才能击杀的敌人，不会在「清空敌人」房间中生成。\n\n"
      "- 随机：每次载入房间时敌人随机化。\n"
      "- 随机（带种子）：根据当前随机种子/存档来随机化敌人。\n" },
    { "Enemies and Bosses spawn with random sizes.", "敌人与头目以随机大小生成。" },
    { "Scales normal enemies Health with their randomized size.\n"
      "*This will NOT affect Bosses!*",
      "普通敌人的生命值随其随机大小缩放。\n"
      "*这不会影响头目！*" },
    { "Randomized Enemy Sizes", "随机敌人大小" },
    { "Scale Health with Size", "生命值随大小缩放" },
    { "Enemy List", "敌人列表" },

    // ===== OTRGlobals.cpp =====
    { "Extracting %s...%s", "正在解包 %s...%s" },

    // ===== Plandomizer (randomizer/Plandomizer.cpp) =====
    { "Gossip Stones", "闲话石" },
    { "Hint Entries", "提示条目" },
    { "Spoiler Log Check Name", "剧透日志检查名" },
    { "Spoiler Log Reward", "剧透日志奖励项" },
    { "Additional Options", "附加选项" },
    { "Spoiler Log Rewards", "剧透日志奖励" },
    { "Load/Save Spoiler Log", "载入/保存剧透日志" },
    { "No Spoiler Logs found.", "未找到剧透日志。" },
    { "Load", "载入" },
    { "Save", "保存" },
    { "Current Seed Hash", "当前种子哈希" },
    { "No Spoiler Log Loaded", "未载入剧透日志" },
    { "Please Load Spoiler Data...", "请载入剧透数据……" },
    { "Clear All Hints", "清空所有提示" },
    { "Randomize All Hints", "随机化所有提示" },
    { "Empty All Rewards", "清空所有奖励" },
    { "Current Hint: ", "当前提示：" },
    { "Resources", "资源" },
    { "Name: ", "名称：" },
    { "New Hint:     ", "新提示：" },
    { "Randomize Hint", "随机化提示" },

    // ===== Randomizer Trackers (check/entrance/item) =====
    { "Enable Dragging", "启用拖拽" },
    { "Only Enable While Paused", "仅暂停时启用" },
    { "Display Mode", "显示模式" },
    { "Combo Button 1", "组合键按钮 1" },
    { "Combo Button 2", "组合键按钮 2" },
    // item tracker
    { "Inventory", "背包" },
    { "Circle display", "圆形显示" },
    { "Songs", "歌曲" },
    { "Horizontal display", "横向显示" },
    { "Maps and compasses", "地图与指南针" },
    { "Checks: %d/%d", "检查：%d/%d" },
    { "Total Checks", "检查总数" },
    { "Customize what the numbers under each item are tracking.\n\nNote: items without capacity upgrades will track ammo even in capacity mode",
      "自定义每个物品下方数字所追踪的内容。\n\n注意：没有容量升级的物品即使在容量模式下也会追踪弹药。" },
    { "Customize what numbers are shown for key tracking.", "自定义钥匙追踪所显示的数字。" },
    { "Customize what numbers are shown for triforce piece tracking.", "自定义三角力量碎片追踪所显示的数字。" },
    { "Shows an 'H' or an 'L' to more easily distinguish between Hookshot and Longshot.",
      "显示「H」或「L」以更容易区分钩索与长钩索。" },
    // entrance tracker
    { "Highlight previous", "高亮上一个" },
    { "Highlight available", "高亮可用" },
    { "Hide undiscovered", "隐藏未发现" },
    { "Hide reverse", "隐藏反向" },
    { "Show Source", "显示来源" },
    { "Show Destination", "显示目的地" },
    { "Sort entrances by the original source entrance", "按原始来源入口对入口排序" },
    { "Sort entrances by the overrided destination", "按覆盖后的目的地对入口排序" },
    { "Highlight the previous entrance that Link came from", "高亮林克来时的上一个入口" },
    { "Highlight available entrances in the current scene", "高亮当前场景中的可用入口" },
    { "Collapse undiscovered entrances towards the bottom of each group", "将未发现的入口折叠到各组底部" },
    { "Hide reverse entrance transitions when Decouple Entrances is off", "当「解耦入口」关闭时隐藏反向入口转换" },
    { "Reveal the source for undiscovered entrances", "揭示未发现入口的来源" },
    { "Reveal the destination for undiscovered entrances", "揭示未发现入口的目的地" },
    { "The entrance tracker will only track shuffled entrances", "入口追踪器仅追踪已洗牌的入口" },
    { "Sort By", "排序方式" },
    { "List Items", "列表项" },
    { "Group By", "分组方式" },
    { "Spoiler Reveal", "剧透揭示" },
    { "Legend", "图例" },
    // check tracker
    { "Font Size", "字体大小" },
    { "Filter Empty Areas", "过滤空白区域" },
    { "Hidden Items Toggle", "隐藏物品开关" },
    { "Available Checks Toggle", "可用检查开关" },
    { "Expand/Collapse Buttons", "展开/折叠按钮" },
    { "Search Input", "搜索框" },
    { "Check Totals", "检查总数" },
    { "Sets the font size used in the check tracker.", "设置检查追踪器中使用的字体大小。" },
    { "If enabled, Vanilla/MQ dungeons will show on the tracker immediately. "
      "Otherwise, Vanilla/MQ dungeon locations must be unlocked.",
      "若启用，原版/MQ 迷宫将立即在追踪器中显示。否则，原版/MQ 迷宫位置必须被解锁。" },
    { "If enabled, will prevent the tracker from displaying slots with non-shop-item shuffles.",
      "若启用，将阻止追踪器显示非商店物品洗牌的槽位。" },
    { "If enabled, will show GS locations in the tracker regardless of tokensanity settings.",
      "若启用，无论代币理智设置如何，都会在追踪器中显示 GS 位置。" },
    { "If enabled, will show a check's logic when hovering over it.", "若启用，悬停在检查上时将显示其逻辑。" },
    { "If enabled, will show the checks that are available to be collected "
      "with your current progress.",
      "若启用，将显示基于当前进度可收集的检查。" },
    { "Waiting for file load...", "等待载入存档……" },
    { "Tracker Header Visibility", "追踪器标题可见性" },

    // ===== Input Viewer (controls/InputViewer.cpp) =====
    { "Show Background Layer", "显示背景层" },
    { "Use for all buttons", "用于所有按钮" },
    { "Show A-Button Layers", "显示 A 按钮图层" },
    { "Show B-Button Layers", "显示 B 按钮图层" },
    { "Show C-Down Layers", "显示 C 下按钮图层" },
    { "Show C-Left Layers", "显示 C 左按钮图层" },
    { "Show C-Right Layers", "显示 C 右按钮图层" },
    { "Show C-Up Layers", "显示 C 上按钮图层" },
    { "Show D-Pad Layers", "显示十字键图层" },
    { "Show L-Button Layers", "显示 L 按钮图层" },
    { "Show Modifier Button 1 Layers", "显示修饰键 1 图层" },
    { "Show Modifier Button 2 Layers", "显示修饰键 2 图层" },
    { "Show R-Button Layers", "显示 R 按钮图层" },
    { "Show Start Button Layers", "显示 Start 按钮图层" },
    { "Show Z-Button Layers", "显示 Z 按钮图层" },
    { "Show Analog Stick Angle Values", "显示摇杆角度值" },
    { "Highlight Walking Speed Angles", "高亮行走速度角度" },
    { "Sets the on screen size of the input viewer", "设置输入查看器在屏幕上的大小。" },
    { "Sets the desired visibility behavior for the button outline/background layers. Useful for "
      "custom input viewers.",
      "设置按钮轮廓/背景图层的可见性行为。适用于自定义输入查看器。" },
    { "Sets the distance to move the analog stick in the input viewer. Useful for "
      "custom input viewers.",
      "设置输入查看器中左摇杆的移动距离。适用于自定义输入查看器。" },
    { "Sets the distance to move the right stick in the input viewer. Useful for "
      "custom input viewers.",
      "设置输入查看器中右摇杆的移动距离。适用于自定义输入查看器。" },
    { "Displays analog stick angle values in the input viewer", "在输入查看器中显示摇杆角度值。" },
    { "Highlights the angle value text when the analog stick is in ESS position (on flat ground)",
      "当摇杆处于 ESS 位置（平地）时高亮角度值文本。" },
    { "Highlights the angle value text when the analog stick is at an angle that would "
      "produce a walking speed (on flat ground)\n\n"
      "Useful for 1.0 Empty Jumpslash Quick Put Away",
      "当摇杆处于会产生行走速度的角度（平地）时高亮角度值文本。\n\n"
      "适用于 1.0 空挥斩快速收刀。" },
    { "Buttons", "按钮" },
    { "X: %-3d  Y: %-3d", "X：%-3d  Y：%-3d" },

    // ===== Input Editor (controls/SohInputEditorWindow.cpp) =====
    { "Keyboard", "键盘" },
    { "Mouse", "鼠标" },
    { "Gamepad (SDL)", "游戏手柄 (SDL)" },
    { "Link (P1)", "林克 (P1)" },
    { "Ivan (P2)", "伊万 (P2)" },
    { "Port %d", "端口 %d" },
    { "Set Defaults", "恢复默认" },
    { "Set Defaults for Keyboard", "恢复键盘默认" },
    { "Set Defaults for Gamepad (SDL)", "恢复游戏手柄 (SDL) 默认" },
    { "D-Pad", "十字键" },
    { "Analog Stick", "模拟摇杆" },
    { "Analog Stick Options", "模拟摇杆选项" },
    { "Dpad Ocarina Playback", "十字键陶笛演奏" },
    { "This option has been disabled because only one type of O2R has been loaded",
      "此选项已被禁用，因为只载入了一种类型的 O2R" },
    { "Loach hint is only avaliable with \"Fishsanity\" set to \"Shuffle only Hyrule Loach\"\n"
      "as that's the only setting where you present the loach to the fishing pond owner.",
      "仅在\"Fishsanity\"设为\"仅洗牌海拉鲁鲫鱼\"时才有钓翁提示，\n"
      "因为只有在该设定下你才会把鲫鱼交给钓鱼池主人。" },
    { "Malon's hint points to a cow, so requires cows to be shuffled.",
      "玛隆的提示指向一头奶牛，因此需要开启奶牛洗牌。" },
    { "This option is disabled since the fishing pole is not shuffled.",
      "此选项已被禁用，因为钓鱼竿未加入洗牌。" },
    { "There is no point to hinting 100 skulls if it is not shuffled.",
      "如果 100 个骷髅未加入洗牌，就没有提示它们的必要。" },
    { "This option is disabled because \"Dungeon Rewards\" are shuffled to \"End of Dungeons\".",
      "此选项已被禁用，因为「地牢奖励」已被洗牌到「地牢末尾」。" },
    { "Enables free look camera control\nNote: You must remap C buttons off of the right stick in the "
      "controller config menu, and map the camera stick to the right stick.\n"
      "Doesn't work in areas were the game locks the camera.\n"
      "Scene reload may be necessary to enable.",
      "启用自由视角摄像机控制。\n注意：你必须在控制器配置菜单中将 C 键从右摇杆移开，\n"
      "并将摄像机摇杆映射到右摇杆。\n在游戏锁定摄像机的区域无法生效。\n"
      "可能需要重新载入场景才能生效。" },
    { "Always Shown", "始终显示" },
    { "Shown Only While Not Pressed", "仅在未按下时显示" },
    { "Shown Only While Pressed", "仅在按下时显示" },
    { "Always Hidden", "始终隐藏" },
    { "When Medallions are collected, the Medallion imprints around the Master Sword Pedestal in the Temple "
      "of Time will become colored-in.",
      "当收集到徽章后，时之神庙中圣剑基座周围的徽章印记将被填色显示。" },
    { "Add a button to the combination", "为组合添加一个按键" },
    { "This option is disabled due to other options making the game unbeatable.",
      "此选项已被禁用，因为其他选项会导致游戏无法通关。" },
    { "Preserve the minimap visibility state when going between areas rather than default it to \"on\" "
      "when going through loading zones.",
      "在区域间切换时保留小地图的可见状态，而非在进入读盘区域时将其默认设为\"开\"。" },
    { "Forced off because Right Stick Aiming is disabled.", "因「右摇杆瞄准」已禁用而被强制关闭。" },
    { "Additional (\"Right\") Stick", "额外（「右」）摇杆" },
    { "Input Viewer Scale: %.2f", "输入显示器缩放：%.2f" },
    { "Button Outlines/Backgrounds", "按键描边/背景" },
    { "Analog Stick Visibility", "模拟摇杆可见性" },
    { "Analog Stick Outline/Background Visibility", "模拟摇杆描边/背景可见性" },
    { "Analog Stick Movement: %dpx", "模拟摇杆位移：%d 像素" },
    { "Right Stick Visibility", "右摇杆可见性" },
    { "Right Stick Outline/Background Visibility", "右摇杆描边/背景可见性" },
    { "Right Stick Movement: %dpx", "右摇杆位移：%d 像素" },
    { "Determines the conditions under which the moving layer of the analog stick texture is visible.",
      "决定模拟摇杆贴图的活动层在何种条件下可见。" },
    { "Determines the conditions under which the analog stick outline/background texture is visible.",
      "决定模拟摇杆描边/背景贴图在何种条件下可见。" },
    { "Determines the conditions under which the moving layer of the right stick texture is visible.",
      "决定右摇杆贴图的活动层在何种条件下可见。" },
    { "Determines the conditions under which the right stick outline/background texture is visible.",
      "决定右摇杆描边/背景贴图在何种条件下可见。" },
    { "Enable Mods", "启用 Mod" },
    { "Mods Tab Hotkey", "Mod 标签快捷键" },
    { "Already editing...", "已在编辑中……" },
    // 下拉框选项值（combobox 内部对选项值不套 L()，InputViewer 调用处已用翻译副本）
    { "Always", "总是" },
    { "Never", "从不" },
    { "While In Use", "使用时" },
    { "Mods are currently not reloaded at runtime. Close and re-open Ship for the changes to take effect.\n"
      "Drag ordering for the enabled list is available.\nMod priority is top to bottom. They override mods listed "
      "below them.",
      "Mod 当前不会在运行时重新加载。请关闭并重新打开 Ship 以使更改生效。\n"
      "已启用的列表支持拖拽排序。\nMod 优先级由上到下，靠上的会覆盖其下方的 Mod。" },
    { "Rumble", "震动" },
    { "Gyro", "陀螺仪" },
    { "LEDs", "LED" },
    { "Modifier Buttons", "修饰键" },
    { "Ocarina Controls", "陶笛控制" },
    { "Camera Controls", "相机控制" },
    { "D-Pad Controls", "十字键控制" },
    { "Press any button,\nmove any axis,\nor press any key\nto add mapping",
      "按下任意按钮、\n移动任意轴、\n或按下任意键\n以添加映射" },
    { "Press any button,\nmove any axis,\nor press any key\nto edit mapping",
      "按下任意按钮、\n移动任意轴、\n或按下任意键\n以编辑映射" },
    { "Axis Threshold\n\nThe extent to which the joystick\nmust be moved or the trigger\npressed to initiate the assigned\nbutton action.",
      "轴阈值\n\n摇杆需移动、或扳机需按下的程度，\n以触发所分配的\n按钮动作。" },
    { "Sensitivity:", "灵敏度：" },
    { "Deadzone:", "死区：" },
    { "Notch Snap Angle:", "凹槽吸附角度：" },
    { "Trigger axis threshold:", "扳机轴阈值：" },
    { "Stick axis threshold:", "摇杆轴阈值：" },
    { "Press any button\nor move any axis\nto add rumble device", "按下任意按钮\n或移动任意轴\n以添加震动设备" },
    { "Press any button\nor move any axis\nto add LED device", "按下任意按钮\n或移动任意轴\n以添加 LED 设备" },
    { "Press any button\nor move any axis\nto add gyro device", "按下任意按钮\n或移动任意轴\n以添加陀螺仪设备" },
    { "LED Color:", "LED 颜色：" },
    { "Custom Color", "自定义颜色" },
    { "Small Motor Intensity:", "小马达强度：" },
    { "Large Motor Intensity:", "大马达强度：" },
    { "Edit axis threshold", "编辑轴阈值" },
    { "Notes", "说明" },
    { "Disable song detection", "禁用歌曲检测" },
    { "Pitch", "音高" },
    { "Clear All", "全部清除" },
    { "Set defaults", "恢复默认" },
    { "Recalibrate", "重新校准" },
    { "Customize Ocarina Controls", "自定义陶笛控制" },
    { "Right Stick Aiming", "右摇杆瞄准" },
    { "Allow moving while in first-person mode", "允许在第一人称模式下移动" },
    { "Invert Aiming X Axis", "反转瞄准 X 轴" },
    { "Invert Aiming Y Axis", "反转瞄准 Y 轴" },
    { "Invert Shield Aiming X Axis", "反转盾牌瞄准 X 轴" },
    { "Invert Shield Aiming Y Axis", "反转盾牌瞄准 Y 轴" },
    { "Invert Z-Weapon Aiming Y Axis", "反转 Z 武器瞄准 Y 轴" },
    { "Disable Auto-Centering in First-Person View", "禁用第一人称视角自动居中" },
    { "Enable Custom Aiming/First-Person sensitivity", "启用自定义瞄准/第一人称灵敏度" },
    { "Invert Camera X Axis", "反转相机 X 轴" },
    { "Invert Camera Y Axis", "反转相机 Y 轴" },
    { "D-pad hold change", "十字键长按变更" },
    { "Critical Health Override", "危险生命值覆盖" },
    { "Source", "来源" },
    { "Brightness: %.1f %%", "亮度：%.1f %%" },
    { "Aiming/First-Person Vertical Sensitivity: %.0f %%", "瞄准/第一人称垂直灵敏度：%.0f %%" },
    { "Third-Person Horizontal Sensitivity: %.0f %%", "第三人称水平灵敏度：%.0f %%" },
    { "Right Stick Ocarina Playback", "右摇杆陶笛演奏" },
    { "D-pad Support on Pause Screen", "暂停界面十字键支持" },
    { "D-pad Support in Text Boxes", "文本框内十字键支持" },
    { "Allows for aiming with the right stick in:\n-First-Person/C-Up view\n-Weapon Aiming",
      "允许用右摇杆瞄准：\n-第一人称/C-U 视角\n-武器瞄准" },
    { "Changes the left stick to move the player while in first-person mode", "更改左摇杆以在第一人称模式下移动玩家" },
    { "Inverts the Camera X Axis in:\n-First-Person/C-Up view\n-Weapon Aiming",
      "反转相机 X 轴：\n-第一人称/C-U 视角\n-武器瞄准" },
    { "Inverts the Camera Y Axis in:\n-First-Person/C-Up view\n-Weapon Aiming",
      "反转相机 Y 轴：\n-第一人称/C-U 视角\n-武器瞄准" },
    { "Inverts the Shield Aiming X Axis", "反转盾牌瞄准 X 轴" },
    { "Inverts the Shield Aiming Y Axis", "反转盾牌瞄准 Y 轴" },
    { "Inverts the Camera Y Axis in:\n-Z-Weapon Aiming", "反转相机 Y 轴：\n-Z 武器瞄准" },
    { "Prevents the C-Up view from auto-centering, allowing for Gyro Aiming", "阻止 C-U 视角自动居中，以便进行陀螺仪瞄准" },
    { "Inverts the Camera X Axis in:\n-Free look", "反转相机 X 轴：\n-自由视角" },
    { "Inverts the Camera Y Axis in:\n-Free look", "反转相机 Y 轴：\n-自由视角" },
    { "Enable Mouse Controls", "启用鼠标控制" },
    { "Auto Capture Mouse Input", "自动捕获鼠标输入" },
    { "Aiming/First-Person Camera", "瞄准/第一人称相机" },
    { "Third-Person Camera", "第三人称相机" },
    { "Free Look", "自由视角" },
    { "D-Pad Options", "十字键选项" },
    { "Third-Person Vertical Sensitivity: %.0f %%", "第三人称垂直灵敏度：%.0f %%" },
    { "Camera Distance: %d", "相机距离：%d" },
    { "Camera Transition Speed: %d", "相机过渡速度：%d" },
    { "The cursor will only move a single space no matter how long a D-pad direction is held",
      "无论十字键方向按住多久，光标只移动一格" },
    { "Health\n- Red when health critical (13-20% depending on max health)\n- Yellow when health < 40%. Green otherwise.\n\n"
      "Tunics: colors will mirror currently equipped tunic, whether original or the current values in Cosmetics Editor.\n\n"
      "Custom: single, solid color",
      "生命值\n- 生命危急时（取决于最大生命值的 13-20%）为红色\n- 生命值低于 40% 时为黄色，否则为绿色。\n\n"
      "外套：颜色将镜像当前装备的外套，无论是原版还是在外观编辑器中的当前值。\n\n"
      "自定义：单一纯色" },
    { "Sets the brightness of controller LEDs. 0% brightness = LEDs off.", "设置控制器 LED 的亮度。0% 亮度 = LED 关闭。" },
    { "When Mouse Controls are enabled, this toggles whether the program will automatically "
      "hide the cursor and capture mouse input when closing the menu.",
      "启用鼠标控制时，此选项切换程序在关闭菜单时是否自动隐藏光标并捕获鼠标输入。" },
    { "Navigate Pause with the D-pad\nIf used with \"D-pad as Equip Items\", you must hold "
      "C-Up to equip instead of navigate",
      "用十字键在暂停菜单导航\n若与「十字键作为装备物品」配合使用，必须按住 C-Up 进行装备而非导航" },
    { "Navigate choices in text boxes, shop item selection, and the file select / name entry "
      "screens with the D-pad",
      "用十字键在文本框、商店物品选择以及读档/命名界面中导航选项" },
    { "Override redundant for health source.", "对于生命值来源此覆盖项冗余。" },
    { "This will clear all mappings for port %d.\n\nContinue?", "这将清除端口 %d 上的所有映射。\n\n继续？" },
    { "This will clear all existing mappings for\nKeyboard on port %d.\n\nContinue?",
      "这将清除端口 %d 上键盘的\n所有现有映射。\n\n继续？" },
    { "This will clear all existing mappings for\nGamepad (SDL) on port %d.\n\nContinue?",
      "这将清除端口 %d 上\n游戏手柄（SDL）的所有现有映射。\n\n继续？" },
    // 追踪器 / 输入编辑器 / 联机等窗口补充
    { "Close", "关闭" },
    { "Add rumble device", "添加震动设备" },
    { "Add LED device", "添加 LED 设备" },
    { "Add gyro device", "添加陀螺仪设备" },
    { "Analog Angle Values", "摇杆角度数值" },
    { "%d Undiscovered", "%d 个未发现" },
    { "Auto scroll", "自动滚动" },
    { "Align count to left side", "计数左对齐" },
    { "Apply & Close", "应用并关闭" },
    { "Automatically scroll to the first available entrance in the current scene",
      "自动滚动到当前场景中第一个可用的入口" },
    { "Group entrances by their area", "按区域分组入口" },
    { "Group entrances by their entrance type", "按入口类型分组入口" },
    { "Customize what the numbers under each item are tracking."
      "\n\nNote: items without capacity upgrades will track ammo even in capacity mode",
      "自定义每个物品下方数字所追踪的内容。"
      "\n\n注意：没有容量升级的物品即使在容量模式下也会追踪弹药" },
    { "If enabled, will hide area headers that have no locations matching filter",
      "启用后，将隐藏没有与筛选条件匹配位置的区域标题" },
    { "Sets the distance to move the analog stick in the input viewer. Useful for custom "
      "input viewers.",
      "设置输入查看器中摇杆的移动距离。适用于自定义输入查看器。" },
    { "Health\n- Red when health critical (13-20% depending on max health)\n- Yellow when "
      "health < 40%. Green otherwise.\n\n"
      "Tunics: colors will mirror currently equipped tunic, whether original or the current "
      "values in Cosmetics Editor.\n\n"
      "Custom: single, solid color",
      "生命值\n- 生命危急时为红色（依最大生命值为 13-20%）\n- 生命值低于 40% 时为黄色，其余为绿色。\n\n"
      "服装：颜色会跟随当前所穿服装，无论是原始颜色还是外观编辑器中的当前值。\n\n"
      "自定义：单一纯色" },
    { "Allows for using the mouse to control the camera (must enable Free Look), "
      "aim with the shield, and perform quickspin attacks (quickly rotate the mouse then press B)\n"
      "Press F2 to toggle mouse capture manually.",
      "允许使用鼠标控制摄像机（须启用自由视角）、用盾牌瞄准，以及执行快速旋转攻击（快速转动鼠标后按 B）\n"
      "按 F2 手动切换鼠标捕获。" },

    // ===========================================================================
    //  Gameplay Stats window (gameplaystats.cpp)
    // ===========================================================================
    { "Git Branch:", "Git 分支：" },
    { "Git Commit Hash:", "Git 提交哈希：" },
    { "Build Version:", "构建版本：" },
    { "Total Time (RTA):", "总时间（RTA）：" },
    { "Total Game Time:", "游戏总时间：" },
    { "Gameplay Time:", "游戏内时间：" },
    { "Pause Menu Time:", "暂停菜单时间：" },
    { "Time in scene:", "场景内时间：" },
    { "Time in room:", "房间内时间：" },
    { "play->sceneNum:", "play->sceneNum：" },
    { "gSaveContext.entranceIndex:", "gSaveContext.entranceIndex：" },
    { "gSaveContext.cutsceneIndex:", "gSaveContext.cutsceneIndex：" },
    { "play->roomCtx.curRoom.num:", "play->roomCtx.curRoom.num：" },
    { "Enemies Defeated:", "击败敌人：" },
    { "Enemy Details...", "敌人详情……" },
    { "Rupees Collected:", "收集卢比：" },
    { "Rupees Spent:", "花费卢比：" },
    { "Chests Opened:", "开启宝箱：" },
    { "Ammo Used:", "使用弹药：" },
    { "Ammo Details...", "弹药详情……" },
    { "Damage Taken:", "受到伤害：" },
    { "Sword Swings:", "挥剑次数：" },
    { "Steps Taken:", "行走步数：" },
    { "Bunny Hood Time:", "兔耳头巾时间：" },
    { "Rolls:", "翻滚次数：" },
    { "Bonks:", "撞头次数：" },
    { "Sidehops:", "侧跳次数：" },
    { "Backflips:", "后空翻次数：" },
    { "Ice Traps:", "冰陷阱：" },
    { "Pauses:", "暂停次数：" },
    { "Pots Smashed:", "砸碎花盆：" },
    { "Bushes Cut:", "砍断灌木：" },
    { "Buttons Pressed:", "按键次数：" },
    { "Buttons...", "按键……" },
    { "Room", "房间" },
    { "Includes rupees collected with a full wallet.", "包含钱包已满时收集的卢比。" },
    { "Show in-game total timer", "在游戏内显示总计时器" },
    { "Show latest timestamps on top", "最新时间戳置顶显示" },
    { "Room Breakdown", "房间细分" },
    { "RTA Timing on new files", "新存档使用 RTA 计时" },
    { "Show additional detail timers", "显示额外详细计时器" },
    { "Show Debug Info", "显示调试信息" },
    { "Timestamps", "时间戳" },
    { "Counts", "计数" },
    { "Breakdown", "细分" },
    { "Options", "选项" },
    { "Note: Gameplay stats are saved to the current file and will be\nlost if you quit without saving.",
      "注意：游戏统计会保存到当前存档，若退出时未保存将会丢失。" },
    { "Keep track of the timer as an in-game HUD element. The position of the "
      "timer can be changed in the Cosmetics Editor.",
      "将计时器作为游戏内 HUD 元素显示。计时器位置可在外观编辑器中更改。" },
    { "Allows a more in-depth perspective of time spent in a certain map.",
      "以更深入的视角查看在某个地图中所花费的时间。" },
    { "Timestamps are relative to starting timestamp rather than in game time, "
      "usually necessary for races/speedruns.\n\n"
      "Starting timestamp is on first non-C-up input after intro cutscene.\n\n"
      "NOTE: THIS NEEDS TO BE SET BEFORE CREATING A FILE TO TAKE EFFECT",
      "时间戳以起始时间戳而非游戏内时间为基准，通常用于竞速/速通。\n\n"
      "起始时间戳为开场过场后首次非 C 键向上的输入。\n\n"
      "注意：需在创建存档前设置才能生效" },

    // ---- Gameplay Stats: enemy/ammo/button count labels (countMappings) ----
    { "Anubis:", "阿努比斯：" },
    { "Armos:", "阿摩斯：" },
    { "Arwing:", "阿尔温：" },
    { "Bari:", "巴力：" },
    { "Beamos:", "比莫斯：" },
    { "Big Octo:", "大章鱼：" },
    { "Biri:", "比力：" },
    { "Bubble (Green):", "泡泡（绿）：" },
    { "Bubble (Blue):", "泡泡（蓝）：" },
    { "Bubble (White):", "泡泡（白）：" },
    { "Bubble (Red):", "泡泡（红）：" },
    { "Business Scrub:", "商人德库：" },
    { "Dark Link:", "暗林克：" },
    { "Dead Hand:", "死亡之手：" },
    { "Deku Baba:", "德库芭芭：" },
    { "Deku Baba (Big):", "德库芭芭（大）：" },
    { "Deku Scrub:", "德库史克：" },
    { "Dinolfos:", "迪诺尔夫：" },
    { "Dodongo:", "多东哥：" },
    { "Dodongo (Baby):", "多东哥（幼）：" },
    { "Door Mimic:", "门之拟态：" },
    { "Flare Dancer:", "烈焰舞者：" },
    { "Floormaster:", "地板大师：" },
    { "Flying Pot:", "飞行壶：" },
    { "Flying Floor Tile:", "飞行地板：" },
    { "Freezard:", "冰怪：" },
    { "Gerudo Thief:", "格鲁多盗贼：" },
    { "Gibdo:", "吉布多：" },
    { "Gohma Larva:", "哥马幼虫：" },
    { "Guay:", "呱依：" },
    { "Iron Knuckle:", "铁拳：" },
    { "Iron Knuckle (Nab):", "铁拳（娜柏茹）：" },
    { "Keese:", "奇斯：" },
    { "Keese (Fire):", "奇斯（火）：" },
    { "Keese (Ice):", "奇斯（冰）：" },
    { "Leever:", "利弗：" },
    { "Leever (Big):", "利弗（大）：" },
    { "Like-Like:", "莱克莱克：" },
    { "Lizalfos:", "利扎尔夫：" },
    { "Mad Scrub:", "疯狂史克：" },
    { "Moblin:", "莫布林：" },
    { "Moblin (Club):", "莫布林（棍棒）：" },
    { "Octorok:", "章鱼怪：" },
    { "Parasitic Tentacle:", "寄生触手：" },
    { "Peahat:", "皮哈特：" },
    { "Peahat Larva:", "皮哈特幼虫：" },
    { "Poe:", "波克：" },
    { "Poe (Big):", "波克（大）：" },
    { "Poe (Composer):", "波克（作曲者）：" },
    { "Poe Sisters:", "波克四姐妹：" },
    { "Redead:", "瑞迪德：" },
    { "Shabom:", "沙邦：" },
    { "Shell Blade:", "贝壳刃：" },
    { "Skulltula:", "骷髅蜘蛛：" },
    { "Skulltula (Big):", "骷髅蜘蛛（大）：" },
    { "Skulltula (Gold):", "骷髅蜘蛛（金）：" },
    { "Skullwalltula:", "墙骷髅蜘蛛：" },
    { "Skull Kid:", "斯克比德：" },
    { "Spike:", "尖刺：" },
    { "Stalchild:", "骷髅童：" },
    { "Stalfos:", "斯陶夫：" },
    { "Stinger:", "刺刺：" },
    { "Tailpasaran:", "尾帕萨兰：" },
    { "Tektite (Blue):", "忒克泰特（蓝）：" },
    { "Tektite (Red):", "忒克泰特（红）：" },
    { "Torch Slug:", "火把蛞蝓：" },
    { "Wallmaster:", "墙之主：" },
    { "Withered Deku Baba:", "枯萎德库芭芭：" },
    { "Wolfos:", "沃尔夫斯：" },
    { "Wolfos (White):", "沃尔夫斯（白）：" },
    { "Deku Sticks:", "德库木棒：" },
    { "Deku Nuts:", "德库坚果：" },
    { "Bombs:", "炸弹：" },
    { "Arrows:", "箭：" },
    { "Deku Seeds:", "德库种子：" },
    { "Bombchus:", "炸弹鼠：" },
    { "Beans:", "魔法豆：" },
    { "A:", "A：" },
    { "B:", "B：" },
    { "L:", "L：" },
    { "R:", "R：" },
    { "Z:", "Z：" },
    { "C-Up:", "C上：" },
    { "C-Right:", "C右：" },
    { "C-Down:", "C下：" },
    { "C-Left:", "C左：" },
    { "D-Up:", "D上：" },
    { "D-Right:", "D右：" },
    { "D-Down:", "D下：" },
    { "D-Left:", "D左：" },
    { "Start:", "开始：" },

    // ---- Gameplay Stats: scene names (sceneMappings) ----
    { "Inside the Deku Tree", "德库树内部" },
    { "Dodongo's Cavern", "多东哥洞穴" },
    { "Inside Jabu-Jabu's Belly", "加卜加卜腹内" },
    { "Forest Temple", "森林神殿" },
    { "Fire Temple", "火之神殿" },
    { "Water Temple", "水之神殿" },
    { "Spirit Temple", "魂之神殿" },
    { "Shadow Temple", "暗之神殿" },
    { "Bottom of the Well", "井底" },
    { "Ice Cavern", "冰之洞窟" },
    { "Ganon's Tower", "盖侬塔" },
    { "Gerudo Training Ground", "格鲁德训练场" },
    { "Thieves' Hideout", "盗贼藏身处" },
    { "Inside Ganon's Castle", "盖侬城堡内部" },
    { "Tower Collapse", "高塔崩塌" },
    { "Castle Collapse", "城堡崩塌" },
    { "Treasure Box Shop", "宝箱商店" },
    { "Gohma's Lair", "哥马巢穴" },
    { "King Dodongo's Lair", "多东哥王巢穴" },
    { "Barinade's Lair", "巴林内德巢穴" },
    { "Phantom Ganon's Lair", "幻影盖侬巢穴" },
    { "Volvagia's Lair", "沃沃基亚巢穴" },
    { "Morpha's Lair", "莫尔法巢穴" },
    { "Twinrova's Lair", "孪生洛娃巢穴" },
    { "Bongo Bongo's Lair", "邦戈邦戈巢穴" },
    { "Ganondorf's Lair", "盖侬道夫巢穴" },
    { "Ganon's Lair", "盖侬巢穴" },
    { "Market Entrance (Day)", "市场入口（白天）" },
    { "Market Entrance (Night)", "市场入口（夜晚）" },
    { "Market Entrance (Adult)", "市场入口（成人）" },
    { "Back Alley (Day)", "后巷（白天）" },
    { "Back Alley (Night)", "后巷（夜晚）" },
    { "Market (Day)", "市场（白天）" },
    { "Market (Night)", "市场（夜晚）" },
    { "Market (Adult)", "市场（成人）" },
    { "Outside ToT (Day)", "时之殿外（白天）" },
    { "Outside ToT (Night)", "时之殿外（夜晚）" },
    { "Outside ToT (Adult)", "时之殿外（成人）" },
    { "Know-It-All Bros' House", "万事通兄弟之家" },
    { "Twins' House", "双胞胎之家" },
    { "Mido's House", "米多之家" },
    { "Saria's House", "萨莉亚之家" },
    { "Carpenter Boss's House", "木工头目之家" },
    { "Man in Green's House", "绿衣人之家" },
    { "Bazaar", "集市" },
    { "Kokiri Shop", "科克里商店" },
    { "Goron Shop", "格雷商店" },
    { "Zora Shop", "卓拉商店" },
    { "Kakariko Potion Shop", "卡卡利科药水店" },
    { "Market Potion Shop", "市场药水店" },
    { "Bombchu Shop", "炸弹鼠商店" },
    { "Happy Mask Shop", "快乐面具店" },
    { "Link's House", "林克之家" },
    { "Richard's House", "理查德之家" },
    { "Stable", "马厩" },
    { "Impa's House", "英帕之家" },
    { "Lakeside Lab", "湖畔实验室" },
    { "Carpenters' Tent", "木工帐篷" },
    { "Gravekeeper's Hut", "守墓人之屋" },
    { "Great Fairy", "大精灵" },
    { "Fairy Fountain", "精灵之泉" },
    { "Grotto", "洞窟" },
    { "Redead Grave", "瑞迪德墓" },
    { "Fairy Fountain Grave", "精灵之泉墓" },
    { "Royal Family's Tomb", "王族之墓" },
    { "Shooting Gallery", "射击场" },
    { "Temple of Time", "时之殿" },
    { "Chamber of Sages", "贤者之间" },
    { "Castle Maze (Day)", "城堡迷宫（白天）" },
    { "Castle Maze (Night)", "城堡迷宫（夜晚）" },
    { "Cutscene Map", "过场地图" },
    { "Dampe's Grave", "达培之墓" },
    { "Fishing Pond", "钓鱼池" },
    { "Castle Courtyard", "城堡庭院" },
    { "Bombchu Bowling Alley", "炸弹鼠保龄球场" },
    { "Ranch House", "牧场小屋" },
    { "Guard House", "守卫之屋" },
    { "Granny's Potion Shop", "老奶奶药水店" },
    { "Ganon Fight", "盖侬战斗" },
    { "House of Skulltula", "骷髅蜘蛛之屋" },
    { "Hyrule Field", "海拉鲁平原" },
    { "Kakariko Village", "卡卡利科村" },
    { "Graveyard", "墓地" },
    { "Zora's River", "卓拉河" },
    { "Kokiri Forest", "科克里森林" },
    { "Sacred Forest Meadow", "神圣森林草甸" },
    { "Lake Hylia", "海拉鲁湖" },
    { "Zora's Domain", "卓拉领地" },
    { "Zora's Fountain", "卓拉喷泉" },
    { "Gerudo Valley", "格鲁德大峡谷" },
    { "Lost Woods", "迷失森林" },
    { "Desert Colossus", "巨大邪神像" },
    { "Gerudo's Fortress", "格鲁德要塞" },
    { "Haunted Wasteland", "幻影沙漠" },
    { "Hyrule Castle", "海拉鲁城堡" },
    { "Death Mountain Trail", "死神山径" },
    { "Death Mountain Crater", "死亡山脉火山口" },
    { "Goron City", "格雷城" },
    { "Lon Lon Ranch", "隆隆牧场" },
    { "Outside Ganon's Castle", "盖侬城堡外" },
    { "Test Map", "测试地图" },
    { "Test Room", "测试房间" },
    { "Depth Test", "深度测试" },
    { "Stalfos Mini-Boss", "斯陶夫小头目" },
    { "Stalfos Boss", "斯陶夫头目" },
    { "Dark Link", "暗林克" },
    { "Castle Maze (Broken)", "城堡迷宫（破损）" },
    { "SRD Room", "SRD 房间" },
    { "Chest Room", "宝箱房间" },
    { "Generic Grotto", "通用洞窟" },
    { "Lake Hylia Scrub Grotto", "海拉鲁湖史克洞窟" },
    { "Redead Grotto", "瑞迪德洞窟" },
    { "Cow Grotto", "奶牛洞窟" },
    { "Scrub Trio", "史克三人组" },
    { "Flooded Grotto", "淹没洞窟" },
    { "Scrub Duo (Upgrade)", "史克二人组（升级）" },
    { "Wolfos Grotto", "沃尔夫斯洞窟" },
    { "Hyrule Castle Storms Grotto", "海拉鲁城堡风暴洞窟" },
    { "Scrub Duo", "史克二人组" },
    { "Tektite Grotto", "忒克泰特洞窟" },
    { "Forest Stage", "森林舞台" },
    { "Webbed Grotto", "蛛网洞窟" },
    { "Big Skulltula Grotto", "大骷髅蜘蛛洞窟" },
    { "Windmill", "风车" },


    // ---- Gameplay Stats: item/event timestamp display names (SetupDisplayNames) ----
    { "Fairy Bow:", "妖精弓：" },
    { "Fire Arrows:", "火焰箭：" },
    { "Din's Fire:", "丁斯的火焰：" },
    { "Slingshot:", "弹弓：" },
    { "Fairy Ocarina:", "妖精陶笛：" },
    { "Ocarina of Time:", "时光之笛：" },
    { "Bombchus:", "炸弹鼠：" },
    { "Hookshot:", "钩爪：" },
    { "Longshot:", "长钩爪：" },
    { "Ice Arrows:", "冰箭：" },
    { "Farore's Wind:", "花柔之风：" },
    { "Boomerang:", "飞旋镖：" },
    { "Lens of Truth:", "真实之镜：" },
    { "Megaton Hammer:", "百万顿锤：" },
    { "Light Arrows:", "光箭：" },
    { "Bottle:", "空瓶：" },
    { "Zelda's Letter:", "塞尔达的信：" },
    { "Kokiri Sword:", "科克里剑：" },
    { "Master Sword:", "大师之剑：" },
    { "Biggoron's Sword:", "大格雷之剑：" },
    { "Deku Shield:", "德库盾：" },
    { "Hylian Shield:", "海拉鲁盾：" },
    { "Mirror Shield:", "镜盾：" },
    { "Goron Tunic:", "格雷外衣：" },
    { "Zora Tunic:", "卓拉外衣：" },
    { "Iron Boots:", "铁靴：" },
    { "Hover Boots:", "悬浮靴：" },
    { "Bomb Bag:", "炸弹袋：" },
    { "Goron's Bracelet:", "格雷手镯：" },
    { "Silver Gauntlets:", "银护腕：" },
    { "Gold Gauntlets:", "金护腕：" },
    { "Silver Scale:", "银鳞：" },
    { "Gold Scale:", "金鳞：" },
    { "Adult's Wallet:", "成人钱包：" },
    { "Giant's Wallet:", "巨人钱包：" },
    { "Weird Egg:", "奇怪的蛋：" },
    { "Gerudo's Card:", "格鲁德之卡：" },
    { "Cojiro:", "小公鸡：" },
    { "Pocket Egg:", "口袋蛋：" },
    { "Skull Mask:", "骷髅面具：" },
    { "Spooky Mask:", "诡异面具：" },
    { "Keaton Mask:", "基顿面具：" },
    { "Bunny Hood:", "兔耳头巾：" },
    { "Odd Mushroom:", "奇怪蘑菇：" },
    { "Odd Potion:", "奇怪药水：" },
    { "Poacher's Saw:", "偷猎者锯：" },
    { "Broken Goron Sword:", "破损格雷剑：" },
    { "Prescription:", "处方：" },
    { "Eyeball Frog:", "大眼青蛙：" },
    { "Eye Drops:", "眼药水：" },
    { "Claim Check:", "领取单：" },
    { "Minuet of Forest:", "森林小步舞曲：" },
    { "Bolero of Fire:", "火焰波丽露：" },
    { "Serenade of Water:", "流水小夜曲：" },
    { "Requiem of Spirit:", "灵之安魂曲：" },
    { "Nocturne of Shadow:", "暗夜小夜曲：" },
    { "Prelude of Light:", "光之前奏曲：" },
    { "Zelda's Lullaby:", "塞尔达的摇篮曲：" },
    { "Epona's Song:", "伊波纳之歌：" },
    { "Saria's Song:", "萨莉亚之歌：" },
    { "Sun's Song:", "太阳之歌：" },
    { "Song of Time:", "时间之歌：" },
    { "Song of Storms:", "风暴之歌：" },
    { "Forest Medallion:", "森林勋章：" },
    { "Fire Medallion:", "火焰勋章：" },
    { "Water Medallion:", "流水勋章：" },
    { "Spirit Medallion:", "灵之勋章：" },
    { "Shadow Medallion:", "暗之勋章：" },
    { "Light Medallion:", "光之勋章：" },
    { "Kokiri's Emerald:", "科克里翡翠：" },
    { "Goron's Ruby:", "格雷红宝石：" },
    { "Zora's Sapphire:", "卓拉蓝宝石：" },
    { "Ganon's Boss Key:", "盖侬 Boss 之钥：" },
    { "Magic:", "魔法：" },
    { "Double Defense:", "双重防御：" },
    { "Gohma Defeated:", "哥马击败：" },
    { "KD Defeated:", "多东哥王击败：" },
    { "Barinade Defeated:", "巴林内德击败：" },
    { "PG Defeated:", "幻影盖侬击败：" },
    { "Volvagia Defeated:", "沃沃基亚击败：" },
    { "Morpha Defeated:", "莫尔法击败：" },
    { "Bongo Defeated:", "邦戈邦戈击败：" },
    { "Twinrova Defeated:", "孪生洛娃击败：" },
    { "Ganondorf Defeated:", "盖侬道夫击败：" },
    { "Ganon Defeated:", "盖侬击败：" },
    { "Boss Rush Finished:", "Boss 速通完成：" },
    { "Greg Found:", "找到格雷格：" },
    { "Triforce Completed:", "三角力量完成：" },

    // ===========================================================================
    //  Time Splits window (TimeSplits.cpp)
    // ===========================================================================
    { "Splits", "分段" },
    { "Manage List", "管理列表" },
    { "Options", "选项" },
    { "Preview", "预览" },
    { "Equipment", "装备" },
    { "Inventory", "道具" },
    { "Quest", "任务" },
    { "Entrances", "入口" },
    { "Bosses", "头目" },
    { "Miscellaneous", "杂项" },
    { "Window Options", "窗口选项" },
    { "Background Color", "背景颜色" },
    { "Window Scale", "窗口缩放" },
    { "Split List Management", "分段列表管理" },
    { "New List Name: ", "新列表名称：" },
    { "Select List to Load: ", "选择要载入的列表：" },
    { "Create List", "创建列表" },
    { "Load List", "载入列表" },
    { "Save List", "保存列表" },
    { "Delete List", "删除列表" },
    { "New Attempt", "新尝试" },
    { "Update Splits", "更新分段" },
    { "Set Tokens", "设置代币" },
    { "No Saved Lists", "无已保存列表" },
    { "Move %s", "移动 %s" },
    { "%d Tokens", "%d 个代币" },
    { " - ##Set Tokens", " - ##Set Tokens" },
    { " + ##Set Tokens", " + ##Set Tokens" },
    { "Deku Stick", "德库木棒" },
    { "Deku Nut", "德库坚果" },
    { "Bomb", "炸弹" },
    { "Fairy Bow", "妖精弓" },
    { "Fire Arrow", "火焰箭" },
    { "Din's Fire", "丁斯的火焰" },
    { "Fairy Slingshot", "妖精弹弓" },
    { "Fairy Ocarina", "妖精陶笛" },
    { "Ocarina of Time", "时光之笛" },
    { "Bombchu", "炸弹鼠" },
    { "Hookshot", "短钩" },
    { "Longshot", "长钩" },
    { "Ice Arrow", "冰箭" },
    { "Farore's Wind", "花柔之风" },
    { "Boomerang", "飞旋镖" },
    { "Lens of Truth", "真实之镜" },
    { "Magic Bean", "魔法豆" },
    { "Megaton Hammer", "百万顿锤" },
    { "Light Arrow", "光箭" },
    { "Nayru's Love", "娜茹之爱" },
    { "Empty Bottle", "空瓶" },
    { "Red Potion", "红色药水" },
    { "Green Potion", "绿色药水" },
    { "Blue Potion", "蓝色药水" },
    { "Bottled Fairy", "瓶装妖精" },
    { "Fish", "鱼" },
    { "Milk", "牛奶" },
    { "Ruto's Letter", "茹特的信" },
    { "Blue Fire", "蓝色火焰" },
    { "Bug", "虫子" },
    { "Big Poe", "大妖婆" },
    { "Poe", "波克" },
    { "Weird Egg", "奇怪的蛋" },
    { "Chicken", "小鸡" },
    { "Zelda's Letter", "塞尔达的信" },
    { "Keaton Mask", "基顿面具" },
    { "Skull Mask", "骷髅面具" },
    { "Spooky Mask", "诡异面具" },
    { "Bunny Hood", "兔耳头巾" },
    { "Goron Mask", "格雷面具" },
    { "Zora Mask", "卓拉面具" },
    { "Gerudo Mask", "格鲁多面具" },
    { "Mask of Truth", "真实面具" },
    { "Pocket Egg", "口袋蛋" },
    { "Pocket Cucco", "口袋咕咕" },
    { "Cojiro", "小公鸡" },
    { "Odd Mushroom", "奇怪蘑菇" },
    { "Odd Potion", "奇怪药水" },
    { "Poacher's Saw", "偷猎者锯" },
    { "Goron's Sword (Broken)", "格雷之剑（破损）" },
    { "Prescription", "处方" },
    { "Eyeball Frog", "大眼青蛙" },
    { "Eye Drops", "眼药水" },
    { "Claim Check", "领取单" },
    { "Kokiri Sword", "科克里剑" },
    { "Master Sword", "大师之剑" },
    { "Giant's Knife & Biggoron's Sword", "巨人刀与大格雷之剑" },
    { "Deku Shield", "德库盾" },
    { "Hylian Shield", "海拉鲁盾" },
    { "Mirror Shield", "镜盾" },
    { "Goron Tunic", "格雷外套" },
    { "Zora Tunic", "卓拉外套" },
    { "Iron Boots", "铁靴" },
    { "Hover Boots", "悬浮靴" },
    { "Bullet Bag (30)", "种子袋（30）" },
    { "Bullet Bag (40)", "种子袋（40）" },
    { "Bullet Bag (50)", "种子袋（50）" },
    { "Quiver (30)", "箭袋（30）" },
    { "Big Quiver (40)", "大箭袋（40）" },
    { "Biggest Quiver (50)", "最大箭袋（50）" },
    { "Bomb Bag (20)", "炸弹袋（20）" },
    { "Big Bomb Bag (30)", "大炸弹袋（30）" },
    { "Biggest Bomb Bag (40)", "最大炸弹袋（40）" },
    { "Goron's Bracelet", "格雷手镯" },
    { "Silver Gauntlets", "银护腕" },
    { "Golden Gauntlets", "金护腕" },
    { "Silver Scale", "银鳞" },
    { "Golden Scale", "金鳞" },
    { "Giant's Knife (Broken)", "巨人刀（破损）" },
    { "Adult's Wallet", "成人钱包" },
    { "Giant's Wallet", "巨人钱包" },
    { "Fishing Pole", "钓竿" },
    { "Minuet of Forest", "森林小步曲" },
    { "Bolero of Fire", "烈火之舞曲" },
    { "Serenade of Water", "水中小夜曲" },
    { "Requiem of Spirit", "精灵安魂曲" },
    { "Nocturne of Shadow", "暗影梦幻曲" },
    { "Prelude of Light", "光之前奏曲" },
    { "Zelda's Lullaby", "塞尔达的摇篮曲" },
    { "Epona's Song", "伊波纳之歌" },
    { "Saria's Song", "萨莉亚之歌" },
    { "Sun's Song", "太阳之歌" },
    { "Song of Time", "时光曲" },
    { "Song of Storms", "风雪壮歌" },
    { "Forest Medallion", "森林勋章" },
    { "Fire Medallion", "火焰勋章" },
    { "Water Medallion", "流水勋章" },
    { "Spirit Medallion", "灵之勋章" },
    { "Shadow Medallion", "暗之勋章" },
    { "Light Medallion", "光之勋章" },
    { "Kokiri's Emerald", "科克里翡翠" },
    { "Goron's Ruby", "格雷红宝石" },
    { "Zora's Sapphire", "卓拉蓝宝石" },
    { "Stone of Agony", "振动石" },
    { "Gerudo's Card", "格鲁多之卡" },
    { "Skulltula Token", "骷髅蜘蛛代币" },
    { "Magic Meter", "魔法槽" },
    { "Double Magic", "双重魔法" },
    { "Double Defense", "双重防御" },
    { "Deku Stick Upgrade (20)", "德库木棒升级（20）" },
    { "Deku Stick Upgrade (30)", "德库木棒升级（30）" },
    { "Deku Nut Upgrade (30)", "德库坚果升级（30）" },
    { "Deku Nut Upgrade (40)", "德库坚果升级（40）" },
    { "Queen Gohma", "哥马女王" },
    { "King Dodongo", "多东哥王" },
    { "Barinade", "巴林内德" },
    { "Phantom Ganon", "幻影盖侬" },
    { "Volvagia", "沃沃基亚" },
    { "Morpha", "莫尔法" },
    { "Bongo Bongo", "邦哥邦哥" },
    { "Twinrova", "孪生洛娃" },
    { "Ganondorf", "盖侬道夫" },
    { "Ganon", "盖侬" },
    { "Enter Deku Tree", "进入德库树" },
    { "Enter Dodongos Cavern", "进入多东哥洞穴" },
    { "Enter Jabu Jabu's Belly", "进入加卜加卜之腹" },
    { "Enter Forest Temple", "进入森林神殿" },
    { "Enter Fire Temple", "进入火之神殿" },
    { "Enter Water Temple", "进入水之神殿" },
    { "Enter Spirit Temple", "进入魂之神殿" },
    { "Enter Shadow Temple", "进入暗之神殿" },
    { "Enter Bottom of the Well", "进入井底" },
    { "Enter Ice Cavern", "进入冰之洞窟" },
    { "Enter Ganons Tower", "进入盖侬之塔" },
    { "Enter Gerudo Training Ground", "进入格鲁德训练场" },
    { "Enter Thieves Hideout", "进入盗贼藏身处" },
    { "Enter Ganons Castle", "进入盖侬城堡" },
    { "Enter Tower Collapse Interior", "进入高塔崩塌内部" },
    { "Enter Ganons Castle Collapse", "进入盖侬城堡崩塌" },
    { "Lost Woods Escape", "迷失森林逃脱" },
    { "Forest Escape", "森林逃脱" },
    { "Watchtower Death", "瞭望塔死亡" },

    // ===========================================================================
    //  Audio Editor window (AudioEditor.cpp)
    // ===========================================================================
    // 音轨名（AudioCollection.cpp 的 SEQUENCE_MAP_ENTRY label，AudioEditor 主列表/下拉已包 SohGui::L）
    { "Game Over", "游戏结束" },
    { "Boss Clear", "击败 Boss" },
    { "Obtain Item", "获得道具" },
    { "Enter Ganondorf", "盖侬道夫登场" },
    { "Obtain Heart Container", "获得心之容器" },
    { "Open Treasure Chest", "开启宝箱" },
    { "Hyrule Field Morning Theme", "海拉鲁平原早晨主题曲" },
    { "Spiritual Stone Get", "获得精灵石" },
    { "Obtain Small Item", "获得小道具" },
    { "Escape from Lon Lon Ranch", "逃离隆隆牧场" },
    { "Obtain Fairy Ocarina", "获得妖精之笛" },
    { "Horse Race Goal", "赛马终点" },
    { "Obtain Medallion", "获得勋章" },
    { "Enter Zelda", "塞尔达登场" },
    { "Master Sword", "大师之剑" },
    { "Seal of Six Sages", "六贤者封印" },
    { "Great Fairy's Fountain", "大精灵之泉" },
    { "Zelda's Theme", "塞尔达主题曲" },
    { "Horse Race", "赛马" },
    { "Fairy Flying", "精灵飞舞" },
    { "Deku Tree", "德库树" },
    { "Legend of Hyrule", "海拉鲁传说" },
    { "Shooting Gallery", "射击场" },
    { "Sheik's Theme", "什克主题曲" },
    { "Goodbye to Zelda", "告别塞尔达" },
    { "Ganon Intro", "盖侬登场" },
    { "Chamber of the Sages", "贤者之间" },
    { "Open Door of Temple of Time", "开启时之殿之门" },
    { "Kaepora Gaebora's Theme", "卡波拉·盖波拉主题曲" },
    { "Ganon's Castle Bridge", "盖侬城堡吊桥" },
    { "Kotake & Koume's Theme", "科塔克与科梅主题曲" },
    { "Escape from Ganon's Castle", "逃离盖侬城堡" },
    { "Mini-Game", "小游戏" },
    // 战斗音轨（SEQ_BGM_BATTLE）
    { "Boss Battle", "Boss 战" },
    { "Mini-Boss Battle", "小 Boss 战" },
    { "Ganondorf Battle", "盖侬道夫战" },
    { "Ganon Battle", "盖侬战" },
    { "King Dodongo & Volvagia Boss Battle", "多顿多加王与伏尔瓦吉亚 Boss 战" },
    // 片尾曲（SEQ_ENDING）
    { "End Credits I", "片尾曲 I" },
    { "End Credits II", "片尾曲 II" },
    { "End Credits III", "片尾曲 III" },
    { "End Credits IV", "片尾曲 IV" },
    // 陶笛歌曲（SEQ_OCARINA）
    { "Ocarina Saria's Song", "陶笛·萨莉亚之歌" },
    { "Ocarina Epona's Song", "陶笛·艾波娜之歌" },
    { "Ocarina Zelda's Lullaby", "陶笛·塞尔达摇篮曲" },
    { "Ocarina Sun's Song", "陶笛·太阳之歌" },
    { "Ocarina Song of Time", "陶笛·时之曲" },
    { "Ocarina Song of Storms", "陶笛·风暴之歌" },
    // 音效（SEQ_SFX）
    { "Bomb Explosion", "炸弹爆炸" },
    { "Sword Bonk", "挥剑落空" },
    { "Bow Twang", "拉弓嗡鸣" },
    { "Horse Trot", "马蹄声" },
    { "Drawbridge Set", "吊桥落定" },
    { "Cluck", "咯咯叫" },
    { "Chicken Cry", "鸡鸣" },
    { "Cockadoodiedoo", "公鸡打鸣" },
    { "Switch", "开关" },
    { "Thunder", "雷声" },
    { "Plant Explode", "植物爆裂" },
    { "Bottle Cork", "拔瓶塞" },
    { "Pot Shattering", "陶罐破碎" },
    { "Dusk Howl", "黄昏嚎叫" },
    { "Bark", "犬吠" },
    { "Moo", "牛叫" },
    { "Ribbit", "蛙鸣" },
    { "Rupee (Silver)", "卢比（银）" },
    { "Stalchild Attack", "骷髅仔攻击" },
    { "Armos", "阿摩斯" },
    { "Shellblade", "贝刃" },
    { "Deku Baba", "德库芭芭" },
    { "Randomize All Groups", "随机化所有分组" },

    { "Reset All Groups", "重置所有分组" },
    { "Lock All Groups", "锁定所有分组" },
    { "Unlock All Groups", "解锁所有分组" },
    { "Randomizes all unlocked music and sound effects across tab groups",
      "随机化所有标签页分组中已解锁的音乐与音效" },
    { "Resets all unlocked music and sound effects across tab groups",
      "重置所有标签页分组中已解锁的音乐与音效" },
    { "Locks all music and sound effects across tab groups", "锁定所有标签页分组中的音乐与音效" },
    { "Unlocks all music and sound effects across tab groups", "解锁所有标签页分组中的音乐与音效" },
    { "Audio Options", "音频选项" },
    { "Background Music", "背景音乐" },
    { "Fanfares", "号角" },
    { "Events", "事件" },
    { "Battle Music", "战斗音乐" },
    { "Ending", "结局" },
    { "Instruments", "乐器" },
    { "Ocarina", "时光之笛" },
    { "Sound Effects", "音效" },
    { "Voices", "语音" },
    { "Audio Shuffle Pool Management", "音频洗牌池管理" },
    { "Reset All", "全部重置" },
    { "Randomize All", "全部随机化" },
    { "Lock All", "全部锁定" },
    { "Unlock All", "全部解锁" },
    { "No Shuffle", "不洗牌" },
    { "World", "世界" },
    { "Event", "事件" },
    { "Battle", "战斗" },
    { "Ocarina", "时光之笛" },
    { "Fanfare", "号角" },
    { "Error", "错误" },
    { "SFX", "音效" },
    { "Voice", "语音" },
    { "Instrument", "乐器" },
    { "Malon", "玛隆" },
    { "Whistle", "口哨" },
    { "Harp", "竖琴" },
    { "Organ", "管风琴" },
    { "Flute", "长笛" },
    { "Skulltula Damage", "骷髅蜘蛛伤害" },
    { "Scrub Emerge", "德库灌木钻出" },
    { "Spit Nut", "吐坚果" },
    { "Business Scrub", "商人德库" },
    { "Guay", "呱依" },
    { "Bubble Laugh", "泡泡怪笑声" },
    { "Redead Moan", "死灵低吟" },
    { "Redead Scream", "死灵尖叫" },
    { "Goron Wake", "格雷苏醒" },
    { "Hammer Bonk", "锤子重击" },
    { "Iron Knuckle", "铁拳" },
    { "Bomb Bounce", "炸弹弹跳" },
    { "Shabom Pop", "夏波姆破裂" },
    { "Bongo Bongo Low", "邦哥邦哥低鼓" },
    { "Bongo Bongo High", "邦哥邦哥高鼓" },
    { "Gohma Larva Croak", "哥马幼虫呱叫" },
    { "Flare Dancer Startled", "火焰舞者受惊" },
    { "Flare Dancer Laugh", "火焰舞者笑声" },
    { "Ganondorf Teh!", "盖侬道夫「咻！」" },
    { "Phantom Ganon Laugh", "幻影盖侬笑声" },
    { "Rupee", "卢比" },
    { "HP Recover", "生命恢复" },
    { "Target Neutral", "锁定中立目标" },
    { "Low HP Beep", "低血量蜂鸣" },
    { "Target Enemy", "锁定敌人" },
    { "Gunshot", "枪声" },
    { "Tambourine", "铃鼓" },
    { "File Select Cursor", "存档选择光标" },
    { "File Select Choose", "存档选择确定" },
    { "File Select Back", "存档选择返回" },
    { "Gold Skulltula Token", "金色骷髅蜘蛛代币" },
    { "Carrot Refill", "胡萝卜补充" },
    { "Cartoon Fall", "卡通坠落" },
    { "Child Link - Slash", "小林克—挥砍" },
    { "Child Link - Big Slash", "小林克—大挥砍" },
    { "Child Link - Hootshot Latch", "小林克—胡肖特钩挂" },
    { "Child Link - Dangling Gasp", "小林克—悬吊喘息" },
    { "Child Link - Climb Edge", "小林克—攀爬边缘" },
    { "Child Link - Small Damage", "小林克—轻微受创" },
    { "Child Link - Freeze", "小林克—冻结" },
    { "Child Link - Fall Gasp", "小林克—坠落喘息" },
    { "Child Link - Fall Scream", "小林克—坠落尖叫" },
    { "Child Link - Low Health Sigh", "小林克—低血量叹息" },
    { "Child Link - Bottle Sigh", "小林克—喝瓶叹息" },
    { "Child Link - Death", "小林克—死亡" },
    { "Child Link - Taken away by Wallmaster", "小林克—被墙壁主宰带走" },
    { "Child Link - Grabbed by Wallmaster", "小林克—被墙壁主宰抓住" },
    { "Child Link - Sneeze", "小林克—打喷嚏" },
    { "Child Link - Gasp (Hot Room)", "小林克—喘息（高温房间）" },
    { "Child Link - Yawn", "小林克—打哈欠" },
    { "Child Link - Yell (Sword Putaway)", "小林克—喊叫（收剑）" },
    { "Child Link - Jump/Swing Bottle", "小林克—跳/挥瓶" },
    { "Child Link - Use Nayru's Love", "小林克—使用娜茹之爱" },
    { "Child Link - Surprised Gasp", "小林克—惊讶喘息" },
    { "Child Link - Use Farore's Wind", "小林克—使用法洛雷之風" },
    { "Child Link - Push", "小林克—推" },
    { "Child Link - Hookshot Hang", "小林克—钩绳悬挂" },
    { "Child Link - Fall Damage", "小林克—坠落伤害" },
    { "Child Link - Small Gasp (unused?)", "小林克—轻微喘息（未使用？）" },
    { "Child Link - Din's Fire", "小林克—丁斯之火" },
    { "Child Link - Scream (Nocturne?)", "小林克—尖叫（夜想曲？）" },
    { "Child Link - Scream 2 (Nocturne?)", "小林克—尖叫2（夜想曲？）" },
    { "Navi - Unused Enemy Target", "娜薇—未使用·敌人目标" },
    { "Navi - Unused NPC Hello", "娜薇—未使用·NPC 问候" },
    { "Navi - Unused Other Target", "娜薇—未使用·其他目标" },
    { "Navi - Look/Hey/Watchout (Target Enemy)", "娜薇—看/嘿/小心（锁定敌人）" },
    { "Navi - Hello", "娜薇—问候" },
    { "Talon - Snore", "塔隆—打鼾" },
    { "Talon - Surprised", "塔隆—惊讶" },
    { "Talon - Hmm", "塔隆—嗯" },
    { "Talon - Scream", "塔隆—尖叫" },
    { "Ingo - WAAAH!", "印格—哇啊啊！" },
    { "Ingo - KAAAAH! (Lost)", "印格—咔啊啊！（落败）" },
    { "Ingo - Heyeah (Horse 1)", "印格—嘿呀（马1）" },
    { "Ingo - Ha (Horse 2)", "印格—哈（马2）" },
    { "Great Fairy - Big Laugh", "大妖精—大笑" },
    { "Great Fairy - Small Laugh", "大妖精—小笑" },
    { "Nabooru - Pained Gasp", "娜波如—痛苦喘息" },
    { "Nabooru - Scream", "娜波如—尖叫" },
    { "Nabooru - Hmm?", "娜波如—嗯？" },
    { "Navi - Watchout!", "娜薇—小心！" },
    { "Navi - Look!", "娜薇—看！" },
    { "Navi - Hey! (C-up Sound)", "娜薇—嘿！（C上键音效）" },
    { "Ruto - Crash", "茹特—撞击" },
    { "Ruto - Found", "茹特—发现" },
    { "Ruto - Fall", "茹特—坠落" },
    { "Ruto - Giggle", "茹特—咯咯笑" },
    { "Ruto - Lifted/Navi - Intro Bonk", "茹特—被举起/娜薇—开场撞击" },
    { "Ruto - Thrown", "茹特—被抛出" },
    { "Ruto - Held Tantrum", "茹特—被抱住耍赖" },
    { "Cursed Man - Scream", "被诅咒者—尖叫" },
    { "Cursed Man - Gasp", "被诅咒者—喘息" },
    { "Child Zelda - Hurry", "小塞尔达—快点" },
    { "Child Zelda - Meeting Link Gasp", "小塞尔达—与林克相遇喘息" },
    { "Child Zelda - Question", "小塞尔达—疑问" },
    { "Child Zelda - Sigh", "小塞尔达—叹息" },
    { "Child Zelda - Laugh", "小塞尔达—笑" },
    { "Child Zelda - Sees Ganon Gasp", "小塞尔达—看见盖侬道夫喘息" },
    { "Child Zelda - Throws Ocarina", "小塞尔达—抛出陶笛" },
    { "Sheik - Pained Gasp (Nocturne)", "什克—痛苦喘息（夜想曲）" },
    { "Sheik - Pained Scream (Nocturne)", "什克—痛苦尖叫（夜想曲）" },
    { "Sheik - Pained Landing (Nocturne)", "什克—痛苦落地（夜想曲）" },
    { "Navi - Listen!", "娜薇—听！" },
    { "Sheik - Shout (Throwing Deku Nut)", "什克—喊叫（投掷德库坚果）" },
    { "Adult Zelda - Scream 1", "成年塞尔达—尖叫1" },
    { "Adult Zelda - Scream 2", "成年塞尔达—尖叫2" },
    { "Adult Zelda - Open Seseme Magic Gasp", "成年塞尔达—芝麻开门魔法喘息" },
    { "Adult Zelda - Gasp", "成年塞尔达—喘息" },
    { "Adult Zelda - Pained Gasp", "成年塞尔达—痛苦喘息" },
    { "King Zora - Mweep!", "卓拉王—姆呜噗！" },
    { "Navi - Hello!", "娜薇—你好！" },
    { "Kakariko Village (Adult)", "卡卡利科村（成年）" },
    { "Market", "市场" },
    { "Title Theme", "标题主题曲" },
    { "House", "小屋" },
    { "Kakariko Village (Child)", "卡卡利科村（童年）" },
    { "Hyrule Castle Courtyard", "海拉鲁城堡庭院" },
    { "Ganondorf's Theme", "盖侬道夫主题曲" },
    { "Ingo's Theme", "印格主题曲" },
    { "Windmill Hut", "风车小屋" },
    { "Shop", "商店" },
    { "Potion Shop", "药水店" },
    { "Ganon's Castle Under Ground", "盖侬城堡地下" },
    { "Hair", "头发" },
    { "Linen", "亚麻布" },
    { "Gauntlets Gem", "铁手套宝石" },
    { "Emblem", "徽记" },
    { "Mirror", "镜面" },
    { "Boomerang Gem", "飞旋镖宝石" },
    { "Bow Handle", "弓柄" },
    { "Bow String", "弓弦" },
    { "Bow Tips", "弓梢" },
    { "Bombchu Body", "炸弹虫身体" },
    { "Bombchu Face", "炸弹虫面部" },
    { "Hammer Handle", "锤柄" },
    { "Hookshot Chain", "钩绳锁链" },
    { "Slingshot String", "弹弓绳" },
    { "Blue Rupee", "蓝色卢比" },
    { "Heart Border", "红心边框" },
    { "DD Heart Border", "双防红心边框" },
    { "Gold Rupee", "金色卢比" },
    { "Green Rupee", "绿色卢比" },
    { "Magic Active", "魔法（激活）" },
    { "Magic Border", "魔法边框" },
    { "Magic Border Active", "魔法边框（激活）" },
    { "Purple Rupee", "紫色卢比" },
    { "Red Rupee", "红色卢比" },
    { "Silver Rupee", "银色卢比" },
    { "Infinite Magic", "无限魔法" },
    { "Din's Secondary", "丁斯之火（副色）" },
    { "Farore's Secondary", "法洛雷之風（副色）" },
    { "Nayru's Secondary", "娜茹之爱（副色）" },
    { "Fire Secondary", "火焰（副色）" },
    { "Ice Secondary", "冰霜（副色）" },
    { "Light Secondary", "光芒（副色）" },
    { "Normal Secondary", "普通（副色）" },
    { "Level 1 Secondary", "一级旋转攻击（副色）" },
    { "Level 2 Primary", "二级旋转攻击（主色）" },
    { "Biggoron Sword", "大格雷之剑" },
    { "Hammer", "锤" },
    { "Stick", "木棒" },
    { "Block of Time", "时间方块" },
    { "Gossip Stone", "闲话石" },
    { "Moon", "月亮" },
    { "Enemy Secondary", "敌人（副色）" },
    { "Idle Secondary", "待机（副色）" },
    { "NPC Secondary", "NPC（副色）" },
    { "Props Secondary", "道具（副色）" },
    { "Ivan Idle Secondary", "伊万待机（副色）" },
    { "Dog 1", "狗1" },
    { "Dog 2", "狗2" },
    { "Fire Keese Secondary", "火蝙蝠（副色）" },
    { "Ice Keese Secondary", "冰蝙蝠（副色）" },
    { "Metal Trap", "金属陷阱" },
    { "Hearts counts use margins", "红心计数使用边距" },
    { "Magic meter use margins", "魔法槽使用边距" },
    { "Visual stone of agony use margins", "振动石使用边距" },
    { "B Button use margins", "B 键使用边距" },
    { "A Button use margins", "A 键使用边距" },
    { "Start Button use margins", "Start 键使用边距" },
    { "C Button Up use margins", "C 键上使用边距" },
    { "C Button Down use margins", "C 键下使用边距" },
    { "C Button Left use margins", "C 键左使用边距" },
    { "C Button Right use margins", "C 键右使用边距" },
    { "DPad items use margins", "十字键道具使用边距" },
    { "Minimap use margins", "小地图使用边距" },
    { "Small Keys counter use margins", "小钥匙计数使用边距" },
    { "Carrots use margins", "胡萝卜使用边距" },
    { "Timers use margins", "计时器使用边距" },
    { "Archery scores use margins", "射箭得分使用边距" },
    { "Title cards (overworld) use margins", "标题卡（野外）使用边距" },
    { "Title cards (Bosses) use margins", "标题卡（首领）使用边距" },
    { "In-game Gameplay Timer use margins", "游戏内计时器使用边距" },
    { "Anchor to life bar", "锚定到生命槽" },
    { "Anchor to Enemy", "锚定到敌人" },
    { "Anchor to the top", "锚定到顶部" },
    { "Anchor to the bottom", "锚定到底部" },
    { "Item Name", "道具名称" },
    { "Current Time", "当前时间" },
    { "Prev. Best", "前次最佳" },
    { "Included", "已包含" },
    { "Excluded", "已排除" },
    { "Kokiri Forest", "科克里森林" },
    { "Mido Top Left Chest", "米多左上宝箱" },
    { "Mido Top Right Chest", "米多右上宝箱" },
    { "Mido Bottom Left Chest", "米多左下宝箱" },
    { "Mido Bottom Right Chest", "米多右下宝箱" },
    { "Storms Grotto Chest", "暴风雨洞窟宝箱" },
    { "Lost Woods", "迷失森林" },
    { "Ocarina Memory Game", "陶笛记忆游戏" },
    { "Target in Woods", "森林中的靶子" },
    { "Near Shortcuts Grotto Chest", "近捷径洞窟宝箱" },
    { "Deku Theater Skull Mask", "德库剧院骷髅面具" },
    { "Deku Theater Mask of Truth", "德库剧院真实面具" },
    { "Skull Kid", "骷髅小子" },
    { "Deku Scrub Near Bridge", "桥边德库灌木" },
    { "Deku Scrub Grotto Front", "洞窟前德库灌木" },
    { "Deku Scrub Grotto", "德库灌木洞窟" },
    { "Sacred Forest Meadow", "神圣森林草甸" },
    { "Wolfos Grotto Chest", "狼型怪洞窟宝箱" },
    { "Hyrule Field", "海拉鲁平原" },
    { "Near Market Grotto Chest", "近市场洞窟宝箱" },
    { "Tektite Grotto Freestanding PoH", "特克泰特洞窟独立红心碎片" },
    { "Southeast Grotto Chest", "东南洞窟宝箱" },
    { "Open Grotto Chest", "空旷洞窟宝箱" },
    { "Bush Near Lake 1", "湖边灌木1" },
    { "Bush Near Lake 2", "湖边灌木2" },
    { "Bush Near Lake 3", "湖边灌木3" },
    { "Bush Near Lake 4", "湖边灌木4" },
    { "Bush Near Lake 5", "湖边灌木5" },
    { "Bush Near Lake 6", "湖边灌木6" },
    { "Bush Near Lake 7", "湖边灌木7" },
    { "Bush Near Lake 8", "湖边灌木8" },
    { "Bush Near Lake 9", "湖边灌木9" },
    { "Bush Near Lake 10", "湖边灌木10" },
    { "Bush Near Lake 11", "湖边灌木11" },
    { "Northern Bush 1", "北部灌木1" },
    { "Northern Bush 2", "北部灌木2" },
    { "Northern Bush 3", "北部灌木3" },
    { "Northern Bush 4", "北部灌木4" },
    { "Northern Bush 5", "北部灌木5" },
    { "Northern Bush 6", "北部灌木6" },
    { "Child Northern Bush 1", "童年北部灌木1" },
    { "Child Northern Bush 2", "童年北部灌木2" },
    { "Child Northern Bush 3", "童年北部灌木3" },
    { "Child Northern Bush 4", "童年北部灌木4" },
    { "Child Northern Bush 5", "童年北部灌木5" },
    { "Child Northern Bush 6", "童年北部灌木6" },
    { "Child Northern Bush 7", "童年北部灌木7" },
    { "Child Northern Bush 8", "童年北部灌木8" },
    { "Child Northern Bush 9", "童年北部灌木9" },
    { "Child Northern Bush 10", "童年北部灌木10" },
    { "Child Northern Bush 11", "童年北部灌木11" },
    { "Bush By Rocky Path 1", "岩石路旁灌木1" },
    { "Bush By Rocky Path 2", "岩石路旁灌木2" },
    { "Bush By Rocky Path 3", "岩石路旁灌木3" },
    { "Bush By Rocky Path 4", "岩石路旁灌木4" },
    { "Bush By Rocky Path 5", "岩石路旁灌木5" },
    { "Bush By Rocky Path 6", "岩石路旁灌木6" },
    { "Southern Bush 1", "南部灌木1" },
    { "Southern Bush 2", "南部灌木2" },
    { "Southern Bush 3", "南部灌木3" },
    { "Southern Bush 4", "南部灌木4" },
    { "Southern Bush 5", "南部灌木5" },
    { "Southern Bush 6", "南部灌木6" },
    { "Southern Bush 7", "南部灌木7" },
    { "Southern Bush 8", "南部灌木8" },
    { "Southern Bush 9", "南部灌木9" },
    { "Southern Bush 10", "南部灌木10" },
    { "Southern Bush 11", "南部灌木11" },
    { "Southern Bush 12", "南部灌木12" },
    { "Child Southern Bush 1", "童年南部灌木1" },
    { "Child Southern Bush 2", "童年南部灌木2" },
    { "Child Southern Bush 3", "童年南部灌木3" },
    { "Child Southern Bush 4", "童年南部灌木4" },
    { "Child Southern Bush 5", "童年南部灌木5" },
    { "Child Southern Bush 6", "童年南部灌木6" },
    { "Child Southern Bush 7", "童年南部灌木7" },
    { "Child Southern Bush 8", "童年南部灌木8" },
    { "Child Southern Bush 9", "童年南部灌木9" },
    { "Child Southern Bush 10", "童年南部灌木10" },
    { "Child Southern Bush 11", "童年南部灌木11" },
    { "Child Southern Bush 12", "童年南部灌木12" },
    { "Lake Hylia", "海拉鲁湖" },
    { "Underwater Item", "水下道具" },
    { "Child Fishing", "童年钓鱼" },
    { "Adult Fishing", "成年钓鱼" },
    { "Lab Dive", "实验室潜水" },
    { "Freestanding PoH", "独立心之碎片" },
    { "Sun", "太阳（火之箭）" },
    { "Gerudo Valley", "格鲁德大峡谷" },
    { "Crate Freestanding PoH", "木箱独立心之碎片" },
    { "Waterfall Freestanding PoH", "瀑布独立心之碎片" },
    { "Gerudo Fortress", "格鲁德要塞" },
    { "HBA 1000 Points", "射击场1000分" },
    { "HBA 1500 Points", "射击场1500分" },
    { "Haunted Wasteland", "幻影沙漠" },
    { "Desert Colossus", "巨大邪神像" },
    { "Great Fairy Reward", "大妖精奖励" },
    { "Hyrule Market", "海拉鲁市场" },
    { "Shooting Gallery", "射击场" },
    { "Bombchu Bowling First Prize", "炸弹鼠保龄球头奖" },
    { "Bombchu Bowling Second Prize", "炸弹鼠保龄球二等奖" },
    { "Lost Dog", "走失的狗" },
    { "Treasure Chest Game Reward", "宝箱游戏奖励" },
    { "10 Big Poes", "10只大波爱" },
    { "ToT Light Arrow Cutscene", "时之殿光之箭过场" },
    { "ToT Master Sword", "时之殿大师之剑" },
    { "Completed Triforce", "已集齐三角神力" },
    { "Hyrule Castle", "海拉鲁城堡" },
    { "OGC Great Fairy Reward", "城堡庭院大妖精奖励" },
    { "Kakariko Village", "卡卡利科村" },
    { "Anju as Child", "安茹（童年）" },
    { "Anju as Adult", "安茹（成年）" },
    { "Impas House Freestanding PoH", "因帕家独立心之碎片" },
    { "Windmill Freestanding PoH", "风车独立心之碎片" },
    { "Man on Roof", "屋顶上的男人" },
    { "Open Grotto Chest", "空旷洞窟宝箱" },
    { "Redead Grotto Chest", "瑞迪德洞窟宝箱" },
    { "Shooting Gallery Reward", "射击场奖励" },
    { "10 Gold Skulltula Reward", "10个金色骷髅蜘蛛奖励" },
    { "20 Gold Skulltula Reward", "20个金色骷髅蜘蛛奖励" },
    { "30 Gold Skulltula Reward", "30个金色骷髅蜘蛛奖励" },
    { "40 Gold Skulltula Reward", "40个金色骷髅蜘蛛奖励" },
    { "50 Gold Skulltula Reward", "50个金色骷髅蜘蛛奖励" },
    { "100 Gold Skulltula Reward", "100个金色骷髅蜘蛛奖励" },
    { "Custom", "自定义" },
    { "No Sequence Type", "无序列类型" },
    { "Exclude All", "全部排除" },
    { "Include All", "全部包含" },
    { "Filter (inc,-exc)", "筛选（包含,-排除）" },
    { "Stop Preview", "停止预览" },
    { "Play Preview", "播放预览" },
    { "Reset##linkVoiceFreqMultiplier", "重置##林克语音频率倍数" },
    { "Mute Low HP Alarm", "静音低血量警报" },
    { "Disable Navi Call Audio", "禁用娜薇呼叫语音" },
    { "Disable Enemy Proximity Music", "禁用敌人接近音乐" },
    { "Enable Enemy Proximity Music for Leever", "为利弗启用敌人接近音乐" },
    { "Disable Leading Music in Lost Woods", "禁用迷失森林的引导音乐" },
    { "Display Sequence Name in Notifications", "在通知中显示序列名" },
    { "Sequence Notification Duration: %d seconds", "序列通知时长：%d 秒" },
    { "Link's Voice Pitch Multiplier", "林克语音音高倍数" },
    { "Automatically Randomize All Music and Sound Effects", "自动随机化所有音乐与音效" },
    { "Lower Octaves of Unplayable High Notes", "降低无法演奏高音的音符八度" },
    { "Disable the low HP beeping sound.", "禁用低血量时的哔哔声。" },
    { "Disables the voice audio when Navi calls you.", "禁用娜薇呼叫你时的语音。" },
    { "Disables the music change when getting close to enemies. Useful for hearing "
      "your custom music for each scene more often.",
      "禁用接近敌人时的音乐变化。便于更常听到你为每个场景设置的自定义音乐。" },
    { "Plays the battle music when getting close to a Leever, like in Majora's Mask.",
      "接近利弗时播放战斗音乐，如同《魔吉拉的面具》中一样。" },
    { "Disables the volume shifting in the Lost Woods. Useful for hearing "
      "your custom music in the Lost Woods if you don't need the navigation assitance "
      "the volume changing provides. If toggling this while in the Lost Woods, reload "
      "the area for the effect to kick in.",
      "禁用迷失森林中的音量变化。若你不需要音量变化提供的导航辅助，便于在迷失森林听到自定义音乐。"
      "若在迷失森林中切换此选项，需重新载入区域才能生效。" },
    { "Emits a notification with the current song name whenever it changes. "
      "(does not apply to fanfares or enemy BGM).",
      "每当当前曲目变化时发出通知（不适用于号角或敌人 BGM）。" },
    { "Some custom sequences may have notes that are too high for the game's audio "
      "engine to play. Enabling this checkbox will cause these notes to drop a "
      "couple of octaves so they can still harmonize with the other notes of the "
      "sequence.",
      "某些自定义序列可能含有游戏音频引擎无法演奏的过高音符。启用后将使这些音符降低若干八度，"
      "以便与序列中的其他音符和谐。" },
    { "Set when the music and sound effects is automaticly randomized:\n"
      "- Manual: Manually randomize music or sound effects by pressing the 'Randomize all Groups' "
      "button\n"
      "- On New Scene : Randomizes when you enter a new scene.\n"
      "- On Rando Gen Only: Randomizes only when you generate a new randomizer.\n"
      "- On File Load: Randomizes on File Load.\n"
      "- On File Load (Seeded): Randomizes on file load based on the current randomizer seed/file.",
      "设置音乐与音效自动随机化的时机：\n"
      "- 手动：按下\"随机化所有分组\"按钮时手动随机化音乐或音效\n"
      "- 进入新场景：进入新场景时随机化\n"
      "- 仅随机生成时：仅在你生成新的随机存档时随机化\n"
      "- 载入存档时：载入存档时随机化\n"
      "- 载入存档时（固定种子）：基于当前随机种子/存档在载入时随机化" },
    { "Manual", "手动" },
    { "On New Scene", "进入新场景" },
    { "On Rando Gen Only", "仅随机生成时" },
    { "On File Load", "载入存档时" },
    { "On File Load (Seeded)", "载入存档时（固定种子）" },

    // CosmeticsEditor.cpp - Fairies
    { "Fairies Size", "精灵大小" },


    // ===========================================================================
    //  Network / Anchor (soh/soh/Network/Anchor/Menu.cpp)
    //  该菜单大量使用直接 ImGui::Text/TextWrapped/SeparatorText 调用，未经 MenuDrawItem
    //  自动翻译，故在调用点用 SohGui::L() 包裹；Button/WindowButton/Tooltip/Combobox/
    //  Checkbox 的标签则经 UIWidgets 集中翻译，只需在此加表。
    // ===========================================================================
    // 直接 ImGui 文本（调用点已包 SohGui::L）
    { "Connection Settings", "连接设置" },
    { "Host & Port", "主机与端口" },
    { "Name & Color", "名称与颜色" },
    { "Room ID", "房间 ID" },
    { "Team ID (Items & Flags Shared)", "队伍 ID（共享道具与标记）" },
    { "Connecting...", "连接中……" },
    { "Current Room", "当前房间" },
    { "%s Connected", "%s 已连接" },
    { "Room Settings (Admin Only)", "房间设置（仅管理员）" },
    { "Usage Instructions", "使用说明" },
    { "1. All players involved should start at the file select screen",
      "1. 所有参与的玩家都应从读档界面开始" },
    { "2. Come up with a unique Room ID (this is basically your password) and enter it, along with "
      "your desired player name and team ID and click Enable",
      "2. 想一个独一无二的房间 ID（基本相当于你的密码）并填入，连同你想要的玩家名与队伍 ID 一起输入，"
      "然后点击「启用」" },
    { "3. The host should configure the randomizer settings and generate a seed, then share the newly "
      "generated JSON spoiler file with other players.",
      "3. 房主应配置随机生成设置并生成一个种子，然后将新生成的 JSON 剧透文件分享给其他玩家。" },
    { "4. All players should load the same JSON spoiler file (drag it into SoH window), make sure "
      "seed icons match, then create a new file.",
      "4. 所有玩家都应载入同一个 JSON 剧透文件（拖入 SoH 窗口），确认种子图标一致，然后创建新存档。" },
    { "5. All players should now load into their game. IMPORTANT! If using an existing save/seed "
      "ensure the player with the most progress loads the file first.",
      "5. 现在所有玩家都应载入各自的游戏。重要！如果使用已有的存档/种子，请确保进度最多的玩家先载入存档。" },
    { "6. After everyone has loaded in, verify on the network tab that it doesn't warn about anyone "
      "being on a wrong version or seed.",
      "6. 在所有人载入后，请在网络标签页确认没有关于任何人版本或种子错误的警告。" },
    { "Note: Team ID is used to group players together in the same team, sharing items and flags. Make sure all "
      "players who want to share progress use the same Team ID. All players with the same Team ID should be using "
      "the same randomizer seed, while players on different teams can use different seeds.",
      "注意：队伍 ID 用于将玩家归入同一队伍，共享道具与标记。确保所有希望共享进度的玩家使用相同的队伍 ID。"
      "所有相同队伍 ID 的玩家应使用相同的随机种子，而不同队伍的玩家可以使用不同的种子。" },
    // UIWidgets::Button / WindowButton / Tooltip / Combobox / Checkbox 标签（经 UIWidgets 集中翻译）
    { "Enable", "启用" },
    { "Disable", "禁用" },
    { "Restore Defaults", "恢复默认" },
    { "Global Room", "公共房间" },
    { "Request Team State", "请求队伍状态" },
    { "Clear All Team State", "清除全部队伍状态" },
    { "Toggle Anchor Room Window", "切换 Anchor 房间窗口" },
    { "Always-online public room so you don't have to experience Hyrule alone. PVP and syncing are disabled.",
      "始终在线的公共房间，让你不必独自体验海拉鲁。已禁用 PVP 与同步。" },
    { "Try this if you are missing items or flags that your team members have collected",
      "如果你缺少队友已收集的道具或标记，请尝试此操作" },
    { "PvP Mode:", "PVP 模式：" },
    { "Show Locations For:", "显示位置：" },
    { "Allow Teleporting To:", "允许传送至：" },
    { "Sync Items & Flags", "同步道具与标记" },
    // 下拉框选项值（Combobox 内部对 trueLabel 套 L()）
    { "On + Friendly Fire", "开启 + 友伤" },
    { "Team Only", "仅队伍" },

    // ===== Cosmetics / Appearance Editor (cosmetics/CosmeticsEditor.cpp) =====
    // 标签页（BeginTabItem 已包 SohGui::L）
    { "Link & Items", "林克与道具" },
    { "Keys", "钥匙" },
    { "Effects", "特效" },
    { "World & NPCs", "世界与 NPC" },
    { "Silly", "趣味" },
    { "HUD Placement", "HUD 布局" },
    // 分组标签（DrawCosmeticGroup 已包 SohGui::L）
    { "Link", "林克" },
    { "Gloves", "手套" },
    { "Swords", "剑" },
    { "Consumables", "消耗品" },
    // 单条目标签（DrawCosmeticRow 已包 SohGui::L）
    { "Kokiri Tunic", "科克里外衣" },
    { "Goron Bracelet", "格雷手镯" },
    { "Body", "本体" },
    { "Boomerang Body", "飞旋镖本体" },
    { "Bow Body", "弓本体" },
    { "Hammer Head", "大锤锤头" },
    { "Non-Hookshotable Reticle", "不可钩取准星" },
    { "Hookshotable Reticle", "可钩取准星" },
    { "Biggoron Sword Blade", "大格雷之剑剑身" },
    { "Kokiri Sword Blade", "科克里剑剑身" },
    { "Master Sword Blade", "大师之剑剑身" },
    { "DD Hearts", "双倍防御之心" },
    { "Hearts", "心" },
    // 颜色行按钮/复选框（Random/Reset 经 UIWidgets::Button 自动翻译；Rainbow/Locked 已在源码包 L()）
    { "Rainbow", "彩虹" },
    { "Cycles through colors on a timer\nOverwrites previously chosen color",
      "按计时器循环切换颜色\n覆盖之前已选择的颜色" },
    { "Locked", "锁定" },
    { "Lock", "锁定" },
    // ===== 钥匙（CosmeticsEditor.cpp 的 Keys 标签页：Keyring/Small Keys/Boss Keys 分组）=====
    // 分组标签（DrawCosmeticGroup 已包 SohGui::L）
    { "Keyring", "钥匙串" },
    { "Small Keys", "小钥匙" },
    { "Boss Keys", "Boss 钥匙" },
    // 单条目标签（DrawCosmeticRow 已包 SohGui::L）
    { "Key Ring Ring", "钥匙环" },
    { "Forest Small Key Body", "森林小钥匙本体" },
    { "Forest Small Key Emblem", "森林小钥匙纹章" },
    { "Forest Boss Key Body", "森林 Boss 钥匙本体" },
    { "Forest Boss Key Gem", "森林 Boss 钥匙宝石" },
    { "Fire Small Key Body", "火之小钥匙本体" },
    { "Fire Small Key Emblem", "火之小钥匙纹章" },
    { "Fire Boss Key Body", "火之 Boss 钥匙本体" },
    { "Fire Boss Key Gem", "火之 Boss 钥匙宝石" },
    { "Water Small Key Body", "水之小钥匙本体" },
    { "Water Small Key Emblem", "水之小钥匙纹章" },
    { "Water Boss Key Body", "水之 Boss 钥匙本体" },
    { "Water Boss Key Gem", "水之 Boss 钥匙宝石" },
    { "Spirit Small Key Body", "灵魂小钥匙本体" },
    { "Spirit Small Key Emblem", "灵魂小钥匙纹章" },
    { "Spirit Boss Key Body", "灵魂 Boss 钥匙本体" },
    { "Spirit Boss Key Gem", "灵魂 Boss 钥匙宝石" },
    { "Shadow Small Key Body", "暗影小钥匙本体" },
    { "Shadow Small Key Emblem", "暗影小钥匙纹章" },
    { "Shadow Boss Key Body", "暗影 Boss 钥匙本体" },
    { "Shadow Boss Key Gem", "暗影 Boss 钥匙宝石" },
    { "Ganons Small Key Body", "盖侬小钥匙本体" },
    { "Ganons Small Key Emblem", "盖侬小钥匙纹章" },
    { "Ganons Boss Key Body", "盖侬 Boss 钥匙本体" },
    { "Ganons Boss Key Gem", "盖侬 Boss 钥匙宝石" },
    { "Well Small Key", "井中小钥匙" },
    { "Well Small Key Emblem", "井中小钥匙纹章" },
    { "Fortress Small Key", "要塞小钥匙" },
    { "Fortress Small Key Emblem", "要塞小钥匙纹章" },
    { "GTG Small Key", "GTG 小钥匙" },
    { "GTG Small Key Emblem", "GTG 小钥匙纹章" },
    // "Skeleton Key" → 万能钥匙 已在表 1939 行，此处不再重复
    // ===== 魔法/箭/旋转攻击/拖尾（CosmeticsEditor.cpp 的 Magic/Arrows/Spin Attack/Trails 分组）=====
    // 分组标签（DrawCosmeticGroup 已包 SohGui::L）
    { "Magic Effects", "魔法特效" },
    { "Arrow Effects", "箭特效" },
    { "Spin Attack", "旋转攻击" },
    { "Trails", "拖尾" },
    // 单条目标签（DrawCosmeticRow 已包 SohGui::L）
    { "Din's Primary", "丁之主色" },
    { "Farore's Primary", "花柔之主色" },
    { "Nayru's Primary", "娜茹之主色" },
    { "Normal Primary", "普通主色" },
    { "Fire Primary", "火主色" },
    { "Ice Primary", "冰主色" },
    { "Light Primary", "光主色" },
    { "Level 1 Primary", "一级主色" },
    { "Level 1 Secondary", "一级副色" },
    { "Level 2 Secondary", "二级副色" },
    // ===== 世界/NPC/娜薇/伊万 颜色（CosmeticsEditor.cpp 的 World/Navi/Ivan/NPC 分组）=====
    // 分组标签（DrawCosmeticGroup 已包 SohGui::L）
    { "Ivan", "伊万" },
    { "Navi", "娜薇" }, // 表 305 行已有，此处确保分组标签一致
    // 单条目标签（DrawCosmeticRow 已包 SohGui::L）
    { "Mystery Item", "神秘道具" },
    { "Red Ice", "红冰" },
    { "Enemy Primary", "敌人主色" },
    { "Idle Primary", "待机主色" },
    { "NPC Primary", "NPC 主色" },
    { "Props Primary", "道具主色" },
    { "Ivan Idle Primary", "伊万待机主色" },
    { "Fire Keese Primary", "火之吉斯主色" },
    { "Ice Keese Primary", "冰之吉斯主色" },
    { "Golden Skulltula", "黄金蜘蛛" },
    { "Kokiri", "科克里" },
    { "Gerudo", "格鲁德" },
    { "Iron Knuckles", "铁拳" },
    // ===== HUD / 标题画面 颜色（CosmeticsEditor.cpp 的 HUD / Title Screen 分组）=====
    // 分组标签（DrawCosmeticGroup 已包 SohGui::L）
    { "HUD", "HUD" },
    { "Title Screen", "标题画面" },
    // 单条目标签（DrawCosmeticRow 已包 SohGui::L）
    { "A Button", "A 键" },
    { "B Button", "B 键" },
    { "C Buttons", "C 键" },
    { "C Up Button", "C 上键" },
    { "C Down Button", "C 下键" },
    { "C Left Button", "C 左键" },
    { "C Right Button", "C 右键" },
    { "Start Button", "开始键" },
    { "Dpad", "方向键" },
    { "Minimap", "小地图" },
    { "Minimap Position", "小地图位置" },
    { "Minimap Entrance", "小地图入口" },
    { "Enemy Health Bar", "敌人血条" },
    { "Enemy Health Border", "敌人血条边框" },
    { "Key Count", "钥匙计数" },
    { "Nametag Background", "名称标签背景" },
    { "Nametag Text", "名称标签文字" },
    { "Map Title Card", "地图标题卡" },
    { "Boss Title Card", "Boss 标题卡" },
    { "Copyright Text", "版权文字" },
    { "File Choose", "选择文件" },
    { "Nintendo Logo", "任天堂标志" },
    { "N64 Red", "N64 红" },
    { "N64 Blue", "N64 蓝" },
    { "N64 Green", "N64 绿" },
    { "N64 Yellow", "N64 黄" },
    // Kaleido（暂停菜单）配色（DrawCosmeticRow 已包 SohGui::L）
    { "Equip Select Color", "装备选择颜色" },
    { "Equip Select Color B", "装备选择颜色 B" },
    { "Equip Select Color C", "装备选择颜色 C" },
    { "Equip Select Color D", "装备选择颜色 D" },
    { "Item Select Color", "道具选择颜色" },
    { "Item Select Color B", "道具选择颜色 B" },
    { "Item Select Color C", "道具选择颜色 C" },
    { "Item Select Color D", "道具选择颜色 D" },
    { "Map Dungeon Color", "地图地牢颜色" },
    { "Map Dungeon Color B", "地图地牢颜色 B" },
    { "Map Dungeon Color C", "地图地牢颜色 C" },
    { "Map Dungeon Color D", "地图地牢颜色 D" },
    { "Quest Status Color", "任务状态颜色" },
    { "Quest Status Color B", "任务状态颜色 B" },
    { "Quest Status Color C", "任务状态颜色 C" },
    { "Quest Status Color D", "任务状态颜色 D" },
    { "Map Color", "地图颜色" },
    { "Map Color B", "地图颜色 B" },
    { "Map Color C", "地图颜色 C" },
    { "Map Color D", "地图颜色 D" },
    { "Name Panel", "名称面板" },
    { "Save Color", "存档颜色" },
    { "Save Color B", "存档颜色 B" },
    { "Save Color C", "存档颜色 C" },
    { "Save Color D", "存档颜色 D" },
    // Message（对话框文字）配色（COSMETICS_GROUP_MESSAGE，DrawCosmeticRow 已包 SohGui::L）
    { "Message", "消息" },
    { "Message Adjustable Color", "消息可调颜色" },
    { "Message Adjustable (Wooden) Color", "消息可调（木纹）颜色" },
    { "Message Black Color", "消息黑色" },
    { "Message Blue Color", "消息蓝色" },
    { "Message Blue (Wooden) Color", "消息蓝色（木纹）" },
    { "Message Default (None No Shadow)", "消息默认（无阴影）" },
    { "Message Default Color", "消息默认颜色" },
    { "Message Light Blue (None No Shadow)", "消息浅蓝（无阴影）" },
    { "Message Light Blue Color", "消息浅蓝" },
    { "Message Light Blue (Wooden) Color", "消息浅蓝（木纹）" },
    { "Message Purple Color", "消息紫色" },
    { "Message Purple (Wooden) Color", "消息紫色（木纹）" },
    { "Message Red Color", "消息红色" },
    { "Message Red (Wooden) Color", "消息红色（木纹）" },
    { "Message Yellow Color", "消息黄色" },
    { "Message Yellow (Wooden) Color", "消息黄色（木纹）" },

    // ===== HUD 排版 / 边距（CosmeticsEditor.cpp 的 Draw_Placements / Draw_Table_Dropdown）=====

    // 通用边距滑块标签（已包 SohGui::L）
    { "Top: %dpx", "上：%d 像素" },
    { "Left: %dpx", "左：%d 像素" },
    { "Right: %dpx", "右：%d 像素" },
    { "Bottom: %dpx", "下：%d 像素" },
    // 边距一键开关按钮（UIWidgets::Button 已包 SohGui::L）
    { "All margins on", "全部开启边距" },
    { "All margins off", "全部关闭边距" },
    // 各元素位置设置标题（Draw_Table_Dropdown 已包 SohGui::L）
    { "B Button position", "B 键位置" },
    { "A Button position", "A 键位置" },
    { "Start Button position", "开始键位置" },
    { "C Button Up position", "C 键上位置" },
    { "C Button Down position", "C 键下位置" },
    { "C Button Left position", "C 键左位置" },
    { "C Button Right position", "C 键右位置" },
    { "Minimaps position", "小地图位置" },
    { "Small Keys counter position", "小钥匙计数器位置" },
    // ===== HUD 排版（续）：位置设置标题 + 单选框 + use margins（CosmeticsEditor.cpp 的 Draw_Table_Dropdown / DrawPositionsRadioBoxes / DrawUseMarginsSlider）=====
    // 位置设置标题（Draw_Table_Dropdown 已包 SohGui::L）
    { "Rupee counter position", "卢比计数器位置" },
    { "Carrots position", "胡萝卜位置" },
    { "Timers position", "计时器位置" },
    { "Archery Scores position", "射箭分数位置" },
    { "Title cards (Maps) position", "标题卡（地图）位置" },
    { "Title cards (Bosses) position", "标题卡（Boss）位置" },
    { "In-game Gameplay Timer position", "游戏内玩法计时器位置" },
    // 位置类型单选框（DrawPositionsRadioBoxes 已包 SohGui::L）
    { "Original position", "原始位置" },
    { "Anchor to the left", "锚定到左侧" },
    { "Anchor to the right", "锚定到右侧" },
    { "No anchors", "无锚定" },
    // use margins 复选框（DrawUseMarginsSlider 已包 SohGui::L，动态拼接串，仅 Rupee counter 用到此条目）
    { "Rupee counter use margins", "卢比计数器使用边距" },
    // ===== 音频编辑器 VOICE 分组：Adult Link 音效名（AudioCollection.cpp 的 SEQUENCE_MAP_ENTRY，AudioEditor.cpp 已包 SohGui::L）=====
    { "Adult Link - Slash", "成年林克 - 挥砍" },
    { "Adult Link - Big Slash", "成年林克 - 重挥砍" },
    { "Adult Link - Hookshot Latch Yell", "成年林克 - 钩索锁定叫喊" },
    { "Adult Link - Dangling Gasp", "成年林克 - 悬吊喘息" },
    { "Adult Link - Climb Edge", "成年林克 - 攀缘" },
    { "Adult Link - Small Damage", "成年林克 - 轻微受伤" },
    { "Adult Link - Freeze", "成年林克 - 冻结" },
    { "Adult Link - Fall Gasp", "成年林克 - 坠落喘息" },
    { "Adult Link - Fall Scream", "成年林克 - 坠落尖叫" },
    { "Adult Link - Low Health Sigh", "成年林克 - 低血量叹息" },
    { "Adult Link - Bottle Sigh", "成年林克 - 喝瓶叹息" },
    { "Adult Link - Death", "成年林克 - 死亡" },
    { "Adult Link - Taken away by Wallmaster", "成年林克 - 被墙主抓走" },
    { "Adult Link - Grabbed by Wallmaster", "成年林克 - 被墙主抓住" },
    { "Adult Link - Sneeze", "成年林克 - 打喷嚏" },
    { "Adult Link - Gasp (Hot Room)", "成年林克 - 喘息（闷热房间）" },
    { "Adult Link - Yawn", "成年林克 - 打哈欠" },
    { "Adult Link - Yell (Sword Putaway)", "成年林克 - 叫喊（收剑）" },
    { "Adult Link - Jump/Swing Bottle", "成年林克 - 跳跃/挥瓶" },
    { "Adult Link - Use Nayru's Love", "成年林克 - 使用娜茹之爱" },
    { "Adult Link - Suprised Gasp", "成年林克 - 惊讶喘息" },
    { "Adult Link - Use Farore's Wind", "成年林克 - 使用花柔之风" },
    { "Adult Link - Push", "成年林克 - 推" },
    { "Adult Link - Hookshot hang", "成年林克 - 钩索悬吊" },
    { "Adult Link - Fall damage", "成年林克 - 坠落伤害" },
    { "Adult Link - Small grunt (unused?)", "成年林克 - 轻微闷哼（未使用？）" },
    { "Adult Link - Din's Fire", "成年林克 - 丁之火焰" },
    { "Adult Link - Scream (Nocturne?)", "成年林克 - 尖叫（夜之镇魂曲？）" },
    { "Adult Link - Pained Land (Nocturne?)", "成年林克 - 痛苦落地（夜之镇魂曲？）" },
    { "Adult Link - Drinking", "成年林克 - 喝东西" },

    // ==== 全面补全：通用词条 ====
    { "Add", "添加" },
    { "Remove", "移除" },
    { "Delete", "删除" },
    { "Refresh", "刷新" },
    { "Import", "导入" },
    { "Export", "导出" },
    { "Filter", "筛选" },
    { "Name", "名称" },
    { "Description", "描述" },
    { "Position", "位置" },
    { "Size", "大小" },
    { "Value", "数值" },
    { "Color", "颜色" },
    { "Slot", "栏位" },
    { "Map", "地图" },
    { "Random", "随机" },
    { "Load", "加载" },
    { "Preview", "预览" },
    { "Play", "播放" },
    { "Pause", "暂停" },
    { "Legend", "图例" },
    { "Group", "分组" },
    { "Clear", "清除" },
    { "Highlight", "高亮" },
    { "Host", "主机" },
    { "Ghost", "幽灵" },
    { "Guest", "访客" },
    { "List", "列表" },
    { "Deselect", "取消选择" },
    { "Address", "地址" },
    { "Category", "类别" },
    { "Params", "参数" },
    { "Rotation", "旋转" },
    { "Never", "从不" },
    { "Disabled", "已禁用" },
    { "Active", "活动" },
    { "Registered", "已注册" },
    { "Duration", "持续时间" },

    // ==== MOD 菜单 (SohModMenu) ====
    { "Attempt to fix crashes when loading mods", "尝试修复加载 MOD 时的崩溃" },
    { "Delete Mod", "删除 MOD" },
    { "Disable Mod", "禁用 MOD" },
    { "Enable Mod", "启用 MOD" },
    { "Failed to load mod", "加载 MOD 失败" },
    { "Loaded Mods", "已加载的 MOD" },
    { "Memory Contradiction", "内存冲突" },
    { "Mod Directory", "MOD 目录" },
    { "Mod loaded successfully", "MOD 加载成功" },
    { "No mods found", "未找到 MOD" },
    { "Open Mod Directory", "打开 MOD 目录" },
    { "Reload Mods", "重新加载 MOD" },
    { "Restart required", "需要重启" },

    // ==== 网络 (SohMenuNetwork / Anchor) ====
    { "Client Colors", "客户端颜色" },
    { "Connecting...", "连接中..." },
    { "Connected", "已连接" },
    { "Only Anchor and Crowd Control cannot be enabled at the same time", "锚点与人群控制不能同时启用" },
    { "Server Host", "服务器地址" },
    { "Server Port", "服务器端口" },
    { "Anchor Settings", "锚点设置" },
    { "Randomizer needs to be enabled to use Anchor!", "使用锚点需要先启用随机器！" },
    { "Copied to clipboard", "已复制到剪贴板" },
    { "Host & Port", "地址与端口" },
    { "About Crowd Control", "关于人群控制" },
    { "Connect to Crowd Control", "连接到人群控制" },
    { "Additional Settings", "附加设置" },
    { "Enemy Name Tags", "敌人名称标签" },
    { "Spawned Enemies Ignored Ingame", "生成的敌人在游戏内被忽略" },

    // ==== 音频编辑器 (SohMenuAudioEditor) ====
    { "Load All", "全部加载" },
    { "Sequences", "音序" },
    { "SFX", "音效" },
    { "Unload All", "全部卸载" },

    // ==== 外观编辑器 (CosmeticsEditor) ====
    { "Cosmetic Editor", "外观编辑器" },
    { "Cosmetics Editor - Fix static [rainbow effect]?", "外观编辑器 - 修复静态[彩虹效果]？" },
    { "Link's Hair", "林克的头发" },
    { "Lock/Unlock all", "锁定/解锁全部" },
    { "Locked", "已锁定" },
    { "Randomize all", "全部随机" },
    { "Randomize enabled", "随机已启用" },
    { "Reset all", "全部重置" },
    { "Rainbow", "彩虹" },
    { "Unlocked", "已解锁" },

    // ==== 高级分辨率 (AdvancedResolutionSettings) ====
    { "Advanced Resolution", "高级分辨率" },
    { "Aspect Ratio", "宽高比" },
    { "Vertical Resolution", "垂直分辨率" },
    { "Visual Guide", "视觉参考线" },
    { "Integer Scaling", "整数缩放" },
    { "Aspect Ratio (X:Y)", "宽高比 (X:Y)" },
    { "Ratio to Vertical Res.", "相对垂直分辨率比例" },
    { "Advanced Resolution Settings", "高级分辨率设置" },
    { "Read the description", "请阅读说明" },

    // ==== 输入编辑器 (SohInputEditorWindow / cvarInputEditor) ====
    { "Attention:", "注意：" },
    { "Cluster", "群组" },
    { "Devices", "设备" },
    { "Gyro Options", "陀螺仪选项" },
    { "Gyro Sensitivity", "陀螺仪灵敏度" },
    { "Gyro X", "陀螺仪 X" },
    { "Gyro Y", "陀螺仪 Y" },
    { "Mappings", "映射" },
    { "Add Mapping", "添加映射" },
    { "Rumble", "振动" },
    { "Rumble Strength", "振动强度" },
    { "Threshold", "阈值" },
    { "Deadzone", "死区" },
    { "Notch Snap Angle", "卡位吸附角度" },
    { "Bumper", "缓冲区" },
    { "Turbo", "连发" },
    { "Turbo Threshold", "连发阈值" },
    { "Analog Stick", "摇杆" },
    { "Rumble Devices", "振动设备" },
    { "Left Stick", "左摇杆" },
    { "Right Stick", "右摇杆" },
    { "Gyro", "陀螺仪" },
    { "Sensitivity", "灵敏度" },
    { "Enable Rumble", "启用振动" },
    { "Extra Buttons", "额外按键" },
    { "First Person Camera Sensitivity X", "第一人称镜头灵敏度 X" },
    { "First Person Camera Sensitivity Y", "第一人称镜头灵敏度 Y" },
    { "Bindings", "绑定" },
    { "Additional Bindings", "附加绑定" },
    { "Clear All", "全部清除" },
    { "Reset to Defaults", "恢复默认" },
    { "D-Pad", "方向键" },
    { "C Buttons", "C 键" },

    // ==== 检查追踪器 (randomizer_check_tracker) ====
    { "Area Incomplete", "区域未完成" },
    { "Area Complete", "区域已完成" },
    { "Collected", "已收集" },
    { "Details", "详情" },
    { "Vanilla/MQ Dungeon Spoilers", "原版/MQ 地牢剧透" },
    { "Hide Unshuffled Shop Item Checks", "隐藏未洗牌的商店道具检查" },
    { "Always Show Gold Skulltulas", "始终显示金色骷髅蜘蛛" },
    { "Enable Available Checks", "启用可用检查" },
    { "Spawn", "生成" },
    { "Spawn as Child", "以童年形态生成" },
    { "Best of Luck", "祝你好运" },
    { "Checks", "检查项" },
    { "Collapse All", "全部折叠" },
    { "Expand All", "全部展开" },
    { "Hide Completed Checks", "隐藏已完成检查" },
    { "Hide Checks", "隐藏检查" },
    { "Show Hidden", "显示隐藏" },
    { "Skipped", "已跳过" },
    { "Scummed", "已刷档" },
    { "Seen", "已见" },
    { "Show Logic", "显示逻辑" },
    { "Unchecked", "未检查" },
    { "Checked", "已检查" },
    { "Saved", "已保存" },
    { "Hints", "提示" },
    // 检查追踪器颜色区段说明 tooltip（ImGuiDrawTwoColorPickerSection）
    { "Checks you have not interacted with at all.", "你完全没有互动过的检查项。" },
    { "Used for shops. Shows item names for shop slots when walking in, and prices when highlighting them in buy mode.",
      "用于商店。进入时显示商店格位的道具名称，在购买模式下高亮时显示价格。" },
    { "Checks you collect, but then reload before saving so you no longer have them.",
      "你已收集，但在保存前重新读档、因而不再拥有的检查项。" },
    { "Checks you have collected without saving or reloading yet.", "你已收集但尚未保存或重新读档的检查项。" },
    { "Checks that you saved the game while having collected.", "你在已收集状态下保存了游戏的检查项。" },
    { "When active, checks will hide by default when updated to this state. Can "
              "be overridden with the \"Show Hidden Items\" option.",
      "启用后，检查项更新至此状态将默认隐藏。可通过\"显示隐藏项目\"选项覆盖。" },

    // ==== 入口追踪器 (randomizer_entrance_tracker) ====
    { "Last Entrance", "上一个入口" },
    { "Show Vanilla", "显示原版" },
    { "Spoiler", "剧透" },
    { "Need to be in game to view entrances", "需进入游戏才能查看入口" },
    { "Sphere", "层级" },

    // ==== 道具追踪器 (randomizer_item_tracker) ====
    { "Item Tracker Settings", "道具追踪设置" },
    { "Track Bottled Contents", "追踪瓶装内容" },
    { "Current Ammo/Capacity", "当前弹药/容量" },
    { "Key Counts", "钥匙数量" },
    { "Only Show Key Counts", "仅显示钥匙数量" },
    { "Show all item slots", "显示所有道具栏" },
    { "Gauntlet Colors", "护手颜色" },
    { "Show Gear Menu", "显示装备菜单" },
    { "Draw Values", "绘制数值" },
    { "Text Color", "文字颜色" },
    { "Background Color", "背景颜色" },
    { "Draw Ammo", "绘制弹药" },
    { "Draw Key Counts", "绘制钥匙数量" },

    // ==== 存档编辑器补充 (debugSaveEditor) ====
    { "Bank", "存款" },
    { "Boss Key", "BOSS 钥匙" },
    { "Compass", "罗盘" },
    { "Current Scene", "当前场景" },
    { "Dungeon", "迷宫" },
    { "Flag", "标志" },
    { "Gold Skulltulas", "金色骷髅蜘蛛" },
    { "Infinite", "无限" },
    { "Inventory", "道具栏" },
    { "Player State", "玩家状态" },
    { "Quest Status", "任务状态" },
    { "Scene Flags", "场景标志" },
    { "Small Keys", "小钥匙" },
    { "Grotto ID", "洞穴 ID" },
    { "Grotto Chest Flags", "洞穴宝箱标志" },
    { "Grotto ID (Full)", "洞穴 ID（完整）" },
    { "Overworld", "大地图" },
    { "Actor Flags", "角色标志" },
    { "Bombchus", "炸弹鼠" },

    // ==== 角色查看器 (actorViewer) ====
    { "Actor List", "角色列表" },

    // ==== 钩子调试器 (hookDebugger) ====
    { "Hooks", "钩子" },
    { "Fire count", "触发次数" },

    // ==== 碰撞查看器 (colViewer) ====
    { "Waterbox", "水域盒" },
    { "Wireframe", "线框" },
    { "Line Width", "线宽" },

    // ==== 显示列表查看器 (dlViewer) ====
    { "Sideload", "侧载" },

    // ==== 游戏统计 (gameplaystats) ====
    { "Enimies Defeated", "击败敌人数" },
    { "Ammo Used", "弹药使用量" },
    { "Damage Taken", "受到伤害" },
    { "Game Time", "游戏时间" },
    { "Steps Taken", "步数" },
    { "Timestamps", "时间戳" },
    { "Analog Angles", "摇杆角度" },
    { "Displays", "显示项" },
    { "Total Time", "总时间" },

    // ==== 通知 (Notification) ====
    { "Notifications", "通知" },
    { "Background Opacity", "背景不透明度" },
    { "Font Size", "字体大小" },
    { "Top Left", "左上" },
    { "Top Right", "右上" },
    { "Bottom Left", "左下" },
    { "Bottom Right", "右下" },
};

const char* L(const char* english) {
    if (english == nullptr || !gMenuChinese) {
        return english;
    }
    // ImGui labels may carry a "##" suffixed internal ID (e.g. "Reset##Link_BodySize").
    // The translation table keeps the full label (including "##id") as the key so that widget
    // IDs remain unique after translation. Look up the full string first; if it is missing, fall
    // back to the visible text before "##".
    auto it = gChineseTable.find(english);
    if (it != gChineseTable.end()) {
        return it->second.c_str();
    }
    std::string key = english;
    auto sep = key.find("##");
    if (sep != std::string::npos) {
        key = key.substr(0, sep);
        auto it2 = gChineseTable.find(key);
        if (it2 != gChineseTable.end()) {
            return it2->second.c_str();
        }
    }
    return english;
}

} // namespace SohGui
