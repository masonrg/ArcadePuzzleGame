#pragma once

#include "Sprite.h"
#include "../Engine/Drawer.h"

Sprite::Sprite(std::string texturePath)// : textureName(texturePath)
{
	this->textureName = texturePath;
	Vector2Int textureSize = Drawer::GetTextureSize(texturePath);
	src = { 0, 0, textureSize.x, textureSize.y };
	Update(0, 0, 1, 1, 0);
}

Sprite::Sprite(std::string texturePath, int xpos, int ypos, float xscl, float yscl, int rot)// : textureName(texturePath)
{
	this->textureName = texturePath;
	Vector2Int textureSize = Drawer::GetTextureSize(texturePath);
	src = { 0, 0, textureSize.x, textureSize.y };
	Update(xpos, ypos, xscl, yscl, rot);
}

void Sprite::Update(const Transform& parent)
{
	Update(parent.position.x, parent.position.y, parent.scale.x, parent.scale.y, parent.rotation);
}

void Sprite::Update(int xpos, int ypos, float xscl, float yscl, int rot)
{
	dst.x = xpos;
	dst.y = ypos;
	dst.w = (int)(src.w * xscl);
	dst.h = (int)(src.h * yscl);
	rotation = rot;
}

void Sprite::Render()
{
	Drawer::DrawTexture(textureName, src, dst, rotation);
}