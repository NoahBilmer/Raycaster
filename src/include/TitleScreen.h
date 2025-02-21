#pragma once
#include "raylib.h"
#include "raymath.h"
#include "../ui/include/button.h"
#include "Screen.h"
#include "Input.h"
#include "Game.h"
#include <string.h>


class TitleScreen : public Screen
{
public:

	TitleScreen();
	std::shared_ptr<Screen> update(Input& input) override;
	void draw();

private:
	int fontSize;
	int smallFontSize;
	std::string txt;
	std::string title;
	std::string info;
	std::string githubLink;
	Vector2 titleLength;
	Vector2 infoLength;
	Vector2 githubLength;
	Color backgroundColor;
	int colorFadeDir;
	Button startBtn;
	int frameCount;
};
