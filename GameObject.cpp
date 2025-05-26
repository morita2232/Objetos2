#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer, Vector2Int _textureCoor, Vector2Int _sizeToClamp) {

	//Posicion inicial
	position = Vector2(50.f, 50.f);
	
	//Rotacion
	zRotation = 0.f;
	
	//Escala
	scale = Vector2(1.f, 1.f);

	//Coordenadas del spritesheet
	textureCoor = _textureCoor;

	//Tamaño del sprite a recortar
	sizeToClamp = _sizeToClamp;

	//Cargado de la imagen del spritesheet
	SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");

	//Mensaje de error
	if (surf == nullptr) {
		std::cout << "Error al inicializar la surface: " << SDL_GetError();
	}

	//Creacion de la textura
	texture = SDL_CreateTextureFromSurface(renderer, surf);

	//Mensaje de error
	if (texture == nullptr) {
		std::cout << "Error al inicializar la texture: " << SDL_GetError();
	}

	//Liberacion de superficie temporal
	SDL_FreeSurface(surf);

}

GameObject::~GameObject() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}


void GameObject::Render(SDL_Renderer* renderer) {
	//Definicion del area del sprite dentro del spritesheet
	SDL_Rect source{ textureCoor.x, textureCoor.y, sizeToClamp.x, sizeToClamp.y };		

	//Destino donse se dibujara en pantalla
	 destination = {
		(int)(position.x),
		(int)(position.y),
		(int)(source.w * scale.x),
		(int)(source.h * scale.y)
	};

	//Renderizacion
	SDL_RenderCopyEx(renderer, texture, &source, &destination, zRotation, NULL, SDL_FLIP_NONE);

}

void GameObject::Collider() {


	destination = {
		(int)(position.x / 2),
		(int)(position.y / 2),
		(int)(position.x + 5),
		(int)(position.y + 10)
	};

}