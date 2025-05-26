#pragma once
#include "Scene.h"

class MenuScene : public Scene {

public:
	SDL_Renderer* renderer;

	void Start(SDL_Renderer* rend, InputManager* inputManager) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* rend) override;
	void Exit() override;

};

