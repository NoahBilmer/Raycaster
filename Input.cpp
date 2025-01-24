#include "Input.h"  
#include "raymath.h"
#include "raylib.h" 
#include "Player.h"

#include <cmath>    

// Constructor to initialize moveVec and lookVec to (0, 0)
Input::Input() {
    
}

// Function to handle user input and update the moveVec and lookVec
void Input::getInput(Player* player) {
    Vector2 vec = { 0 , 0 };
    if (IsKeyDown(KEY_W))
       vec.y--;
    if (IsKeyDown(KEY_S))
       vec.y++;
    if (IsKeyDown(KEY_A))
       vec.x--;
    if (IsKeyDown(KEY_D))
       vec.x++;
    player->setMoveVec(vec);
    vec.x = 0;
    vec.y = 0;
    // Determine look direction (currently not implemented)
    if (IsKeyDown(KEY_LEFT)) {
        player->setLookDir(0);
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player->setLookDir(1);
    }
}

