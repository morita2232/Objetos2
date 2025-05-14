#pragma once
#include "GameObject.h"

class Projectile : public GameObject {
private:
    Vector2 velocity;
    bool isAlive = true;

public:
    Projectile(SDL_Renderer* renderer, Vector2 pos, float angleDegrees, float speed);
    bool IsAlive() const { return isAlive; }
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;

};

