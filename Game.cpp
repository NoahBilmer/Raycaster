#include "Game.h"
#include "raymath.h"
#include "raylib.h"
#include "Player.h"
#include "Map.h"
#include "stdio.h"
#include "string.h"
#include <iostream>

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

Game::Game() {

    player = Player({ 500,500 });
    map = Map(" ");
    frameCounter = 0;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Raycaster");
    SetWindowSize(screenWidth, screenHeight);

    target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // Texture scale filter to use
    float frameCounter = 0;

    map.loadMap("map");

    SetTargetFPS(60);
}

void Game::update() {
    // Start by getting input
    getInput();
    // update the position to match the desired movement every frame. 
    player.updatePosition();

    frameCounter++;
    // Render 
    render();
}

void Game::render() {
    float scale = MIN((float)GetScreenWidth() / screenWidth, (float)GetScreenHeight() / screenHeight);
    Vector2 position = player.getPosition();
    Vector2 look = player.getLookVec();
    BeginDrawing();

    ClearBackground(RAYWHITE);

    for (Line line : map.getMap()) {
        DrawLineEx(line.p1, line.p2, 3, line.color);
    }


    char positionStr[50];
    std::snprintf(positionStr, 50, "Position: (%f,%f)", position.x, position.y);
    char lookStr[50];
    std::snprintf(lookStr, 50, "LookVec: (% f, % f)", look.x, look.y);

    DrawText(positionStr, 10, 50, 30, LIGHTGRAY);
    DrawText(lookStr, 10, 75, 30, LIGHTGRAY);

    DrawFPS(10, 10);

    DrawRectangle(position.x, position.y, 10, 10, BLUE);

    look.x = look.x * 100;
    look.y = look.y * 100;
    look.x = position.x + look.x;
    look.y = position.y + look.y;

    DrawLineEx(position, look, 20, YELLOW);


    EndDrawing();
}

void Game::getInput() {
    Vector2 vec = { 0 , 0 };
    if (IsKeyDown(KEY_W))
        vec.y--;
    if (IsKeyDown(KEY_S))
        vec.y++;
    if (IsKeyDown(KEY_A))
        vec.x--;
    if (IsKeyDown(KEY_D))
        vec.x++;
    player.setMoveVec(vec);
    vec.x = 0;
    vec.y = 0;
    // Determine look direction (currently not implemented)
    if (IsKeyDown(KEY_LEFT)) {
        player.setLookDir(0);
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player.setLookDir(1);
    }
}

Game::~Game() {
    UnloadRenderTexture(target);        
    CloseWindow();
}
