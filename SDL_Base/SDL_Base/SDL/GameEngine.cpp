#include "GameEngine.h"
#include "GameObject.h"
#include "InputManager.h"


GameEngine::GameEngine(int windowWidth, int windowHeight) {
	InitSDL();
	InitWindowAndRenderer(windowWidth, windowHeight);
}

void GameEngine::Updater() {

	float dt = 0.0f;
	//float lastTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();

	const int FPS = 60;
	const float frameTime = 1.0f/(float)FPS;

	std::map<std::string, Scene*> gameScene;

	gameScene["MainMenu"] = new MenuScene();
	gameScene["HighScores"] = new HighScoresScene();
	gameScene["GamePlay"] = new GamePlayScene();

	Scene* currentScene = gameScene["GamePlay"];

	currentScene->Start(renderer);

	float lastTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();

	while (!IM.GetQuit()) {
		IM.Listen();

		float currentTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();
		float dt = currentTime - lastTime;
		lastTime = currentTime;

		currentScene->Update(dt);

		SDL_SetRenderDrawColor(renderer, 76, 0, 153, 1);
		SDL_RenderClear(renderer);
		currentScene->Render(renderer);
		SDL_RenderPresent(renderer);

		if (currentScene->IsFinished()) {
			currentScene->Exit();
			currentScene = gameScene[currentScene->GetTargetScene()];
			currentScene->Start(renderer);
		}
	}



		  /*
	while (!IM.GetQuit()) {
	
		IM.Listen();

		float currentTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();
		dt += currentTime - lastTime;

		if (dt > frameTime) {			

			currentScene->Update(dt);

			SDL_SetRenderDrawColor(renderer, 76, 0, 153, 1);
			SDL_RenderClear(renderer);

			currentScene->Render(renderer);

			SDL_RenderPresent(renderer);

			if (currentScene->IsFinished()) {

				currentScene->Exit();
				currentScene = gameScene[currentScene->GetTargetScene()];
				currentScene->Start(renderer);

			}

			dt -= frameTime;

		}
	}
		   */

}

void GameEngine::Finish() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

}

void GameEngine::InitSDL() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error al inicializar el SDL: " << SDL_GetError();
	}

	if (TTF_Init() < 0) {
		std::cout << "Error al inicializar el TTF: " << TTF_GetError();
	}

}

void GameEngine::InitWindowAndRenderer(int windowWidth, int windowHeight) {

	//WINDOW

	window = SDL_CreateWindow("My First Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		std::cout << "Error al inicializar window: " << SDL_GetError();
	}

	//RENDERER

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "Error al inicializar renderer: " << SDL_GetError();
	}

}