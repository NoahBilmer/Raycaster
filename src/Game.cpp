#include "include/Game.h"
#include "resources/romulus.h"

Map Game::map;
Font Game::defaultFont;
float Screen::scale;

/**
 * Constructor for the Game class.
 */
Game::Game() {
    map = Map();
    map.loadMap();
    player = Player(Vector2{ 1110,1110 }, map);
    rayCaster = RayCaster(map, player.getEntity(), 66, 500);
    
    frameCounter = 0;
}

/**
 * The update function for the application. Runs once per tick.
 */
std::shared_ptr<Screen> Game::update(Input& input) {
    if (input.isPaused()) {
        std::shared_ptr<Screen> screen = Screen::getInstanceOf<PauseScreen>();
        /* the main/secondary layer is not static or anything, so we need to set the main layer
           of the pause screen to be the game's main layer.*/
        screen.get()->mainLayer = mainLayer;
        return screen;
    }
    frameCounter++;
    player.setMoveVec(input.getMoveVec());
    player.updateRotation(player.getRotation() + input.getLookDir());
    doLogic();
    render();
    return Screen::getInstanceOf<Game>();
}

/*
 * Returns the map 
 */
Map& Game::getMap()
{
    return map;
}

/**
 * Does all of the game logic for this frame.
 */
void Game::doLogic() {
    rayCaster.castRays();
    // Do the collision check.
    for (auto line : map.getLineVector()) {
        Vector2 res = findPointOfIntersection(player.getPosition(),player.getNextPosition(), line.p1, line.p2);
        if (res.x != -1 && res.y != -1) {
            return;
        }
    }
    
    player.updatePosition();
   
}


/**
 * Renders the game state.
 */
void Game::render() {
    Screen::mainLayerTransparency = 255;
    Vector2 position = player.getPosition();
    Color lightBlue = Color{ 64, 96, 145,255 };
    Color darkBlue = Color{ 12, 24, 41,255 };
    BeginTextureMode(this->mainLayer);
        ClearBackground(RAYWHITE);
        
        // Create the background 
        DrawRectangleGradientV(0, 0, screenWidth, screenHeight / 2, lightBlue, darkBlue);
        DrawRectangleGradientV(0, screenHeight / 2, screenWidth, screenHeight / 2, darkBlue, lightBlue);
        char positionStr[50];
        std::snprintf(positionStr, 50, "Position: (%f,%f)", position.x, position.y);
        char lookStr[50];
        std::snprintf(lookStr, 50, "Rotation: (%f)", player.getRotation());
        DrawText(positionStr, 10, 50, 30, LIGHTGRAY);
        DrawText(lookStr, 10, 75, 30, LIGHTGRAY);
        drawView();

        DrawFPS(10, 10);
    EndTextureMode();
}

/**
 * Draw the representation of the game world.
 */
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
    Color colorVal = Color{0,0,0,255};

   for (auto const ray : rays) {
       
        rayVector.x = abs(ray.point.x - player.getPosition().x);
        rayVector.y = abs(ray.point.y - player.getPosition().y);
        float angle = atan2(rayVector.y,rayVector.x);
        // Get the distance (Add a tiny constant so we never divide by 0)
        dist = abs(sqrt(rayVector.x * rayVector.x + rayVector.y * rayVector.y));
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
