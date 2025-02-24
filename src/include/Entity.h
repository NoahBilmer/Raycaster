#pragma once
#include "raymath.h"


struct Entity {
	Vector2 position;
	float rotation;
	Entity(Vector2 pos = { 0,0 }, float rot = 90) : position(pos), rotation(rot) {}
};