# stop script execution if error occurs
$ErrorActionPreference = "Stop"

# add deploy key
$docs_deploy_key = Join-Path (Get-Location) 'docs_deploy_key'
Add-Content -Path $docs_deploy_key -Value $env:docs_deploy_key

# don't ask to add the fingerprint on clone
$configFile = "$env:USERPROFILE\.ssh\config"
$configContent = "Host github.com`n`tStrictHostKeyChecking no`n`tIdentityFile $docs_deploy_key`n"
Add-Content -Path $configFile -Value $configContent

# clone gh-pages branch
$branch = 'gh-pages'
$repoUri = 'git@github.com:lukaswagner/logger.git'
$cloneDir = 'gh-pages'
& git clone -b $branch $repoUri $cloneDir

# clean gh-pages dir
Set-Location $cloneDir
Remove-Item * -Recurse

# copy docs to gh-pages dir
$docsDir = '..\html'
Copy-Item $docsDir\* -Recurse

# set up git config
& git config --global push.default simple
& git config user.name $env:APPVEYOR_REPO_COMMIT_AUTHOR
& git config user.email $env:APPVEYOR_REPO_COMMIT_AUTHOR_EMAIL

# commit and push
& git add --all
& git commit -m "Updated docs based on commit: $env:APPVEYOR_REPO_COMMIT" -m "Original commit message: $env:APPVEYOR_REPO_COMMIT_MESSAGE"
& git push --force
