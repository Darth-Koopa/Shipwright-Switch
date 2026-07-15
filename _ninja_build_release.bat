@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
if errorlevel 1 exit /b 1
set PATH=e:\SOHCN\ninja_bin;%PATH%
ninja -C e:\SOHCN\build\ninja-release %1
