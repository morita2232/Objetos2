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
    void Kill() { isAlive = false; }

    SDL_Rect GetCollider() const {
        return SDL_Rect{
            (int)(position.x),
            (int)(position.y),
            sizeToClamp.x,
            sizeToClamp.y
        };
    }

};

