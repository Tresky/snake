#include "utils/globals.hpp"

#include "game/snake_game.hpp"
#include "game/video.hpp"

bool CreateSingletons()
{
  snake_game = SnakeGame::CreateSingleton();
  video_manager = VideoEngine::CreateSingleton();

  if (!video_manager->InitSingleton())
  {
    PRINT_ERROR << "Failed to initialize VideoEngine" << endl;
    return false;
  }

  if (!snake_game->InitSingleton())
  {
    PRINT_ERROR << "Failed to initialize SnakeGame" << endl;
    return false;
  }

  return true;
}

void DestroySingletons()
{
  PRINT_DEBUG << "Destroying Singletons" << endl;
  SnakeGame::DestroySingleton();
  VideoEngine::DestroySingleton();
}

int main()
{
  atexit(DestroySingletons);

  if (!CreateSingletons())
  {
    PRINT_ERROR << "Failed to initialize the singletons" << endl;
    exit(1);
  }

  sf::RenderWindow* window = video_manager->GetWindowHandle();

  // To be abstracted later...
  while (window->isOpen())
  {
    snake_game->PollEvents();

    snake_game->Update();

    video_manager->Clear();
    snake_game->Draw();
    video_manager->Display();
  }

  return 0;
}
