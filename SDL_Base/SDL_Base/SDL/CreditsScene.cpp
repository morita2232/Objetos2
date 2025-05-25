#include "CreditsScene.h"

void CreditsScene::Start(SDL_Renderer* rend, InputManager* inputManager) {

	Scene::Start(rend, inputManager);

	//Se añade un objeto de texto centrado con el titulo
	textObjects.push_back(new UIText(rend, Vector2(190, 40), Vector2(2.f, 2.f), 0.0f, "CREDITS"));
	textObjects.push_back(new UIText(rend, Vector2(250, 150), Vector2(1.f, 1.f), 0.0f, "Sebastian Mora"));
	textObjects.push_back(new UIText(rend, Vector2(250, 190), Vector2(1.f, 1.f), 0.0f, "Lucia Puga"));
	textObjects.push_back(new UIText(rend, Vector2(165, 470), Vector2(1.f, 1.f), 0.0f, "PRESS R TO RETURN"));

}

void CreditsScene::Update(float dt) {

	Scene::Update(dt);

	if (input->GetKey(SDLK_r, HOLD)) {

		targetScene = "MainMenu";
		isFinished = true;

	}

}

void CreditsScene::Render(SDL_Renderer* rend) {
	Scene::Render(rend);

	for (int i = 0; i < textObjects.size(); i++) {
		textObjects[i]->Render(rend);
	}



}

void CreditsScene::Exit() {

	for (int i = 0; i < textObjects.size(); i++) {
		delete(textObjects[i]);
	}

	textObjects.clear();

}