#pragma once
#include "GameObject.h"

class SpaceShip : public GameObject {
private:

	float linealVelocity = 3.f;
	float angularVelocity = 2.f;

public:

	SpaceShip(SDL_Renderer* renderer);

	void Update(float dt) override;

};

