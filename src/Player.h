#pragma once
#include "raylib.h"
#include "Map.h"
#include <iostream>

class Player
{
public:
	Player();
	Player(Vector2 startPos);
	void UpdateStateVecs(Vector2 moveVec, Vector2 lookVec);
	Vector2 getMoveVec();
	void setMoveVec(Vector2 newVec);
	void setLookDir(bool lookDir);
	Vector2 getLookVec();
	Vector2 getPosition();
	float getRotation();
	void updatePosition();

private: 
	Vector2 moveVec;  // Movement vector
	Vector2 lookVec;  // Normalized vector representing the look direction
	Vector2 position;
	int rotation; // rotation in degrees.
	Vector2 rays[100];
	float speed;
};


