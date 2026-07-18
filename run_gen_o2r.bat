@echo off
setlocal
cd /d E:\Desktop\Shipwright-CN-cn-full

echo === Building ZAPD ===
cmake --build build --config Release --target ZAPD > o2r_build.log 2>&1
if %ERRORLEVEL% neq 0 (
  echo ZAPD build failed with %ERRORLEVEL%
  echo ZAPD_EXIT=%ERRORLEVEL% >> o2r_build.log
  exit /b %ERRORLEVEL%
)
echo ZAPD build OK

echo === Generating soh.o2r ===
cmake --build build --config Release --target GenerateSohOtr >> o2r_build.log 2>&1
echo GEN_EXIT=%ERRORLEVEL% >> o2r_build.log
if %ERRORLEVEL% neq 0 (
  echo GenerateSohOtr failed with %ERRORLEVEL%
  exit /b %ERRORLEVEL%
)
echo GenerateSohOtr OK
exit /b 0
