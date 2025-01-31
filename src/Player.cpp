#include "Player.h"
#include "raymath.h"
#include "raylib.h"
#include <vector>
#include "Map.h"
#include "Helpers.h"
#include "RayCaster.h"

Player::Player() { Player({ 300,300 }); }

Player::Player(Vector2 startPos) { 
	moveVec = { 0, 0 };
	rotation = 0;
	lookVec = { 0,  0, };
	horizontalVec = {0,0};
	position = { startPos.x, startPos.y }; 
	speed = 2;
}


void Player::setLookDir(bool lookDir)
{
	
	if (rotation > 360)
		rotation = 0;
	if (rotation < 0)
		rotation = 360;
		
	if (lookDir) { // we wish to look right
		rotation--;
	}
	else { // we wish to look left.
		rotation++;
	}

	lookVec = Vector2Normalize(getRayFromAngle(DEG2RAD * rotation + (DEG2RAD * FOV/2)));
	horizontalVec = Vector2Normalize(getRayFromAngle((DEG2RAD * rotation + DEG2RAD * FOV/2) + (DEG2RAD * 90)));

}

Vector2 Player::getLookVec() {
	return lookVec;
}

Vector2 Player::getPosition()
{
	return position;
}

float Player::getRotation()
{
	return rotation;
}

void Player::updatePosition()
{
	
	position.y += moveVec.x * horizontalVec.y * speed;
	position.x += moveVec.x * horizontalVec.x * speed;
	position.y += moveVec.y * lookVec.y * speed;
	position.x += moveVec.y * lookVec.x * speed;
}
	

Vector2 Player::getMoveVec() {
	return moveVec;
}

void Player::setMoveVec(Vector2 newVec)
{
	moveVec = newVec;
}

void Player::UpdateStateVecs(Vector2 newMove, Vector2 newLook) {
	moveVec.x += newMove.x;
	moveVec.y += newMove.y;
	lookVec.x += newLook.x;
	lookVec.y += newLook.y;

}



