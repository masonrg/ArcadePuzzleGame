#include "GameManager.h"
#include "Blocks/BlockManager.h"
#include "CustomEvents.h"
#include <vector>
#include <utility>
#include "Engine/Logger.h"

BlockManager & GameManager::GetBlockManager()
{
	return blockManager;
}

void GameManager::RestartGame(entt::registry & registry)
{
	GetNewBlock(registry);

	auto activeview = registry.view<StaticBlock>();
	for (auto e : activeview)
	{
		SetCellEmpty(registry, e);
	}
}

void GameManager::ProcessInputDown(entt::registry & registry, SDL_Event & event)
{
	bool isRepeat = (bool)event.key.repeat;
	
	switch (event.key.keysym.sym)
	{
	case SDLK_a:
	case SDLK_LEFT:
		if (!isRepeat)
		{
			MoveActiveBlockSide(registry, -1);
			moveTimer.ForceTick();
		}
		else if (moveTimer.Tick()) 
		{
			MoveActiveBlockSide(registry, -1);
		}
		break;
	case SDLK_d:
	case SDLK_RIGHT:
		if (!isRepeat)
		{
			MoveActiveBlockSide(registry, 1);
			moveTimer.ForceTick();
		}
		else if (moveTimer.Tick())
		{
			MoveActiveBlockSide(registry, 1);
		}
		break;
	case SDLK_s:
	case SDLK_DOWN:
		if (!isRepeat)
		{
			MoveActiveBlockDown(registry);
			moveTimer.ForceTick();
			dropTimer.ResetTick();
		}
		else if (moveTimer.Tick(0.33f))
		{
			MoveActiveBlockDown(registry);
			dropTimer.ResetTick();
		}
		break;
	case SDLK_e:
	case SDLK_UP:
		if (!isRepeat)
		{
			activeBlock->RotateRight();
			if (CheckForCollision(registry, 0, 0))
				activeBlock->RotateLeft();
			else
				wasMoved = true;
		}
		break;
	case SDLK_q:
		if (!isRepeat)
		{
			activeBlock->RotateLeft();
			if (CheckForCollision(registry, 0, 0))
				activeBlock->RotateRight();
			else
				wasMoved = true;
		}
		break;
	default:
		break;
	}
}

void GameManager::Update(entt::registry & registry)
{
	if (dropTimer.Tick())
	{
		MoveActiveBlockDown(registry);
	}

	if (wasMoved)
	{
		UpdateFallBlockPosition(registry);
		wasMoved = false;
	}
}

void GameManager::GetNewBlock(entt::registry & registry)
{
	activeBlock = blockManager.ExchangeBlock(std::move(activeBlock));
	ResetActiveBlock(registry);
	UpdateFallBlockColor(registry);
}

void GameManager::ClearBlock(entt::registry & registry)
{
	ResetActiveBlock(registry); //this will move it out of the way before we return it
	blockManager.ReturnBlock(std::move(activeBlock));
}


/* -------------------- */
/* ACTIVE BLOCK HELPERS */
/* -------------------- */

entt::entity GameManager::GetControlEntity(entt::registry & registry) const
{
	auto ctrlView = registry.view<ControlBlock, Transform>();
	for (entt::entity eCtrl : ctrlView)
		return eCtrl;
	return entt::entity();
}

Transform & GameManager::GetControlTransform(entt::registry & registry) const
{
	return registry.get<Transform>(GetControlEntity(registry));
}

std::array<Vector2Int, 4> GameManager::GetFallBlockCells(entt::registry & registry, int addX, int addY) const
{
	Vector2Int cellPos = GetControlTransform(registry).GetCellPos();
	cellPos.x += addX;
	cellPos.y += addY;
	auto& pieces = activeBlock->GetPieces();

	return {
		cellPos + pieces[0],
		cellPos + pieces[1],
		cellPos + pieces[2],
		cellPos + pieces[3]
	};
}


/* --------------------- */
/* ACTIVE BLOCK HANDLING */
/* --------------------- */

void GameManager::ResetActiveBlock(entt::registry & registry)
{
	GetControlTransform(registry).SetCellPos(GameScreen::block_start_x, -activeBlock.get()->GetBottomMostOffset());
	wasMoved = true;
}

void GameManager::MoveActiveBlockSide(entt::registry& registry, int move)
{
	if (!CheckForSideCollision(registry, move < 0))
	{
		MoveActiveBlock(registry, move, 0);
	}
}

void GameManager::MoveActiveBlockDown(entt::registry & registry)
{
	if (!CheckForDropCollision(registry))
	{
		MoveActiveBlock(registry, 0, 1);
	}
	else
	{
		DropSuccessful(registry);
	}
}

void GameManager::MoveActiveBlock(entt::registry & registry, int moveX, int moveY)
{
	GetControlTransform(registry).MoveByCells(moveX, moveY);
	wasMoved = true;
}


/* --------------------- */
/* UPDATE FALLING BLOCKS */
/* --------------------- */

void GameManager::UpdateFallBlockPosition(entt::registry & registry)
{
	if (activeBlock == nullptr)
		return;

	Vector2Int ctrlCellPos = GetControlTransform(registry).GetCellPos();
	const auto& pieces = activeBlock.get()->GetPieces();

	int i = 0;
	auto blkView = registry.view<FallingBlock, Transform>();
	for (auto eBlk : blkView)
	{
		blkView.get<Transform>(eBlk).SetCellPos(ctrlCellPos.x + pieces[i].x, ctrlCellPos.y + pieces[i].y);
		i++;
	}
}

void GameManager::UpdateFallBlockColor(entt::registry & registry)
{
	if (activeBlock == nullptr)
		return;

	// update the active block to be the correct color
	auto blkView = registry.view<FallingBlock, Sprite>();
	for (auto eBlk : blkView)
	{
		blkView.get<Sprite>(eBlk).textureName = activeBlock->GetTexture();
	}
}


/* ------------------- */
/* COLLISION DETECTION */
/* ------------------- */

bool GameManager::CheckForSideCollision(entt::registry & registry, bool left)
{
	return CheckForCollision(registry, left ? -1 : 1, 0);
}

bool GameManager::CheckForDropCollision(entt::registry & registry)
{
	return CheckForCollision(registry, 0, 1);
}

bool GameManager::CheckForCollision(entt::registry & registry, int moveX, int moveY)
{
	std::array<Vector2Int, 4> checkPositions = GetFallBlockCells(registry, moveX, moveY);

	auto colView = registry.view<Collider, Transform>();
	for (auto eCol : colView)
	{
		Vector2Int colPos = colView.get<Transform>(eCol).GetCellPos();
		for (auto p : checkPositions)
		{
			if (colPos == p)
				return true;
		}
	}
	
	return false;
}


/* ----------------- */
/* CELL MODIFICATION */
/* ----------------- */

void GameManager::SetCellActive(entt::registry& registry, entt::entity entity, std::string& texture)
{
	if (registry.valid(entity) && registry.has<EmptyBlock>(entity))
	{
		registry.remove<EmptyBlock>(entity);
		registry.assign<StaticBlock>(entity);
		registry.assign<Collider>(entity);
		registry.get<Sprite>(entity).textureName = texture;
	}
}

void GameManager::SetCellEmpty(entt::registry& registry, entt::entity entity)
{
	if (registry.valid(entity) && registry.has<StaticBlock>(entity))
	{
		registry.remove<StaticBlock>(entity);
		registry.remove<Collider>(entity);
		registry.assign<EmptyBlock>(entity);
		registry.get<Sprite>(entity).textureName = GameConstants::tile_empty;
	}
}


/* ------------------ */
/* COLLISION HANDLING */
/* ------------------ */

void GameManager::DropSuccessful(entt::registry & registry)
{
	EmplaceActiveBlock(registry);
	CheckEmplacedRows(registry);
	GetNewBlock(registry);
}

void GameManager::EmplaceActiveBlock(entt::registry & registry)
{
	std::array<Vector2Int, 4> emplacePositions = GetFallBlockCells(registry, 0, 0);

	int activatedCells = 0;
	auto gridView = registry.view<Transform, Sprite, EmptyBlock>();
	for (auto e : gridView)
	{
		Vector2Int cell = gridView.get<Transform>(e).GetCellPos();

		for (auto p : emplacePositions)
		{
			if (cell == p)
			{
				SetCellActive(registry, e, activeBlock->GetTexture());
				activatedCells++;
				break;
			}

			if (activatedCells == 4)
				break;
		}
	}
}

bool GameManager::CheckEmplacedRows(entt::registry & registry)
{
	//get the height range that the emplaced block occupies
	Vector2Int ctrlCellPos = GetControlTransform(registry).GetCellPos();
	int minY = ctrlCellPos.y + activeBlock->GetTopMostOffset();
	int maxY = ctrlCellPos.y + activeBlock->GetBottomMostOffset();

	//if any point on the block is above the play area, then the game is over
	if (minY < GameScreen::grid_start_y)
	{
		SendEvent(TetrisEvent::GameOver);
		return false;
	}

	int rowsCleared = 0;
	for (int hgt = minY; hgt <= maxY; hgt++)
	{
		if (ClearRowIfFull(registry, hgt))
		{
			//we can shift rows while iterating because we are clearing rows from the top down
			//so the subsequent height values are not affect by a row shift from above
			ShiftRowsDown(registry, hgt);
			rowsCleared++;
		}
	}

	if (rowsCleared > 0)
	{
		SendEvent((TetrisEvent)rowsCleared);
	}

	return true;
}

bool GameManager::ClearRowIfFull(entt::registry & registry, int height)
{
	std::vector<entt::entity> cellEntities;
	auto gridView = registry.view<Transform, StaticBlock>();
	for (auto e : gridView)
	{
		Vector2Int cell = gridView.get<Transform>(e).GetCellPos();

		if (cell.y == height)
			cellEntities.emplace_back(e);

		if (cellEntities.size() == GameScreen::grid_width)
		{
			for (auto cell : cellEntities)
			{
				SetCellEmpty(registry, cell);
			}
			return true;
		}
	}
	return false;
}

void GameManager::ShiftRowsDown(entt::registry & registry, int height)
{
	//list of the location and texture of shifted cells
	std::vector<std::pair<Vector2Int, std::string>> shiftedCellData;

	//iterate static blocks and find all that need to be shifted and record their information to transfer them to the below empty blocks
	auto staticView = registry.view<Transform, Sprite, StaticBlock>();
	for (auto e : staticView)
	{
		Vector2Int cellPos = staticView.get<Transform>(e).GetCellPos();
		if (cellPos.y < height)
		{
			shiftedCellData.emplace_back(std::make_pair(cellPos + Vector2Int(0, 1), staticView.get<Sprite>(e).textureName));
			SetCellEmpty(registry, e);
		}
	}

	//fill in the empty blocks that were shifted into
	auto emptyView = registry.view<Transform, EmptyBlock>();
	for (auto e : emptyView)
	{
		Vector2Int cellPos = emptyView.get<Transform>(e).GetCellPos();
		for (auto pair : shiftedCellData)
		{
			if (cellPos == pair.first)
			{
				SetCellActive(registry, e, pair.second);
				break;
			}
		}
	}
}