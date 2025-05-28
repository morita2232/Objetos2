#pragma once
#include <SDL.h>
#include <map>
#include "Utils.h"

// Estados posibles de una tecla
enum KeyState { EMPTY, DOWN, UP, HOLD };

// Macro para acceder r�pidamente al InputManager global
#define IM InputManager::Instance()

class InputManager {

private:

	// Mapa que asocia cada tecla con su estado actual
	std::map<Sint32, KeyState> keys;

	// Posici�n actual del rat�n
	Vector2Int mousePos;

	// Estado del bot�n izquierdo del rat�n
	bool leftClick = false;

	// Indica si se ha solicitado cerrar el juego
	bool quitGame = false;

public:

	// Devuelve la instancia �nica del InputManager
	static InputManager& Instance() {
		static InputManager manager;
		return manager;
	}

	// Getters simples
	Vector2Int GetMousePos() { return mousePos; }
	bool GetQuit() { return quitGame; }
	bool GetLeftClick() { return leftClick; }

	// Devuelve si una tecla est� en el estado indicado
	bool GetKey(Sint32 key, KeyState state) {
		auto it = keys.find(key);
		if (it != keys.end()) {
			return it->second == state;
		}
		return false;
	}

	// Procesa los eventos de SDL
	void Listen();
};