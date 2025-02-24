echo Compiling for web...
emcc -o raycaster.html -s EXPORTED_FUNCTIONS=["_free","_malloc","_main"] -s EXPORTED_RUNTIME_METHODS=ccall ^
 src/main.cpp src/Map.cpp src/Input.cpp src/Helpers.cpp src/Game.cpp src/ui/Button.cpp src/PauseScreen.cpp src/Player.cpp src/RayCaster.cpp src/Screen.cpp src/TitleScreen.cpp ^
-Wall -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I. ^
-I C:/raylib/raylib/src -I C:/raylib/raylib/src/external -L. -L C:/raylib/raylib/src -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s ^
FORCE_FILESYSTEM=1 --shell-file C:/raylib/raylib/src/shell.html C:/raylib/raylib/src/web/libraylib.a -s ASSERTIONS ^
-DPLATFORM_WEB -s ALLOW_MEMORY_GROWTH^
