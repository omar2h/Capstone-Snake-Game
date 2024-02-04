#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <atomic>
#include <condition_variable>

class Controller {
 public:
  void HandleInput(bool &running, std::atomic<bool> &paused, std::condition_variable &cond, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif