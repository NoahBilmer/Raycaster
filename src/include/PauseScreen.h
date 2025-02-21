#pragma once
#include "raylib.h"
#include "../ui/include/button.h"
#include "Screen.h"
#include "Input.h"


class PauseScreen : public Screen
{
public:

	PauseScreen();
	std::shared_ptr<Screen> update(Input& input) override;
	void draw();
	
private: 
	float scale;
	RenderTexture2D pauseTarget;
	Button exitBtn;
};

