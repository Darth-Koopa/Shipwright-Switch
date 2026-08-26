@echo off
cd /d e:\Desktop\Shipwright-CN-cn-full
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
set VCPKG_ROOT=
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_POLICY_VERSION_MINIMUM=3.5
if errorlevel 1 (
    echo CONFIGURE_FAILED
    exit /b 1
)
echo CONFIGURE_DONE
