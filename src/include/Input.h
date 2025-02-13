#pragma once
#include "raylib.h"
#include "Player.h"
class Input
{
public:

    // Constructor to initialize moveVec and lookVec
    Input();

    // Method to handle input and update moveVec
    void getInput(Player* player);

    // Method to calculate the angle between two vectors
    float angleBetween(Vector2 firstVec, float theta);
};

