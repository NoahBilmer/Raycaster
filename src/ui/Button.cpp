#include "include/Button.h"
#include "../resources/romulus.h"
#include "../include/Game.h"

Button::Button() : Button(Rectangle{0,0,0,0},0.0f,BLUE,std::string()) {}

Button::Button(Rectangle rect, float radius, Color color, std::string title) {
	
	this->rect = rect;
	this->radius = radius;
	this->color = color;
	this->title = title;
	this->btnState = false;
}

void Button::updateState() {
	Vector2 mouse = GetMousePosition();
	Vector2 virtualMouse = { 0 };
	virtualMouse.x = (mouse.x - (GetScreenWidth() - (Screen::screenWidth* Screen::scale)) * 0.5f) / Screen::scale;
	virtualMouse.y = (mouse.y - (GetScreenHeight() - (Screen::screenHeight * Screen::scale)) * 0.5f) / Screen::scale;
	virtualMouse = Vector2Clamp(virtualMouse, Vector2{ 0, 0 }, Vector2{ (float)Screen::screenWidth , (float)Screen::screenHeight });
	btnState = false;
	if (!checkIfHovering(virtualMouse)) {
		colorCpy = color;
		return;
	} 
	colorCpy.a = 255;
	colorCpy.r = 255;
	colorCpy.g = 255;
	colorCpy.b = 255;
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		btnState = true;
	}
	else {
		btnState = false;
	}
}

bool Button::isPressed()
{
	return btnState;
}

bool Button::checkIfHovering(Vector2 mousePos) {
	if (mousePos.x > rect.x && (mousePos.x < rect.x + rect.width) 
		&& mousePos.y > rect.y && (mousePos.y < rect.y + rect.height)) {
		return true;
	}
	return false;
	
}

void Button::draw()
{
	DrawRectangleRounded(rect, radius, 4, colorCpy);
	int fontSize = 40;
	Vector2 textLength = MeasureTextEx(Game::defaultFont,title.c_str(),fontSize,2);
	DrawTextEx(Game::defaultFont, title.c_str(), Vector2{ rect.x + (rect.width / 2) - textLength.x/2, rect.y + rect.height / 2 - textLength.y/2 }, fontSize,2, BLACK);
}
