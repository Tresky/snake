#include <ctime>

#include "snake_game.hpp"
#include "video.hpp"

#include "snake.hpp"

SnakeGame* snake_game = nullptr;

SnakeGame::SnakeGame() {}

SnakeGame::~SnakeGame()
{
  delete cl;
  delete snake;
}

bool SnakeGame::InitSingleton()
{
  srand((int)time(NULL));

  playing = false;
  cl = new sf::Clock;

  snake = new Snake();
  speed = 150;

  if (!font.loadFromFile("data/font.ttf"))
    return false;
  text.setFont(font);
  text.setColor(sf::Color::White);

  if (!pop.loadFromFile("data/pop.flac"))
    return false;
  if (!game_over.loadFromFile("data/game_over.wav"))
    return false;

  if (!music.openFromFile("data/music.ogg"))
    return false;
  music.play();
  music.setLoop(true);

  GenerateFood();
  return true;
}

void SnakeGame::Reset()
{
  delete snake;
  delete cl;
  playing = true;
  cl = new sf::Clock();
  snake = new Snake();
  speed = 150;

  GenerateFood();

  music.play();
}

void SnakeGame::GameOver()
{
  playing = false;
  music.stop();
  sound.setBuffer(game_over);
  sound.play();
}

void SnakeGame::GenerateFood()
{
  int x = rand() % (video_manager->GetWidth() / video_manager->GetGridSize());
  int y = rand() % (video_manager->GetHeight() / video_manager->GetGridSize());
  food = sf::Vector2i(x, y);
}

void SnakeGame::PollEvents()
{
  sf::RenderWindow* window = video_manager->GetWindowHandle();

  sf::Event evt;
  while (window->pollEvent(evt))
  {
    if (evt.type == sf::Event::Closed)
      video_manager->Close();

    if (evt.type == sf::Event::KeyPressed)
    {
      if (playing)
      {
        Direction curr = snake->GetDirection(), next = curr;

        if (evt.key.code == sf::Keyboard::W)
          next = Direction::UP;
        else if (evt.key.code == sf::Keyboard::D)
          next = Direction::RIGHT;
        else if (evt.key.code == sf::Keyboard::S)
          next = Direction::DOWN;
        else if (evt.key.code == sf::Keyboard::A)
          next = Direction::LEFT;

        bool opposites = false;
        if ((curr == UP && next == DOWN) || (curr == DOWN && next == UP) ||
            (curr == LEFT && next == RIGHT) || (curr == RIGHT && next == LEFT))
          opposites = true;

        if (next != curr && (( opposites && snake->GetLength() == 1 ) || !opposites))
        {
          snake->SetDirection(next);
          snake->Update();
          cl->restart();
        }
      }
      else if (evt.key.code == sf::Keyboard::Space)
      {
        Reset();
      }
    }
  }
}

void SnakeGame::Update()
{
  if (!playing)
    return;

  int elapsed = cl->getElapsedTime().asMilliseconds();

  if (elapsed > speed)
  {
    if (!snake->Update())
      GameOver();

    cl->restart();

    if (snake->GetHeadPosition() == food)
    {
      sound.setBuffer(pop);
      sound.play();
      snake->Grow();
      GenerateFood();
      if (snake->GetLength() % 2 == 0)
        speed = (speed - 10 > 30) ? speed - 10 : 30;
      PRINT_DEBUG << "SPEED " << speed << endl;
    }
  }
}

void SnakeGame::Draw()
{
  snake->Draw();

  int grid_size = video_manager->GetGridSize();

  // Draw the food piece
  sf::RectangleShape f(sf::Vector2f(grid_size - 2.f, grid_size - 2.f));
  f.setFillColor(sf::Color::White);
  f.setPosition(1.f + food.x * grid_size, 1.f + food.y * grid_size);
  video_manager->Draw(&f);

  text.setString("Length: " + std::to_string(snake->GetLength()));
  text.setCharacterSize(18);
  text.setPosition(video_manager->GetWidth() - text.getLocalBounds().width - 20.f, 10.f);
  video_manager->Draw(&text);

  if (!playing)
  {
    text.setString("Snake");
    text.setCharacterSize(72);
    text.setPosition(video_manager->GetWidth() / 2 - text.getLocalBounds().width / 2, video_manager->GetHeight() / 3 - text.getLocalBounds().height / 2);
    video_manager->Draw(&text);
    text.setString("Press \'Space\' to start");
    text.setCharacterSize(24);
    text.setPosition(video_manager->GetWidth() / 2 - text.getLocalBounds().width / 2, video_manager->GetHeight() / 2 - text.getLocalBounds().height / 2);
    video_manager->Draw(&text);
  }
}
