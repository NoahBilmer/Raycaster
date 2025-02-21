#include "include/PauseScreen.h"
#include "include/Game.h"
#include "include/TitleScreen.h"

/*
 * Constructor for the pause screen 
 */
PauseScreen::PauseScreen()
{
    std::string txt = "exit";
    exitBtn = Button(Rectangle{ Screen::screenWidth / 2 - 200,Screen::screenHeight / 2,400,100 }, .2, Color{ 220,220,240,255 }, txt);
}


/*
 * Update function for the pause screen.
 * Returns: the next screen.
 */
std::shared_ptr<Screen> PauseScreen::update(Input& input)
{
    if (!input.isPaused()) {
        Screen::clearScreen();
        Screen::mainLayerTransparency = 255;
        Screen::secondaryLayerTransparency = 255; 
        return Screen::getInstanceOf<Game>();
    }
    exitBtn.updateState();
    if (exitBtn.isPressed()) {
        Screen::clearScreen();
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
    Screen::mainLayerTransparency = 100;
    Screen::secondaryLayerTransparency = 200;
    BeginTextureMode(Screen::secondaryLayer);
    exitBtn.draw();
    EndTextureMode();
}
