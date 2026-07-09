@echo off
cd /d e:\Shipwright-wind-waker-style-cel-shading

REM Proxy so git can reach GitHub via Clash.
SET HTTP_PROXY=http://127.0.0.1:7897
SET HTTPS_PROXY=http://127.0.0.1:7897
SET http_proxy=http://127.0.0.1:7897
SET https_proxy=http://127.0.0.1:7897
SET NO_PROXY=127.0.0.1,localhost

REM Stage any new/changed files (build/, x64/, external/ are gitignored).
git add -A

REM If nothing is staged, there is nothing to back up.
git diff --cached --quiet
if %errorlevel%==0 (
    echo AUTO_PUSH: nothing to commit.
    exit /b 0
)

git commit -m "auto backup %date% %time%"
git push --force origin wind-waker-style-cel-shading
echo AUTO_PUSH_DONE
