$ErrorActionPreference = 'Continue'
$log = 'e:\SOHCN\build.log'
function Log($m) { Add-Content -Path $log -Value ("[{0:HH:mm:ss}] $m" -f (Get-Date)) }

Log '==== Build start ===='
$cmake = 'C:\Program Files\CMake\bin\cmake.exe'
$root  = 'e:\SOHCN'
$build = 'e:\SOHCN\build\x64'

# 0) 环境摘要
Log "cmake: $cmake"
Log "PWD:   $(Get-Location)"
Log "HTTP_PROXY=$($env:HTTP_PROXY) HTTPS_PROXY=$($env:HTTPS_PROXY)"

# 1) cmake 配置（会自动 vcpkg_bootstrap + 安装 15 个依赖库，最耗时）
Log '--- [1/3] cmake configure (vcpkg bootstrap + install deps) ---'
& $cmake -S $root -B $build -G "Visual Studio 17 2022" -T v143 -A x64 *> 'e:\SOHCN\configure.log'
Log ("configure exit code: " + $LASTEXITCODE)
if ($LASTEXITCODE -ne 0) { Log '!! CONFIGURE FAILED -- see configure.log'; exit 1 }

# 2) 生成 soh.o2r
Log '--- [2/3] target GenerateSohOtr ---'
& $cmake --build $build --target GenerateSohOtr *> 'e:\SOHCN\genotr.log'
Log ("GenerateSohOtr exit code: " + $LASTEXITCODE)

# 3) 编译主工程
Log '--- [3/3] build soh ---'
& $cmake --build $build *> 'e:\SOHCN\buildmain.log'
Log ("build exit code: " + $LASTEXITCODE)

Log '==== Build end ===='
