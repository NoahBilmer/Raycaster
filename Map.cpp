#include "Map.h"

Map::Map() {
	Map("");
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
	map.push_back(line);
}

std::vector<Line> Map::getMap()
{
	return map;
}
