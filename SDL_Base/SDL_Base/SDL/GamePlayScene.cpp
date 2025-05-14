#include "GamePlayScene.h"
#include "SpaceShip.h"

void GamePlayScene::Start(SDL_Renderer* rend) {

	Scene::Start(rend);

	renderer = rend;

	objects.push_back(new SpaceShip(rend, &IM));

}

void GamePlayScene::Update(float dt) {

	Scene::Update(dt);

	// actualizar temporizador
	shootTimer += dt;

	// solo disparar si pasó suficiente tiempo
	if (IM.GetKey(SDLK_SPACE, HOLD) && shootTimer >= shootCooldown) {
		for (GameObject* obj : objects) {
			SpaceShip* ship = dynamic_cast<SpaceShip*>(obj);
			if (ship) {
				Vector2 spawnPos = ship->GetPosition();
				float angle = ship->GetRotation();
				projectiles.push_back(new Projectile(renderer, spawnPos, angle, 400.0f));
			}
		}
		shootTimer = 0.0f; // reiniciar cooldown
	}

	for (auto* proj : projectiles) {
		proj->Update(dt);
	}

	for (int i = 0; i < projectiles.size(); ) {
		if (!projectiles[i]->IsAlive()) {
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i); // no incrementa i
		}
		else {
			++i;
		}
	}


}

void GamePlayScene::Render(SDL_Renderer* rend) {

	Scene::Render(rend);

	for (auto* proj : projectiles) {
		proj->Render(rend);
	}

}

void GamePlayScene::Exit() {

	for (int i = 0; i < objects.size(); i++) {
		delete(objects[i]);
	}

	objects.clear();

}