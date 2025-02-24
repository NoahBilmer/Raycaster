#pragma once
#include "raylib.h"
#include "Player.h"
class Input
{
public:

    // Constructor to initialize moveVec and lookVec
    Input();

    // Method to handle input and update moveVec
    void getInput();

    Vector2 getMoveVec();
    int getLookDir();
    bool isPaused();
    void reset();
    bool startKeyPressed();

private:
    Vector2 moveVec;
    int lookDir;
    bool paused;
    bool start;
};

