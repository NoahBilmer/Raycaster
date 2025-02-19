#pragma once
#include "raylib.h"
#include "../ui/include/button.h"
#include "Screen.h"


class PauseScreen : public Screen
{
public:

	PauseScreen();
	int update() override;
	void draw();
	void doLogic();
	RenderTexture2D getPauseTarget();
	
private: 
	float scale;
	RenderTexture2D pauseTarget;
	Button exitBtn;
};

