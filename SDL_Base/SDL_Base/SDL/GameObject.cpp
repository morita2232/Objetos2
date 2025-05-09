#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer) {

	position = Vector2(50.f, 50.f);
	zRotation = 0.f;
	scale = Vector2(1.f, 1.f);

	SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");

	if (surf == nullptr) {
		std::cout << "Error al inicializar la surface: " << SDL_GetError();
	}

	texture = SDL_CreateTextureFromSurface(renderer, surf);

	if (texture == nullptr) {
		std::cout << "Error al inicializar la texture: " << SDL_GetError();
	}

	SDL_FreeSurface(surf);

}

void GameObject::Update(float dt) {



}

void GameObject::Render(SDL_Renderer* renderer) {

	SDL_Rect source{ 0, 0, 30, 40 };
	
	SDL_Rect destination{ position.x, position.y, (source.w * scale.x), (source.h * scale.y) };

	SDL_RenderCopy(renderer, texture, &source, &destination);

}