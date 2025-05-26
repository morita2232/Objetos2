#pragma once
#include "GameObject.h"
#include "Utils.h"

class EnemyShip : public GameObject {
private:
	Vector2 velocity;
	float speed;
	bool isAlive;

public:
	EnemyShip(SDL_Renderer* rend, Vector2 pos);

	void Update(float dt) override;
	void Render(SDL_Renderer* rend) override;

	SDL_Rect GetCollider();

	bool IsAlive() const { return isAlive; }
	void Kill() { isAlive = false; }
};