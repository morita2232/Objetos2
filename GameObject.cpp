#include "GameObject.h"

//CONSTRUCTOR: inicializa un objeto con coordenadas de textura, tama�o, y carga el sprite desde archivo
GameObject::GameObject(SDL_Renderer* renderer, Vector2Int _textureCoor, Vector2Int _sizeToClamp) {

	// Posici�n inicial del objeto en pantalla
	position = Vector2(50.f, 50.f);

	// �ngulo de rotaci�n (en grados)
	zRotation = 0.f;

	// Escala por defecto (sin zoom)
	scale = Vector2(1.f, 1.f);

	// Coordenadas dentro del spritesheet (posici�n del sprite)
	textureCoor = _textureCoor;

	// Tama�o del sprite a recortar dentro del spritesheet
	sizeToClamp = _sizeToClamp;

	// Carga del spritesheet desde archivo
	SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");

	// Comprobaci�n de error en la carga de la imagen
	if (surf == nullptr) {
		std::cout << "Error al inicializar la surface: " << SDL_GetError();
	}

	// Creaci�n de la textura desde la superficie cargada
	texture = SDL_CreateTextureFromSurface(renderer, surf);

	// Comprobaci�n de error en la creaci�n de la textura
	if (texture == nullptr) {
		std::cout << "Error al inicializar la texture: " << SDL_GetError();
	}

	// Liberaci�n de la superficie, ya no es necesaria tras crear la textura
	SDL_FreeSurface(surf);
}

//DESTRUCTOR: libera la textura para evitar fugas de memoria
GameObject::~GameObject() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

//RENDER: dibuja el sprite del objeto en pantalla con sus par�metros actuales
void GameObject::Render(SDL_Renderer* renderer) {
	// Define la porci�n del spritesheet que se va a usar (sprite concreto)
	SDL_Rect source{ textureCoor.x, textureCoor.y, sizeToClamp.x, sizeToClamp.y };

	// �rea destino en pantalla (posici�n y tama�o final del sprite)
	destination = {
		(int)(position.x),
		(int)(position.y),
		(int)(source.w * scale.x),
		(int)(source.h * scale.y)
	};

	// Renderiza el sprite con rotaci�n y sin efecto espejo
	SDL_RenderCopyEx(renderer, texture, &source, &destination, zRotation, NULL, SDL_FLIP_NONE);
}

//COLLIDER: define manualmente el �rea de colisi�n del objeto (actualmente no usada directamente)
void GameObject::Collider() {

	// �rea de colisi�n calculada de forma simple (ajustable seg�n necesidad)
	destination = {
		(int)(position.x / 2),
		(int)(position.y / 2),
		(int)(position.x + 5),
		(int)(position.y + 10)
	};
}