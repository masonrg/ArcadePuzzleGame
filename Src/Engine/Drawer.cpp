#include "Drawer.h"
#include "Logger.h"
#include "Vector2Int.h"

SDL_Renderer* Drawer::renderer = nullptr;
TextureCache Drawer::imageCache;
FontCache Drawer::fontCache;

/* ------ */
/* PUBLIC */
/* ------ */
void Drawer::SetDrawColor(Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

Vector2Int Drawer::GetTextureSize(std::string texturePath)
{
	SDL_Texture* texture = GetImage(texturePath);
	if (texture)
	{
		int width;
		int height;
		if (SDL_QueryTexture(texture, NULL, NULL, &width, &height) == 0)
			return { width, height };
		else
			LOG_ERROR("SDL ERROR", SDL_GetError());
	}
	return { 0, 0 };
}

void Drawer::DrawTextureToFullWindow(std::string texturePath)
{
	DrawTexture_Internal(texturePath, NULL, NULL, 0);
}

void Drawer::DrawTexture(std::string texturePath, const SDL_Rect& dst, int rotation)
{
	DrawTexture_Internal(texturePath, NULL, &dst, rotation);
}

void Drawer::DrawTexture(std::string texturePath, const SDL_Rect& src, const SDL_Rect& dst, int rotation)
{
	DrawTexture_Internal(texturePath, &src, &dst, rotation);
}


void Drawer::DrawText(std::string & fontPath, int fontSize, std::string & text, SDL_Color & color, Vector2Int & position, Vector2 & scale, TextJustify & justify)
{
	TTF_Font* font = GetFont(fontPath, fontSize);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

	SDL_Rect dst = { position.x, position.y, texW * scale.x, texH * scale.y };
	switch (justify)
	{
	case CenteredTop:
		dst.x -= texW / 2;
		break;
	case CenteredMid:
		dst.x -= texW / 2;
		dst.y -= texH / 2;
		break;
	case CenteredBottom:
		dst.x -= texW / 2;
		dst.y -= texH;
		break;
	default:
		break;
	}
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}


void Drawer::Clear()
{
	for (auto t : imageCache)
	{
		SDL_DestroyTexture(t.second);
	}
	imageCache.clear();

	for (auto f : fontCache)
	{
		TTF_CloseFont(f.second);
	}
	fontCache.clear();
}

/* ------- */
/* PRIVATE */
/* ------- */
SDL_Texture* Drawer::GetImage(std::string texturePath)
{
	//check if image exists yet
	if (imageCache.find(texturePath) == imageCache.end())
	{
		imageCache[texturePath] = IMG_LoadTexture(renderer, texturePath.c_str());
		if (imageCache[texturePath] == nullptr)
			LOG_ERROR("SDL ERROR", SDL_GetError());
	}

	return imageCache[texturePath];
}

void Drawer::DrawTexture_Internal(std::string texturePath, const SDL_Rect * src, const SDL_Rect * dst, int rotation)
{
	SDL_Texture* texture = GetImage(texturePath);
	if (texture)
	{
		if (rotation == 0)
		{
			if (SDL_RenderCopy(renderer, texture, src, dst))
				LOG_ERROR("SDL ERROR", SDL_GetError());
		}
		else
		{
			if (SDL_RenderCopyEx(renderer, texture, src, dst, rotation, NULL, SDL_FLIP_NONE))
				LOG_ERROR("SDL ERROR", SDL_GetError());
		}
	}
}

TTF_Font * Drawer::GetFont(std::string& fontPath, int ptSize)
{
	//path to font is combo of the font name and ptsize
	std::string fontKey = fontPath + std::to_string(ptSize);

	//check if font exists yet
	if (fontCache.find(fontKey) == fontCache.end())
	{
		fontCache[fontKey] = TTF_OpenFont(fontPath.c_str(), ptSize);
		if (fontCache[fontKey] == nullptr)
			LOG_ERROR("TTF ERROR", SDL_GetError());
	}

	return fontCache[fontKey];
}
