# $ErrorActionPreference and CMake don't work properly together, so we'll have to track the result manually
$result = 0
# run CMake
New-Item build -ItemType directory
Set-Location build
cmake .. -G "$env:CMakeGeneratorName" -DBUILD_EXAMPLE=ON -DBUILD_TESTS=ON -DBUILD_DOCS=ON -DCMAKE_BUILD_TYPE=$env:CONFIGURATION
$result = $result -bor $LASTEXITCODE
# build - docs aren't included in default build target and have to be build seperately
cmake --build . --config $env:CONFIGURATION -- ($env:CMakeCompilerSpecificFlags -split ';')
$result = $result -bor $LASTEXITCODE
cmake --build . --config $env:CONFIGURATION --target "docs" -- ($env:CMakeCompilerSpecificFlags -split ';')
$result = $result -bor $LASTEXITCODE
Set-Location ..
return $result
