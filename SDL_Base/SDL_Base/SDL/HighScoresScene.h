#pragma once
#include "Scene.h"

class HighScoresScene : public Scene {

public:

	void Start(SDL_Renderer* rend) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* rend) override;
	void Exit() override;

};