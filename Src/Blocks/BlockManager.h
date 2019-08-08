#pragma once

#include "Blocks.h"
#include <array>
#include <memory>

/* Manages all the blocks. We only need one of each type. */

class BlockManager
{
public:
	BlockManager();

	static const int NUM_BLOCKS = 7;
	static const int NUM_COLORS = 7;

	std::unique_ptr<BlockBase> ExchangeBlock(std::unique_ptr<BlockBase> returnBlock);
	void ReturnBlock(std::unique_ptr<BlockBase> returnBlock);
	const std::string& GetColor(int index);

private:
	int activeBlockIndex;
	std::array<std::unique_ptr<BlockBase>, NUM_BLOCKS> blocks;
	std::array<std::string, NUM_COLORS> colors;
};