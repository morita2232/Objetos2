#pragma once
#include "Scene.h"
#include "Projectile.h"
#include "Asteroid.h"
#include "EnemyShip.h"

class GamePlayScene : public Scene {
private:

	//Lista de las balas
	std::vector<Projectile*> projectiles;

	//Puntero al renderer
	SDL_Renderer* renderer;

	//Tiempo minimo entre disparos
	float shootCooldown = COOLDOWN;

	//Control de cuando se puede volver a disparar
	float shootTimer = NULL;

	std::vector<Asteroid*> asteroids;

	// Para la creacion de los EnemyShips, anado un vector de estos
	std::vector<EnemyShip*> enemyShips;
	// Temporizador para saber cuanto tardará en spawnear otro enemyShip
	float enemySpawnTimer = 0.0f;
	float enemySpawnInterval = 15.0f;

	//Para la puntuacion
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