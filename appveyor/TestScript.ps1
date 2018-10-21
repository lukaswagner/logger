# stop script execution if error occurs
$ErrorActionPreference = "Stop"
# test location is different based on OS
if($isWindows)
{
    & build/$env:CONFIGURATION/tests.exe
}
else
{
    & build/tests
}
