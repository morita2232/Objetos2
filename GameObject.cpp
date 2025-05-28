#include "GameObject.h"

//CONSTRUCTOR: inicializa un objeto con coordenadas de textura, tamaño, y carga el sprite desde archivo
GameObject::GameObject(SDL_Renderer* renderer, Vector2Int _textureCoor, Vector2Int _sizeToClamp) {

	// Posición inicial del objeto en pantalla
	position = Vector2(50.f, 50.f);

	// Ángulo de rotación (en grados)
	zRotation = 0.f;

	// Escala por defecto (sin zoom)
	scale = Vector2(1.f, 1.f);

	// Coordenadas dentro del spritesheet (posición del sprite)
	textureCoor = _textureCoor;

	// Tamaño del sprite a recortar dentro del spritesheet
	sizeToClamp = _sizeToClamp;

	// Carga del spritesheet desde archivo
	SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");

	// Comprobación de error en la carga de la imagen
	if (surf == nullptr) {
		std::cout << "Error al inicializar la surface: " << SDL_GetError();
	}

	// Creación de la textura desde la superficie cargada
	texture = SDL_CreateTextureFromSurface(renderer, surf);

	// Comprobación de error en la creación de la textura
	if (texture == nullptr) {
		std::cout << "Error al inicializar la texture: " << SDL_GetError();
	}

	// Liberación de la superficie, ya no es necesaria tras crear la textura
	SDL_FreeSurface(surf);
}

//DESTRUCTOR: libera la textura para evitar fugas de memoria
GameObject::~GameObject() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

//RENDER: dibuja el sprite del objeto en pantalla con sus parámetros actuales
void GameObject::Render(SDL_Renderer* renderer) {
	// Define la porción del spritesheet que se va a usar (sprite concreto)
	SDL_Rect source{ textureCoor.x, textureCoor.y, sizeToClamp.x, sizeToClamp.y };

	// Área destino en pantalla (posición y tamaño final del sprite)
	destination = {
		(int)(position.x),
		(int)(position.y),
		(int)(source.w * scale.x),
		(int)(source.h * scale.y)
	};

	// Renderiza el sprite con rotación y sin efecto espejo
	SDL_RenderCopyEx(renderer, texture, &source, &destination, zRotation, NULL, SDL_FLIP_NONE);
}

//COLLIDER: define manualmente el área de colisión del objeto (actualmente no usada directamente)
void GameObject::Collider() {

	// Área de colisión calculada de forma simple (ajustable según necesidad)
	destination = {
		(int)(position.x / 2),
		(int)(position.y / 2),
		(int)(position.x + 5),
		(int)(position.y + 10)
	};
}