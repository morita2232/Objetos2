#include "MenuScene.h"

void MenuScene::Start(SDL_Renderer* rend, InputManager* inputManager) {

	Scene::Start(rend, inputManager);

	//Se añade un objeto de texto centrado con el titulo
	textObjects.push_back(new UIText(rend, Vector2(175, 40), Vector2(2.f, 2.f), 0.0f, "ASTEROIDS"));
	textObjects.push_back(new UIText(rend, Vector2(100, 150), Vector2(1.f, 1.f), 0.0f, "1 - Play", 20));
	textObjects.push_back(new UIText(rend, Vector2(115, 185), Vector2(1.f, 1.f), 0.0f, "2 - Credits", 20));
	textObjects.push_back(new UIText(rend, Vector2(143, 220), Vector2(1.f, 1.f), 0.0f, "3 - High Scores", 20));
	textObjects.push_back(new UIText(rend, Vector2(143, 125), Vector2(1.f, 1.f), 0.0f, ".", 20));

}

void MenuScene::Update(float dt) {

	Scene::Update(dt);

	for (int i = 0; i < textObjects.size(); i++) {

		if(input->GetMousePos() == textObjects[i].)

	}

	if (input->GetMousePos().x >= 50 && input->GetMousePos().x <= 150 && input->GetMousePos().y >= 125 && input->GetMousePos().y <= 160 && input->GetLeftClick() == true) {
//		std::cout << "Pito" << std::endl;
		targetScene = "GamePlay";
		isFinished = true;
	}

	if (input->GetKey(SDLK_1, HOLD)) {

		targetScene = "GamePlay";
		isFinished = true;	

	}
		else if (input->GetKey(SDLK_2, HOLD)) {

			targetScene = "Credits";
			isFinished = true;

		}
		

	else if (input->GetKey(SDLK_3, HOLD)) {

		targetScene = "HighScores";
		isFinished = true;

	}
}

void MenuScene::Render(SDL_Renderer* rend) {

	Scene::Render(rend);

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

void MenuScene::Exit() {

	for (int i = 0; i < textObjects.size(); i++) {
		delete(textObjects[i]);
	}

	textObjects.clear();

}