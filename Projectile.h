#pragma once
#include "GameObject.h"

class Projectile : public GameObject {
private:

    // Direcci�n y velocidad
    Vector2 velocity;

    // Estado de vida
    bool isAlive = true;

public:

    // Constructor
    Projectile(SDL_Renderer* renderer, Vector2 pos, float angleDegrees, float speed);

    // Getters y l�gica de vida
    bool IsAlive() const { return isAlive; }
    void Kill() { isAlive = false; }

    // Actualiza posici�n
    void Update(float dt) override;

    // Dibuja el proyectil
    void Render(SDL_Renderer* renderer) override;

    // �rea de colisi�n
    SDL_Rect GetCollider() const {
        return SDL_Rect{
            (int)(position.x),
            (int)(position.y),
            sizeToClamp.x,
            sizeToClamp.y
        };
    }
};