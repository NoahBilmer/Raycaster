#pragma once
#include "raymath.h"
#include "raylib.h"

#include <functional> 

struct Ray2d {
	Vector2 point;
	Color color;
	int index;
	Ray2d(Vector2 pointVal = { -1,-1 }, Color colorVal = BLUE, int i = -1) : point(pointVal), color(colorVal), index(i) {}
	bool operator==(const Ray2d& other) const {
		return point.x == other.point.x && other.point.y == point.y; // Two points are equal if their points are equal, color is not relevant.
	}
};

namespace std {
	template <>
	struct hash<Ray2d> {
		size_t operator()(const Ray2d& p) const {
			return std::hash<float>()(p.point.x) ^ (std::hash<float>()(p.point.y)) % 5;
		}
	};
}
