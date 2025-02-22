#include "include/Screen.h"
#include "include/PauseScreen.h"
#include "include/Game.h"
#include "include/TitleScreen.h"
#include "resources/romulus.h"

std::array<std::shared_ptr<Screen>, Screen::screenCount> Screen::screenArr;

Screen::Screen()
{
	
	mainLayer = LoadRenderTexture(Screen::screenWidth, Screen::screenHeight);
	mainLayerTransparency = 255;
	secondaryLayer = LoadRenderTexture(Screen::screenWidth, Screen::screenHeight);
	secondaryLayerTransparency = 255;
}

Screen::~Screen()
{
	UnloadRenderTexture(mainLayer);
	UnloadRenderTexture(secondaryLayer);
}

void Screen::setupScreenArray()
{
	addToArr<Game>(std::make_shared<Game>());
	addToArr<PauseScreen>(std::make_shared<PauseScreen>());
	addToArr<TitleScreen>(std::make_shared<TitleScreen>());
	
}

bool Screen::isUsingSecondaryLayer()
{
	return useSecondaryLayer;
}

void Screen::clearScreen()
{
	UnloadRenderTexture(this->mainLayer);
	UnloadRenderTexture(secondaryLayer);
	mainLayer = LoadRenderTexture(screenWidth, screenHeight);
	secondaryLayer = LoadRenderTexture(screenWidth, screenHeight);
}
