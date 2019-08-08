#pragma once

#include "BlockBase.h"

class T_Block : public BlockBase
{
public:
	void OrientFlatDown() override
	{
		pieces[0] = Vector2Int(0, 0);
		pieces[1] = Vector2Int(-1, 0);
		pieces[2] = Vector2Int(1, 0);
		pieces[3] = Vector2Int(0, -1);
	}

	void OrientFlatLeft() override
	{
		pieces[0] = Vector2Int(0, 0);
		pieces[1] = Vector2Int(1, 0);
		pieces[2] = Vector2Int(0, -1);
		pieces[3] = Vector2Int(0, 1);
	}

	void OrientFlatUp() override
	{
		pieces[0] = Vector2Int(0, 0);
		pieces[1] = Vector2Int(-1, 0);
		pieces[2] = Vector2Int(1, 0);
		pieces[3] = Vector2Int(0, 1);
	}

	void OrientFlatRight() override
	{
		pieces[0] = Vector2Int(0, 0);
		pieces[1] = Vector2Int(-1, 0);
		pieces[2] = Vector2Int(0, -1);
		pieces[3] = Vector2Int(0, 1);
	}
};