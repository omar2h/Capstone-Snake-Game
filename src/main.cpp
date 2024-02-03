#include <iostream>
#include <fstream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "player.h"
#include "scoreManager.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::string playerName;
  std::cout << "Enter your name: ";
  std::getline(std::cin, playerName);

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  Player player{playerName};
  ScoreManager scoreManager{"high_scores.txt"};

  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  scoreManager.getScoresFromFile();
  scoreManager.saveScoresToFile(player.name(), game.GetScore());

  return 0;
}