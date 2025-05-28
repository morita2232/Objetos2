#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Utils.h"

// Mostrar texto en pantalla
class UIText {

private:

	// --- Propiedades del texto ---

	// Posición del texto en pantalla
	Vector2 position;

	// Escala aplicada al texto
	Vector2 scale;

	// Rotación en grados del texto
	float zRotation;

	// Textura generada a partir del texto
	SDL_Texture* texture;

	// Dimensiones de la textura
	int width;
	int height;

	// Tamaño de la fuente en puntos
	int fontSize;

	// Ruta al archivo de fuente .ttf
	std::string fontPath;

	// Texto que se va a mostrar
	std::string text;

	// Método privado que genera o regenera la textura del texto
	void GenerateTexture(SDL_Renderer* rend);

public:

	// --- Métodos públicos ---

	// Constructor
	UIText(SDL_Renderer* rend, Vector2 pos, Vector2 initScale, float initZRotation, std::string textToPrint, int initFontSize = 28);

	// Update
	void Update(float dt);

	// Renderiza el texto
	void Render(SDL_Renderer* rend);

	// Cambia el contenido del texto mostrado y regenera la textura
	void SetText(std::string newText, SDL_Renderer* rend);

	// Devuelve el contenido
	std::string GetText() const { return text; }

	// Devuelve el área de colisión
	SDL_Rect GetCollider() const;
};
