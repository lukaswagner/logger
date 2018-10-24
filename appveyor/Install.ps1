# stop script execution if error occurs
$ErrorActionPreference = "Stop"
# setup vars and install dependencies based OS
if($isWindows)
{
    # on Windows, VS is used
    $env:CMakeGeneratorName = 'Visual Studio 15 2017 Win64'
    # Make VS shut up
    $env:CMakeCompilerSpecificFlags = '/m;/verbosity:minimal;/logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"'
    # decrypt github token - only done on windows since we'll only push once anyway
    if("$env:docs_deploy_secret" -ne "")
    {
        Invoke-Expression ((New-Object Net.WebClient).DownloadString('https://raw.githubusercontent.com/appveyor/secure-file/master/install.ps1'))
        & appveyor-tools/secure-file -decrypt appveyor/DocsDeployKey.enc -secret $env:docs_deploy_secret
    }
    # install doxygen using chocolatey
    & cinst doxygen.install
}
else
{
    # on Linux, make is used
    $env:CMakeGeneratorName = 'Unix Makefiles'
    # install doxygen using apt
    & sudo apt install -y doxygen
}
