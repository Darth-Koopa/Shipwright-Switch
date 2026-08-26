#!/usr/bin/env pwsh
# Generate chinese_menu_hd.o2r — HD texture mod for Chinese UI textures.
#
# PowerShell + System.Drawing equivalent of generate_hd_menu_o2r.py.
# No Python/uv required. Fixes the texture-type constants in the original
# script (which used wrong values and omitted IA16) using the real
# Fast::TextureType enum from libultraship/include/fast/resource/type/Texture.h:
#   I4=5, I8=6, IA4=7, IA8=8, IA16=9
#
# For every Chinese (CHI) custom texture under soh/assets/custom/textures/<folder>/,
# if a matching HD PNG exists at <this_dir>/<folder>/<texName>.png, pack it.
#
# Usage:
#   powershell -ExecutionPolicy Bypass -File generate_hd_menu_o2r.ps1

Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.IO.Compression

$ErrorActionPreference = "Stop"

$HERE  = Split-Path -Parent $MyInvocation.MyCommand.Definition
$REPO  = (Resolve-Path (Join-Path $HERE "..\..\..")).Path
$CUSTOM_DIR = Join-Path $REPO "soh\assets\custom\textures"
$HD_DIR     = $HERE
$OUT_O2R    = Join-Path $REPO "chinese_menu_hd.o2r"

# --- Constants (Fast::TextureType) ---
$RESOURCE_TYPE_TEXTURE = 0x4F544558
$TEX_FLAG_LOAD_AS_RAW  = 1
$I4   = 5
$I8   = 6
$IA4  = 7
$IA8  = 8
$IA16 = 9

function Get-TexTypeFromPngName($name) {
    if ($name -match '\.ia16\.') { return $IA16 }
    if ($name -match '\.ia8\.')  { return $IA8 }
    if ($name -match '\.i8\.')   { return $I8 }
    if ($name -match '\.ia4\.')  { return $IA4 }
    if ($name -match '\.i4\.')   { return $I4 }
    return $IA4
}

function Get-OrigBytesPerRow($origW, $texType) {
    switch ($texType) {
        $IA16 { return $origW * 2.0 }
        $I8   { return $origW * 1.0 }
        $IA8  { return $origW * 1.0 }
        $I4   { return $origW * 0.5 }
        default { return $origW * 0.5 } # IA4
    }
}

# Read width/height from PNG IHDR (bytes 16..23, big-endian).
function Get-PngSize($path) {
    $b = [System.IO.File]::ReadAllBytes($path)
    $w = ($b[16]*16777216)+($b[17]*65536)+($b[18]*256)+$b[19]
    $h = ($b[20]*16777216)+($b[21]*65536)+($b[22]*256)+$b[23]
    return @($w, $h)
}

# Load PNG via System.Drawing, return raw RGBA32 bytes (BGRA -> RGBA swap).
function Get-RgbaBytes($path) {
    $bmp = New-Object System.Drawing.Bitmap($path)
    try {
        $rect = New-Object System.Drawing.Rectangle(0, 0, $bmp.Width, $bmp.Height)
        $bmpd = $bmp.LockBits($rect, [System.Drawing.Imaging.ImageLockMode]::ReadOnly,
                               [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
        $w = $bmp.Width; $h = $bmp.Height
        $stride = $bmpd.Stride
        $ptr = $bmpd.Scan0
        $lineBytes = $w * 4
        $out = New-Object byte[] ($lineBytes * $h)
        for ($y = 0; $y -lt $h; $y++) {
            $srcOff = $y * $stride
            $dstOff = $y * $lineBytes
            for ($x = 0; $x -lt $lineBytes; $x += 4) {
                $b = [System.Runtime.InteropServices.Marshal]::ReadByte($ptr, $srcOff + $x + 0)
                $g = [System.Runtime.InteropServices.Marshal]::ReadByte($ptr, $srcOff + $x + 1)
                $r = [System.Runtime.InteropServices.Marshal]::ReadByte($ptr, $srcOff + $x + 2)
                $a = [System.Runtime.InteropServices.Marshal]::ReadByte($ptr, $srcOff + $x + 3)
                $out[$dstOff + $x + 0] = $r
                $out[$dstOff + $x + 1] = $g
                $out[$dstOff + $x + 2] = $b
                $out[$dstOff + $x + 3] = $a
            }
        }
        $bmp.UnlockBits($bmpd)
        return $out
    } finally {
        $bmp.Dispose()
    }
}

# Build one complete OTR binary resource (mirrors build_otr_resource in the .py).
function New-OtrResource($rgbaData, $origW, $origH, $hdW, $hdH, $texType) {
    $ms = New-Object System.IO.MemoryStream
    $bw = New-Object System.IO.BinaryWriter($ms)
    # OTR header (64 bytes)
    $bw.Write([byte]0); $bw.Write([byte]0); $bw.Write([byte]0); $bw.Write([byte]0)
    $bw.Write([uint32]$RESOURCE_TYPE_TEXTURE)
    $bw.Write([uint32]1)
    # Asset ID 0xDEADBEEFDEADBEEF (8 bytes, little-endian). Written as raw bytes
    # because PowerShell parses the hex literal as a signed long and rejects [uint64] cast.
    foreach ($bb in @(0xEF, 0xBE, 0xAD, 0xDE, 0xEF, 0xBE, 0xAD, 0xDE)) { $bw.Write([byte]$bb) }
    while ($ms.Length -lt 0x40) { $bw.Write([uint32]0) }
    # V1 texture data
    $obpr = Get-OrigBytesPerRow $origW $texType
    $hByteScale = ($hdW * 4.0) / $obpr
    $vPixelScale = [double]$hdH / [double]$origH
    $bw.Write([uint32]$texType)
    $bw.Write([uint32]$hdW)
    $bw.Write([uint32]$hdH)
    $bw.Write([uint32]$TEX_FLAG_LOAD_AS_RAW)
    $bw.Write([single]$hByteScale)
    $bw.Write([single]$vPixelScale)
    $bw.Write([uint32]$rgbaData.Length)
    # Append the raw RGBA bytes via the underlying MemoryStream. Do NOT use
    # $bw.Write($rgbaData): PowerShell mis-resolves BinaryWriter.Write(byte[])
    # and only writes a single byte of the array.
    $bw.Flush()
    $ms.Write($rgbaData, 0, $rgbaData.Length)
    return $ms.ToArray()
}

function Add-ZipEntry($zip, $entryName, $bytes) {
    $ze = $zip.CreateEntry($entryName)
    $s = $ze.Open()
    $s.Write($bytes, 0, $bytes.Length)
    $s.Close()
}

# --- Main ---
if (-not (Test-Path $CUSTOM_DIR)) { Write-Error "Custom dir not found: $CUSTOM_DIR"; exit 1 }
if (Test-Path $OUT_O2R) { Remove-Item $OUT_O2R -Force }

$fs = [System.IO.File]::Create($OUT_O2R)
$zip = New-Object System.IO.Compression.ZipArchive($fs, [System.IO.Compression.ZipArchiveMode]::Create)
try {
    Add-ZipEntry $zip "portVersion" ([System.Text.Encoding]::ASCII.GetBytes("9.2.3"))

    $packed = 0; $skipped = 0
    foreach ($cdir in (Get-ChildItem $CUSTOM_DIR -Directory | Sort-Object Name)) {
        $folder = $cdir.Name
        $hdir = Join-Path $HD_DIR $folder
        foreach ($png in (Get-ChildItem $cdir.FullName -Filter *.png | Sort-Object Name)) {
            if ($png.Name -notmatch 'CHI') { continue }
            $tn = $png.BaseName
            if ($tn -match '\.(ia16|ia8|ia4|i8|i4|rgba16|rgba32)$') {
                $tn = $tn -replace '\.(ia16|ia8|ia4|i8|i4|rgba16|rgba32)$', ''
            }
            $hdPng = Join-Path $hdir "$tn.png"
            if (-not (Test-Path $hdPng)) { $skipped++; continue }

            try {
                $orig = Get-PngSize $png.FullName
                $origW = $orig[0]; $origH = $orig[1]
                $texType = Get-TexTypeFromPngName $png.Name
                $hdSize = Get-PngSize $hdPng
                $hdW = $hdSize[0]; $hdH = $hdSize[1]
                $rgba = Get-RgbaBytes $hdPng
                if ($rgba.Length -ne ($hdW * $hdH * 4)) {
                    Write-Warning "Size mismatch for $tn (rgba len $($rgba.Length) vs $hdW x $hdH x 4); skipping"
                    $skipped++; continue
                }
                $otr = New-OtrResource $rgba $origW $origH $hdW $hdH $texType
                Add-ZipEntry $zip "alt/textures/$folder/$tn" $otr
                $packed++
            } catch {
                Write-Warning "Failed to process $tn : $_"
                $skipped++
            }
        }
    }
} finally {
    $zip.Dispose()
}

$mb = (Get-Item $OUT_O2R).Length / 1MB
Write-Host "Done: $OUT_O2R ($('{0:0.0}' -f $mb) MB, $packed packed, $skipped skipped)"
Write-Host "Place in: mods/chinese_menu_hd.o2r"
