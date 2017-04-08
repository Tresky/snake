#include "snake.hpp"

#include "video.hpp"

Snake::Snake()
  : direction(RIGHT)
  , head_pos(0, 0)
{
  body.push_front(head_pos);
  // body.push_front(sf::Vector2i(1, 0));
  // body.push_front(sf::Vector2i(2, 0));
  // body.push_front(sf::Vector2i(3, 0));
  // body.push_front(sf::Vector2i(4, 0));
  // body.push_front(sf::Vector2i(5, 0));
  // body.push_front(sf::Vector2i(6, 0));
}

Snake::~Snake() {}

sf::Vector2i Snake::GetHeadPosition()
{
  return body.front();
}

Direction Snake::GetDirection()
{
  return direction;
}

void Snake::SetDirection(const Direction _dir)
{
  direction = _dir;
}

const int Snake::GetLength()
{
  return body.size();
}

void Snake::Grow()
{
  PRINT_DEBUG << "Growing from " << body.size() << " -> " << (body.size() + 1) << endl;
  body.push_back(body[body.size() - 1]);
}

bool Snake::Update()
{
  sf::Vector2i delta = body.front();
  if (direction == UP)
    delta.y -= 1;
  else if (direction == RIGHT)
    delta.x += 1;
  else if (direction == DOWN)
    delta.y += 1;
  else
    delta.x -= 1;

  sf::RenderWindow* window = video_manager->GetWindowHandle();
  sf::IntRect bounds(0, 0, window->getSize().x / video_manager->GetGridSize(), window->getSize().y / video_manager->GetGridSize());

  // Check to see if we are leaving the bounds of the window
  if (!bounds.contains(delta))
    return false;

  // Check to see if we are going to run into outselves
  // If so, return false so the game can end
  for (int k = 0; k < body.size(); ++k)
    if (body.at(k).x == delta.x && body.at(k).y == delta.y)
      return false;

  body.push_front(delta);
  body.pop_back();

  return true;
}

void Snake::Draw()
{
  int grid_size = video_manager->GetGridSize();
  for (int i = 0; i < body.size(); ++i)
  {
    sf::RectangleShape rect(sf::Vector2f(grid_size - 2.f, grid_size - 2.f));
    rect.setFillColor(sf::Color::White);
    rect.setPosition(1 + body[i].x * grid_size, 1 + body[i].y * grid_size);
    video_manager->Draw(&rect);
  }
}
