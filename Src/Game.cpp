#include "Game.h"
#include "Engine/Drawer.h"
#include "Engine/Logger.h"
#include "Factory.h"
#include "Blocks/BlockManager.h"
#include "CustomEvents.h"
#include "GameText.h"
#include <time.h>

Game::Game(std::string title, int width, int height)
{
	srand(time(NULL));

	initSDL(title, width, height);
	initEntt();

	gameManager.RestartGame(registry);
}

Game::~Game()
{
	Drawer::Clear();

	LOG("Drawer Cleaned");
	
	registry.reset();

	LOG("EnTT Cleaned");

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	TTF_Quit();
	SDL_Quit();

	LOG("SDL Cleaned");
}

void Game::initSDL(std::string title, int width, int height)
{
	isRunning = SDL_Init(SDL_INIT_EVERYTHING) == 0;
	if (isRunning)
	{
		LOG("SDL Subsystems Initialized");

		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		if (window)
		{
			LOG("Window Created");
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			Drawer::SetRenderer(renderer);
			LOG("Renderer Created");
		}

		//initialize font
		TTF_Init();

		//initialize our custom events
		InitEvent();
	}
}

void Game::initEntt()
{
	MakeBackground(registry);
	MakePlayArea(registry);
	MakeGameTexts(registry);
	MakeActiveBlock(registry);
}


void Game::HandleEvents()
{
	while (SDL_PollEvent(NULL))
	{
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
			}
			else if (event.key.keysym.sym == SDLK_RETURN)
			{
				gameManager.RestartGame(registry);
				score = 0;
				UpdateScoreText(registry, score);
				isAwaitingStart = false;
			}
			else if(!isAwaitingStart)
			{
				gameManager.ProcessInputDown(registry, event);
			}
		default:
			break;
		}

		if (event.type == TETRIS_EVENT_TYPE)
		{
			switch (event.user.code)
			{
			case GameOver:
				isAwaitingStart = true;
				break;
			case Cleared1:
				score += GameConstants::score_base_value;
				UpdateScoreText(registry, score);
				break;
			case Cleared2:
				score += GameConstants::score_base_value * 2 + GameConstants::score_2line_bonus;
				UpdateScoreText(registry, score);
				break;
			case Cleared3:
				score += GameConstants::score_base_value * 3 + GameConstants::score_3line_bonus;
				UpdateScoreText(registry, score);
				break;
			case Cleared4:
				score += GameConstants::score_base_value * 4 + GameConstants::score_4line_bonus;
				UpdateScoreText(registry, score);
				break;
			default:
				break;
			}
		}
	}
}

void Game::Update()
{
	if (!isAwaitingStart)
	{
		gameManager.Update(registry);
	}

	//update dynamic sprites
	auto fallView = registry.view<Transform, Sprite, FallingBlock>();
	for (auto e : fallView)
	{
		fallView.get<Sprite>(e).Update(fallView.get<Transform>(e));
	}

	auto staticView = registry.view<Transform, Sprite, StaticBlock>();
	for (auto e : staticView)
	{
		staticView.get<Sprite>(e).Update(staticView.get<Transform>(e));
	}
	
}

void Game::Render()
{
	Drawer::SetDrawColor(Color::grey());
	SDL_RenderClear(renderer);
	
	//render background
	auto bgView = registry.view<Sprite, Background>();
	for (auto e : bgView)
	{
		bgView.get<Sprite>(e).Render();
	}

	//render empty cells
	auto emptyView = registry.view<Sprite, EmptyBlock>();
	for (auto e : emptyView)
	{
		emptyView.get<Sprite>(e).Render();
	}

	//render other sprites
	auto sprView = registry.view<Sprite>();
	for (auto e : sprView)
	{
		if (registry.has<EmptyBlock>(e) || registry.has<Background>(e))
			continue;

		sprView.get(e).Render();
	}
	
	//render text
	auto txtView = registry.view<Text>();
	for (auto e : txtView)
	{
		//game over text only shows if we are awaiting restart
		if (registry.has<GameOverText>(e) && !isAwaitingStart)
			continue;

		txtView.get(e).Render();
	}

	SDL_RenderPresent(renderer);
}
