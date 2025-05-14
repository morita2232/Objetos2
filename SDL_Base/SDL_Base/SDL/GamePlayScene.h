#pragma once
#include "Scene.h"
#include "Projectile.h"

class GamePlayScene : public Scene {
private:

	std::vector<Projectile*> projectiles;
	SDL_Renderer* renderer;
	float shootCooldown = 0.2f;
	float shootTimer = 0.0f;




public:

	void Start(SDL_Renderer* rend) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* rend) override;
	void Exit() override;

};