#include "GameText.h"
#include "Components/Text.h"
#include "Components/TextTags.h"
#include <string>

void UpdateScoreText(entt::registry & reg, int score)
{
	auto view = reg.view<ScoreText, Text>();
	for (auto e : view)
	{
		view.get<Text>(e).text = std::to_string(score);
	}
}
