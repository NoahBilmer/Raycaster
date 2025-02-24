#pragma once
#include "raylib.h"
#include "../ui/include/Button.h"
#include "Screen.h"
#include "Input.h"


class PauseScreen : public Screen
{
public:

	PauseScreen();
	std::shared_ptr<Screen> update(Input& input) override;
	void draw();
	
private: 
	Color textColor = {100,100,100,255};
	int colorFadeDir;
	Button exitBtn;
};

