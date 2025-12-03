param(
    [Parameter(Mandatory = $true)]
    [int]$Day,

    [Parameter(Mandatory = $true)]
    [int]$Part,

    [Parameter(Mandatory = $true)]
    [string]$InputFile,

    [int]$Year
)

# Default Year (if not provided)
if (-not $Year) {
    $Year = (Get-Date).Year
}

# Validate Day
if ($Day -lt 1 -or $Day -gt 25) {
    Write-Host "Error: Day must be between 1 and 25."
    exit 1
}

# Validate Part
if ($Part -ne 1 -and $Part -ne 2) {
    Write-Host "Error: Part must be 1 or 2."
    exit 1
}

# Compute project root (one level above scripts/)
$projectRoot = Split-Path $PSScriptRoot -Parent

# Format day number (01, 02, ...)
$dayStr = "{0:D2}" -f $Day
$dayPath = Join-Path $projectRoot "$Year/day$dayStr"

# Check puzzle folder exists
if (-not (Test-Path $dayPath)) {
    Write-Host "Error: folder for Year $Year, Day $dayStr not found."
    exit 1
}

# Resolve input file path
$inputPath = Join-Path $dayPath "input/$InputFile.txt"

if (-not (Test-Path $inputPath)) {
    Write-Host "Error: input file '$InputFile.txt' not found."
    exit 1
}

# Resolve output file path
$outputFile = Join-Path $dayPath "output/$InputFile.part$Part.txt"

# Ensure build directory exists
$buildDir = Join-Path $projectRoot "build"
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

# Source and executable paths
$sourceFile = Join-Path $dayPath "main.cpp"
$exeFile = Join-Path $buildDir "day$dayStr.exe"

# Compile
Write-Host "Compiling..."
g++ -std=c++17 "$sourceFile" -o "$exeFile"
if ($LASTEXITCODE -ne 0) {
    Write-Host "Error: compilation failed."
    exit 1
}
Write-Host "OK: compiled."

# Run
Write-Host "Running..."
$inputContent = Get-Content $inputPath
$result = $inputContent | & $exeFile $Part

if ($LASTEXITCODE -ne 0) {
    Write-Host "Error: execution failed."
    exit 1
}

# Save output
Set-Content -Path $outputFile -Value $result

# Convert absolute path to relative path
$relativeOutput = $outputFile.Replace($projectRoot + "\", "")
Write-Host "OK: output saved to $relativeOutput"