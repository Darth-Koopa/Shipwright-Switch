@echo off
cd /d e:\Shipwright-wind-waker-style-cel-shading

REM Proxy so any git network operation can reach GitHub via Clash.
SET HTTP_PROXY=http://127.0.0.1:7897
SET HTTPS_PROXY=http://127.0.0.1:7897
SET http_proxy=http://127.0.0.1:7897
SET https_proxy=http://127.0.0.1:7897

REM 1. Initialize a git repo at the project root.
git init
git checkout -b wind-waker-style-cel-shading

REM 2. Commit identity (repo-local).
git config user.name "LinkFish1"
git config user.email "LinkFish1@users.noreply.github.com"
git config --global credential.helper manager

REM 3. Flatten the 6 nested sub-repos into ordinary files so the whole
REM    project is backed up as one tree (per chosen approach).
for /d %%d in (libultraship ZAPDTR OTRExporter external\imgui external\prism external\ThreadPool) do (
    if exist "%%d\.git" rmdir /s /q "%%d\.git"
)

REM 4. Wire up the remote.
git remote remove origin >nul 2>&1
git remote add origin https://github.com/LinkFish1/Shipwright.git

REM 5. Stage everything (build/, x64/, external/ are already gitignored) and commit.
git add -A
git commit -m "Initial flattened backup of wind-waker-style cel-shading project"
echo SETUP_DONE
