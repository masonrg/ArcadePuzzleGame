#pragma once

#include "BlockBase.h"

class O_Block : public BlockBase
{
public:
	void OrientFlatDown() override
	{
		pieces[0] = Vector2Int(0, 0);
		pieces[1] = Vector2Int(1, 0);
		pieces[2] = Vector2Int(0, 1);
		pieces[3] = Vector2Int(1, 1);
	}

	void OrientFlatLeft() override
	{
		OrientFlatDown();
	}

	void OrientFlatUp() override
	{
		OrientFlatDown();
	}

	void OrientFlatRight() override
	{
		OrientFlatDown();
	}
};