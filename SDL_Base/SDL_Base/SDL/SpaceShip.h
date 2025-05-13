#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include <cmath>

class SpaceShip : public GameObject {
private:

	Vector2 velocity;
	Vector2 acceleration;
	Vector2 direction;

	float angularVelocity;
	float linearDrag;
	float angularDrag;
	float maxSpeed;
	float accelerationFactor;

	InputManager* input;

public:

	SpaceShip(SDL_Renderer* renderer, InputManager* inputManager);

	void Update(float dt) override;

};

