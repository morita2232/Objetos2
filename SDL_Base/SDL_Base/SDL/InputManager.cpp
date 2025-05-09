#include "InputManager.h"
#include <iostream>

void InputManager::Listen() {

	for (std::map<Sint32, KeyState>::iterator it = keys.begin(); it != keys.end(); it++) {

		if (it->second == DOWN) {
			
			it->second = HOLD;

		}

		if (it->second == UP) {
			
			it->second = EMPTY;

		}

	}

	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {

		switch (e.type) {

		case SDL_QUIT:
			quitGame = true;
			break;

		case SDL_KEYDOWN:			
			if (keys[e.key.keysym.sym] != HOLD) {

			keys[e.key.keysym.sym] = DOWN;
			std::cout << "key pressed" << std::endl;
			
			}

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

}