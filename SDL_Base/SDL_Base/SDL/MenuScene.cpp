#include "MenuScene.h"
#include "SpaceShip.h"

			  //ESTO EN GAMEPLAY
void MenuScene::Start(SDL_Renderer* rend) {

	Scene::Start(rend);

	objects.push_back(new SpaceShip(rend));

}

void MenuScene::Update(float dt) {

	Scene::Update(dt);

}

void MenuScene::Render(SDL_Renderer* rend) {

	Scene::Render(rend);

}

void MenuScene::Exit() {

	for (int i = 0; i < objects.size(); i++) {
		delete(objects[i]);
	}

	objects.clear();

}