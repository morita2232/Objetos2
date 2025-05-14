/*#include "InputManager.h"
#include <iostream>

void InputManager::Listen() {

	std::map<Sint32, KeyState> updatedKeys = keys;



	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {

		switch (e.type) {

		case SDL_QUIT:
			quitGame = true;
			break;

		case SDL_KEYDOWN:			

			if (keys.find(e.key.keysym.sym) == keys.end()) {
				keys[e.key.keysym.sym] = DOWN;
			}
			else if (keys[e.key.keysym.sym] != HOLD) {
				keys[e.key.keysym.sym] = DOWN;
			}
			std::cout << "key pressed" << std::endl;
			break;

		case SDL_KEYUP:
			keys[e.key.keysym.sym] = UP;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT) {
				leftClick = true;
			}
			break;
		
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT) {
				leftClick = false;
			}
			break;

		default:
			break;



		}
	}
	for (auto it = updatedKeys.begin(); it != updatedKeys.end(); ++it) {
		Sint32 key = it->first;
		KeyState state = it->second;

		if (state == DOWN) {
			keys[key] = HOLD;
		}
		else if (state == UP) {
			keys[key] = EMPTY;
		}
	}

}*/

/*
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

	for (auto& pair : keys) {
		if (pair.second == DOWN) {
			pair.second = HOLD;
		}
		else if (pair.second == UP) {
			pair.second = EMPTY;
		}
	}

}*/
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

