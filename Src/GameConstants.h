#pragma once

#include <string>

class GameConstants
{
public:
	static const int fps = 60;

	static const int score_base_value = 100;
	static const int score_2line_bonus = 50;
	static const int score_3line_bonus = 200;
	static const int score_4line_bonus = 800;

	static const std::string font_sans;

	static const std::string tile_empty;
	static const std::string tile_red;
	static const std::string tile_blue;
	static const std::string tile_green;
	static const std::string tile_yellow;
	static const std::string tile_orange;
	static const std::string tile_magenta;
	static const std::string tile_cyan;

	static const std::string window_background;
};

