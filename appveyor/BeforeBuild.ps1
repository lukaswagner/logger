# stop script execution if error occurs
$ErrorActionPreference = "Stop"
# set up dependencies
Set-Location dependencies
& cmake . -G "$env:CMakeGeneratorName"
Set-Location ..
