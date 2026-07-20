@echo off
cd /d e:\Desktop\Shipwright-CN-cn-full
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
set VCPKG_ROOT=
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_POLICY_VERSION_MINIMUM=3.5 > configure.log 2>&1
echo CONFIGURE_EXIT=%ERRORLEVEL% >> configure.log
