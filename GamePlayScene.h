#pragma once
#include "Scene.h"
#include "Projectile.h"
#include "Asteroid.h"
#include "EnemyShip.h"

class GamePlayScene : public Scene {
private:

	// Balas disparadas
	std::vector<Projectile*> projectiles;

	// Renderer
	SDL_Renderer* renderer;

	// Control de disparo
	float shootCooldown = COOLDOWN;
	float shootTimer = NULL;

	// Asteroides activos
	std::vector<Asteroid*> asteroids;

	// Enemigos
	std::vector<EnemyShip*> enemyShips;
	float enemySpawnTimer = 0.0f;

	// Puntuación y estado del juego
	int score = 0;
	bool started = false;
	bool gameOver = false;

public:

	void Start(SDL_Renderer* rend, InputManager* inputManager) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* rend) override;
	void SpawnAsteroids(int count);
	void Exit() override;
};
