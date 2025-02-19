#include "include/Screen.h"
#include "include/PauseScreen.h"

std::shared_ptr<Screen> Screen::screenArr[screenCount];

void Screen::setIndex(int i)
{
	index = i;
}

int Screen::getIndex()
{
	return index;
}

void Screen::setupScreenArray()
{
	addToArr(std::make_shared<PauseScreen>());
	
}

std::shared_ptr<Screen> Screen::getScreen(int index)
{
	return screenArr[index];
}

void Screen::addToArr(std::shared_ptr<Screen> screen)
{
	for (int i = 0; i < sizeof(screenArr) / sizeof(Screen); i++) {
		if (screenArr[i] == nullptr) {
			screenArr[i] = screen;
			screenArr[i].get()->setIndex(i);
		}
	}
}
