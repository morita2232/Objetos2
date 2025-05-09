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
	SDL_Window* window;
	SDL_Renderer* renderer;

	GameEngine(int windowWidth, int windowHeight);

	void Updater();
	void Finish();

	void InitSDL();
	void InitWindowAndRenderer(int windowWidth, int windowHeight);

};
