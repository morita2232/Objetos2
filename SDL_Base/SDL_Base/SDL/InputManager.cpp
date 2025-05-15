#include "InputManager.h"
#include <iostream>

void InputManager::Listen() {
	
	//Obtiene la posicion del raton y la guarda en mousePos
	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	//Proceso de eventos SDL
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			//Se cierra la ventana y se acaba el juego
			quitGame = true;
			break;

		case SDL_KEYDOWN:
			//Se presiona una tecla
			keys[e.key.keysym.sym] = DOWN;
			break;

		case SDL_KEYUP:
			//Se deja de presionar una tecla
			keys[e.key.keysym.sym] = UP;
			break;

		case SDL_MOUSEBUTTONDOWN:
			//Se presiona un boton del raton, y se mira si fue el izquierdo
			if (e.button.button == SDL_BUTTON_LEFT)
				leftClick = true;
			break;

		case SDL_MOUSEBUTTONUP:
			//Se deja de presionar un boton del raton
			if (e.button.button == SDL_BUTTON_LEFT)
				leftClick = false;
			break;
		}
	}
	
	//Actualizacion de estados de las teclas en el mapa de keys
	for (std::map<SDL_Keycode, KeyState>::iterator it = keys.begin(); it != keys.end(); ++it) {
		if (it->second == DOWN)
			//Si estaba presionada se mantiene presionada
			it->second = HOLD;
		else if (it->second == UP)
			//Si se suelta, se limpia el estado
			it->second = EMPTY;
	}

}

