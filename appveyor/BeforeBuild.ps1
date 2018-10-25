# $ErrorActionPreference and CMake don't work properly together, so we'll have to track the result manually
$result = 0
# set up dependencies
Set-Location dependencies
cmake . -G "$env:CMakeGeneratorName"
$result = $result -bor $LASTEXITCODE
Set-Location ..
return $result
