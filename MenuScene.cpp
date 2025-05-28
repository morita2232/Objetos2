#include "MenuScene.h"

//START: se ejecuta al entrar en la escena del men� principal
void MenuScene::Start(SDL_Renderer* rend, InputManager* inputManager) {

	//Inicializa la escena base con renderer e input
	Scene::Start(rend, inputManager);

	//Guardamos el renderer para poder usarlo en eventos
	renderer = rend;

	//Textos
	textObjects.push_back(new UIText(rend, Vector2(175, 40), Vector2(2.f, 2.f), 0.0f, "ASTEROIDS"));
	
	textObjects.push_back(new UIText(rend, Vector2(100, 150), Vector2(1.f, 1.f), 0.0f, "1 - Play", 20));
	textObjects.push_back(new UIText(rend, Vector2(115, 185), Vector2(1.f, 1.f), 0.0f, "2 - Credits", 20));
	textObjects.push_back(new UIText(rend, Vector2(143, 220), Vector2(1.f, 1.f), 0.0f, "3 - High Scores", 20));
}

//UPDATE: se ejecuta cada frame, detecta hover, clics y teclas del men�
void MenuScene::Update(float dt) {

	Scene::Update(dt);

	//Obtenemos la posici�n del rat�n para usarla como punto de colisi�n
	SDL_Point mouse = { input->GetMousePos().x, input->GetMousePos().y };

	//Por cada opci�n de texto (excepto el t�tulo), comprobamos si el rat�n est� encima
	for (UIText* text : textObjects) {
		SDL_Rect collider = text->GetCollider();

		if (text->GetText() != "ASTEROIDS") {

			//Si el rat�n est� dentro del collider
			if (SDL_PointInRect(&mouse, &collider)) {

				//Si no tiene a�n ">> ", se lo a�adimos
				if (text->GetText().rfind(">> ", 0) != 0) {
					text->SetText(">> " + text->GetText(), renderer);
				}

				//Si hacemos clic sobre una opci�n, cambiamos de escena
				if (input->GetLeftClick() && text->GetText() == ">> 1 - Play") {
					targetScene = "GamePlay";
					isFinished = true;
				}
				if (input->GetLeftClick() && text->GetText() == ">> 2 - Credits") {
					targetScene = "Credits";
					isFinished = true;
				}
				if (input->GetLeftClick() && text->GetText() == ">> 3 - High Scores") {
					targetScene = "HighScores";
					isFinished = true;
				}
			}
			else {
				//Si el texto ten�a ">> " pero ya no est� seleccionado, se lo quitamos
				if (text->GetText().rfind(">> ", 0) == 0) {
					std::string cleanText = text->GetText().substr(3);
					text->SetText(cleanText, renderer);
				}
			}
		}
	}

	//ATAJOS POR TECLADO
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

//RENDER: dibuja todas las opciones del men�
void MenuScene::Render(SDL_Renderer* rend) {

	Scene::Render(rend);

	//Si por alg�n error no hay textos, se muestra un mensaje por defecto
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

//EXIT: se ejecuta al salir del men�, libera todos los textos
void MenuScene::Exit() {

	for (int i = 0; i < textObjects.size(); i++) {
		delete(textObjects[i]);
	}

	textObjects.clear();
}
