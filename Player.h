#pragma once
#include "raylib.h"

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
	void updatePosition();
	float angleBetween(Vector2 firstVec, Vector2 secondVec);

private: 
	void updateLookVec(float theta);
	Vector2 moveVec;  // Movement vector
	Vector2 lookVec;  // Normalized vector representing the look direction
	Vector2 position;
	int rotation; // rotation in degrees.
	float speed;
};


