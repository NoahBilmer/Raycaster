#pragma once
#include "raylib.h"

Vector2 findPointOfIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4);
Vector2 getRayFromAngle(float theta);
float withinDelta(Vector2 p1, Vector2 p2, float delta);

struct Entity {
	Vector2 position;
	float rotation;
	Entity(Vector2 pos = { 0,0 }, float rot = 90) : position(pos), rotation(rot) {}

};