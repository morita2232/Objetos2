#pragma once
#include "GameObject.h"

// Tamaños posibles de asteroide
enum AsteroidSize { BIG, MEDIUM, SMALL };

class Asteroid : public GameObject {
private:

	// Velocidad del asteroide
	Vector2 velocity;

	// Tamaño (big, medium, small)
	AsteroidSize size;

	// Estado de vida
	bool isAlive = true;

public:

	// Constructor
	Asteroid(SDL_Renderer* renderer, AsteroidSize size, Vector2 pos, Vector2 vel);

	// Movimiento
	void Update(float dt) override;

	// Dibujo
	void Render(SDL_Renderer* renderer) override;

	// Getters
	bool IsAlive() const { return isAlive; }
	AsteroidSize GetSize() const { return size; }
	Vector2 GetVelocity() const { return velocity; }

	// Devuelve el área de colisión
	SDL_Rect GetCollider() const {
		return SDL_Rect{
			(int)(position.x),
			(int)(position.y),
			sizeToClamp.x,
			sizeToClamp.y
		};
	}

	// Marca como destruido
	void Destroy() { isAlive = false; }
};

