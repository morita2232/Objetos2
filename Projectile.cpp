#include "Projectile.h"
#include <cmath>

Projectile::Projectile(SDL_Renderer* renderer, Vector2 pos, float angleDegrees, float speed)
    : GameObject(renderer, Vector2Int(112, 48), Vector2Int(8, 8))
{
    //Posicion inicial desde donde se genera la bala
    position = pos;

    //Conversion del angulo a radianes para calcular el vector de direccion
    float radians = (angleDegrees - NINENTYDGS) * (M_PI / ONEEIGHTYDGS);
    
    //Vector de velocidad
    velocity = Vector2(cos(radians), sin(radians)) * speed;
}

//Aqui no utilice el sprite porque se me veia muy pequeño
void Projectile::Render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = (int)(position.x);
    rect.y = (int)(position.y);
    rect.w = PROJECTILEWANDH;
    rect.h = PROJECTILEWANDH;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}


void Projectile::Update(float dt) {
    
    //Movimiento constante
    position += velocity * dt;

    //Limites de pantalla
    const float SCREEN_WIDTH = SCREENW;
    const float SCREEN_HEIGHT = SCREENH;

    //Marca como muerta a la bala que se pase de los limites
    if (position.x < -SCREENLIMIT || position.x > SCREEN_WIDTH + SCREENLIMIT ||
        position.y < -SCREENLIMIT || position.y > SCREEN_HEIGHT + SCREENLIMIT) {
        isAlive = false;
    }

}
