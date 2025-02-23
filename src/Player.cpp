#include "include/Player.h"

/**
 * Default constructor for the Player class.
 */
Player::Player() {
	moveVec = { 0, 0 };
	lookVec = { 0,  0, };
	horizontalVec = { 0,0 };
	speed = 2;
	this->map = Map();
	this->entity = Entity{ Vector2{1100,1100 }, 60
};
}


/**
 * Custom constructor for Player
 */
Player::Player(Vector2 startPos, Map& map) : Player() { 
	this->map = map;
	this->entity = Entity{ startPos,60 };
}

/**
 * Updates the rotation of player.
 * 
 * @param newDir the new direction of the player.
 */
void Player::updateRotation(int newDir)
{
	entity.rotation = newDir;
	if (entity.rotation > 360)
		entity.rotation = 0;
	if (entity.rotation < 0)
		entity.rotation = 360;

	lookVec = Vector2Normalize(getRayFromAngle(DEG2RAD * entity.rotation + (DEG2RAD * fov/2)));
	horizontalVec = Vector2Normalize(getRayFromAngle((DEG2RAD * entity.rotation + DEG2RAD * fov/2) + (DEG2RAD * 90)));

}

/*
 * Returns the lookVec.
 */
Vector2 Player::getLookVec() {
	return lookVec;
}

/*
 * Returns the position.
 */
Vector2 Player::getPosition()
{
	return entity.position;
}

/*
 * Returns the rotation.
 */
float Player::getRotation()
{
	return entity.rotation;
}

/*
 * Updates the position of the player based on the state of the 
 * moveVec/horizontalVec/lookVec (represents this frame's input.)
 */
void Player::updatePosition()
{
	entity.position = getNextPosition();
}

Vector2 Player::getNextPosition() {
	Vector2 nextPos = entity.position;
	nextPos.y += moveVec.x * horizontalVec.y * speed;
	nextPos.x += moveVec.x * horizontalVec.x * speed;
	nextPos.y += moveVec.y * lookVec.y * speed;
	nextPos.x += moveVec.y * lookVec.x * speed;
	return nextPos;
}

/*
 * Returns the pointer to the players entity object.
 */
Entity& Player::getEntity()
{
	return entity;
}
	
/*
 * Returns the move vector. 
 */
Vector2 Player::getMoveVec() {
	return moveVec;
}

/*
 * Sets the move vector.
 */
void Player::setMoveVec(Vector2 newVec)
{
	moveVec = newVec;
}

/*
 * Updates the "state" vectors to match the current input.
 */
void Player::UpdateStateVecs(Vector2 newMove, Vector2 newLook) {
	moveVec.x += newMove.x;
	moveVec.y += newMove.y;
	lookVec.x += newLook.x;
	lookVec.y += newLook.y;

}



