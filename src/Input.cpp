#include "include/Input.h"  
#include "raymath.h"
#include "raylib.h" 
  

/*
 * Constructor for the Input class
 */
Input::Input() {
    moveVec = Vector2{ 0,0 };
    lookDir = 0;
    paused = false;
    start = false;
}

/*
 * Poll for input this frame.
 */
void Input::getInput()
{
    Vector2 vec = { 0 , 0 };
    int dir = 0;
    start = false;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        vec.y++;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        vec.y--;
    if (IsKeyDown(KEY_A))
        vec.x--;
    if (IsKeyDown(KEY_D))
        vec.x++;
    if (IsKeyDown(KEY_LEFT)) {
        dir = -1;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        dir = 1;
    }
    if (IsKeyPressed(KEY_ENTER)) {
        start = true;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        paused = !paused;
    }
    moveVec = vec;
    lookDir = dir;
}

/*
 * Reset all of our input values
 */
void Input::reset()
{
    moveVec = Vector2{ 0,0 };
    lookDir = 0;
    paused = false;
    start = false;
}

/** Getters/setters **/
Vector2 Input::getMoveVec()
{
    return moveVec;
}

int Input::getLookDir()
{
    return lookDir;
}

bool Input::isPaused()
{
    return paused;
}

bool Input::startKeyPressed()
{
    return start;
}





