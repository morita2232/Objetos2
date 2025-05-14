#include "Projectile.h"
#include <cmath>

Projectile::Projectile(SDL_Renderer* renderer, Vector2 pos, float angleDegrees, float speed)
    : GameObject(renderer, new Vector2Int(112, 48), new Vector2Int(8, 8))
{
    position = pos;

    float radians = (angleDegrees - 90.0f) * (M_PI / 180.0f);
    velocity = Vector2(cos(radians), sin(radians)) * speed;
}

void Projectile::Render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = 6;
    rect.h = 6;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}


void Projectile::Update(float dt) {
    
    position += velocity * dt;

    const float SCREEN_WIDTH = 800.0f;
    const float SCREEN_HEIGHT = 600.0f;

    if (position.x < -10 || position.x > SCREEN_WIDTH + 10 ||
        position.y < -10 || position.y > SCREEN_HEIGHT + 10) {
        isAlive = false;
    }

}
