#pragma once
#include "Scene.h"

class CreditsScene : public Scene {

public:

	void Start(SDL_Renderer* rend, InputManager* inputManager) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* rend) override;
	void Exit() override;

};
