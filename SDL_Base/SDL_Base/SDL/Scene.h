#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include "GameObject.h"
#include "UIText.h"

class Scene {
protected:

	std::vector <GameObject*> objects;
	std::vector <UIText*> textObjects;

	std::string targetScene;
	bool isFinished = true;

public:

	virtual void Start(SDL_Renderer* rend) {

		isFinished = false;

	}

	virtual void Update(float dt) {

		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Update(dt);
		}

	}

	virtual void Render(SDL_Renderer* rend) {

		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Render(rend);
		}

	}

	virtual void Exit() = 0;

	bool IsFinished() { return isFinished; }
	std::string GetTargetScene() { return targetScene; }

};
