#include "GamePlayScene.h"
#include "SpaceShip.h"
								  //ESTO EN MENU

void GamePlayScene::Start(SDL_Renderer* rend) {

	Scene::Start(rend);

	objects.push_back(new SpaceShip(rend, 3.f, 2.f, 5.f, 1.f));

}

void GamePlayScene::Update(float dt) {

	Scene::Update(dt);

}

void GamePlayScene::Render(SDL_Renderer* rend) {

	Scene::Render(rend);

}

void GamePlayScene::Exit() {

	for (int i = 0; i < objects.size(); i++) {
		delete(objects[i]);
	}

	objects.clear();

}