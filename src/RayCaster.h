#pragma once
#include "raylib.h"
#include <vector>
#include "Map.h"
#include "Player.h"
#include <iostream>

#define RAYCOUNT 450
#define RAYSIZE 1000

struct Ray2d {
	Vector2 point;
	Color color;
	Ray2d(Vector2 pointVal = { -1,-1 }, Color colorVal = BLUE) : point(pointVal), color(colorVal) {}
};

class RayCaster
{
private:
	Map *map;
	Player *player;
public:
	RayCaster();
	RayCaster(Map& map, Player& player);
	std::array<Ray2d, RAYCOUNT> castRays();
	Ray2d closestPoint(Vector2 ray);
};

