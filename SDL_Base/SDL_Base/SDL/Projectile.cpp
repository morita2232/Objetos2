#include "Projectile.h"
#include <cmath>

Projectile::Projectile(SDL_Renderer* renderer, Vector2 pos, float angleDegrees, float speed)
    : GameObject(renderer, new Vector2Int(112, 48), new Vector2Int(8, 8))
{
    //Posicion inicial desde donde se genera la bala
    position = pos;

    //Conversion del angulo a radianes para calcular el vector de direccion
    float radians = (angleDegrees - 90.0f) * (M_PI / 180.0f);
    
    //Vector de velocidad
    velocity = Vector2(cos(radians), sin(radians)) * speed;
}

//Aqui no utilice el sprite porque se me veia muy peque�o
void Projectile::Render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = (int)(position.x);
    rect.y = (int)(position.y);
    rect.w = 6;
    rect.h = 6;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}


void Projectile::Update(float dt) {
    
    //Movimiento constante
    position += velocity * dt;

    //Limites de pantalla
    const float SCREEN_WIDTH = 800.0f;
    const float SCREEN_HEIGHT = 600.0f;

    //Marca como muerta a la bala que se pase de los limites
    if (position.x < -10 || position.x > SCREEN_WIDTH + 10 ||
        position.y < -10 || position.y > SCREEN_HEIGHT + 10) {
        isAlive = false;
    }

}
