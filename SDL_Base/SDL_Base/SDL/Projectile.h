#pragma once
#include "GameObject.h"

class Projectile : public GameObject {
private:
    //Velocidad y direccion del proyectil
    Vector2 velocity;

    //Variable para saber si la bala esta viva o no
    bool isAlive = true;

public:
    Projectile(SDL_Renderer* renderer, Vector2 pos, float angleDegrees, float speed);
    bool IsAlive() const { return isAlive; }
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;

};

