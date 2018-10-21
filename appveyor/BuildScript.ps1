# stop script execution if error occurs
$ErrorActionPreference = "Stop"
# run CMake
New-Item build -ItemType directory
Set-Location build
& cmake .. -G "$env:CMakeGeneratorName" -DBUILD_EXAMPLE=ON -DBUILD_TESTS=ON -DBUILD_DOCS=ON -DCMAKE_BUILD_TYPE=$env:CONFIGURATION
# build - docs aren't included in default build target and have to be build seperately
& cmake --build . --config "$env:CONFIGURATION" -- $env:CMakeCompilerSpecificFlags
& cmake --build . --config "$env:CONFIGURATION" --target "docs"
Set-Location ..
