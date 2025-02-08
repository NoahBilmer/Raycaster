#include "Player.h"
#include "raymath.h"
#include "raylib.h"
#include <vector>
#include "Map.h"
#include "Helpers.h"
#include "RayCaster.h"
#include "Entity.h"


Player::Player() {
	moveVec = { 0, 0 };
	lookVec = { 0,  0, };
	horizontalVec = { 0,0 };
	speed = 2;
	this->map = new Map();
	this->entity = new Entity{ Vector2{500,500},90 };
}

Player::Player(Vector2 startPos, Map& map) : Player() { 
	this->map = &map;
	this->entity = new Entity{ startPos,90 };
}

void Player::setLookDir(bool lookDir)
{
	
	if (entity->rotation > 360)
		entity->rotation = 0;
	if (entity->rotation < 0)
		entity->rotation = 360;
		
	if (lookDir) { // we wish to look right
		entity->rotation--;
	}
	else { // we wish to look left.
		entity->rotation++;
	}

	lookVec = Vector2Normalize(getRayFromAngle(DEG2RAD * entity->rotation + (DEG2RAD * fov/2)));
	horizontalVec = Vector2Normalize(getRayFromAngle((DEG2RAD * entity->rotation + DEG2RAD * fov/2) + (DEG2RAD * 90)));

}

Vector2 Player::getLookVec() {
	return lookVec;
}

Vector2 Player::getPosition()
{
	return entity->position;
}

float Player::getRotation()
{
	return entity->rotation;
}

void Player::updatePosition()
{
	
	entity->position.y += moveVec.x * horizontalVec.y * speed;
	entity->position.x += moveVec.x * horizontalVec.x * speed;
	entity->position.y += moveVec.y * lookVec.y * speed;
	entity->position.x += moveVec.y * lookVec.x * speed;
}

Entity* Player::getEntity()
{
	return entity;
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



