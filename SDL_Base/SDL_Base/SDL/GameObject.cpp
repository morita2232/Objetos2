#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer, Vector2Int* _textureCoor, Vector2Int* _sizeToClamp) {

	position = Vector2(50.f, 50.f);
	zRotation = 0.f;
	scale = Vector2(1.f, 1.f);

	textureCoor = *_textureCoor;
	sizeToClamp = *_sizeToClamp;

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

void GameObject::Render(SDL_Renderer* renderer) {

	SDL_Rect source{ textureCoor.x, textureCoor.y, sizeToClamp.x, sizeToClamp.y };
	
	SDL_Rect destination{ position.x, position.y, (source.w * scale.x), (source.h * scale.y) };

	//SDL_RenderCopy(renderer, texture, &source, &destination);

	SDL_RenderCopyEx(renderer, texture, &source, &destination, zRotation, NULL, SDL_FLIP_NONE);

}