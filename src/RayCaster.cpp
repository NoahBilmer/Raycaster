#include "RayCaster.h"


// TODO: fix the default constructor mess here 
RayCaster::RayCaster()
{
	if (map == nullptr)
		this->map = new Map(); 
	if (entity == nullptr)
		this->entity = new Entity{ Vector2{500,500},90 };
	fov = 66;
	rayCount = 300;
}

RayCaster::RayCaster(Map& map, Entity& entity,int fov, int rayCount)
{
	this->map = &map;
	this->entity = &entity;
	this->fov = fov;
	this->rayCount = rayCount;
}

RayCaster::~RayCaster()
{
	
}

// Cast out a ray from the player position to the nearest object.
// and then return the point of intersection.
void RayCaster::castRays()
{
	rays.clear();
	float theta = entity->rotation*DEG2RAD;
	const long float deg = (0.0174533 * fov) / rayCount;
	theta = theta - deg;
	for (int i = 0; i < rayCount; i++) {
		theta += deg;
		Ray2d ray = closestPoint(Vector2Scale(getRayFromAngle(theta), rayLength));
		if (ray.point.x == -1 && ray.point.y == -1)
			continue;
		ray.index = i;
		rays.insert(ray);
	}
}

std::unordered_set<Ray2d> RayCaster::getRays() {
	return rays;
}

const int RayCaster::getRayCount()
{
	return rayCount;
}

Vector2 RayCaster::getLookRay()
{
	return Vector2Normalize(getRayFromAngle(DEG2RAD * entity->rotation + (DEG2RAD * fov / 2)));
}

Ray2d RayCaster::closestPoint(Vector2 ray) {
	Vector2 lookVecAbs = { (entity->position.x + ray.x), (entity->position.y + ray.y)};
	Vector2 point;
	float closestDistance = 99999;
	float distance;
	Ray2d closestPoint = Ray2d({ -1,-1 }, BLUE);
	// Loop through all the lines on the map and determine the closest line that intersects
	// TODO: more efficient solution ?
	for (Line line : map->getMap()) {
		point = findPointOfIntersection(line.p1, line.p2, entity->position, lookVecAbs);
		distance = Vector2Distance(entity->position, point);
		if (point.x == -1 && point.y == -1) 
			continue;
		if (distance < closestDistance) {
			closestDistance = distance;
			closestPoint.point = point;
			closestPoint.color = line.color;
			closestPoint.lineHit = line;
		}
	}
	return closestPoint;
}

Vector2 RayCaster::getPosition()
{
	return entity->position;
}

float RayCaster::getRotation()
{
	return entity->rotation;
}

int RayCaster::getRayLength()
{
	return rayLength;
}
