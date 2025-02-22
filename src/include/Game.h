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
#include "Input.h"
#include "GameScreen.h"

class Game : public Screen
{
public:
	Game();
	std::shared_ptr<Screen> update(Input& input) override;
	static Map& getMap();
	static Font defaultFont;
private:
	static Map map;
	Color targetColor = Color{ 255,255,255,255 };
	Player player;
	Input input;
	RayCaster rayCaster;

	int frameCounter;
	void drawView();
	void doLogic(void);
	void render(void);

};

