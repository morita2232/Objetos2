#pragma once
#include "GameObject.h"

class Projectile : public GameObject {
private:

    // Dirección y velocidad
    Vector2 velocity;

    // Estado de vida
    bool isAlive = true;

public:

    // Constructor
    Projectile(SDL_Renderer* renderer, Vector2 pos, float angleDegrees, float speed);

    // Getters y lógica de vida
    bool IsAlive() const { return isAlive; }
    void Kill() { isAlive = false; }

    // Actualiza posición
    void Update(float dt) override;

    // Dibuja el proyectil
    void Render(SDL_Renderer* renderer) override;

    // Área de colisión
    SDL_Rect GetCollider() const {
        return SDL_Rect{
            (int)(position.x),
            (int)(position.y),
            sizeToClamp.x,
            sizeToClamp.y
        };
    }
};