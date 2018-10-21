# stop script execution if error occurs
$ErrorActionPreference = "Stop"
# setup vars and install dependencies based OS
if($isWindows)
{
    # on Windows, VS is used
    [System.Environment]::SetEnvironmentVariable("CMakeGeneratorName", "Visual Studio 15 2017 Win64", "Machine")
    # Make VS shut up
    [System.Environment]::SetEnvironmentVariable("CMakeCompilerSpecificFlags", "/m /verbosity:minimal /logger:`"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll`"", "Machine")
    # decrypt github token - only done on windows since we'll only push once anyway
    Invoke-Expression ((New-Object Net.WebClient).DownloadString('https://raw.githubusercontent.com/appveyor/secure-file/master/install.ps1'))
    if("$env:docs_deploy_secret" -ne "") { & appveyor-tools/secure-file -decrypt docs_deploy_key.enc -secret $env:docs_deploy_secret }
    # install doxygen using chocolatey
    & cinst doxygen.install
}
else
{
    # on Linux, make is used
    [System.Environment]::SetEnvironmentVariable("CMakeGeneratorName", "Unix Makefiles", "Machine")
    # install doxygen using apt
    & sudo apt install -y doxygen
}
