@echo off
cd /d e:\Desktop\Shipwright-CN-cn-full
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
set VCPKG_ROOT=
cmake --build build --config Release --target soh > build.log 2>&1
echo BUILD_EXIT=%ERRORLEVEL% >> build.log
