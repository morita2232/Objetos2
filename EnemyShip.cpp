#include "EnemyShip.h"
#include <cmath>

EnemyShip::EnemyShip(SDL_Renderer* rend, Vector2 pos)
	: GameObject(rend, Vector2Int(0,0), Vector2Int(30, 40)) {

	position = pos;
	speed = 150.0f;
	isAlive = true;

	float randX = rand() % 100 - 50;
	float randY = rand() % 100 - 50;

	velocity = Vector2(randX, randY);

}

void EnemyShip::Update(float dt) {

	//Movimiento enemigo por delta time
	position += velocity * dt;

	//Screen wrap para que aparezca en el lado contrario al salirse del mapa
	if (position.x < -sizeToClamp.x) position.x = SCREENW;
	if (position.x > SCREENW) position.x = -sizeToClamp.x;
	if (position.y < -sizeToClamp.y) position.y = SCREENH;
	if (position.y > SCREENH) position.y = -sizeToClamp.y;
}

void EnemyShip::Render(SDL_Renderer* rend) {
	GameObject::Render(rend);
}

SDL_Rect EnemyShip::GetCollider() {
	return SDL_Rect{
		(int)position.x,
		(int)position.y,
		sizeToClamp.x,
		sizeToClamp.y
	};
}