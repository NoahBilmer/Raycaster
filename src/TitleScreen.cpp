#include "include/TitleScreen.h"
#include "include/Helpers.h"

/*
 * Constructor for the title screen
 */
TitleScreen::TitleScreen()
{
    useSecondaryLayer = false;
    mainLayerTransparency = 255;

    fontSize = 60;
    smallFontSize = 35;
    txt = "start";
    title = "raycaster demo built in raylib";
    info = "press enter to start";
    githubLink = "https://github.com/noahbilmer/raycaster/";
    titleLength = MeasureTextEx(Game::defaultFont, title.c_str(), fontSize, 2);
    infoLength = MeasureTextEx(Game::defaultFont, info.c_str(), fontSize, 2);
    githubLength = MeasureTextEx(Game::defaultFont, githubLink.c_str(), smallFontSize, 2);
    startBtn = Button(Rectangle{Screen::screenWidth / 2 - 200,Screen::screenHeight - titleLength.y*2 - githubLength.y*2 - smallFontSize,400,100}, .2, Color{ 190,190,240,255 }, txt);
    frameCount = 0;
}

/*
 * Update function for the title screen.
 * Returns: the next screen.
 */
std::shared_ptr<Screen> TitleScreen::update(Input& input)
{
    frameCount++;
    startBtn.updateState();
    if (startBtn.isPressed() || input.startKeyPressed()) {     
        input.reset();
        return Screen::getInstanceOf<Game>();
    }
	draw();
	return Screen::getInstanceOf<TitleScreen>();
}

/*
 * the draw function for the title screen.
 */
void TitleScreen::draw()
{
	BeginTextureMode(this->mainLayer);
        transitionBackgroundHue(&backgroundColor,&colorFadeDir);
        startBtn.draw();
        ClearBackground(backgroundColor);
        Color txtColor = backgroundColor;
        txtColor.r = Clamp(255 - txtColor.b,0,255);  // we use the blue value as the red value so the 
                                                     // text is always clearly visible.
        txtColor.g = 30;
        txtColor.b = 50;
        DrawTextEx(Game::defaultFont, githubLink.c_str(), Vector2{ (Screen::screenWidth / 2) - githubLength.x / 2, (float)smallFontSize }, 35, 2, txtColor);
        DrawTextEx(Game::defaultFont, title.c_str(), Vector2{ (Screen::screenWidth / 2) - titleLength.x / 2, (float)fontSize + smallFontSize }, fontSize, 2, txtColor);
        
       // DrawTextEx(Game::defaultFont, info.c_str(), Vector2{ (Screen::screenWidth / 2) - infoLength.x / 2, Screen::screenHeight - infoLength.x }, fontSize, 2, txtColor);
	EndTextureMode();
}

