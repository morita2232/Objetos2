#include "Projectile.h"
#include <cmath>

//CONSTRUCTOR: inicializa la bala con posición, dirección y velocidad
Projectile::Projectile(SDL_Renderer* renderer, Vector2 pos, float angleDegrees, float speed)
    : GameObject(renderer, Vector2Int(112, 48), Vector2Int(PROJECTILE_SIZE, PROJECTILE_SIZE))
{
    // Posición inicial desde la que se genera la bala
    position = pos;

    // Conversión del ángulo de rotación de grados a radianes (ajustado para sprite)
    float radians = (angleDegrees - NINENTYDGS) * (M_PI / ONEEIGHTYDGS);

    // Cálculo de la velocidad como vector dirección * magnitud
    velocity = Vector2(cos(radians), sin(radians)) * speed;
}

//RENDER: dibuja un rectángulo blanco simple (en lugar de sprite, que era muy pequeño)
void Projectile::Render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = (int)(position.x);
    rect.y = (int)(position.y);
    rect.w = PROJECTILEWANDH;
    rect.h = PROJECTILEWANDH;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color blanco
    SDL_RenderFillRect(renderer, &rect);                  // Dibujo del proyectil
}

//UPDATE: mueve la bala y la marca como muerta si sale de los límites de pantalla
void Projectile::Update(float dt) {

    // Movimiento basado en velocidad y deltaTime
    position += velocity * dt;

    // Constantes de límites de pantalla
    const float SCREEN_WIDTH = SCREENW;
    const float SCREEN_HEIGHT = SCREENH;

    // Si la bala se sale de los márgenes visibles (con margen extra), se marca como muerta
    if (position.x < -SCREENLIMIT || position.x > SCREEN_WIDTH + SCREENLIMIT ||
        position.y < -SCREENLIMIT || position.y > SCREEN_HEIGHT + SCREENLIMIT) {
        isAlive = false;
    }
}
