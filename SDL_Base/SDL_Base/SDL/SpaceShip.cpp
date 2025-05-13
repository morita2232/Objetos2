#include "SpaceShip.h"

SpaceShip::SpaceShip(SDL_Renderer* rend, float _linealVelocity, float _angularVelocity, float _velocity, float _acceleration):GameObject(rend, new Vector2Int(0, 0), new Vector2Int(30, 40)) {

	linealVelocity = _linealVelocity;
	angularVelocity = _angularVelocity;
	velocity = _velocity;
	acceleration = _acceleration;

}

void SpaceShip::Update(float dt) {

	//position = position + (linealVelocity * dt);

}