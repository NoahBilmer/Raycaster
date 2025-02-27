#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"

struct Line {
	Vector2 p1;
	Vector2 p2;
	Color color;

	Line(Vector2 p1Val, Vector2 p2Val, Color colorVal) : p1(p1Val), p2(p2Val), color(colorVal) {}

};

class Map
{
private:
	std::vector<Line> map;
public:
	Map() = default;
	Map(std::string mapDirectory);
	void loadMap();
	const std::vector<Line>& getLineVector();
	void createRect(Rectangle rect, Color color);

};


