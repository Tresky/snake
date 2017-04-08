#include "video.hpp"

VideoEngine *video_manager = nullptr;

VideoEngine::VideoEngine() {}

VideoEngine::~VideoEngine()
{
  delete window;
}

bool VideoEngine::InitSingleton()
{
  grid_size = 15;
  window = new sf::RenderWindow(sf::VideoMode(1035, 720), "Snake");
  return true;
}

sf::RenderWindow* VideoEngine::GetWindowHandle()
{
  return window;
}

int VideoEngine::GetWidth()
{
  return window->getSize().x;
}

int VideoEngine::GetHeight()
{
  return window->getSize().y;
}

int VideoEngine::GetGridSize()
{
  return grid_size;
}

void VideoEngine::Close()
{
  window->close();
}

void VideoEngine::Clear(sf::Color _color)
{
  window->clear(_color);
}

void VideoEngine::Clear()
{
  Clear(sf::Color::Black);
}

void VideoEngine::Draw(sf::Shape *_shape)
{
  window->draw(*_shape);
}

void VideoEngine::Draw(sf::Text *_text)
{
  window->draw(*_text);
}

void VideoEngine::Display()
{
  window->display();
}
