#pragma once

#include "Screen.h"
#include "raylib.h"
#include <memory>
#include "Input.h"

class GameScreen : public Screen {

public:
	GameScreen();
	std::shared_ptr<Screen> update(Input input);
	void doLogic();
	void render();

};