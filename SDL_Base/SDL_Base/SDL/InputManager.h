#pragma once
#include <SDL.h>
#include <map>
#include "Utils.h"

enum KeyState { EMPTY, DOWN, UP, HOLD };

#define IM InputManager::Instance()

class InputManager {

private:


	std::map<Sint32, KeyState> keys;

	Vector2Int mousePos;
	bool leftClick = false;

	bool quitGame = false;


public:

	static InputManager& Instance() {

		static InputManager manager;

		return manager;

	}

	Vector2Int GetMousePos() { return mousePos; }

	bool GetQuit() { return quitGame; }

	bool GetLeftClick() { return leftClick; }

	bool GetKey(Sint32 key, KeyState state) { return keys[key] == state; }

	void Listen();

};
