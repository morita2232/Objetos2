#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Utils.h"

class GameObject {
protected:

	// Posici�n en pantalla
	Vector2 position;

	// Escala del objeto
	Vector2 scale;

	// Rotaci�n en grados
	float zRotation;

	// Textura del sprite
	SDL_Texture* texture;

	// Coordenadas dentro del spritesheet
	Vector2Int textureCoor;

	// Tama�o del sprite recortado
	Vector2Int sizeToClamp;

	// Rect�ngulo de destino para render
	SDL_Rect destination;

	// Estado de vida
	bool alive = true;

public:

	// Constructor y destructor
	GameObject(SDL_Renderer* renderer, Vector2Int textureCoor, Vector2Int sizeToClamp);
	virtual ~GameObject();

	// M�todos virtuales a implementar
	virtual void Update(float dt) = 0;
	virtual void Render(SDL_Renderer* renderer);

	// Getters y l�gica de vida
	bool IsAlive() const { return alive; }
	void Kill() { alive = false; } // Marca el objeto como muerto

	// C�lculo del �rea de colisi�n
	void Collider();

	// Devuelve la posici�n
	Vector2 GetPosition() const { return position; }
};