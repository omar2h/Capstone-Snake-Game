#include "game.h"
#include <iostream>
#include "SDL.h"
#include <chrono>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp{SDL_GetTicks()};
  Uint32 frame_start{};
  Uint32 frame_end{};
  Uint32 frame_duration{};
  int frame_count{0};
  bool running{true};
  std::atomic<bool> paused{false};
  std::atomic<bool> gameFinished{false};
  std::condition_variable cond{};
  std::mutex mutex{};
  std::atomic<int> elapsedTime{};

  std::thread timeThread([&]() {
    while (!gameFinished.load()) {
      {
        std::unique_lock<std::mutex> lock{mutex};
        cond.wait(lock, [&]{return !paused.load() || gameFinished.load();});
      }
      elapsedTime.store(elapsedTime.load()+1);
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });
  timeThread.detach();

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, paused, cond, snake);
    if (!paused.load()) {
        Update();
        renderer.Render(snake, food, m_special_food);
    }
    
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, elapsedTime);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
  gameFinished.store(true);
  cond.notify_one();
}

void Game::PlaceFood() {
  int x, y, random;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    random = random_food(engine)%10 + 1;
    m_special_food = random == 10 ? true : false;
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive()) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x());
  int new_y = static_cast<int>(snake.head_y());

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score+= m_special_food ? 5 : 1;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.SetSpeed(snake.speed()+0.02);
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size(); }
bool Game::special_food() const {return m_special_food;}