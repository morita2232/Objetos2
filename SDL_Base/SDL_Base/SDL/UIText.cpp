#include "UIText.h"

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

	//Ruta al archio de la fuente
	fontPath = "resources/PixelPowerline-9xOK.ttf";
	width = 0;
	height = 0;

	//Generacion de la textura
	GenerateTexture(rend);

}

void UIText::GenerateTexture(SDL_Renderer* rend) {

	//Abrir archivo font
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);

	//Mensaje de error
	if (font == nullptr) {
		std::cout << "Error al inicializar la font: " << TTF_GetError();
		return;
	}

	//Dandole color al texto
	SDL_Color textColor{ 255, 255, 255, 255 };

	//Creacion de la superficie del texto renderizado
	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), textColor);

	//Mensaje de error
	if (surf == nullptr) {
		std::cout << "Error al inicializar la surface: " << TTF_GetError();
		TTF_CloseFont(font);
		return;
	}

	//Creacion de la textura segun la superficie
	texture = SDL_CreateTextureFromSurface(rend, surf);

	//Mensaje de error
	if (texture == nullptr) {
		std::cout << "Error al inicializar la textura: " << SDL_GetError();
		TTF_CloseFont(font);
		return;
	}

	//Guarda el ancho y alto de la superficie para renderizar
	width = surf->w;
	height = surf->h;

	//Liberacion de recursos
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

}


//EL UPDATE SIRVE PARA METER ANIMACIONES AL TEXTO
void UIText::Update(float dt) {



}

void UIText::Render(SDL_Renderer* rend) {

	//Si no hay textura no se pùede renderizar
	if (texture == nullptr) {

		return;

	}

	//Calculacion del tamaño final teniendo en cuenta la escala
	SDL_Rect dest;

	dest.w = width * scale.x;
	dest.h = height * scale.y;
	dest.x = position.x - (width / 2.f);
	dest.y = position.y - (height / 2.f);

	//Renderizacion de la textura con rotacion (si hay) y sin flip
	SDL_RenderCopyEx(rend, texture, NULL, &dest, zRotation, NULL, SDL_FLIP_NONE);

}

void UIText::SetText(std::string newText, SDL_Renderer* rend) {

	//Si ya existe una textura previa, se elimina para evitar fugas de memoria
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	text = newText;

	//Se vuelve a generar la textura con el nuevo texto
	GenerateTexture(rend);

}