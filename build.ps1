# Collect every .cpp file in src/ (all subfolders) and in libs/imgui/
$src = @(Get-ChildItem -Path src -Recurse -Filter *.cpp) +
       @(Get-ChildItem -Path libs/imgui -Filter *.cpp) |
       ForEach-Object { $_.FullName }

g++ -Wfatal-errors -Wno-template-body -O2 -std=c++17 -I"./libs/" -I"C:/msys64/ucrt64/include/SDL2" $src -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer "-llua5.3" -o gameengine.exe

if ($LASTEXITCODE -eq 0) { Write-Host "BUILD OK" -ForegroundColor Green }