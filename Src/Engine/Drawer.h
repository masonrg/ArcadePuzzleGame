#pragma once

#include "Core.h"
#include "Color.h"
#include "Vector2Int.h"
#include "Vector2.h"

#include <string>
#include <memory>
#include <map>

using TextureCache = std::unordered_map<std::string, SDL_Texture*>;
using FontCache = std::unordered_map<std::string, TTF_Font*>;

enum TextJustify {
	CenteredTop,
	CenteredMid,
	CenteredBottom
};

class Drawer
{
public:
	static void SetDrawColor(Color color);

	static Vector2Int GetTextureSize(std::string texturePath);

	static void DrawTextureToFullWindow(std::string texturePath);
	static void DrawTexture(std::string texturePath, const SDL_Rect& dst, int rotation);
	static void DrawTexture(std::string texturePath, const SDL_Rect& src, const SDL_Rect& dst, int rotation);

	static void DrawText(std::string& fontPath, int fontSize, std::string& text, SDL_Color& color, Vector2Int& position, Vector2& scale, TextJustify& justify);

	static void Clear();

	static void SetRenderer(SDL_Renderer* renderer)
	{
		Drawer::renderer = renderer;
	}

private:
	static SDL_Renderer* renderer;
	static TextureCache imageCache;
	static FontCache fontCache;

	static SDL_Texture* GetImage(std::string texturePath);
	static void DrawTexture_Internal(std::string texturePath, const SDL_Rect* src, const SDL_Rect* dst, int rotation);

	static TTF_Font* GetFont(std::string& fontPath, int ptSize);
};