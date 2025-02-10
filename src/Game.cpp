#include "Game.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

Game::Game() {

    player.setLookDir(1);
    map = Map(" ");
    player = Player({ 550,500 }, map);
    rayCaster = RayCaster(map,*player.getEntity(),66,300);
    
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
    doLogic();
    // Render 
    render();
}

void Game::doLogic() {
    player.updatePosition();
    rayCaster.castRays();
}

void Game::render() {
    float scale = MIN((float)GetScreenWidth() / screenWidth, (float)GetScreenHeight() / screenHeight);
    Vector2 position = player.getPosition();
    Color lightBlue = Color{ 64, 96, 145,255 };
    Color darkBlue = Color{ 12, 24, 41,255 };
    BeginTextureMode(target);
        ClearBackground(RAYWHITE);
        char positionStr[50];
        std::snprintf(positionStr, 50, "Position: (%f,%f)", position.x, position.y);
        char lookStr[50];
        std::snprintf(lookStr, 50, "Rotation: (%f)",player.getRotation());
        // Create the background 
        DrawRectangleGradientV(0, 0, screenWidth, screenHeight / 2, lightBlue, darkBlue);
        DrawRectangleGradientV(0, screenHeight / 2, screenWidth, screenHeight / 2, darkBlue, lightBlue);
        // Draw the view.
        drawView();

        DrawText(positionStr, 10, 50, 30, LIGHTGRAY);
        DrawText(lookStr, 10, 75, 30, LIGHTGRAY);
        DrawFPS(10, 10);
   
        if (0) {
        
            for (Line line : map.getMap()) {
                DrawLineEx(line.p1, line.p2, 3, line.color);
            }
        
            rayCaster.castRays();
            std::unordered_set<Ray2d> rays = rayCaster.getRays();
            DrawLineEx(rayCaster.getPosition(), Vector2Scale(getRayFromAngle(rayCaster.getRotation() * DEG2RAD), rayCaster.getRayLength()), 2, YELLOW);
            for (auto const ray : rays)
                DrawLineEx(rayCaster.getPosition(), ray.point, 1, RED);

        }
    EndTextureMode();
        BeginDrawing();
        DrawTexturePro(target.texture, Rectangle{ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                 Rectangle{ (GetScreenWidth() - ((float)screenWidth * scale))*0.5f, (GetScreenHeight() - ((float)screenHeight * scale))*0.5f,
                 (float)screenWidth * scale, (float)screenHeight * scale },
                 Vector2{ 0, 0 }, 0.0f, Color{255,255,255,255});
 
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
    std::unordered_set<Ray2d> rays = rayCaster.getRays();
    float const lineWidth = (float)screenWidth / (float)rayCaster.getRayCount();
    float dist;
    int count = 0;
    int wallSize = 20;
    int wallHeight = 96;
    float intensity;
    Vector2 lineStart = { 0, 0,};
    Vector2 lineEnd = { 0,screenHeight / 2 - 150 };
    Vector2 rayVector = { 0,0 };
    Color colorVal;

   for (auto const ray : rays) {
       
        rayVector.x = abs(ray.point.x - player.getPosition().x);
        rayVector.y = abs(ray.point.y - player.getPosition().y);
        // Get the distance (Add a tiny constant so we never divide by 0)
        dist = sqrt(rayVector.x * rayVector.x + rayVector.y * rayVector.y);
        float lineSize = ((wallHeight / dist) * 277) + wallSize;
        // for the y positions, we start the line in the middle of the screen
        // plus half the line height so the line is centered. 
        lineStart.y = ((screenHeight / 2) + (lineSize / 2));
        lineEnd.y = lineStart.y - lineSize;
        
        colorVal.r = ray.color.r;
        colorVal.g = ray.color.g;
        colorVal.b = ray.color.b;
        if (IsKeyDown(KEY_F)) {
            printf("debug\n");
        }
        
        lineStart.x = ray.index * lineWidth;
        lineEnd.x = ray.index * lineWidth;
        
        // To determine the intensity of the color we divide some constant by the distance,
        // and then normalize that value between 0 and 1.
        intensity = 170 / (dist);
        intensity = Normalize(intensity, 0, 1);
        colorVal.b = Clamp(colorVal.b * intensity, 0 ,ray.color.b);
        colorVal.g = Clamp(colorVal.g * intensity, 0, ray.color.g);
        colorVal.r = Clamp(colorVal.r * intensity, 0, ray.color.r); 
        DrawLineEx(lineStart, lineEnd, lineWidth , colorVal);
        
    }
}

Game::~Game() {
    UnloadRenderTexture(target);        
    CloseWindow();
}
