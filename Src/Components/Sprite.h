#pragma once

#include "SDL.h"
#include "Transform.h"
#include <string>

class Background {};

class Sprite 
{
public:
	std::string textureName;
	SDL_Rect src;
	SDL_Rect dst;
	int rotation;

	Sprite(std::string texturePath);
	Sprite(std::string texturePath, int xpos, int ypos, float xscl, float yscl, int rot);

	void Update(const Transform& parent);
	void Update(int xpos, int ypos, float xscl, float yscl, int rot);

	void Render();
};