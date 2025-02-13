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

	Line(Vector2 p1Val, Vector2 p2Val, Color colorVal) : p1(p1Val), p2(p2Val), color(colorVal) { }

};

class Map
{

private:
	/* Map is just a list of lines.*/
	std::vector<Line> map;


public:
	Map();
	Map(std::string mapDirectory);
	void serializeMap(char* name);
	std::vector<std::string> getMapList();

	void loadMap(std::string mapName);

	std::vector<Line> getMap();

	void createRect(Rectangle rect, Color color);

};

