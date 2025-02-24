#include "include/PauseScreen.h"
#include "include/Game.h"
#include "include/TitleScreen.h"
#include "include/Helpers.h"

/*
 * Constructor for the pause screen 
 */
PauseScreen::PauseScreen()
{
    std::string txt = "exit";
    exitBtn = Button(Rectangle{ Screen::screenWidth / 2 - 200,Screen::screenHeight / 2,400,100 }, .2, Color{ 190,190,240,255 }, txt);
    useSecondaryLayer = true;
    mainLayerTransparency = 100;
    secondaryLayerTransparency = 200;
}


/*
 * Update function for the pause screen.
 * Returns: the next screen.
 */
std::shared_ptr<Screen> PauseScreen::update(Input& input)
{
    if (!input.isPaused()) {
        //Screen::clearScreen();
        return Screen::getInstanceOf<Game>();
    }
    exitBtn.updateState();
    if (exitBtn.isPressed()) {
        //Screen::clearScreen();
        return Screen::getInstanceOf<TitleScreen>();
    }
    draw();
    
    return Screen::getInstanceOf<PauseScreen>();
}

/*
 * The draw function for the pause screen.
 */
void PauseScreen::draw()
{
    int fontSize = 60;
    std::string pauseTxt = "paused";
    Vector2 pauseTxtLength = MeasureTextEx(Game::defaultFont, pauseTxt.c_str(), fontSize, 2);
    transitionBackgroundHue(&textColor, &colorFadeDir);
    BeginTextureMode(this->secondaryLayer);
    DrawTextEx(Game::defaultFont, pauseTxt.c_str(), Vector2{ (Screen::screenWidth / 2) - pauseTxtLength.x / 2, (float)fontSize }, fontSize, 2, textColor);
    exitBtn.draw();
    EndTextureMode();
}
