#include "GameEngine.h"
#include "GameObject.h"
#include "InputManager.h"


GameEngine::GameEngine(int windowWidth, int windowHeight) {
	InitSDL();
	InitWindowAndRenderer(windowWidth, windowHeight);
}

void GameEngine::Updater() {

	//Tiempo entre frames
	float dt = NULL;	

	//Fotogramas por segundo
	int FPS = FPSNUM;

	//Tiempo por fotogramas
	const float frameTime = FTNUM/(float)FPS;

	//Mapa de escenas
	std::map<std::string, Scene*> gameScene;

	gameScene["MainMenu"] = new MenuScene();
	gameScene["HighScores"] = new HighScoresScene();
	gameScene["GamePlay"] = new GamePlayScene();

	//Escena con la que se empieza
	Scene* currentScene = gameScene["MainMenu"];

	//Comienzo de la escena
	currentScene->Start(renderer, &IM);

	//Calculacion del tiempo inicial para medir frames
	float lastTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();

	//Bucle del juego
	while (!IM.GetQuit()) {
		IM.Listen();

		//Calculo del delta time
		float currentTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();
		float dt = currentTime - lastTime;
		lastTime = currentTime;

		//Se actualiza la escena actual
		currentScene->Update(dt);

		//Creacion de la mantalla con su color
		SDL_SetRenderDrawColor(renderer, 76, 0, 153, 1);
		SDL_RenderClear(renderer);

		//Renderizado de la escena
		currentScene->Render(renderer);

		//Se enseña el resultado por pantalla
		SDL_RenderPresent(renderer);

		//Cambio de escena si la actual ha acabado
		if (currentScene->IsFinished()) {
			currentScene->Exit();
			currentScene = gameScene[currentScene->GetTargetScene()];
			currentScene->Start(renderer, &IM);
		}
	}		 

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