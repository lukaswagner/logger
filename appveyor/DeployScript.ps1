# stop script execution if error occurs
$ErrorActionPreference = "Stop"

# check branch - only deploy docs when master is updated
if ($env:APPVEYOR_REPO_BRANCH -ne 'master')
{
    Write-Output("Currently building on branch $env:APPVEYOR_REPO_BRANCH. Docs will only be deployed when building commits on master.")
    exit
}

# check OS and configuration - make sure docs are only deployed once
if($isLinux)
{
    Write-Output("Currently running on Linux. Docs will only be deployed when building on Windows.")
    exit
}
if($env:CONFIGURATION -eq 'Debug')
{
    Write-Output("Active configuration is Debug. Docs will only be deployed when building Release.")
    exit
}
Write-Output("Running on Windows on branch $env:APPVEYOR_REPO_BRANCH. Configuration is $env:CONFIGURATION. Deploying docs.")

# add deploy key
$docsDeployKey = Join-Path ($env:APPVEYOR_BUILD_FOLDER) 'appveyor/DocsDeployKey'

# if the key file doesn't exist, we can't deploy - this usually means a PR is being build
if(-Not (Test-Path $docsDeployKey))
{
    Write-Output("Deploy key could not be found. This probably means this is a PR build. Skipping docs deployment.")
    exit
}

# don't ask to add the fingerprint on clone
$configFile = "$env:USERPROFILE\.ssh\config"
$configContent = "Host github.com`n`tStrictHostKeyChecking no`n`tIdentityFile $docsDeployKey`n"
Add-Content -Path $configFile -Value $configContent

# clone gh-pages branch
$branch = 'gh-pages'
$repoUri = 'git@github.com:lukaswagner/logger.git'
$cloneDir = 'gh-pages'
# git doens't properly work together with ErrorActionPreference set to Stop
$ErrorActionPreference = "SilentlyContinue"
& git clone -b $branch $repoUri $cloneDir
if($LASTEXITCODE -ne 0) { exit 1 }
$ErrorActionPreference = "Stop"

# clean gh-pages dir
Set-Location $cloneDir
Remove-Item * -Recurse

# copy docs to gh-pages dir
$docsDir = '..\build\html'
Copy-Item $docsDir\* -Recurse

# set up git config
& git config --global push.default simple
& git config user.name $env:APPVEYOR_REPO_COMMIT_AUTHOR
& git config user.email $env:APPVEYOR_REPO_COMMIT_AUTHOR_EMAIL

# commit and push
& git add --all
& git commit -m "Updated docs based on commit: $env:APPVEYOR_REPO_COMMIT" -m "Original commit message: $env:APPVEYOR_REPO_COMMIT_MESSAGE"
# git doens't properly work together with ErrorActionPreference set to Stop
$ErrorActionPreference = "SilentlyContinue"
& git push --force
if($LASTEXITCODE -ne 0) { exit 1 }
