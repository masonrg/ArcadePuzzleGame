#include "Factory.h"
#include "GameScreen.h"
#include "GameConstants.h"
#include "Engine/Logger.h"
#include <string>

void MakeBackground(entt::registry & reg)
{
	auto e = reg.create();
	reg.assign<Sprite>(e, GameConstants::window_background);
	reg.assign<Background>(e);
}

void MakePlayArea(entt::registry& reg)
{
	/* Make the playable area, centered on the width and coming down from the top. */
	
	int startX = GameScreen::grid_start_x;
	int endX = startX + GameScreen::grid_width;
	
	int startY = 0;
	int endY = startY + GameScreen::grid_height;

	for (int y = startY; y < endY; y++) {
		for (int x = startX; x < endX; x++)
		{
			auto e = reg.create();
			auto& trans = reg.assign<Transform>(e, GameScreen::toPxl(x), GameScreen::toPxl(y), 1.0f, 1.0f);
			auto& spr = reg.assign<Sprite>(e, GameConstants::tile_empty);
			reg.assign<EmptyBlock>(e);
			
			spr.Update(trans);
		}
	}
	
	//create colliders around the perimeter
	for (int y = startY; y < endY+1; y++) {
		for (int x = startX-1; x < endX+1; x++)
		{
			//only perimeter pieces
			if (x == startX-1 || x == endX || y == endY)
			{
				auto e = reg.create();
				auto& trans = reg.assign<Transform>(e, GameScreen::toPxl(x), GameScreen::toPxl(y));
				reg.assign<Collider>(e);
				reg.assign<Boundary>(e);
			}
		}
	}

	LOG(std::string("Play Area Created: (") + std::to_string(GameScreen::grid_width) + std::string("x") + std::to_string(GameScreen::grid_height) + std::string(")"));
}

void MakeGameTexts(entt::registry & reg)
{
	MakeScoreText(reg);
	MakeHelpText(reg);
	MakeExitText(reg);
	MakeGameOverText(reg);
}

void MakeScoreText(entt::registry & reg)
{
	int centerX = GameScreen::info_center_x;
	SDL_Color color = { 50, 230, 0, 255 };
	auto e = reg.create();
	reg.assign<Text>(e, GameConstants::font_sans, 55, "0", centerX, GameScreen::toPxl(4), 1.0f, 1.0f, color, TextJustify::CenteredMid);
	reg.assign<ScoreText>(e);
}

void MakeHelpText(entt::registry & reg)
{
	const int DROP_STEP = 25;
	const int FONT_SIZE = 20;

	int centerX = GameScreen::info_center_x;
	int currY = GameScreen::toPxl(GameScreen::grid_height / 2 + 1) - GameScreen::pixel_per_unit / 2;
	
	SDL_Color color = { 235, 235, 235, 255 };

	auto e0 = reg.create();
	auto e1 = reg.create();
	auto e2 = reg.create();
	auto e3 = reg.create();

	reg.assign<Text>(e0, GameConstants::font_sans, FONT_SIZE, "a/Larrow : move left", centerX, currY += DROP_STEP, 1.0f, 1.0f, color, TextJustify::CenteredTop);
	reg.assign<Text>(e1, GameConstants::font_sans, FONT_SIZE, "d/Rarrow : move right", centerX, currY += DROP_STEP, 1.0f, 1.0f, color, TextJustify::CenteredTop);
	reg.assign<Text>(e2, GameConstants::font_sans, FONT_SIZE, "s/Darrow : move down", centerX, currY += DROP_STEP, 1.0f, 1.0f, color, TextJustify::CenteredTop);
	reg.assign<Text>(e3, GameConstants::font_sans, FONT_SIZE, "q,e/Uarrow : rotate", centerX, currY += DROP_STEP, 1.0f, 1.0f, color, TextJustify::CenteredTop);

	reg.assign<HelpText>(e0);
	reg.assign<HelpText>(e1);
	reg.assign<HelpText>(e2);
	reg.assign<HelpText>(e3);
}

void MakeExitText(entt::registry & reg)
{
	const int FONT_SIZE = 20;

	int centerX = GameScreen::info_center_x;
	int currY = GameScreen::toPxl(GameScreen::grid_height + GameScreen::border_bottom / 2) + GameScreen::pixel_per_unit / 2;

	SDL_Color color = { 235, 235, 235, 255 };

	auto e0 = reg.create();
	auto e1 = reg.create();

	reg.assign<Text>(e0, GameConstants::font_sans, FONT_SIZE, "enter : restart", centerX, currY, 1.0f, 1.0f, color, TextJustify::CenteredBottom);
	reg.assign<Text>(e1, GameConstants::font_sans, FONT_SIZE, "esc : quit game", centerX, currY + GameScreen::pixel_per_unit, 1.0f, 1.0f, color, TextJustify::CenteredBottom);

	reg.assign<HelpText>(e0);
	reg.assign<HelpText>(e1);
}



void MakeGameOverText(entt::registry & reg)
{
	int X = GameScreen::toPxl(GameScreen::grid_start_x + GameScreen::grid_width / 2);
	int Y = GameScreen::toPxl(GameScreen::grid_height / 2);
	SDL_Color color = { 255, 0, 0, 255 };

	auto e = reg.create();
	reg.assign<Text>(e, GameConstants::font_sans, 55, "GAME OVER", X, Y, 1.0f, 1.0f, color, TextJustify::CenteredMid);
	reg.assign<GameOverText>(e);
}



void MakeActiveBlock(entt::registry & reg)
{
	// create the control block which we will use to indicate where the falling piece is
	auto e = reg.create();
	reg.assign<ControlBlock>(e);
	reg.assign<Transform>(e);

	MakeFallingBlock(reg);
	MakeFallingBlock(reg);
	MakeFallingBlock(reg);
	MakeFallingBlock(reg);
}


entt::entity MakeFallingBlock(entt::registry & reg)
{
	auto e = reg.create();
	reg.assign<FallingBlock>(e);
	reg.assign<Transform>(e, 0, 0, 1.0f, 1.0f);
	reg.assign<Sprite>(e, GameConstants::tile_empty);
	return e;
}
