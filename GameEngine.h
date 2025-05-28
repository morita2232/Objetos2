#pragma once
#include <SDL.h>
#include <iostream>
#include <map>
#include "Scene.h"
#include "MenuScene.h"
#include "HighScoresScene.h"
#include "CreditsScene.h"
#include "GamePlayScene.h"

class GameEngine {

public:

	// Puntero a la ventana principal
	SDL_Window* window;

	// Puntero al renderer asociado a la ventana
	SDL_Renderer* renderer;

	// Constructor
	GameEngine(int windowWidth, int windowHeight);

	// Bucle principal
	void Updater();

	// Cierre del motor
	void Finish();

	// Inicializa SDL
	void InitSDL();

	// Crea la ventana y el renderer
	void InitWindowAndRenderer(int windowWidth, int windowHeight);
};

