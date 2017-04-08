#ifndef SNAKE_H
#define SNAKE_H

#include "../utils/globals.hpp"

#include <deque>

enum Direction
{
  UP = 0,
  RIGHT,
  DOWN,
  LEFT
};

class Snake
{
public:
  Snake();

  ~Snake();

  sf::Vector2i GetHeadPosition();

  Direction GetDirection();

  void SetDirection(const Direction _dir);

  const int GetLength();

  void Grow();

  bool Update();

  void Draw();

private:
  std::deque<sf::Vector2i> body;
  Direction direction;
  sf::Vector2i head_pos;
};

#endif // SNAKE_H
