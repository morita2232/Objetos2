#include "Asteroid.h"
#include <cmath>
#include <cstdlib>

//CONSTRUCTOR: crea un asteroide del tamaño especificado con posición y velocidad dadas
Asteroid::Asteroid(SDL_Renderer* renderer, AsteroidSize size, Vector2 pos, Vector2 vel)
	: GameObject(renderer,
		// Posición del sprite en la spritesheet según el tamaño
		(size == BIG) ? Vector2Int(156, 0) :
		(size == MEDIUM) ? Vector2Int(39, 0) :
		Vector2Int(126, 0),

		// Tamaño del sprite a recortar en la spritesheet
		(size == BIG) ? Vector2Int(101, 90) :
		(size == MEDIUM) ? Vector2Int(39, 39) :
		Vector2Int(21, 21))
{
	// Asignamos posición y velocidad inicial
	this->position = pos;
	this->velocity = vel;
	this->size = size;

	// Ajustamos la escala visual en pantalla según el tamaño
	switch (size) {
	case BIG:    scale = Vector2(1.5f, 1.5f); break;
	case MEDIUM: scale = Vector2(1.25f, 1.25f); break;
	case SMALL:  scale = Vector2(1.0f, 1.0f); break;
	}
}

//UPDATE: mueve el asteroide según su velocidad y aplica el wrap-around de pantalla
void Asteroid::Update(float dt) {
	// Movimiento = velocidad * tiempo
	position += velocity * dt;

	// Wrap-around horizontal
	if (position.x < -sizeToClamp.x) position.x = SCREENW;
	if (position.x > SCREENW)        position.x = -sizeToClamp.x;

	// Wrap-around vertical
	if (position.y < -sizeToClamp.y) position.y = SCREENH;
	if (position.y > SCREENH)        position.y = -sizeToClamp.y;
}

//RENDER: se apoya en la lógica común de GameObject para dibujar el sprite
void Asteroid::Render(SDL_Renderer* renderer) {
	GameObject::Render(renderer);
}
