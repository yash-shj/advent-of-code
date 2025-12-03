param(
    [Parameter(Mandatory = $true)]
    [int]$Day,

    [int]$Year
)

# Default to current year if not provided
if (-not $Year) {
    $Year = (Get-Date).Year
}

# Validate Day
if ($Day -lt 1 -or $Day -gt 25) {
    Write-Host "Error: Day must be between 1 and 25."
    exit 1
}

# Compute project root (one folder above scripts/)
$projectRoot = Split-Path $PSScriptRoot -Parent

# Template file (absolute path)
$templateFile = Join-Path $projectRoot "template.cpp"
if (-not (Test-Path $templateFile)) {
    Write-Host "Error: template.cpp not found in root directory."
    exit 1
}

# Format day as two digits (01, 02, ...)
$dayStr = "{0:D2}" -f $Day

# Folder paths
$yearPath = Join-Path $projectRoot "$Year"
$dayPath  = Join-Path $yearPath  ("day$dayStr")

# Prevent overwriting existing folder
if (Test-Path $dayPath) {
    Write-Host "Error: folder for Year $Year, Day $dayStr already exists."
    exit 1
}

# Ensure year folder exists
if (-not (Test-Path $yearPath)) {
    New-Item -ItemType Directory -Path $yearPath | Out-Null
}

# Create folders
New-Item -ItemType Directory -Path $dayPath | Out-Null
New-Item -ItemType Directory -Path (Join-Path $dayPath "input")  | Out-Null
New-Item -ItemType Directory -Path (Join-Path $dayPath "output") | Out-Null

# Example input file
New-Item -ItemType File -Path (Join-Path $dayPath "input/example.txt") | Out-Null

# Copy template as main.cpp
Copy-Item $templateFile (Join-Path $dayPath "main.cpp")

Write-Host "OK: folder for Year $Year, Day $dayStr created."
