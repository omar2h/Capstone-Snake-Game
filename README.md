# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## New Features

1. Press p during game to pause
2. Enter your name at the start of the game
3. Save high scores in a file
4. Add new type of food which increase score by 5 that has 10% chance of appearing 
5. Add a timer to window tile

## Rubric points
### Loops, Functions, I/O

functions to read and write to file in main.cpp
```cpp
  scoreManager.getScoresFromFile();
  scoreManager.UpdateHighScores(player.name(), game.GetScore());
  scoreManager.saveScoresToFile();
```
read user input
```cpp
  std::string playerName;
  std::cout << "Enter your name: ";
  std::getline(std::cin, playerName);
```

pause if p is pressed in controller.cpp
```cpp
case SDLK_p:
  paused = !paused;
  break;
```
### Object Oriented Programming
- new classes are added: Player and ScoreManager
- Class constructors utilize member initialization lists.
```cpp
  Player(std::string const& name) : m_name{name} {}
```
```cpp
  ScoreManager(const std::string& filename)
  : m_filename{filename} {}
```
- Classes abstract implementation details from their interfaces.

### Memory Management
- The project makes use of references in function declarations.
```cpp
void ScoreManager::UpdateHighScores(const std::string& playerName, int playerScore) {
    m_scores.emplace_back(playerName, playerScore);
    std::sort(m_scores.begin(), m_scores.end(), [](Score const& a, Score const& b){return a.m_score > b.m_score;});
}
```
- The project follows the Rule of 5 in player class
```cpp
  Player(std::string const& name) : m_name{name} {}
  Player(const Player &source);
  Player &operator=(const Player &source); 
  Player(Player &&source); 
  Player &operator=(Player &&source);
  ~Player();
```
- The project uses move semantics to move data instead of copying it, where possible.
emplace_back
```cpp
void ScoreManager::UpdateHighScores(const std::string& playerName, int playerScore) {
    m_scores.emplace_back(playerName, playerScore);
    std::sort(m_scores.begin(), m_scores.end(), [](Score const& a, Score const& b){return a.m_score > b.m_score;});
}
```

### Concurrency
- The project uses multithreading in game.cpp
```cpp
std::thread timeThread([&]() {
  startTime = std::chrono::high_resolution_clock::now();
  while (!gameFinished.load()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      auto now = std::chrono::high_resolution_clock::now();
      elapsedTime = now - startTime;
  }
});
timeThread.detach();
```
```cpp
std::atomic<bool> gameFinished{false};
```










## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
