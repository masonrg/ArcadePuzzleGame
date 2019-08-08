#pragma once

#include "Engine/Core.h"
#include "Engine/TickTimer.h"
#include "GameScreen.h"
#include "Blocks/BlockManager.h"
#include "Components/Components.h"
#include <array>
#include <memory>

class GameManager
{
public:
	BlockManager& GetBlockManager();

	void RestartGame(entt::registry& registry);
	void ProcessInputDown(entt::registry& registry, SDL_Event& event);
	void Update(entt::registry& registry);
	void GetNewBlock(entt::registry& registry);
	void ClearBlock(entt::registry& registry);

private:
	BlockManager blockManager;
	std::unique_ptr<BlockBase> activeBlock;

	bool wasMoved = false;

	TickTimer dropTimer = TickTimer(0.50f, GameConstants::fps);
	TickTimer moveTimer = TickTimer(0.06f, GameConstants::fps);

	// Helpers
	entt::entity GetControlEntity(entt::registry& registry) const;
	Transform& GetControlTransform(entt::registry& registry) const;
	std::array<Vector2Int, 4> GetFallBlockCells(entt::registry& registry, int addX, int addY) const;

	// Dealing with the active block
	void ResetActiveBlock(entt::registry& registry);
	void MoveActiveBlockSide(entt::registry& registry, int move);
	void MoveActiveBlockDown(entt::registry& registry);
	void MoveActiveBlock(entt::registry& registry, int moveX, int moveY);
	

	// Updating falling blocks
	void UpdateFallBlockPosition(entt::registry& registry);
	void UpdateFallBlockColor(entt::registry& registry);

	// Collision detection
	bool CheckForSideCollision(entt::registry& registry, bool left);
	bool CheckForDropCollision(entt::registry& registry);
	bool CheckForCollision(entt::registry& registry, int moveX, int moveY);

	// Cell Modification
	void SetCellActive(entt::registry& registry, entt::entity entity, std::string& texture);
	void SetCellEmpty(entt::registry& registry, entt::entity entity);

	// Collision handling
	void DropSuccessful(entt::registry& registry);
	void EmplaceActiveBlock(entt::registry& registry);
	bool CheckEmplacedRows(entt::registry& registry);
	bool ClearRowIfFull(entt::registry& registry, int height);
	void ShiftRowsDown(entt::registry& registry, int height);
};