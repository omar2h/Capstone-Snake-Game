#include "scoreManager.h"
#include <fstream>
#include <iostream>

void ScoreManager::getScoresFromFile() {
    std::ifstream scoreFile(m_filename);
    if (scoreFile.is_open()) {
        std::string name;
        int score;
        while (scoreFile >> name >> score) {
            m_scores.emplace_back(name, score);
        }
        scoreFile.close();
    }
}

void ScoreManager::saveScoresToFile() const {
    std::ofstream scoreFile(m_filename, std::ios::trunc);
    
    if(scoreFile.is_open()) {
        for (const auto& score : m_scores) {
            scoreFile << score.m_playerName << " " << score.m_score << "\n";
        }
        scoreFile.close();
        std::cout << "Scores saved!\n";
    } else {
        std::cout << "Unable to open file.\n";
    }
}

void ScoreManager::UpdateHighScores(const std::string& playerName, int playerScore) {
    m_scores.emplace_back(playerName, playerScore);
    std::sort(m_scores.begin(), m_scores.end(), [](Score const& a, Score const& b){return a.m_score > b.m_score;});
}