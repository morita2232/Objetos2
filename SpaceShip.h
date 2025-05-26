#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include <cmath>

class SpaceShip : public GameObject {
private:

	//Velocidad actual de la nave
	Vector2 velocity;

	//Direccion hacia donde apunta la nave
	Vector2 direction;

	//Velocidad de rotacion
	float angularVelocity;

	//Friccion que desacelera la nave progresivamente
	float linearDrag;

	//Friccion que desacelera la rotacion
	float angularDrag;

	//Limite de velocidad
	float maxSpeed;

	//Guarda cuanta aceleracion se aplica
	float accelerationFactor;

	InputManager* input;

public:

	SpaceShip(SDL_Renderer* renderer, InputManager* inputManager);

	Vector2 GetPosition() const { return position; }
	float GetRotation() const { return zRotation; }
	SDL_Rect GetCollider() const {
		return SDL_Rect{
			(int)(position.x),
			(int)(position.y),
			sizeToClamp.x,
			sizeToClamp.y
		};
	}

	void Update(float dt) override;

};

