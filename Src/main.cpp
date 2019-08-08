#include "Game.h"
#include "GameConstants.h"
#include "GameScreen.h"

int main(int argc, char* argv[])
{
	const int fps = 60;
	const int frameDelay = 1000 / GameConstants::fps;

	Uint32 frameStart;
	int frameTime;

	std::unique_ptr<Game> game = std::make_unique<Game>(std::string("Arcade Puzzle"), GameScreen::total_pixel_width, GameScreen::total_pixel_height);

	while (game->IsRunning())
	{
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	return 0;
}
