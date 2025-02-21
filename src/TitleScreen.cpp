#include "include/TitleScreen.h"

/*
 * Constructor for the title screen
 */
TitleScreen::TitleScreen()
{
    fontSize = 60;
    smallFontSize = 35;
    txt = "start";
    title = "raycaster demo built in raylib";
    info = "press enter to start";
    githubLink = "https://github.com/noahbilmer/raycaster/";
    titleLength = MeasureTextEx(Game::defaultFont, title.c_str(), fontSize, 2);
    infoLength = MeasureTextEx(Game::defaultFont, info.c_str(), fontSize, 2);
    githubLength = MeasureTextEx(Game::defaultFont, githubLink.c_str(), smallFontSize, 2);
    startBtn = Button(Rectangle{Screen::screenWidth / 2 - 200,Screen::screenHeight - titleLength.y*2 - githubLength.y*2 - smallFontSize,400,100}, .2, Color{ 220,220,240,255 }, txt);
    frameCount = 0;
}

/*
 * Update function for the title screen.
 * Returns: the next screen.
 */
std::shared_ptr<Screen> TitleScreen::update(Input& input)
{
    frameCount++;
    Screen::mainLayerTransparency = 255;
    Screen::secondaryLayerTransparency = 255;
    startBtn.updateState();
    if (startBtn.isPressed() || input.startKeyPressed()) {
        Screen::clearScreen();
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
	BeginTextureMode(Screen::mainLayer);
        transitionBackgroundHue();
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

/**
* transitions the background hue to a slightly different color every frame.
* We use this in the title screen to create an interesting background color effect.
*/
void TitleScreen::transitionBackgroundHue() {
    int MAX_RED = 190;
    int MAX_GREEN = 200;
    int MAX_BLUE = 220;
    int MIN_RED = 87;
    int MIN_GREEN = 103;
    int MIN_BLUE = 178;

    if (backgroundColor.r == MAX_RED && backgroundColor.g == MAX_GREEN && backgroundColor.b == MAX_BLUE) {
        colorFadeDir = -1;
    }
    else if (backgroundColor.r == MIN_RED && backgroundColor.g == MIN_GREEN && backgroundColor.b == MIN_BLUE) {
        colorFadeDir = 1;
    }
    
    backgroundColor.r += colorFadeDir;
    backgroundColor.g += colorFadeDir;
    backgroundColor.b += colorFadeDir;
    
    // Clamp our color values to ensure they stay between our desired range.
    backgroundColor.r = Clamp(backgroundColor.r, MIN_RED, MAX_RED);
    backgroundColor.g = Clamp(backgroundColor.g, MIN_GREEN, MAX_GREEN);
    backgroundColor.b = Clamp(backgroundColor.b, MIN_BLUE, MAX_BLUE);

}
