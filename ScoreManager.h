#pragma once
#include <vector>
#include <algorithm>

class ScoreManager {
public:
	static void AddScore(int score);
	static const std::vector<int>& GetScores();

	//Carga el archivo de puntuaciones
	static void LoadFromFile();
	//Guarda las puntuaciones
	static void SaveToFile();

private:
	static std::vector<int> scores;
};