#include "GamePlayScene.h"
#include "SpaceShip.h"

void GamePlayScene::Start(SDL_Renderer* rend, InputManager* inputManager) {

	Scene::Start(rend, inputManager);

	renderer = rend;

	//Creacion de una nave
	objects.push_back(new SpaceShip(rend, &IM));

	textObjects.push_back(new UIText(rend, Vector2(100, 40), Vector2(1.f, 1.f), 0.0f, "SCORE: 0"));

	SpawnAsteroids(5);
}

void GamePlayScene::Update(float dt) {

	Scene::Update(dt);

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
		Vector2 pos(rand() % (int)SCREENW, rand() % (int)SCREENH);
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
}



