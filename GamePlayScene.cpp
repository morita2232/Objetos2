#include "GamePlayScene.h"
#include "SpaceShip.h"
#include "ScoreManager.h"

void GamePlayScene::Start(SDL_Renderer* rend, InputManager* inputManager) {
	Scene::Start(rend, inputManager);

	// Reinicio de estado
	for (UIText* txt : textObjects) {
		delete txt;
	}
	textObjects.clear();

	started = false;
	gameOver = false;
	score = 0;

	//Dejamos todos los vectores preparados y vacios para empezar
	for (Projectile* p : projectiles) delete p;
	projectiles.clear();

	for (Asteroid* a : asteroids) delete a;
	asteroids.clear();

	for (EnemyShip* e : enemyShips) delete e;
	enemyShips.clear();

	renderer = rend;

	//Creacion de una nave
	objects.push_back(new SpaceShip(rend, &IM));

	//Textos de inicio
	textObjects.push_back(new UIText(rend, Vector2(100, 40), Vector2(1.f, 1.f), 0.0f, "SCORE: 0"));
	textObjects.push_back(new UIText(rend, Vector2(255, 70), Vector2(1.f, 1.f), 0.0f, "PRESS ARROW KEY TO START"));
}


void GamePlayScene::Update(float dt) {

	Scene::Update(dt);

	//Los asteroides comienzan a spawnear cuando muevo la nave por primera vez
	if (!started && (IM.GetKey(SDLK_UP, HOLD) || IM.GetKey(SDLK_LEFT, HOLD) || IM.GetKey(SDLK_RIGHT, HOLD))) {
		if (textObjects.size() > 1) {
			delete textObjects[1];
			textObjects.erase(textObjects.begin() + 1);
		}
		started = true;
		SpawnAsteroids(5);
	}

	// ENEMY SPACE SHIP SPAWN:
	// Si el juego ha empezado y no ha finalizado - if
	if (started && !gameOver) {
		//Empieza la cuenta para el spawner
		enemySpawnTimer += dt;

		//Ha llegado al tiempo indicado - if
		if (enemySpawnTimer >= enemySpawnInterval) {

			// Posicion de spawn random entre las dimensiones del mapa
			float randScreenW = rand() % (int)SCREENW;
			float randScreenH = rand() % (int)SCREENH;
			Vector2 spawnPos(randScreenW, randScreenH);

			// Se anade nuevo enemigo en vector con dicha pos random
			enemyShips.push_back(new EnemyShip(renderer, spawnPos));

			//Se reinicia el temporizador para que se vuelva a producir el loop
			enemySpawnTimer = 0.0f;
		}
	}

	//Actualizacion del temporizador de disparo
	shootTimer += dt;

	//Comprobacion de disparo, solo disparar si pasó suficiente tiempo
	if (IM.GetKey(SDLK_SPACE, HOLD) && shootTimer >= shootCooldown) {
		for (GameObject* obj : objects) {

			//El dynamic_cast lo tuve que buscar con chatGPT porque no me funcionaba el disparo sin esto
			SpaceShip* ship = dynamic_cast<SpaceShip*>(obj);
			if (ship) {
				//Desde donde se spawnea la bala
				Vector2 spawnPos = ship->GetPosition();

				//Hacia donde va la bala
				float angle = ship->GetRotation();

				//Creacion de la bala
				projectiles.push_back(new Projectile(renderer, spawnPos, angle, 400.0f));
			}
		}
		//Reinicio del cooldown
		shootTimer = 0.0f;
	}

	//Actualizacion y eliminacion de balas no vivas
	for (auto it = projectiles.begin(); it != projectiles.end(); ) {
		(*it)->Update(dt);
		if (!(*it)->IsAlive()) {
			delete* it;
			it = projectiles.erase(it);
		}
		else {
			++it;
		}
	}

	for (int i = 0; i < asteroids.size(); ) {
		if (!asteroids[i]->IsAlive()) {
			delete asteroids[i];
			asteroids.erase(asteroids.begin() + i);
		}
		else {
			asteroids[i]->Update(dt);
			++i;
		}
	}

	// ENEMY SHIP UPDATE and KILL:
	//Por cada enemyShip en vector - for
	for (int i = 0; i < enemyShips.size(); ) {

		//Checkea si estan vivos o no, si NO estan vivos, se borran, esto hara que no haya memory leaks.
		EnemyShip* enemy = enemyShips[i];
		if (!enemy->IsAlive()) {
			delete enemy;
			enemyShips.erase(enemyShips.begin() + i);
		}
		//Si estan vivos simplemente actualiza dichos enemigos por deltatime  - Update(dt)
		else {
			enemy->Update(dt);
			++i;
		}
	}

	// Colisión entre balas y asteroides
	for (auto p = projectiles.begin(); p != projectiles.end(); ) {
		bool projectileUsed = false;
		SDL_Rect r1 = { (int)(*p)->GetPosition().x, (int)(*p)->GetPosition().y, 8, 8 };

		// ASTEROIDES
		for (auto a = asteroids.begin(); a != asteroids.end(); ++a) {
			if ((*a)->IsAlive() && (*p)->IsAlive()) {
				SDL_Rect r2 = (*a)->GetCollider(); // Te explico abajo cómo crearlo

				//Colisionan - if
				if (SDL_HasIntersection(&r1, &r2)) {
					// Cogemos sus dimensiones, posicion y velocidad para cambiarlas luego
					AsteroidSize size = (*a)->GetSize();
					Vector2 pos = (*a)->GetPosition();
					Vector2 vel = (*a)->GetVelocity();

					// Ambos se destruyen
					(*a)->Destroy();
					(*p)->Kill();

					//Si el asteroide es grande o mediano, es decir, se tiene que partir en dos - if
					if (size == BIG || size == MEDIUM) {
						//Cogemos nuevo tamano con un operador
						AsteroidSize newSize = (size == BIG) ? MEDIUM : SMALL;

						// Se crean dos nuevos asteroides con dir y vel aleatoria
						for (int i = 0; i < 2; ++i) {
							// Dirección aleatoria
							Vector2 newVel = Vector2((rand() % 100 - 50), (rand() % 100 - 50));
							asteroids.push_back(new Asteroid(renderer, newSize, pos, newVel));
						}
					}

					// Sumar puntuación según tamaño
					if (size == BIG) score += 50;
					else if (size == MEDIUM) score += 30;
					else if (size == SMALL) score += 20;

					textObjects[0]->SetText("SCORE: " + std::to_string(score), renderer);

					projectileUsed = true;
					break;
				}
			}
		}

		// ENEMY SHIPS
		for (auto e = enemyShips.begin(); e != enemyShips.end(); ++e) {
			//Si enemyShip sigue vivo - if
			if ((*e)->IsAlive()) {
				// Coge su collider
				SDL_Rect r3 = (*e)->GetCollider();

				//Si este tiene una colision con una bala del jugador
				if (SDL_HasIntersection(&r1, &r3)) {
					// Destruir enemyShip y bala
					(*p)->Kill();
					(*e)->Kill();
					projectileUsed = true;

					//Se actualiza score (+150 puntos!)
					score += 150;
					textObjects[0]->SetText("SCORE: " + std::to_string(score), renderer);
					break;
				}
			}
		}

		//Si se ha usado la bala se destruye:
		if (projectileUsed) {
			delete* p;
			p = projectiles.erase(p);
		}
		else {
			++p;
		}
	}

	//ASTEROID VS SHIP
	for (GameObject* obj : objects) {
		SpaceShip* ship = dynamic_cast<SpaceShip*>(obj);
		if (!ship) continue; // No es una nave, saltamos

		if (ship->IsRespawning()) continue;

		if (!ship || !ship->IsAlive()) continue;

		for (Asteroid* a : asteroids) {
			if (!a->IsAlive()) continue;

			SDL_Rect shipRect = ship->GetCollider(); // ver abajo

			int shipLives = ship->GetLives();

			SDL_Rect asteroidRect = a->GetCollider();

			//Si se ha colisionado con el jugador
			if (SDL_HasIntersection(&shipRect, &asteroidRect)) {
				
				/*// Primero tenemos que saber de que tamano es el asteroid colisionado:
				AsteroidSize size = a->GetSize();

				// Si es BIG o MEDIUM - if
				if (size == BIG || size == MEDIUM) {

					// Con un operador decidimos si este nuevo tamano es mediano o pequeno
					AsteroidSize newSize = (size == BIG) ? MEDIUM : SMALL;

					//Se crean nuevos asteroides que van a diferentes direcciones
					for (int s = 0; s < 2; ++s) {
						Vector2 newVel(rand() % 100 - 50, rand() % 100 - 50);
						asteroids.push_back(new Asteroid(renderer, newSize, a->GetPosition(), newVel));
					}
				}
				*/

				ship->MinusLives();

				if (shipLives == 0) {
					a->Destroy();
					ship->Kill();
					ScoreManager::AddScore(score);
					gameOver = true;
					textObjects.push_back(new UIText(renderer, Vector2(140, 200), Vector2(1.5f, 1.5f), 0.0f, "YOU LOSE"));
					textObjects.push_back(new UIText(renderer, Vector2(100, 240), Vector2(1.f, 1.f), 0.0f, "PRESS R TO RETURN"));
				}
				else {
				//Se destruye asteroide original
					a->Destroy();
					ship->StartRespawn();

				}

				break;
			}
		}
	}

	// ENEMY SHIP VS ELEMENTOS DEL MAPA
	//Por cada enemyShip vivo del vector - for
	for (EnemyShip* enemy : enemyShips) {
		if (!enemy->IsAlive()) continue;

		// ENEMY VS ASTEROID
		//Por cada asteroide vivo del vector - for
		for (Asteroid* a : asteroids) {
			if (!a->IsAlive()) continue;

			SDL_Rect enemyRect = enemy->GetCollider();
			SDL_Rect asteroidRect = a->GetCollider();

			//Si se tiene colision se destruyen ambos
			if (SDL_HasIntersection(&enemyRect, &asteroidRect)) {
				// Primero tenemos que saber de que tamano es el asteroid colisionado:
				AsteroidSize size = a->GetSize();

				// Si es BIG o MEDIUM - if
				if (size == BIG || size == MEDIUM) {

					// Con un operador decidimos si este nuevo tamano es mediano o pequeno
					AsteroidSize newSize = (size == BIG) ? MEDIUM : SMALL;

					//Se crean nuevos asteroides que van a diferentes direcciones
					for (int s = 0; s < 2; ++s) {
						Vector2 newVel(rand() % 100 - 50, rand() % 100 - 50);
						asteroids.push_back(new Asteroid(renderer, newSize, a->GetPosition(), newVel));
					}
				}
				//Se destruye asteroide original y enemyShip
				a->Destroy();
				enemy->Kill();
				break;
			}
		}

		// SHIP VS ENEMY
		//Por cada objeto vivo del vector - for
		for (GameObject* obj : objects) {
			//Cogemos nuestra nave como objeto
			SpaceShip* ship = dynamic_cast<SpaceShip*>(obj);

			//Si esta viva y tiene interaccion con el EnemyShip, ambos se destruyen y se muestra un mensaje de GAMEOVER
			if (ship && ship->IsAlive()) {

				//Cogemos sus coliders
				SDL_Rect enemyRect = enemy->GetCollider();
				SDL_Rect shipRect = ship->GetCollider();

				//Comprobamos si han chocado y si es asi, ambos mueren y sale mensaje de gameOver
				if (SDL_HasIntersection(&enemyRect, &shipRect)) {
					ship->Kill();
					enemy->Kill();
					gameOver = true;
					textObjects.push_back(new UIText(renderer, Vector2(140, 200), Vector2(1.5f, 1.5f), 0.0f, "YOU LOSE"));
					textObjects.push_back(new UIText(renderer, Vector2(100, 240), Vector2(1.f, 1.f), 0.0f, "PRESS R TO RETURN"));
				}
			}
		}
	}

	//Actualizacion de punuaciones 
	for (int i = 0; i < objects.size(); ++i) {
		SpaceShip* ship = dynamic_cast<SpaceShip*>(objects[i]);
		if (ship && !ship->IsAlive()) {
			targetScene = "HighScores";
			isFinished = true;
			break;
		}
	}

	if (gameOver && IM.GetKey(SDLK_r, HOLD)) {
		targetScene = "HighScores";
		isFinished = true;
	}

}

void GamePlayScene::Render(SDL_Renderer* rend) {

	Scene::Render(rend);

	//Renderizacion de las balas activas
	for (std::vector<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); ++it) {
		(*it)->Render(rend);
	}

	// ASTEROIDS
	for (Asteroid* a : asteroids) {
		a->Render(renderer);
	}

	// ENEMY SHIP
	for (EnemyShip* e : enemyShips) {
		e->Render(renderer);
	}

	//Si textObjects esta vacio coge este valor para que no este vacia la pantalla
	if (textObjects.empty()) {
		textObjects[0]->SetText("NO HAY TEXTO", rend);
		textObjects[0]->Render(rend);
	}
	else {
		for (int i = 0; i < textObjects.size(); i++) {
			textObjects[i]->Render(rend);
		}
	}
}

void GamePlayScene::SpawnAsteroids(int count) {
	for (int i = 0; i < count; ++i) {
		Vector2 pos;
		float minDistance = 100.0f; // distancia mínima respecto al centro

		do {
			pos = Vector2(rand() % (int)SCREENW, rand() % (int)SCREENH);
		} while ((pos - Vector2(SCREENW / 2.0f, SCREENH / 2.0f)).Magnitude() < minDistance);

		Vector2 vel((rand() % 100 - 50), (rand() % 100 - 50));
		asteroids.push_back(new Asteroid(renderer, BIG, pos, vel));
	}
}


void GamePlayScene::Exit() {

	//Liberacion de memoria de balas
	for (int i = 0; i < projectiles.size(); ++i) {
		delete projectiles[i];
	}
	projectiles.clear();

	//Liberacion de memoria de objetos
	for (int i = 0; i < objects.size(); i++) {
		delete(objects[i]);
	}
	objects.clear();

	//Liberaciond e memoria de enemyShips
	for (EnemyShip* e : enemyShips) {
		delete e;
	}

	projectiles.clear();
	asteroids.clear();
	enemyShips.clear();
}