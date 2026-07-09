$ErrorActionPreference = 'Stop'
$rel = 'e:\Shipwright-wind-waker-style-cel-shading\x64\Release'
$out = 'e:\Shipwright-wind-waker-style-cel-shading\soh-cel-shading-release.zip'

if (Test-Path $out) { Remove-Item $out -Force }

Push-Location $rel
try {
    $items = @(
        'soh.exe',
        'DroidSansFallback.ttf',
        'shipofharkinian.json',
        'oot.o2r',
        'soh.o2r',
        'assets',
        'mods',
        'Save'
    )
    # Only include items that actually exist
    $items = $items | Where-Object { Test-Path $_ }
    Write-Output ("Packing: " + ($items -join ', '))
    Compress-Archive -Path $items -DestinationPath $out -CompressionLevel Optimal
} finally {
    Pop-Location
}

$size = (Get-Item $out).Length
Write-Output ("Created: " + $out)
Write-Output ("Size (MB): " + [math]::Round($size/1MB, 1))
