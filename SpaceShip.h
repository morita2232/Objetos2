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

	int lives;

	//RESPAWN
	bool respawning = false;
	float respawnTimer = 0.0f;
	float respawnDuration = 3.0f;
	bool visible = true;
	float blinkTimer = 0.0f;
	float blinkInterval = 0.2f;


public:

	SpaceShip(SDL_Renderer* renderer, InputManager* inputManager);

	void Render(SDL_Renderer* renderer) override;

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

	int GetLives() { return lives; }

	int MinusLives() { lives -= 1; return lives; }


	//RESPAWN
	void StartRespawn();
	bool IsRespawning() const;

	void Update(float dt) override;

};

