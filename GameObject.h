#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Utils.h"

class GameObject {
protected:

	// Posición en pantalla
	Vector2 position;

	// Escala del objeto
	Vector2 scale;

	// Rotación en grados
	float zRotation;

	// Textura del sprite
	SDL_Texture* texture;

	// Coordenadas dentro del spritesheet
	Vector2Int textureCoor;

	// Tamaño del sprite recortado
	Vector2Int sizeToClamp;

	// Rectángulo de destino para render
	SDL_Rect destination;

	// Estado de vida
	bool alive = true;

public:

	// Constructor y destructor
	GameObject(SDL_Renderer* renderer, Vector2Int textureCoor, Vector2Int sizeToClamp);
	virtual ~GameObject();

	// Métodos virtuales a implementar
	virtual void Update(float dt) = 0;
	virtual void Render(SDL_Renderer* renderer);

	// Getters y lógica de vida
	bool IsAlive() const { return alive; }
	void Kill() { alive = false; } // Marca el objeto como muerto

	// Cálculo del área de colisión
	void Collider();

	// Devuelve la posición
	Vector2 GetPosition() const { return position; }
};