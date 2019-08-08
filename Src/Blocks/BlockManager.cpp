#include "BlockManager.h"
#include "../Engine/Logger.h"

BlockManager::BlockManager()
{
	blocks[0] = std::make_unique<O_Block>();
	blocks[1] = std::make_unique<I_Block>();
	blocks[2] = std::make_unique<T_Block>();
	blocks[3] = std::make_unique<S_Block>();
	blocks[4] = std::make_unique<Z_Block>();
	blocks[5] = std::make_unique<J_Block>();
	blocks[6] = std::make_unique<L_Block>();

	colors[0] = GameConstants::tile_red;
	colors[1] = GameConstants::tile_blue;
	colors[2] = GameConstants::tile_green;
	colors[3] = GameConstants::tile_cyan;
	colors[4] = GameConstants::tile_magenta;
	colors[5] = GameConstants::tile_yellow;
	colors[6] = GameConstants::tile_orange;

	activeBlockIndex = -1;

	LOG("BlockManager initialized");
}

std::unique_ptr<BlockBase> BlockManager::ExchangeBlock(std::unique_ptr<BlockBase> returnBlock)
{
	// If the return block is null, then dont give a new block out, unless its the first time a block is being requested.
	if (returnBlock == nullptr && activeBlockIndex != -1)
		return nullptr;

	// Return the block
	if (activeBlockIndex != -1)
	{
		blocks[activeBlockIndex] = std::move(returnBlock);
	}

	// Randomly select the next block, and assign it a color and orientation
	int randBlock = rand() % NUM_BLOCKS;
	int randColor = rand() % NUM_COLORS;
	blocks[randBlock].get()->SetTexture(colors[randColor]);
	blocks[randBlock].get()->SetOrientation(Orientation::FlatLeft);

	// Record the new block's index and return the ptr
	activeBlockIndex = randBlock;
	return std::move(blocks[randBlock]);
}

void BlockManager::ReturnBlock(std::unique_ptr<BlockBase> returnBlock)
{
	// If the return block is null, then there is nothing to do
	if (returnBlock == nullptr)
		return;

	// Return the block
	if (activeBlockIndex != -1)
	{
		blocks[activeBlockIndex] = std::move(returnBlock);
	}

	// No block is currently loaned
	activeBlockIndex = -1;
}

const std::string& BlockManager::GetColor(int index)
{
	if (index < 0 || index >= NUM_COLORS)
		return GameConstants::tile_empty;
	
	return colors[index];
}
