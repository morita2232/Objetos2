#include "HighScoresScene.h"
#include "ScoreManager.h"

void HighScoresScene::Start(SDL_Renderer* rend, InputManager* inputManager) {

	Scene::Start(rend, inputManager);

	//Se añade un objeto de texto centrado con el titulo
	textObjects.push_back(new UIText(rend, Vector2(165, 40), Vector2(2.f, 2.f), 0.0f, "HIGH SCORES"));
	textObjects.push_back(new UIText(rend, Vector2(165, 470), Vector2(1.f, 1.f), 0.0f, "PRESS R TO RETURN"));

	// Mostrar las puntuaciones actuales
	auto scores = ScoreManager::GetScores();
	float y = 100;
	for (int i = 0; i < scores.size(); ++i) {
		std::string line = std::to_string(i + 1) + ". " + std::to_string(scores[i]);
		textObjects.push_back(new UIText(rend, Vector2(180, y), Vector2(1.f, 1.f), 0.0f, line));
		y += 30;
	}
}

void HighScoresScene::Update(float dt) {

	Scene::Update(dt);

	if (input->GetKey(SDLK_r, HOLD)) {

		targetScene = "MainMenu";
		isFinished = true;
	}
}

void HighScoresScene::Render(SDL_Renderer* rend) {
	Scene::Render(rend);

	for (int i = 0; i < textObjects.size(); i++) {
		textObjects[i]->Render(rend);
	}
}

void HighScoresScene::Exit() {

	for (int i = 0; i < textObjects.size(); i++) {
		delete(textObjects[i]);
	}

	textObjects.clear();
}