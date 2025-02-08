#pragma once
#include "raylib.h"

Vector2 findPointOfIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4);
Vector2 getRayFromAngle(float theta);
Vector2 getLineNormal(Vector2 p1,Vector2 p2);
float withinDelta(Vector2 p1, Vector2 p2, float delta);
