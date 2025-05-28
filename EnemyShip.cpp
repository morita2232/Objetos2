#include "EnemyShip.h"
#include <cmath>

//CONSTRUCTOR: inicializa la nave enemiga con su sprite, posici�n y velocidad aleatoria
EnemyShip::EnemyShip(SDL_Renderer* rend, Vector2 pos)
	: GameObject(rend, Vector2Int(195, 93), Vector2Int(ENEMYSHIP_SIZE_X, ENEMYSHIP_SIZE_Y)) { // Coordenadas y tama�o del sprite

	// Escala reducida para que el enemigo se vea m�s peque�o
	scale = Vector2(0.25f, 0.25f);

	// Posici�n inicial asignada desde par�metros
	position = pos;

	// Velocidad base
	speed = 150.0f;

	// Estado inicial: viva
	isAlive = true;

	// Direcci�n aleatoria (x e y entre -50 y 50)
	float randX = VELOCITY_RAND;
	float randY = VELOCITY_RAND;

	// Vector de velocidad final
	velocity = Vector2(randX, randY);
}

//UPDATE: mueve la nave enemiga en su direcci�n actual y aplica wraparound de pantalla
void EnemyShip::Update(float dt) {

	// Movimiento seg�n velocidad y deltaTime
	position += velocity * dt;

	// Si sale de la pantalla, reaparece por el lado opuesto (wrap-around)
	if (position.x < -sizeToClamp.x) position.x = SCREENW;
	if (position.x > SCREENW)        position.x = -sizeToClamp.x;
	if (position.y < -sizeToClamp.y) position.y = SCREENH;
	if (position.y > SCREENH)        position.y = -sizeToClamp.y;
}

//RENDER: dibuja la nave enemiga utilizando la l�gica heredada de GameObject
void EnemyShip::Render(SDL_Renderer* rend) {
	GameObject::Render(rend);
}

//GETCOLLIDER: devuelve el �rea de colisi�n de la nave enemiga
SDL_Rect EnemyShip::GetCollider() {
	return SDL_Rect{
		(int)position.x,
		(int)position.y,
		// Se ajusta el tama�o del collider seg�n la escala de renderizado
		(int)(sizeToClamp.x * scale.x),
		(int)(sizeToClamp.y * scale.y)
	};
}