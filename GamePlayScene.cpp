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

	for (Projectile* p : projectiles) delete p;
	projectiles.clear();

	for (Asteroid* a : asteroids) delete a;
	asteroids.clear();

	renderer = rend;

	//Creacion de una nave
	objects.push_back(new SpaceShip(rend, &IM));

	textObjects.push_back(new UIText(rend, Vector2(100, 40), Vector2(1.f, 1.f), 0.0f, "SCORE: 0"));
	textObjects.push_back(new UIText(rend, Vector2(90, 70), Vector2(1.f, 1.f), 0.0f, "PRESS ARROW KEY TO START"));
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

	// Colisión entre balas y asteroides
	for (auto p = projectiles.begin(); p != projectiles.end(); ) {
		bool projectileUsed = false;

		for (auto a = asteroids.begin(); a != asteroids.end(); ++a) {
			if ((*a)->IsAlive() && (*p)->IsAlive()) {
				SDL_Rect r1 = { (int)(*p)->GetPosition().x, (int)(*p)->GetPosition().y, 8, 8 };
				SDL_Rect r2 = (*a)->GetCollider(); // Te explico abajo cómo crearlo

				if (SDL_HasIntersection(&r1, &r2)) {
					// Destruir asteroide y bala
					(*a)->Destroy();
					(*p)->Kill(); // Necesitarás implementar esto igual que Destroy()

					// Sumar puntuación según tamaño
					AsteroidSize size = (*a)->GetSize();
					if (size == BIG) score += 50;
					else if (size == MEDIUM) score += 30;
					else if (size == SMALL) score += 20;

					// Actualizar texto del HUD
					textObjects[0]->SetText("SCORE: " + std::to_string(score), renderer);

					projectileUsed = true;
					break;
				}
			}
		}

		if (projectileUsed) {
			delete* p;
			p = projectiles.erase(p);
		}
		else {
			++p;
		}
	}

	for (GameObject* obj : objects) {
		SpaceShip* ship = dynamic_cast<SpaceShip*>(obj);
		if (!ship || !ship->IsAlive()) continue;

		for (Asteroid* a : asteroids) {
			if (!a->IsAlive()) continue;

			SDL_Rect shipRect = ship->GetCollider(); // ver abajo
			SDL_Rect asteroidRect = a->GetCollider();

			if (SDL_HasIntersection(&shipRect, &asteroidRect)) {
				ship->Kill();
				ScoreManager::AddScore(score);
				gameOver = true;
				textObjects.push_back(new UIText(renderer, Vector2(140, 200), Vector2(1.5f, 1.5f), 0.0f, "YOU LOSE"));
				textObjects.push_back(new UIText(renderer, Vector2(100, 240), Vector2(1.f, 1.f), 0.0f, "PRESS R TO RETURN"));
				break;
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

	for (Asteroid* a : asteroids) {
		a->Render(renderer);
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

	//Liberacion de memoria
	for (int i = 0; i < objects.size(); i++) {
		delete(objects[i]);
	}
	objects.clear();

	//Liberacion de memoria de balas
	for (int i = 0; i < projectiles.size(); ++i) {
		delete projectiles[i];
	}
	projectiles.clear();

	asteroids.clear();
	projectiles.clear();
}



