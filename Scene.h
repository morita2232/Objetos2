#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include "Utils.h"
#include "GameObject.h"
#include "UIText.h"
#include "InputManager.h"

class Scene {
protected:

	//Lista de objetos en escena
	std::vector <GameObject*> objects;

	//Lista de objetos de texto
	std::vector <UIText*> textObjects;

	//Nombre de la escena
	std::string targetScene;

	InputManager* input;

	//Indica si la escena ha acabdo
	bool isFinished = true;

public:

	virtual void Start(SDL_Renderer* rend, InputManager* inputManager) {

		isFinished = false;
		input = inputManager;

	}

	virtual void Update(float dt) {
		//Actualiza los objetos en escena
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Update(dt);
		}

	}

	virtual void Render(SDL_Renderer* rend) {
		//Renderiza los objetos
		for (int i = 0; i < objects.size(); i++) {		
			objects[i]->Render(rend);
		}

	}

	virtual void Exit() = 0;

	bool IsFinished() { return isFinished; }
	std::string GetTargetScene() { return targetScene; }

};
