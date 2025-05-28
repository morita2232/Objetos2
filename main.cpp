#include "GameEngine.h"

int SDL_main(int argc, char* argv[]) {

	//Se crea una instancia del juego en una ventana de 500 x 500
	GameEngine myEngine(500, 500);

	//Bucle del juego
	myEngine.Updater();

	//Se limpian recursos y se finaliza el SDL
	myEngine.Finish();

	return 0;
}