#pragma once
#include "Map.h"
#include "Player.h"

class Game
{
private:
	RenderTexture2D target;
	Player player;
	Map map;
	const int screenWidth = 1200;
	const int screenHeight = 1000;
	int frameCounter;

public:
	Game();
	~Game();
	void update(void);
	void render(void);
	void getInput();
};

