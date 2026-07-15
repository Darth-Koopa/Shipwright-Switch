@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
if errorlevel 1 exit /b 1
set PATH=e:\SOHCN\ninja_bin;%PATH%
set VCPKG_ROOT=E:\SOHCN\build\x64\vcpkg
"C:\Program Files\CMake\bin\cmake.exe" -S e:\SOHCN -B e:\SOHCN\build\ninja -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_REMOTE_CONTROL=ON
