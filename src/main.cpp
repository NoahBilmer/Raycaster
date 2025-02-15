/*******************************************************************************************
* Raycaster by Noah Bilmer
********************************************************************************************/

#include "include/input.h"
#include "raymath.h"
#include "raylib.h"
#include "include/Player.h"
#include "include/Map.h"
#include "stdio.h"
#include "string.h"
#include <iostream>
#include "include/Game.h"

//#define PLATFORM_WEB 1

/**
 * Entry point of the program.
 */
int main(void)
{
    // Setup the window and config flags
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Game::screenWidth, Game::screenHeight, "Raycaster");
    SetWindowSize(Game::screenWidth, Game::screenHeight);
    SetExitKey(KEY_NULL);
    // Init the game
    Game game = Game();
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(game.update, 0, 1);
#   else
    // Main game loop
    while (!WindowShouldClose())
    {
        game.update();
    }
    #endif
    
    return 0;
}