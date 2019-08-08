#pragma once

#include "Engine/Core.h"
#include "GameManager.h"
#include <string>
#include <memory>

class Game
{
public:
	Game(std::string title, int width, int height);
	~Game();

	void HandleEvents();
	void Update();
	void Render();
	
	bool IsRunning() const { return isRunning; }
	bool IsAwaitingStart() const { return isAwaitingStart; }
	int GetFrameCount() const { return frameCounter; }

private:
	bool isRunning = false;
	bool isAwaitingStart = false;
	int frameCounter = 0;
	int score = 0;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	
	entt::registry registry;

	GameManager gameManager;

	void initSDL(std::string title, int width, int height);
	void initEntt();
};