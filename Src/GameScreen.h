#pragma once

class GameScreen
{
public:
	static const int pixel_per_unit = 32;

	//size is in units, not pixels
	static const int grid_width = 10;
	static const int grid_height = 20;
	
	static const int border_left = 3;
	static const int border_right = 9;
	static const int border_bottom = 3;

	static const int grid_start_x = border_left;
	static const int grid_end_x = grid_start_x + grid_width;
	static const int grid_start_y = 0;
	static const int grid_end_y = grid_height;

	static const int block_start_x = grid_start_x + grid_width / 2;
	static const int info_center_x = pixel_per_unit * (grid_end_x + border_right / 2) + pixel_per_unit / 2;

	static const int total_unit_width = border_left + grid_width + border_right;
	static const int total_unit_height = grid_height + border_bottom;

	static const int total_pixel_width = total_unit_width * pixel_per_unit;
	static const int total_pixel_height = total_unit_height * pixel_per_unit;

	static const int toUnit(int pxl) { return pxl / pixel_per_unit; }
	static const int toPxl(int unit) { return unit * pixel_per_unit; }
};