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
#include <stdexcept>
#include <functional>

class RayCaster
{
private:
	float fov = 66;
	int rayCount;
	int rayLength = 1000;
	Map map;
	std::reference_wrapper<Entity> entity;
	Entity defaultEntity = Entity( Vector2{300,300},90 );
	std::unordered_set<Ray2d> rays;
	
public:
	RayCaster();
	RayCaster(Map& map, Entity& entity, int fov, int rayCount);
	void castRays();
	const std::unordered_set<Ray2d>& getRays();
	const int getRayCount();
	Vector2 getLookRay();
	Ray2d closestPoint(Vector2 ray);
	Vector2 getPosition();
	float getRotation();
	int getRayLength();
};

