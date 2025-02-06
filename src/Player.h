#pragma once
#include "raylib.h"
#include "Map.h"
#include "Helpers.h"
#include "RayCaster.h"
#include <iostream>


class Player
{
public:
	Player();
	Player(Vector2 startPos, Map& map);
	void UpdateStateVecs(Vector2 moveVec, Vector2 lookVec);
	Vector2 getMoveVec();
	void setMoveVec(Vector2 newVec);
	void setLookDir(bool lookDir);
	Vector2 getLookVec();
	Vector2 getPosition();
	float getRotation();
	void updatePosition();
	Entity* getEntity();

private: 
	Vector2 moveVec;  // Movement vector
	Vector2 lookVec;  // Normalized vector representing the look direction
	Vector2 horizontalVec; // the vector perpendicular to the look direction. 
	Entity* entity;
	Map* map;
	Vector2 rays[100];
	float speed;
};


