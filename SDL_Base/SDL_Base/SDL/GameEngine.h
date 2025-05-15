#pragma once
#include <SDL.h>
#include <iostream>
#include <map>
#include "Scene.h"
#include "MenuScene.h"
#include "HighScoresScene.h"
#include "GamePlayScene.h"

class GameEngine {

public:

	//Puntero a la ventana
	SDL_Window* window;

	//Puntero al renderer
	SDL_Renderer* renderer;

	GameEngine(int windowWidth, int windowHeight);

	void Updater();
	void Finish();

	void InitSDL();
	void InitWindowAndRenderer(int windowWidth, int windowHeight);

};
