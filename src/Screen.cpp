#include "include/Screen.h"
#include "include/PauseScreen.h"
#include "include/Game.h"
#include "include/TitleScreen.h"

std::array<std::shared_ptr<Screen>, Screen::screenCount> Screen::screenArr;

void Screen::setupScreenArray()
{
	addToArr<Game>(std::make_shared<Game>());
	addToArr<PauseScreen>(std::make_shared<PauseScreen>());
	addToArr<TitleScreen>(std::make_shared<TitleScreen>());
	
}

void Screen::clearScreen()
{
	UnloadRenderTexture(mainLayer);
	UnloadRenderTexture(secondaryLayer);
	mainLayer = LoadRenderTexture(screenWidth, screenHeight);
	secondaryLayer = LoadRenderTexture(screenWidth, screenHeight);
}
