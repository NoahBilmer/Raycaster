#pragma once
#include "Map.h"
#include "Player.h"
#include "Raycaster.h"
#include "Entity.h"
#include "raymath.h"
#include "stdio.h"
#include "string.h"
#include <iostream>
#include <array>
#include "unordered_set"

class Game
{
private:
	RenderTexture2D target;
	Player player;
	Map map;
	RayCaster rayCaster;
	RayCaster light;
	const int screenWidth = 1200;
	const int screenHeight = 1000;
	int frameCounter;
	void drawView();

public:
	Game();
	~Game();
	void update(void);
	void render(void);
	void getInput();
};

