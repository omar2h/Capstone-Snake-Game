#include <iostream>
#include <fstream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "player.h"

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

  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  std::ofstream highScoreFile("high_scores.txt", std::ios::app);
  if(highScoreFile.is_open()) {
    highScoreFile << player.name() << ", " << game.GetScore() << "\n";
    highScoreFile.close();
    std::cout << "Your score is saved!\n";
  } else {
    std::cout << "Unable to open file.\n";
  }
  return 0;
}