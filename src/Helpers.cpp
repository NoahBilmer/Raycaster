#include "include/Helpers.h"


/**
 * Finds the intersection between two lines.
 *
 * @params p1, p2 define the first line and p2, p3 define the second line.
 *
 * @return If it exists, the point of intersection between the two lines,
 *		   If it does not exist, a Vector of x,y values of -1.
 */
Vector2 findPointOfIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
	/* 
	Here we calculate the point of intersection between two line segments.
	Important to note that we are dealing with line SEGMENTS (and not infinite lines) for this problem, which
	is why the math is a bit more verbose.
	*/ 
	Vector2 poi = { -1,-1 };
	float t = 
		(((c.y - a.y) * (d.x - c.x)) - ((c.x - a.x) * (d.y - c.y)))
		/ (((b.y - a.y)*(d.x-c.x)) - ((b.x - a.x)*(d.y - c.y)));
	float s = 
		(((c.y - a.y) * (b.x - a.x)) - ((c.x - a.x) * (b.y - a.y)))
		/ (((b.y - a.y) * (d.x - c.x)) - ((b.x - a.x) * (d.y - c.y)));
	// Return if the point does not exist on both line segments.
	if (t < 0 || t > 1 || s < 0 || s > 1)
		return poi;
	poi.x = a.x + t * (b.x - a.x);
	poi.y = a.y + t * (b.y - a.y);
	return poi;
}


/**
 * Coverts an angle into it's corresponding unit vector.
 *
 * @params theta - the angle in radians 
 *
 * @return the unit vector
 * 
 */
Vector2 getRayFromAngle(float theta) {
	Vector2 vec;
	vec.x = cos(theta);
	vec.y = sin(theta);
	return vec;
}