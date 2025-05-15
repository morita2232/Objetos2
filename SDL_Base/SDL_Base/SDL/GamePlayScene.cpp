#include "GamePlayScene.h"
#include "SpaceShip.h"

void GamePlayScene::Start(SDL_Renderer* rend) {

	Scene::Start(rend);

	renderer = rend;

	//Creacion de una nave
	objects.push_back(new SpaceShip(rend, &IM));

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

	//Actualizacion de todos las balas vivas
	for (std::vector<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); ++it) {
		(*it)->Update(dt);
	}

	//Elimina las balas que no estan vivas
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

	//Renderizacion de las balas activas
	for (std::vector<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); ++it) {
		(*it)->Render(rend);
	}


}

void GamePlayScene::Exit() {

	//Liberacion de memoria
	for (int i = 0; i < objects.size(); i++) {
		delete(objects[i]);
	}

	objects.clear();

}


