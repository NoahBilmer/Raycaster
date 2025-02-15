#include "include/PauseScreen.h"
#include "include/Game.h"


void exitButtonCallback(void) {
    // todo
}

/*
 * Constructor for the pause screen 
 */
PauseScreen::PauseScreen()
{
    pauseTarget = LoadRenderTexture(Game::screenWidth, Game::screenHeight);
    std::string txt = "Exit";
    exitBtn = Button(Rectangle{ Game::screenWidth / 2 - 200,Game::screenHeight / 2,400,100 }, .2, Color{ 150,150,150,255 }, txt);
    exitBtn.setOnClick(exitButtonCallback);
}

/*
 * The draw function for the pause screen. . 
 */
void PauseScreen::draw()
{
    scale = MIN((float)GetScreenWidth() / Game::screenWidth, (float)GetScreenHeight() / Game::screenHeight);
    BeginTextureMode(pauseTarget);
    //DrawEllipse(Game::screenWidth / 2, Game::screenHeight / 2, 50, 50, BLUE);
    exitBtn.draw();
    EndTextureMode();
}

/*
 * the "logic" function for the pause screen. 
 */
void PauseScreen::doLogic()
{
    exitBtn.updateState();
}

/*
 * Returns the pause "target", which acts as a canvas to draw things to the screen. 
 */
RenderTexture2D PauseScreen::getPauseTarget()
{
    return pauseTarget;
}
