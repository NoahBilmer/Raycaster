
#include "Player.h"
#include "Map.h"
#include "Helpers.h"
#include <raylib.h>
#include <raymath.h>
#include "RayCaster.h"
#include <iostream>
#include <array>


RayCaster::RayCaster() {
	
}

RayCaster::RayCaster(Map& map, Player &player)
{
	this->map = &map;
	this->player = &player;
}

// Cast out a ray from the player position to the nearest object.
// and then return the point of intersection.
std::array<Ray2d, RAYCOUNT> RayCaster::castRays()
{
	std::array<Ray2d, RAYCOUNT> rays;
	float theta = player->getRotation()*DEG2RAD;
	int fov = 66;
	const long float deg = (0.0174533 * fov) / RAYCOUNT;
	theta = theta - deg;
	Ray2d ray = Ray2d({-1,-1},BLUE);
	for (int i = 0; i < RAYCOUNT; i++) {
		theta += deg;
		ray = closestPoint(getRayFromAngle(theta));
		rays[i] = ray;
	}
	return rays;
}

Ray2d RayCaster::closestPoint(Vector2 ray) {
	Vector2 lookVecAbs = { (player->getPosition().x + ray.x), (player->getPosition().y + ray.y)};
	Vector2 point;
	float closestDistance = 99999;
	float distance;
	Ray2d closestPoint = Ray2d({ -1,-1 }, BLUE);
	// Loop through all the lines on the map and determine the closest line that intersects
	// TODO: more efficient solution ?
	for (const Line line : map->getMap()) {
		point = findPointOfIntersection(line.p1, line.p2, player->getPosition(), lookVecAbs);
		distance = Vector2Distance(player->getPosition(), point);
		if (point.x == -1 && point.y == -1) 
			continue;
		if (distance < closestDistance) {
			closestDistance = distance;
			closestPoint.point = point;
			closestPoint.color = line.color;
		}
	}
	return closestPoint;
}