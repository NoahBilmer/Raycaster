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
#include "include/Screen.h"
#include "include/TitleScreen.h"
#include "resources/romulus.h"

//#define PLATFORM_WEB 1

std::unique_ptr<Game> game;
Input input;
std::shared_ptr<Screen> currScreen;

void update();
/**
 * Entry point of the program.
 */
int main(void)
{
    // Setup the window and config flags
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Screen::screenWidth, Screen::screenHeight, "Raycaster");
    SetWindowSize(Screen::screenWidth, Screen::screenHeight);
    SetExitKey(KEY_NULL);
    Game::defaultFont = LoadFont_Romulus();

    SetTargetFPS(60);
    // Intialize all of the screens in the application. 
    // Note that this means we will call the constructors of every screen.
    Screen::setupScreenArray();
    
    currScreen = Screen::getInstanceOf<TitleScreen>();

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(update, 0, 1);
#   else
    // Main game loop
    while (!WindowShouldClose())
    {
        update();
    }
    #endif
    
    return 0;
}

/*
 * The update function for the game. Runs every frame, uses polymorphism to call
 * the required update function for the current screen (the update function returns 
 * the next screen to be displayed.)
 */
void update() {
    Screen::scale = MIN((float)GetScreenWidth() / Screen::screenWidth, (float)GetScreenHeight() / Screen::screenHeight);
    input.getInput();
    // Get our next screen
    currScreen = currScreen.get()->update(input);
    // Draw the current screen
    BeginDrawing();
        DrawTexturePro(currScreen.get()->mainLayer.texture, Rectangle{0.0f, 0.0f, (float)currScreen.get()->mainLayer.texture.width, (float)-currScreen.get()->mainLayer.texture.height},
            Rectangle{ (GetScreenWidth() - ((float)Screen::screenWidth * Screen::scale)) * 0.5f, (GetScreenHeight() - ((float)Screen::screenHeight * Screen::scale)) * 0.5f,
            (float)Screen::screenWidth * Screen::scale, (float)Screen::screenHeight * Screen::scale },
            Vector2{ 0, 0 }, 0.0f, Color{255,255,255,currScreen.get()->mainLayerTransparency});
        
        if (currScreen.get()->isUsingSecondaryLayer())
            DrawTexturePro(currScreen.get()->secondaryLayer.texture, Rectangle{ 0.0f, 0.0f, (float)currScreen.get()->secondaryLayer.texture.width, (float)-currScreen.get()->secondaryLayer.texture.height },
                Rectangle{ (GetScreenWidth() - ((float)Screen::screenWidth * Screen::scale)) * 0.5f, (GetScreenHeight() - ((float)Screen::screenHeight * Screen::scale)) * 0.5f,
                (float)Screen::screenWidth * Screen::scale, (float)Screen::screenHeight * Screen::scale },
                Vector2{ 0, 0 }, 0.0f, Color{ 255,255,255,currScreen.get()->secondaryLayerTransparency });
        ClearBackground(BLACK);
    EndDrawing();
}