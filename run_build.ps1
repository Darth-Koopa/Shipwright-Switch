cmake --build build/x64 --config Release --target soh > build_log10.txt 2>&1
Add-Content build_log10.txt ("BUILD_RC_" + $LASTEXITCODE)
