#include "Player.h"
#include "raymath.h"
#include "raylib.h"

Player::Player() { Player({ 300,300 }); }


Player::Player(Vector2 startPos) { 
	moveVec = { 0, 0 };
	rotation = 0;
	lookVec = { 0,  0, };
	position = { startPos.x, startPos.y }; 
	speed = 5;
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

	updateLookVec(DEG2RAD*rotation);

}

Vector2 Player::getLookVec() {
	return lookVec;
}

Vector2 Player::getPosition()
{
	return position;
}

void Player::updatePosition()
{
	position.x += moveVec.x * speed;
	position.y += moveVec.y * speed;
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

// Function to calculate the angle between two vectors
void Player::updateLookVec(float theta) {
	lookVec.x = cos(theta);
	lookVec.y = sin(theta);
}