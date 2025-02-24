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
	Color textColor = {0,0,0,255};
	int colorFadeDir;
	float scale;
	RenderTexture2D pauseTarget;
	Button exitBtn;
};

