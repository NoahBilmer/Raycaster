#include "include/RayCaster.h"
#include "include/Game.h"

/* Default constructor
*/
RayCaster::RayCaster() : RayCaster(Game::getMap(), defaultEntity, 66, 300) {}


/* Custom constructor for the RayCaster
 * @params map      - the map to use 
 *         entity   - the entity to use 
 *		   fov      - the fov of the raycaster
 *		   rayCount - the number of rays to cast
 */
RayCaster::RayCaster(Map& map, Entity& entity,int fov, int rayCount) : entity(entity),map(map)
{
	this->map = map;
	this->entity = entity;
	this->fov = fov;
	this->rayCount = rayCount;
}

/* Cast out a ray from the player position to the nearest object.
 * and then return the point of intersection.
 */ 
void RayCaster::castRays() {
	rays.clear();
	float theta = entity.get().rotation*DEG2RAD;
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

/* Returns the unordered set of rays
 */
const std::unordered_set<Ray2d>& RayCaster::getRays() {
	return rays;
}

/* Returns the ray count.
 */
const int RayCaster::getRayCount()
{
	return rayCount;
}

/* Returns the unordered set of rays
 */
Vector2 RayCaster::getLookRay()
{
	return Vector2Normalize(getRayFromAngle(DEG2RAD * entity.get().rotation + (DEG2RAD * fov / 2)));
}


/**
 * Finds the closest point on the map between the raycaster's position
 * and the input ray's position.
 *
 * @params ray - the input ray
 *
 * @return the Ray2d object storing all the relevant data about this ray.
 *
 */
Ray2d RayCaster::closestPoint(Vector2 ray) {
	Vector2 lookVecAbs = { (entity.get().position.x + ray.x), (entity.get().position.y + ray.y)};
	Vector2 point;
	float closestDistance = 99999;
	float distance;
	Ray2d closestPoint = Ray2d({ -1,-1 }, BLUE);
	// Loop through all the lines on the map and determine the closest line that intersects
	// TODO: more efficient solution ?
	for (Line line : map.getLineVector()) {
		point = findPointOfIntersection(line.p1, line.p2, entity.get().position, lookVecAbs);
		distance = Vector2Distance(entity.get().position, point);
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

/*
 * Returns the raycaster's position
 */
Vector2 RayCaster::getPosition()
{
	return entity.get().position;
}

/*
 * Returns the raycaster's rotation
 */
float RayCaster::getRotation()
{
	return entity.get().rotation;
}

/*
 * Returns the ray length.
 */
int RayCaster::getRayLength()
{
	return rayLength;
}
