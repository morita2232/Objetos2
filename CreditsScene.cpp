#include "CreditsScene.h"

//START: se ejecuta al entrar en la escena de cr�ditos
void CreditsScene::Start(SDL_Renderer* rend, InputManager* inputManager) {

	//Inicializa la escena base con renderer e input
	Scene::Start(rend, inputManager);

	//Se crean y a�aden los textos que se mostrar�n en pantalla
	textObjects.push_back(new UIText(rend, Vector2(190, 40), Vector2(2.f, 2.f), 0.0f, "CREDITS"));

	textObjects.push_back(new UIText(rend, Vector2(250, 150), Vector2(1.f, 1.f), 0.0f, "Sebastian Mora"));
	textObjects.push_back(new UIText(rend, Vector2(250, 190), Vector2(1.f, 1.f), 0.0f, "Lucia Puga"));
	textObjects.push_back(new UIText(rend, Vector2(250, 230), Vector2(1.f, 1.f), 0.0f, "Sam Corchero"));

	textObjects.push_back(new UIText(rend, Vector2(165, 470), Vector2(1.f, 1.f), 0.0f, "PRESS R TO RETURN"));
}

//UPDATE: l�gica que se ejecuta cada frame
void CreditsScene::Update(float dt) {

	Scene::Update(dt);

	//Si el jugador pulsa la tecla R, volvemos al men� principal
	if (input->GetKey(SDLK_r, HOLD)) {
		targetScene = "MainMenu";
		isFinished = true;
	}
}

//RENDER: dibuja los textos en pantalla
void CreditsScene::Render(SDL_Renderer* rend) {
	Scene::Render(rend);

	//Dibuja todos los textos de la escena
	for (int i = 0; i < textObjects.size(); i++) {
		textObjects[i]->Render(rend);
	}
}

//EXIT: se ejecuta al salir de la escena
void CreditsScene::Exit() {

	//Libera todos los objetos de texto para evitar fugas de memoria
	for (int i = 0; i < textObjects.size(); i++) {
		delete(textObjects[i]);
	}

	//Vac�a la lista de textos
	textObjects.clear();
}