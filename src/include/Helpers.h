#pragma once
#include "raylib.h"
#include <raymath.h>
#include <iostream>
#include "RayCaster.h"
#include <algorithm>

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

Vector2 findPointOfIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4);
Vector2 getRayFromAngle(float theta);
void transitionBackgroundHue(Color* backgroundColor, int* colorFadeDir);
