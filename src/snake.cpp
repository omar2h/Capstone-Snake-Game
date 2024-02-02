#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(m_head_x),
      static_cast<int>(
          m_head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(m_head_x),
      static_cast<int>(m_head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (m_direction) {
    case Direction::kUp:
      m_head_y -= m_speed;
      break;

    case Direction::kDown:
      m_head_y += m_speed;
      break;

    case Direction::kLeft:
      m_head_x -= m_speed;
      break;

    case Direction::kRight:
      m_head_x += m_speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  m_head_x = fmod(m_head_x + m_grid_width, m_grid_width);
  m_head_y = fmod(m_head_y + m_grid_height, m_grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  m_body.push_back(prev_head_cell);

  if (!m_growing) {
    // Remove the tail from the vector.
    m_body.erase(m_body.begin());
  } else {
    m_growing = false;
    m_size++;
  }

  // Check if the snake has died.
  for (auto const &item : m_body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      m_alive = false;
    }
  }
}

void Snake::GrowBody() { m_growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(m_head_x) && y == static_cast<int>(m_head_y)) {
    return true;
  }
  for (auto const &item : m_body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

bool Snake::alive() const
{
  return m_alive;
}

float Snake::head_x() const
{
  return m_head_x;
}

float Snake::head_y() const
{
  return m_head_y;
}

std::vector<SDL_Point> Snake::body() const
{
  return m_body;
}

int Snake::size() const
{
  return m_size;
}

Snake::Direction Snake::direction() const
{
  return m_direction;
}

void Snake::SetDirection(Direction direction)
{
  if(m_direction == direction)
    return;
  m_direction = direction;
}

float Snake::speed() const
{
  return m_speed;
}

void Snake::SetSpeed(float speed)
{
  if(m_speed == speed)
    return;
  m_speed = speed;
}