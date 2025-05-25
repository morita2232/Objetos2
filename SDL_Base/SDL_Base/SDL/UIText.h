#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Utils.h"

class UIText {

private:

	//Propiedades ->

	//Posicion del texto en pantalla
	Vector2 position;

	//Escala del texto
	Vector2 scale;

	//Rotacion del texto
	float zRotation;

	//Tetxura del texto
	SDL_Texture* texture;

	//Ancho de la textura
	int width;

	//Alto de la textura
	int height;

	//Tamaño del texto
	int fontSize;

	//Ruta al archivo de fuente
	std::string fontPath;

	//Texto a mostrar
	std::string text;

	//Genera/regenera la textura del texto
	void GenerateTexture(SDL_Renderer* rend);


public:

	//Metodos ->
	
	//Constructor
	UIText(SDL_Renderer* rend, Vector2 pos, Vector2 initScale, float initZRotation, std::string textToPrint, int initFontSize = 28);

	//EL UPDATE SIRVE PARA METER ANIMACIONES AL TEXTO
	void Update(float dt);

	void Render(SDL_Renderer* rend);

	void SetText(std::string newText, SDL_Renderer* rend);

	std::string GetText() const { return text; }

	SDL_Rect GetCollider() const;


};