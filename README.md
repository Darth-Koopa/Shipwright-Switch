![Ship of Harkinian](docs/shiptitle.darkmode.png#gh-dark-mode-only)
![Ship of Harkinian](docs/shiptitle.lightmode.png#gh-light-mode-only)

 HEAD
A port of Ship of Harkinian for Android.

# Simplified Chinese Support

This fork adds full Simplified Chinese language support to Ship of Harkinian 9.2.3,
replacing untranslated item names, map labels, and action prompts with Chinese
textures from the iQue Player release.

### Features

- **Chinese message text** — 2115 messages from the iQue ROM, calibrated against
  the N64 Simplified Chinese text dump
- **Chinese UI textures** — action labels (29), item names (112), map labels (34),
  dungeon titles (10), place title cards (57), and boss title cards (10),
  all replaced with iQue-original Chinese versions
- **All-CharChn CJK font** — 2183 custom 16×16 I4 glyphs rendered from
  Source Han Sans SC, covering the complete iQue character set + extended range
- **HD texture packs** — 128×128 RGBA32 HD font glyphs and UI textures,
  compatible with [OoT-Reloaded](https://github.com/GhostlyDark/OoT-Reloaded)

### Quick Start

1. Select **Chinese** in Settings → Language
2. For HD textures, place the two O2R mods in the `mods/` folder:
   ```
   mods/
   ├── chinese_font_hd.o2r    # HD CJK glyphs (use with OoT-Reloaded)
   └── chinese_menu_hd.o2r    # HD UI textures
   ```
3. To build HD font mod (chinese_font_hd.o2r):
   ```bash
   cd scripts/chinese
   uv run message/generate_assets.py      # generates CJK glyphs + message table
   uv run message/generate_hd_font_o2r.py # generates chinese_font_hd.o2r
   ```
4. To build HD textures mod (chinese_menu_hd.o2r):
   ```bash
   cd scripts/chinese
   uv run hd_textures/generate_hd_menu_o2r.py
   ```

### Important Note

This Chinese localization has only been tested with the **NTSC (US)** version of
the ROM. Other regional versions may have untested differences in text IDs or
texture layouts. Please use an NTSC-US ROM for the best experience.

### Tools (`scripts/chinese/`)

| Directory | Purpose |
|-----------|---------|
| `message/` | Message extraction, calibration, and asset code generation |
| `texture_extract/` | iQue ROM texture extraction (XML definitions + N64 format decoders) |
| `hd_textures/` | HD texture sources and O2R packer for UI textures |

See `scripts/chinese/message/README.md` for the full control-code reference
and calibration workflow.

### Acknowledgments

This implementation builds upon work from several projects:

| Project | Role |
|---------|------|
| [sxunix/Shipwright](https://github.com/sxunix/Shipwright) | Original Chinese support framework for SoH 9.1.2 |
| [Xzonn/NintendoOfficialChineseGames](https://github.com/Xzonn/NintendoOfficialChineseGames) | N64 Simplified Chinese text dump used for message calibration |
| [zeldaret/Z64Utils](https://github.com/zeldaret/Z64Utils) | iQue ROM message extraction |
| [GhostlyDark/OoT-Reloaded](https://github.com/GhostlyDark/OoT-Reloaded) | HD font glyph style reference (gray210) and O2R format compatibility |
 aba61af46 (Finished chinese-support code editing)

## Website

Official Website: https://www.shipofharkinian.com/

## Discord

Official Discord: https://discord.com/invite/shipofharkinian

If you're having any trouble after reading through this `README`, feel free to ask for help in the Support text channels. Please keep in mind that we do not condone piracy.

# Quick Start

The Ship does not include any copyrighted assets. You are required to provide a supported copy of the game.

### 1. Verify your ROM dump
You can verify you have dumped a supported copy of the game by using the compatibility checker at https://ship.equipment/. If you'd prefer to manually validate your ROM dump, you can cross-reference its `sha1` hash with the hashes [here](docs/supportedHashes.json).

### 2. Install the APK
Download and install the APK from the [Releases](https://github.com/please-be-nice/Shipwright-android/releases) page.

### 3. Set up the game

1. Open the app and allow all file permissions. It will ask to set up files, let it finish.

2. When prompted, select "Yes" to generate an OTR and "Yes" to look for a ROM. Navigate to your ROM and select it. Extraction will begin.

3. When asked whether to extract another ROM, select "Yes" if you have a Master Quest ROM or "No" to start the game.

4. On subsequent launches the game starts directly. To get the ROM selection dialog back, delete the `.otr` files in the `SOH` folder at the root of your device storage.

Use the *Back/Select/-* button on your controller to open the **Enhancements menu**. Use touch controls or a controller to navigate menus.

### 4. Play!

Congratulations, you are now sailing with the Ship of Harkinian! Have fun!

# FAQ

**Q: How do I add mods?**

A: Place mod `.otr` and `.o2r` files in the `SOH` folder at the root of your device storage. Then enable them in the Enhancements menu under Mods.

**Q: The game crashes immediately on launch.**

A: Delete the `SOH` folder and let the app set up its files again. Be patient during black screens; extraction can take a minute.

**Q: The game opened once but now shows a black screen.**

A: Delete `imgui.ini` from your `SOH` folder. Also ensure MSAA is set to 1 in the graphics settings, as higher values cause a black screen on many devices.

**Q: My controller's menu button isn't opening the Enhancements menu.**

A: This is a known first-launch issue caused by Android's input device registration. Close and reopen the app; the controller will work correctly on the second launch.

**Q: D-pad doesn't navigate the menu on first launch.**

A: Same cause as above. Close and reopen the app after the initial ROM extraction completes.

**Q: Touch overlay buttons aren't remappable in the controls editor.**

A: Open the controls editor (Enhancements menu) and look for the "Touch Controls" section under the Link tab. Touch overlay buttons appear as "Touch Overlay" in the device list and can be remapped there.

**Q: Rumble doesn't work with my Bluetooth controller.**

A: External Bluetooth controller rumble is not currently supported. Rumble works via device vibration on handheld devices (e.g. Retroid Pocket). A fix for Bluetooth controller rumble is planned.

# Known Bugs

- External Bluetooth controller rumble is not supported. Device vibration is used as a fallback.
- Touch overlay and physical controller button mappings share the same slot per port, so you cannot assign different actions to the same button on each.

# Build

### Build Tools

- [Ubuntu Noble Numbat | 24.04.2 LTS](https://releases.ubuntu.com/noble/)
- [CMake 3.31.5](https://github.com/Kitware/CMake/releases)
- [OpenJDK 17](https://jdk.java.net/archive/)
- Android SDK 31
- Android NDK 26.0.10792818
- Android Gradle Plugin (AGP) 8.10.1
- Gradle 8.11.1

### Build Instructions

Building requires [Docker](https://docs.docker.com/get-docker/) (or any OCI-compatible tool such as Podman) on a Linux environment. Windows users should use WSL2 and clone the repository to a native Linux path (e.g. `~/Shipwright`) rather than a Windows-mounted path (e.g. `/mnt/c/...`), as NTFS mounts can cause build issues.

1. Clone the repository and submodules:

    ```bash
    git clone https://github.com/please-be-nice/Shipwright-android.git
    cd Shipwright-android
    git submodule update --init --recursive
    ```

2. Pull the build container:

    ```bash
    cd docker
    make setup
    ```

    If you prefer not to use the published image, you can build it locally from the included `Containerfile` instead:

    ```bash
    cd docker
    make create_container
    ```

3. Build the APK:

    ```bash
    make build_release
    ```

The resulting APK will be at `Android/app/build/outputs/apk/release/`.

`make setup` only needs to be run once. On subsequent builds, `make build_release` is all that's needed.
