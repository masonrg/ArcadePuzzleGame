#include "Text.h"
#include "../Engine/Drawer.h"

Text::Text(std::string fontPath, int fontSize, std::string text)
{
	this->fontName = fontPath;
	this->fontSize = fontSize;
	this->text = text;
	this->color = { 255, 255, 255, 255 };
	Update(0, 0, 1, 1, TextJustify::CenteredTop);
}

Text::Text(std::string fontPath, int fontSize, std::string text, int xpos, int ypos, float xscl, float yscl, SDL_Color color, TextJustify justify)
{
	this->fontName = fontPath;
	this->fontSize = fontSize;
	this->text = text;
	this->color = color;
	Update(xpos, ypos, xscl, yscl, justify);
}

void Text::Update(const Transform & parent)
{
	Update(parent.position.x, parent.position.y, parent.scale.x, parent.scale.y);
}

void Text::Update(int xpos, int ypos, float xscl, float yscl)
{
	position.x = xpos;
	position.y = ypos;
	scale.x = xscl;
	scale.y = yscl;
}

void Text::Update(int xpos, int ypos, float xscl, float yscl, TextJustify justify)
{
	Update(xpos, ypos, xscl, yscl);
	this->justify = justify;
}

void Text::Render()
{
	Drawer::DrawText(fontName, fontSize, text, color, position, scale, justify);
}
