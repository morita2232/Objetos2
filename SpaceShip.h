#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include <cmath>

class SpaceShip : public GameObject {
private:

	// Movimiento
	Vector2 velocity;
	Vector2 direction;
	float angularVelocity;

	// Fricciones
	float linearDrag;
	float angularDrag;

	// Velocidades
	float accelerationFactor;

	// Input del jugador
	InputManager* input;

	// Vidas del jugador
	int lives;

	// Estado de respawn
	bool respawning = false;
	float respawnTimer = 0.0f;
	bool visible = true;
	float blinkTimer = 0.0f;

public:

	// Constructor
	SpaceShip(SDL_Renderer* renderer, InputManager* inputManager);

	// Dibujo
	void Render(SDL_Renderer* renderer) override;

	// Movimiento y lógica
	void Update(float dt) override;

	// Getters
	Vector2 GetPosition() const { return position; }
	float GetRotation() const { return zRotation; }

	// Colisión
	SDL_Rect GetCollider() const {
		return SDL_Rect{
			(int)(position.x),
			(int)(position.y),
			sizeToClamp.x,
			sizeToClamp.y
		};
	}

	// Vidas
	int GetLives() { return lives; }
	int MinusLives() { lives -= 1; return lives; }

	// Respawn
	void StartRespawn();
	bool IsRespawning() const;
};