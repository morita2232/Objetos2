#include "UIText.h"

//CONSTRUCTOR: inicializa todos los parámetros del texto y genera su textura
UIText::UIText(SDL_Renderer* rend, Vector2 pos, Vector2 initiScale, float initZRotation, std::string textToPrint, int initFontSize) {

	//Posicion en pantalla
	position = pos;

	//Escala del tamaño del texto
	scale = initiScale;

	//Rotacion en grados del texto
	zRotation = initZRotation;

	//Contenido del texto
	text = textToPrint;

	//Tamaño de la fuente
	fontSize = initFontSize;

	//Ruta al archivo de la fuente
	fontPath = "resources/PixelPowerline-9xOK.ttf";

	//Ancho y alto inicializados a 0
	width = NULL;
	height = NULL;

	//Generación de la textura inicial del texto
	GenerateTexture(rend);
}

//GENERADOR DE TEXTURA: crea la textura a partir del texto, fuente y color
void UIText::GenerateTexture(SDL_Renderer* rend) {

	//Carga de la fuente desde el archivo .ttf
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);

	//Mensaje de error si no carga la fuente
	if (font == nullptr) {
		std::cout << "Error al inicializar la font: " << TTF_GetError();
		return;
	}

	//Color blanco para el texto
	SDL_Color textColor{ 255, 255, 255, 255 };

	//Creación de la superficie con el texto renderizado
	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), textColor);

	//Mensaje de error si no se crea la superficie
	if (surf == nullptr) {
		std::cout << "Error al inicializar la surface: " << TTF_GetError();
		TTF_CloseFont(font);
		return;
	}

	//Creación de la textura final a partir de la superficie
	texture = SDL_CreateTextureFromSurface(rend, surf);

	//Mensaje de error si falla la textura
	if (texture == nullptr) {
		std::cout << "Error al inicializar la textura: " << SDL_GetError();
		TTF_CloseFont(font);
		return;
	}

	//Guarda el tamaño del texto renderizado para el collider y render
	width = surf->w;
	height = surf->h;

	//Liberación de recursos
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
}

//UPDATE: se puede usar para animaciones (actualmente vacío)
void UIText::Update(float dt) {
	//Aquí se pueden añadir animaciones futuras al texto
}

//RENDER: dibuja el texto si hay textura generada
void UIText::Render(SDL_Renderer* rend) {

	//Si no hay textura, no se renderiza nada
	if (texture == nullptr) return;

	//Calcula tamaño y posición final teniendo en cuenta la escala
	SDL_Rect dest;
	dest.w = width * scale.x;
	dest.h = height * scale.y;
	dest.x = position.x - (width / HALF);
	dest.y = position.y - (height / HALF);

	//Renderiza la textura en pantalla con rotación (si hay)
	SDL_RenderCopyEx(rend, texture, NULL, &dest, zRotation, NULL, SDL_FLIP_NONE);
}

//CAMBIO DE TEXTO: destruye la textura anterior y genera una nueva con el nuevo texto
void UIText::SetText(std::string newText, SDL_Renderer* rend) {

	//Borrado de la textura anterior para evitar fugas de memoria
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	//Actualiza el texto y genera nueva textura
	text = newText;
	GenerateTexture(rend);
}

//DEVOLUCIÓN DEL COLLIDER: devuelve un rectángulo útil para colisiones con el ratón
SDL_Rect UIText::GetCollider() const {

	SDL_Rect rect;

	rect.w = width * scale.x;
	rect.h = height * scale.y;
	rect.x = position.x - (rect.w / 2.f);
	rect.y = position.y - (rect.h / 2.f);

	return rect;
}
