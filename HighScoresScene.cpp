#include "HighScoresScene.h"
#include "ScoreManager.h"

//START: se ejecuta al entrar en la escena de puntuaciones
void HighScoresScene::Start(SDL_Renderer* rend, InputManager* inputManager) {

	Scene::Start(rend, inputManager);

	//Se añade el texto
	textObjects.push_back(new UIText(rend, Vector2(165, 40), Vector2(2.f, 2.f), 0.0f, "HIGH SCORES"));
	textObjects.push_back(new UIText(rend, Vector2(165, 470), Vector2(1.f, 1.f), 0.0f, "PRESS R TO RETURN"));

	//Obtenemos la lista de puntuaciones
	auto scores = ScoreManager::GetScores();

	//Posición vertical inicial para imprimir las puntuaciones
	float y = 100;

	//Por cada puntuación, se crea un texto
	for (int i = 0; i < scores.size(); ++i) {
		std::string line = std::to_string(i + 1) + ". " + std::to_string(scores[i]);
		textObjects.push_back(new UIText(rend, Vector2(180, y), Vector2(1.f, 1.f), 0.0f, line));
		y += 30;
	}
}

//UPDATE: detecta entrada del jugador (tecla R para volver al menú)
void HighScoresScene::Update(float dt) {
	Scene::Update(dt);
	if (input->GetKey(SDLK_r, HOLD)) {
		targetScene = "MainMenu";
		isFinished = true;
	}
}

//RENDER: dibuja todos los textos de la escena en pantalla
void HighScoresScene::Render(SDL_Renderer* rend) {
	Scene::Render(rend);
	for (int i = 0; i < textObjects.size(); i++) {
		textObjects[i]->Render(rend);
	}
}

//EXIT: se ejecuta al salir de la escena
void HighScoresScene::Exit() {
	//Liberamos la memoria de todos los objetos de texto
	for (int i = 0; i < textObjects.size(); i++) {
		delete(textObjects[i]);
	}
	//Vaciamos el vector de textos
	textObjects.clear();
}
