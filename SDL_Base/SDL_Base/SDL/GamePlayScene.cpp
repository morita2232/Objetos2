#include "GamePlayScene.h"
								  //ESTO EN MENU

void GamePlayScene::Start(SDL_Renderer* rend) {

	Scene::Start(rend);

	textObjects.push_back(new UIText(rend, Vector2(250, 250), Vector2(1.f, 1.f), 0.0f, "ASTEROIDS"));

}

void GamePlayScene::Update(float dt) {

	Scene::Update(dt);

}

void GamePlayScene::Render(SDL_Renderer* rend) {

	Scene::Render(rend);

	if (!textObjects.empty()) {
		textObjects[0]->Render(rend);
	}

}

void GamePlayScene::Exit() {



}