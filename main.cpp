/*******************************************************************************************
* Raycaster by Noah Bilmer
********************************************************************************************/

#include "input.h"
#include "raymath.h"
#include "raylib.h"
#include "Player.h"
#include "Map.h"
#include "stdio.h"
#include "string.h"
#include <iostream>
#include "Game.h"

//#define PLATFORM_WEB 1


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
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