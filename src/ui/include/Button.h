#pragma once

#include "raylib.h"
#include "string.h"
#include <iostream>

class Button {
public:
	Button();
	Button(Rectangle rect, float radius, Color color, std::string title);
	void setOnClick(void (*function)(void));
	void draw();
	void updateState();
	bool isPressed();
	
private:
	bool checkIfHovering(Vector2 mousePos);
	Rectangle rect;
	float radius;
	Color color;
	Color colorCpy;
	std::string title;
	bool isHovering;
	bool btnState;
};