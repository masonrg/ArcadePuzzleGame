#pragma once

#include "entt/entity/registry.hpp"
#include "Components/Components.h"
#include "Blocks/BlockManager.h"

void MakeBackground(entt::registry& reg);
void MakePlayArea(entt::registry& reg);

void MakeGameTexts(entt::registry& reg);
void MakeScoreText(entt::registry& reg);
void MakeHelpText(entt::registry& reg);
void MakeExitText(entt::registry& reg);
void MakeGameOverText(entt::registry& reg);


void MakeActiveBlock(entt::registry& reg);
entt::entity MakeFallingBlock(entt::registry& reg);