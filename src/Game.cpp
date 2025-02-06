#include "Game.h"
#include "raymath.h"
#include "raylib.h"
#include "Player.h"
#include "Map.h"
#include "stdio.h"
#include "string.h"
#include <iostream>
#include <array>
#include "RayCaster.h"
#include "unordered_set"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

Game::Game() {

   
    player.setLookDir(1);
    map = Map(" ");
    player = Player({ 550,500 }, map);
    rayCaster = RayCaster(map,*player.getEntity());
    this->light = RayCaster(map, *(new Entity{ Vector2{410,183 }, 101}));
    
    frameCounter = 0;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Raycaster");
    SetWindowSize(screenWidth, screenHeight);

    target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // Texture scale filter to use

    map.loadMap("map");

    SetTargetFPS(60);
}

void Game::update() {
    frameCounter++;
    // Start by getting input
    getInput();
    // update the position to match the desired movement every frame. 
    player.updatePosition();
    // Render 
    render();
}

void Game::render() {
    float scale = MIN((float)GetScreenWidth() / screenWidth, (float)GetScreenHeight() / screenHeight);
    Vector2 position = player.getPosition();
    Vector2 look = player.getLookVec();
    BeginTextureMode(target);

    ClearBackground(RAYWHITE);

    char positionStr[50];
    std::snprintf(positionStr, 50, "Position: (%f,%f)", position.x, position.y);
    char lookStr[50];
    std::snprintf(lookStr, 50, "Rotation: (%f)",player.getRotation());
    Color lightBlue = Color{ 64, 96, 145,255 };
    Color darkBlue = Color{ 12, 24, 41,255 };

    DrawRectangleGradientV(0, 0, screenWidth, screenHeight / 2, lightBlue, darkBlue);
    DrawRectangleGradientV(0, screenHeight / 2, screenWidth, screenHeight / 2, darkBlue, lightBlue);

    drawView();

    DrawText(positionStr, 10, 50, 30, LIGHTGRAY);
    DrawText(lookStr, 10, 75, 30, LIGHTGRAY);
    DrawFPS(10, 10);

    if (0) {
        DrawRectangle(light.getPosition().x, light.getPosition().y, 10, 10, BLUE);

        for (Line line : map.getMap()) {
            DrawLineEx(line.p1, line.p2, 3, line.color);
        }
       /*
        std::unordered_set<Ray2d> rays = light.castRays();
        DrawLineEx(light.getPosition(), Vector2Scale(getRayFromAngle(light.getRotation()*DEG2RAD), rayCaster.getRayLength()), 2, YELLOW);
        for (const auto ray : rays)
            DrawLineEx(light.getPosition(), ray.point, 1, RED);
        */
        std::unordered_set<Ray2d> rays = rayCaster.castRays();
        DrawLineEx(light.getPosition(), Vector2Scale(getRayFromAngle(light.getRotation() * DEG2RAD), rayCaster.getRayLength()), 2, YELLOW);
        for (const auto ray : rays)
            DrawLineEx(rayCaster.getPosition(), ray.point, 1, RED);

    }

    look.x = position.x + look.x;
    look.y = position.y + look.y;
  

    EndTextureMode();
    BeginDrawing();
    DrawTexturePro(target.texture, Rectangle{ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
             Rectangle{ (GetScreenWidth() - ((float)screenWidth * scale))*0.5f, (GetScreenHeight() - ((float)screenHeight * scale))*0.5f,
             (float)screenWidth * scale, (float)screenHeight * scale },
             Vector2{ 0, 0 }, 0.0f, WHITE);
   
    ClearBackground(BLACK);
    EndDrawing();
}

void Game::getInput() {
    Vector2 vec = { 0 , 0 };
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        vec.y++;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        vec.y--;
    if (IsKeyDown(KEY_A))
        vec.x--;
    if (IsKeyDown(KEY_D))
        vec.x++;
    player.setMoveVec(vec);
    if (IsKeyDown(KEY_LEFT)) {
        player.setLookDir(1);
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player.setLookDir(0);
    }
}

void Game::drawView() {
    std::unordered_set<Ray2d> rays = rayCaster.castRays();
    float const lineWidth = (float)screenWidth / (float)rayCaster.getRayCount();
    float dist;
    int count = 0;
    int wallSize = 20;
    float intensity;
    Vector2 vec1 = { 0, 0,};
    Vector2 vec2 = { 0,screenHeight / 2 - 150 };
    Vector2 rayVector = { 0,0 };
    Color colorVal;

   for (const auto ray : rays) {
       
        rayVector.x = abs(ray.point.x - player.getPosition().x);
        rayVector.y = abs(ray.point.y - player.getPosition().y);

        dist = sqrt(rayVector.x * rayVector.x + rayVector.y * rayVector.y) + 1;
        float lineSize = ((96 / dist) * 277) + wallSize;
       
        vec1.y = ((screenHeight / 2) + (lineSize / 2));
        vec2.y = vec1.y - lineSize;
        
        colorVal.r = ray.color.r;
        colorVal.g = ray.color.g;
        colorVal.b = ray.color.b;
        if (IsKeyDown(KEY_F)) {
            printf("debug");
        }
        vec1.x = ray.index;
        vec2.x = ray.index;
        // We divide the screen width by the number of rays to allow us to draw any amount of rays
        // and still fill the screen properly.
       
        vec1.x = ray.index * lineWidth;
        vec2.x = ray.index * lineWidth;

        intensity = (0.9 / dist) * 50;
        colorVal.b = Clamp(colorVal.b * intensity, 0 ,ray.color.b);
        colorVal.g = Clamp(colorVal.g * intensity, 0, ray.color.g);
        colorVal.r = Clamp(colorVal.r * intensity, 0, ray.color.r); 
        DrawLineEx(vec1, vec2, lineWidth , colorVal);
        
    }
}

Game::~Game() {
    UnloadRenderTexture(target);        
    CloseWindow();
}
