#pragma once
#include "raylib.h"
#include "../ui/include/button.h"

class PauseScreen
{
public:

	PauseScreen();
	void draw();
	void doLogic();
	RenderTexture2D getPauseTarget();
	
private: 
	float scale;
	RenderTexture2D pauseTarget;
	Button exitBtn;
};

