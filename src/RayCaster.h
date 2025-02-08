#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include "Map.h"
#include "Player.h"
#include <iostream>
#include "Helpers.h"
#include "memory.h"
#include "unordered_set"
#include "Ray2d.h"
#include "Entity.h"

class RayCaster
{
private:
	float fov = 66;
	int rayCount;
	int rayLength = 1000;
	Map *map;
	Entity *entity;
public:
	RayCaster();
	~RayCaster();
	RayCaster(Map& map, Entity& entity, int fov, int rayCount);
	std::unordered_set<Ray2d> castRays();
	const int getRayCount();
	Vector2 getLookRay();
	Ray2d closestPoint(Vector2 ray);
	Vector2 getPosition();
	float getRotation();
	int getRayLength();
};

