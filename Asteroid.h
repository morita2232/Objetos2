#pragma once
#include "GameObject.h"

enum AsteroidSize { BIG, MEDIUM, SMALL };

class Asteroid : public GameObject {
private:
	Vector2 velocity;
	AsteroidSize size;
	bool isAlive = true;

public:
	Asteroid(SDL_Renderer* renderer, AsteroidSize size, Vector2 pos, Vector2 vel);

	void Update(float dt) override;
	void Render(SDL_Renderer* renderer) override;

	bool IsAlive() const { return isAlive; }
	AsteroidSize GetSize() const { return size; }
	void Destroy() { isAlive = false; }

	Vector2 GetVelocity() const { return velocity; }
};

