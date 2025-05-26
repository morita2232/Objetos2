#include "Asteroid.h"
#include <cmath>
#include <cstdlib>

Asteroid::Asteroid(SDL_Renderer* renderer, AsteroidSize size, Vector2 pos, Vector2 vel)
	: GameObject(renderer,
		(size == BIG) ? Vector2Int(156, 0) :
		(size == MEDIUM) ? Vector2Int(160, 0) :
		Vector2Int(192, 0),

		(size == BIG) ? Vector2Int(101, 90) :
		(size == MEDIUM) ? Vector2Int(24, 24) :
		Vector2Int(16, 16))

{
	this->position = pos;
	this->velocity = vel;
	this->size = size;

	// AJUSTE DE ESCALA
	switch (size) {
	case BIG:    scale = Vector2(1.5f, 1.5f); break;
	case MEDIUM: scale = Vector2(1.0f, 1.0f); break;
	case SMALL:  scale = Vector2(0.5f, 0.5f); break;
	}
}


void Asteroid::Update(float dt) {
	position += velocity * dt;

	// Wrap around de pantalla
	if (position.x < -sizeToClamp.x) position.x = SCREENW;
	if (position.x > SCREENW) position.x = -sizeToClamp.x;
	if (position.y < -sizeToClamp.y) position.y = SCREENH;
	if (position.y > SCREENH) position.y = -sizeToClamp.y;
}

void Asteroid::Render(SDL_Renderer* renderer) {
	GameObject::Render(renderer);
}
