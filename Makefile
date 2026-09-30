$makefile = @'
CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors -O2
INCLUDE_PATH = -I"./libs/" -I"C:/msys64/ucrt64/include/SDL2"
SRC_FILES = $(wildcard ./src/*.cpp ./src/Game/*.cpp ./src/Logger/*.cpp ./src/ECS/*.cpp ./src/AssetStore/*.cpp ./libs/imgui/*.cpp)
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua
OBJ_NAME = gameengine.exe

.RECIPEPREFIX = >

build:
> $(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)

release:
> $(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -mwindows -o $(OBJ_NAME)

run:
> .\$(OBJ_NAME)

clean:
> del $(OBJ_NAME)
'@
Set-Content -Path C:\2dgameengine\Makefile -Value $makefile -Encoding ascii