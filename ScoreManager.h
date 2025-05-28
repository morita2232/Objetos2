#pragma once
#include <vector>
#include <algorithm>

class ScoreManager {
public:

	// Añade una nueva puntuación al ranking
	static void AddScore(int score);

	// Devuelve el listado de puntuaciones actuales
	static const std::vector<int>& GetScores();

	// Carga las puntuaciones desde archivo
	static void LoadFromFile();

	// Guarda las puntuaciones en archivo
	static void SaveToFile();

private:

	// Vector que almacena las puntuaciones
	static std::vector<int> scores;
};