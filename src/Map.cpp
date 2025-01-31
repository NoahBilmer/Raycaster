#include "Map.h"

Map::Map() {
	Map(""); // todo: implement saving/loading maps
}

Map::Map(std::string mapDirectory)
{
	map = {};
}

std::vector<std::string> Map::getMapList()
{
	return std::vector<std::string>();
}

void Map::loadMap(std::string mapName)
{
	Line line({ 200,200 },{ 500,500 },DARKBLUE);
	Line line2({ 100,100 }, { 200,350 }, DARKBLUE);
	Line line3({ 700,200 }, { 1200,200 }, RED);
	Line line4({ 700,200 }, { 700,0 }, RED);

	createRect(Rectangle{100,100,50,50}, DARKGREEN);
	createRect(Rectangle{ 1000,800,15,15 }, DARKPURPLE);
	createRect(Rectangle{ 200,500,10,10 }, ORANGE);
	createRect(Rectangle{ 250,550,10,10 }, ORANGE);
	map.push_back(line);
	map.push_back(line2);
	map.push_back(line3);
	map.push_back(line4);
}

void Map::createRect(Rectangle rect, Color color) {
	Line box1({ rect.x,rect.y }, { rect.x + rect.width,rect.y }, color);
	Line box2({ rect.x,rect.y }, { rect.x, rect.y+ rect.height }, color);

	Line box3({ rect.x + rect.width, rect.y + rect.height }, { rect.x + rect.width,rect.y },color);
	Line box4({ rect.x + rect.width, rect.y + rect.height }, { rect.x, rect.y + rect.height }, color);

	map.push_back(box1);
	map.push_back(box2);
	map.push_back(box3);
	map.push_back(box4);
	
}

std::vector<Line> Map::getMap()
{
	return map;
}
