#ifndef VIDEO_HPP
#define VIDEO_HPP

#include "../utils/globals.hpp"
#include "../utils/singleton.hpp"

class VideoEngine;
extern VideoEngine* video_manager;

class VideoEngine : public utils::Singleton<VideoEngine>
{
  friend class utils::Singleton<VideoEngine>;

public:
  ~VideoEngine();

  bool InitSingleton();

  sf::RenderWindow* GetWindowHandle();

  int GetWidth();
  int GetHeight();

  int GetGridSize();

  void Close();

  void Clear(sf::Color _color);
  void Clear();

  void Draw(sf::Shape *_shape);
  void Draw(sf::Text *_text);

  void Display();

private:
  VideoEngine();

  int grid_size;

  sf::RenderWindow* window;
};

#endif // VIDEO_HPP
