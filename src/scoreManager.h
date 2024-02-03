#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <vector>
#include <string>
#include <algorithm>

class ScoreManager
{
    public:
        ScoreManager(const std::string& filename)
        : m_filename{filename} {}

    void getScoresFromFile();
    void saveScoresToFile() const;
    void UpdateHighScores(const std::string& playerName, int playerScore);
    
    private:
        struct Score {
            std::string m_playerName{};
            int m_score{};

            Score(const std::string& name, int score) : m_playerName{name}, m_score{score} {}
        };

        std::vector<Score> m_scores{};
        const std::string m_filename{};
        const int m_limit{};
};

#endif