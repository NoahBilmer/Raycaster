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
#include "PauseScreen.h"

class Game
{
public:
	Game();
	~Game();
	void update(void);
	static Map* getMap();
	static const int screenWidth = 1200;
	static const int screenHeight = 1000;
	static Font defaultFont;
	static float scale;
private:
	static Map* map;
	RenderTexture2D target;
	Color targetColor = Color{ 255,255,255,255 };
	Player player;
	bool isPaused = false;
	RayCaster rayCaster;

	int frameCounter;
	void drawView();
	void doLogic(void);
	void render(void);
	void getInput(void);

};

