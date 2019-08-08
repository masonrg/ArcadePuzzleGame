#pragma once

#include "../Engine/Vector2Int.h"
#include "../GameConstants.h"
#include <vector>
#include <string>
#include <array>

/* Orientations for blocks found at: https://tetris.fandom.com/wiki/Orientation */

enum Orientation
{
	FlatDown, FlatLeft, FlatUp, FlatRight
};

class BlockBase
{
public:
	BlockBase()
	{
		SetTexture(GameConstants::tile_red);
		SetOrientation(Orientation::FlatDown);
	}

	void SetTexture(std::string texture)
	{
		this->texture = texture;
	}

	void SetOrientation(Orientation rotation) 
	{
		switch (rotation)
		{
		case FlatDown:
			OrientFlatDown();
			break;
		case FlatLeft:
			OrientFlatLeft();
			break;
		case FlatUp:
			OrientFlatUp();
			break;
		case FlatRight:
			OrientFlatRight();
			break;
		default:
			break;
		}
		
		this->rotation = rotation;
	}

	std::array<Vector2Int, 4>& GetPieces()
	{
		return pieces;
	}
	
	std::string& GetTexture()
	{
		return texture;
	}

	int GetLeftMostOffset()
	{
		int offset = INT_MAX;
		for (auto p : pieces) if (p.x < offset) offset = p.x;
		return offset;
	}

	int GetRightMostOffset()
	{
		int offset = INT_MIN;
		for (auto p : pieces) if (p.x > offset) offset = p.x;
		return offset;
	}

	int GetTopMostOffset()
	{
		int offset = INT_MAX;
		for (auto p : pieces) if (p.y < offset) offset = p.y;
		return offset;
	}

	int GetBottomMostOffset()
	{
		int offset = INT_MIN;
		for (auto p : pieces) if (p.y > offset) offset = p.y;
		return offset;
	}

	void RotateLeft()
	{
		switch (rotation)
		{
		case FlatDown: SetRotation(FlatRight); break;
		case FlatLeft: SetRotation(FlatDown); break;
		case FlatUp: SetRotation(FlatLeft); break;
		case FlatRight: SetRotation(FlatUp); break;
		default: break;
		}
	}

	void RotateRight()
	{
		switch (rotation)
		{
		case FlatDown: SetRotation(FlatLeft); break;
		case FlatLeft: SetRotation(FlatUp); break;
		case FlatUp: SetRotation(FlatRight); break;
		case FlatRight: SetRotation(FlatDown); break;
		default: break;
		}
	}

protected:
	std::string texture;
	std::array<Vector2Int, 4> pieces;
	Orientation rotation;

	void SetRotation(Orientation rotation)
	{
		this->rotation = rotation;
		switch (rotation)
		{
		case FlatDown: OrientFlatDown(); break;
		case FlatLeft: OrientFlatLeft(); break;
		case FlatUp: OrientFlatUp(); break;
		case FlatRight: OrientFlatRight(); break;
		default: break;
		}
	}

	virtual void OrientFlatDown() {}
	virtual void OrientFlatLeft() {}
	virtual void OrientFlatUp() {}
	virtual void OrientFlatRight() {}
};