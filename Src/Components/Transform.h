#pragma once

#include "../Engine/Vector2.h"
#include "../Engine/Vector2Int.h"
#include "../Engine/Direction.h"

class Transform
{
public:
	Vector2Int position;
	Direction rotation;
	Vector2 scale;

	Transform();
	Transform(int x, int y);
	Transform(int x, int y, float xscl, float yscl);
	Transform(int x, int y, float xscl, float yscl, Direction orientation);

	Vector2Int GetCellPos() const;
	void SetCellPos(int x, int y);
	void MoveByCells(int x, int y);
};