#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : m_grid_width(grid_width),
        m_grid_height(grid_height),
        m_head_x(grid_width / 2),
        m_head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  int size() const;
  bool alive() const;
  float head_x() const;
  float head_y() const;
  std::vector<SDL_Point> body() const;
  Direction direction() const;
  void SetDirection(Direction direction);
  float speed() const;
  void SetSpeed(float speed);

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  int m_size{1};
  bool m_alive{true};
  float m_head_x{};
  float m_head_y{};
  std::vector<SDL_Point> m_body{};
  Direction m_direction{Direction::kUp};
  float m_speed{0.1f};
  bool m_growing{false};
  int m_grid_width{};
  int m_grid_height{};
};

#endif