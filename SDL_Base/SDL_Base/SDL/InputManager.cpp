#include "InputManager.h"
#include <iostream>

void InputManager::Listen() {
	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	// Procesar eventos primero
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			quitGame = true;
			break;

		case SDL_KEYDOWN:
			keys[e.key.keysym.sym] = DOWN;
			break;

		case SDL_KEYUP:
			keys[e.key.keysym.sym] = UP;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
				leftClick = true;
			break;

		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT)
				leftClick = false;
			break;
		}
	}

	// ACTUALIZAR ESTADOS directamente en el mapa real
	for (auto it = keys.begin(); it != keys.end(); ++it) {
		if (it->second == DOWN)
			it->second = HOLD;
		else if (it->second == UP)
			it->second = EMPTY;
	}
}

