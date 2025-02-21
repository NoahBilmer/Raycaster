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

//#define PLATFORM_WEB 1

std::unique_ptr<Game> game;
Input input;
std::shared_ptr<Screen> currScreen;
RenderTexture2D Screen::mainLayer;
RenderTexture2D Screen::secondaryLayer;
unsigned char Screen::secondaryLayerTransparency;
unsigned char Screen::mainLayerTransparency;

void update();
/**
 * Entry point of the program.
 */
int main(void)
{
    Screen::setupScreenArray();
    Screen::mainLayer = LoadRenderTexture(Screen::screenWidth, Screen::screenHeight);
    Screen::mainLayerTransparency = 255;
    Screen::secondaryLayer = LoadRenderTexture(Screen::screenWidth, Screen::screenHeight);
    Screen::secondaryLayerTransparency = 255;
    currScreen = Screen::getInstanceOf<Game>();

    // Init the game
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
 * the required update function for the current screen.
 */
void update() {
    Screen::scale = MIN((float)GetScreenWidth() / Screen::screenWidth, (float)GetScreenHeight() / Screen::screenHeight);
    input.getInput();
    currScreen = currScreen.get()->update(input);
    BeginDrawing();
        DrawTexturePro(Screen::mainLayer.texture, Rectangle{ 0.0f, 0.0f, (float)Screen::mainLayer.texture.width, (float)-Screen::mainLayer.texture.height },
            Rectangle{ (GetScreenWidth() - ((float)Screen::screenWidth * Screen::scale)) * 0.5f, (GetScreenHeight() - ((float)Screen::screenHeight * Screen::scale)) * 0.5f,
            (float)Screen::screenWidth * Screen::scale, (float)Screen::screenHeight * Screen::scale },
            Vector2{ 0, 0 }, 0.0f, Color{255,255,255,Screen::mainLayerTransparency});
        
        DrawTexturePro(Screen::secondaryLayer.texture, Rectangle{ 0.0f, 0.0f, (float)Screen::secondaryLayer.texture.width, (float)-Screen::secondaryLayer.texture.height },
            Rectangle{ (GetScreenWidth() - ((float)Screen::screenWidth * Screen::scale)) * 0.5f, (GetScreenHeight() - ((float)Screen::screenHeight * Screen::scale)) * 0.5f,
            (float)Screen::screenWidth * Screen::scale, (float)Screen::screenHeight * Screen::scale },
            Vector2{ 0, 0 }, 0.0f, Color{ 255,255,255,Screen::secondaryLayerTransparency });
        ClearBackground(BLACK);
    EndDrawing();
}