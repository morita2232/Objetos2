#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Utils.h"

class GameObject {
protected:

	//Posicion del objeto
	Vector2 position;

	//Escala del objeto
	Vector2 scale;

	//Rotacion del objeto
	float zRotation;

	//Textura del objeto
	SDL_Texture* texture;

	//Coordenadas del sprite en el spritesheet
	Vector2Int textureCoor;

	//Tamaño del sprite a recortar
	Vector2Int sizeToClamp;

	SDL_Rect destination;

	bool alive = true;

public:

	GameObject(SDL_Renderer* renderer, Vector2Int textureCoor, Vector2Int sizeToClamp);
	virtual ~GameObject();

	virtual void Update(float dt) = 0;
	virtual void Render(SDL_Renderer* renderer);

	bool IsAlive() const { return alive; }
	void Kill() { alive = false; } // Sam, cuando el objeto muere asegurate que se llame a esta función para que todo funcione gucci

	void Collider();
	Vector2 GetPosition() const { return position; }

};
