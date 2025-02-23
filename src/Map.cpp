#include "include/Map.h"

void Map::loadMap()
{
	// Line line({ 200,200 },{ 500,500 },DARKBLUE);

	createRect(Rectangle{ 1000,1000,75,75 }, DARKGREEN);
	createRect(Rectangle{ 1000,1150,75,75 }, DARKGREEN);
	createRect(Rectangle{ 1150,1150,75,75 }, DARKGREEN);
	createRect(Rectangle{ 1150,1000,75,75 }, DARKGREEN);
	createRect(Rectangle{ 1150,900,75,75 }, RED);
	createRect(Rectangle{ 1000,900,75,75 }, RED);
	Line line({ 1000,900 }, {500, 500}, RED);
	Line line2({ 1225,900 }, { 1000, 500 }, RED);
	Line line3({ 500,500 }, { 1000, 500 }, RED);
	
	map.push_back(line);
	map.push_back(line2);
	map.push_back(line3);


	createRect(Rectangle{ 900,1025,50,50 }, SKYBLUE);
	createRect(Rectangle{ 900,1150,50,50 }, SKYBLUE);

	createRect(Rectangle{ 750,1025,50,50 }, BLUE);
	createRect(Rectangle{ 750,1150,50,50 }, BLUE);

	createRect(Rectangle{ 600,1025,50,50 }, SKYBLUE);
	createRect(Rectangle{ 600,1150,50,50 }, SKYBLUE);

	createRect(Rectangle{ 1025,1275,50,200 }, DARKBLUE);
	createRect(Rectangle{ 875,1275,200,50 }, DARKBLUE);
	createRect(Rectangle{ 1150,1275,50,200 }, DARKBLUE);
	createRect(Rectangle{ 1150,1275,200,50 }, DARKBLUE);

	createRect(Rectangle{ 1275,1135,15,15 }, DARKPURPLE);
	createRect(Rectangle{ 1275,1075,15,15 }, DARKPURPLE);
	createRect(Rectangle{ 1300,1135,15,15 }, GRAY);
	createRect(Rectangle{ 1300,1075,15,15 }, GRAY);
	createRect(Rectangle{ 1325,1135,15,15 }, DARKPURPLE);
	createRect(Rectangle{ 1325,1075,15,15 }, DARKPURPLE);
	createRect(Rectangle{ 1350,1135,15,15 }, GRAY);
	createRect(Rectangle{ 1350,1075,15,15 }, GRAY);
	createRect(Rectangle{ 1375,1135,15,15 }, DARKPURPLE);
	createRect(Rectangle{ 1375,1075,15,15 }, DARKPURPLE);
	createRect(Rectangle{ 1400,1135,15,15 }, GRAY);
	createRect(Rectangle{ 1400,1075,15,15 }, GRAY);

	
	createRect(Rectangle{ 875,1275,50,200 }, DARKBLUE);
	
	createRect(Rectangle{ 1350,1275,50,200 }, DARKBLUE);
	createRect(Rectangle{ 1025,1525,50,200 }, DARKBLUE);
	createRect(Rectangle{ 1150,1525,50,200 }, DARKBLUE);
	
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

const std::vector<Line>& Map::getLineVector()
{
	return map;
}
