#pragma once
#include <SDL.h>
#include <map>
#include "Utils.h"

//Estados de las teclas
enum KeyState { EMPTY, DOWN, UP, HOLD };

//Macro para instanciar facilmente un InputManager
#define IM InputManager::Instance()

class InputManager {

private:

	//Mapa de teclas que guarda su estado 
	std::map<Sint32, KeyState> keys;

	//Posicion del mouse en pantalla
	Vector2Int mousePos;

	//Estado del boton izquierdo del raton
	bool leftClick = false;

	//Indicacion de si se tiene que acabar el juego
	bool quitGame = false;


public:

	//Devuelve una unica instancia global del InputManager
	static InputManager& Instance() {

		static InputManager manager;

		return manager;

	}

	Vector2Int GetMousePos() { return mousePos; }

	bool GetQuit() { return quitGame; }

	bool GetLeftClick() { return leftClick; }

	bool GetKey(Sint32 key, KeyState state) {
		auto it = keys.find(key);
		if (it != keys.end()) {
			return it->second == state;
		}
		return false;
	}


	void Listen();

};
