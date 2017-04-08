#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "../utils/singleton.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SnakeGame;
extern SnakeGame *snake_game;

class Snake;
namespace sf { class Clock; }

class SnakeGame : public utils::Singleton<SnakeGame>
{
  friend class utils::Singleton<SnakeGame>;

public:
  ~SnakeGame();

  bool InitSingleton();

  void Reset();

  void GameOver();

  void GenerateFood();

  void PollEvents();

  void Update();

  void Draw();

private:
  SnakeGame();

  bool playing;
  sf::Clock* cl;

  sf::Vector2i food;

  Snake* snake;
  int speed;

  sf::Text text;
  sf::Font font;
  sf::Music music;
  sf::Sound sound;
  sf::SoundBuffer pop, game_over;
};

#endif // SNAKE_GAME_H
