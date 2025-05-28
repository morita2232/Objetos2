#include <fstream>
#include "ScoreManager.h"

std::vector<int> ScoreManager::scores;

//GUARDADO: almacena los 10 mejores scores en archivo binario
void ScoreManager::SaveToFile() {
	std::ofstream out("scores.dat", std::ios::binary | std::ios::trunc);
	if (!out.is_open()) return;

	int size = static_cast<int>(scores.size());
	out.write(reinterpret_cast<char*>(&size), sizeof(int));

	for (int score : scores) {
		out.write(reinterpret_cast<char*>(&score), sizeof(int));
	}

	out.close();
}

//CARGA: recupera las puntuaciones guardadas desde el archivo binario
void ScoreManager::LoadFromFile() {
	std::ifstream in("scores.dat", std::ios::binary);
	if (!in.is_open()) {
		SaveToFile(); //Si el archivo no existe, lo creamos vacío
		return;
	}

	int size = 0;
	in.read(reinterpret_cast<char*>(&size), sizeof(int));
	if (size <= 0 || size > 100) {
		in.close();
		scores.clear();
		SaveToFile();
		return;
	}

	scores.clear();
	for (int i = 0; i < size; ++i) {
		int s;
		in.read(reinterpret_cast<char*>(&s), sizeof(int));
		scores.push_back(s);
	}

	in.close();
}

//Añade una puntuación, la ordena y guarda el resultado en disco
void ScoreManager::AddScore(int score) {
	LoadFromFile();

	scores.push_back(score);
	std::sort(scores.begin(), scores.end(), std::greater<int>());

	if (scores.size() > 10) {
		scores.resize(10);
	}

	SaveToFile();
}

//Devuelve la lista de puntuaciones ordenadas
const std::vector<int>& ScoreManager::GetScores() {
	LoadFromFile();
	return scores;
}