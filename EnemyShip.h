#pragma once
#include "GameObject.h"
#include "Utils.h"

class EnemyShip : public GameObject {
private:

	// Direcci�n y velocidad
	Vector2 velocity;
	float speed;

	// Estado de vida
	bool isAlive;

public:

	// Constructor
	EnemyShip(SDL_Renderer* rend, Vector2 pos);

	// Movimiento
	void Update(float dt) override;

	// Dibujo
	void Render(SDL_Renderer* rend) override;

	// �rea de colisi�n
	SDL_Rect GetCollider();

	// Getters
	bool IsAlive() const { return isAlive; }

	// Mata al enemigo
	void Kill() { isAlive = false; }
};