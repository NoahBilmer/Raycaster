#pragma once
#include "Player.h"
#include "Map.h"
#include "Raycaster.h"
#include "Entity.h"
#include "Helpers.h"
#include "raymath.h"
#include "stdio.h"
#include "string.h"
#include <iostream>
#include <array>
#include "unordered_set"

class Game
{
public:
	Game();
	~Game();
	void update(void);
	static Map* getMap();
private:
	static Map* map;
	RenderTexture2D target;
	Player player;
	RayCaster rayCaster;
	const int screenWidth = 1200;
	const int screenHeight = 1000;
	int frameCounter;
	void drawView();
	void doLogic(void);
	void render(void);
	void getInput(void);

};

