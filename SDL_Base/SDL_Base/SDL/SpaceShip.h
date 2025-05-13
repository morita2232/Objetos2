#pragma once
#include "GameObject.h"

class SpaceShip : public GameObject {
private:

	float linealVelocity;
	float angularVelocity;
	float velocity;
	float acceleration;

public:

	SpaceShip(SDL_Renderer* renderer, float _linealVelocity, float _angularVelocity, float _velocity, float _acceleration);

	void Update(float dt) override;

};

