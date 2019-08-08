#pragma once

#include "SDL.h"
#include "Transform.h"
#include "../Engine/Vector2.h"
#include "../Engine/Vector2Int.h"
#include "../Engine/Drawer.h"
#include <string>



class Text 
{
public:
	std::string fontName;
	int fontSize;

	std::string text;
	SDL_Color color;
	Vector2Int position;
	Vector2 scale;
	TextJustify justify;

	Text(std::string fontPath, int fontSize, std::string text);
	Text(std::string fontPath, int fontSize, std::string text, int xpos, int ypos, float xscl, float yscl, SDL_Color color, TextJustify justify);

	void Update(const Transform& parent);
	void Update(int xpos, int ypos, float xscl, float yscl);
	void Update(int xpos, int ypos, float xscl, float yscl, TextJustify justify);

	void Render();
};