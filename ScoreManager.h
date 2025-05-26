#pragma once
#include <vector>
#include <algorithm>

class ScoreManager {
public:
	static void AddScore(int score);
	static const std::vector<int>& GetScores();

private:
	static std::vector<int> scores;
};