#include "ScoreManager.h"

std::vector<int> ScoreManager::scores;

void ScoreManager::AddScore(int score) {
	scores.push_back(score);
	std::sort(scores.begin(), scores.end(), std::greater<int>());
	if (scores.size() > 10) {
		scores.resize(10);
	}
}

const std::vector<int>& ScoreManager::GetScores() {
	return scores;
}