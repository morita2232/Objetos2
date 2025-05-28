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

	// Objetos del juego
	std::vector<GameObject*> objects;

	// Textos en pantalla
	std::vector<UIText*> textObjects;

	// Nombre de la siguiente escena
	std::string targetScene;

	// Input del jugador
	InputManager* input;

	// Marca si la escena ha terminado
	bool isFinished = true;

public:

	// Inicializa escena
	virtual void Start(SDL_Renderer* rend, InputManager* inputManager) {
		isFinished = false;
		input = inputManager;
	}

	// Actualiza objetos
	virtual void Update(float dt) {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Update(dt);
		}
	}

	// Renderiza objetos
	virtual void Render(SDL_Renderer* rend) {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Render(rend);
		}
	}

	// Limpieza obligatoria al salir
	virtual void Exit() = 0;

	// Accesores
	bool IsFinished() { return isFinished; }
	std::string GetTargetScene() { return targetScene; }
};
