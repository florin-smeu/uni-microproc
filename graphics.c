/*
 * draw.c
 *
 * Created: 6/19/2019 7:12:22 PM
 *  Author: Florin
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "ili9341.h"
#include "ili9341gfx.h"
#include "graphics.h"
#include "resources.h"

void draw_walls(uint16_t color)
{
	// Draw map corners
	drawBitmapAlpha(W_OFFSET, H_OFFSET, corner_left_up, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + (H_CELLS - 1) * CELL_DIM, H_OFFSET, corner_right_up, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + (H_CELLS - 1) * CELL_DIM, H_OFFSET + (V_CELLS - 1) * CELL_DIM, corner_right_down, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET, H_OFFSET + (V_CELLS - 1) * CELL_DIM, corner_left_down, CELL_DIM, CELL_DIM, color);

	// Upper and lower walls
	for (int i = 1; i <= 26; ++i) {
		if (i != 13 && i != 14) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET, double_wall_up, CELL_DIM, CELL_DIM, color);
		}
		drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + (V_CELLS - 1) * CELL_DIM, double_wall_down, CELL_DIM, CELL_DIM, color);
	}
	
	// Left and right walls
	for (int j = 1; j <= 8; ++j) {
		drawBitmapAlpha(W_OFFSET, H_OFFSET + j * CELL_DIM, double_wall_left, CELL_DIM, CELL_DIM, color);
		drawBitmapAlpha(W_OFFSET + 27 * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_right, CELL_DIM, CELL_DIM, color);
	}
	for (int j = 20; j <= 29; ++j) {
		if (j != 24 && j != 25) {
			drawBitmapAlpha(W_OFFSET, H_OFFSET + j * CELL_DIM, double_wall_left, CELL_DIM, CELL_DIM, color);
			drawBitmapAlpha(W_OFFSET + 27 * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_right, CELL_DIM, CELL_DIM, color);
		}
	}
	
	// Middle height walls
	for (int i = 1; i <= 4; ++i) {
		for (int j = 9; j <= 15; j += 6) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_down, CELL_DIM, CELL_DIM, color);
		}
		for (int j = 13; j <= 19; j += 6) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_up, CELL_DIM, CELL_DIM, color);
		}
	}
	
	// Middle height walls
	for (int i = 23; i <= 26; ++i) {
		for (int j = 9; j <= 15; j += 6) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_down, CELL_DIM, CELL_DIM, color);
		}
		for (int j = 13; j <= 19; j += 6) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_up, CELL_DIM, CELL_DIM, color);
		}
	}
	for (int j = 10; j <= 12; j++) {
		drawBitmapAlpha(W_OFFSET + 5 * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_left, CELL_DIM, CELL_DIM, color);
		drawBitmapAlpha(W_OFFSET + 22 * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_right, CELL_DIM, CELL_DIM, color);
	}
	for (int j = 16; j <= 18; j++) {
		drawBitmapAlpha(W_OFFSET + 5 * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_left, CELL_DIM, CELL_DIM, color);
		drawBitmapAlpha(W_OFFSET + 22 * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_right, CELL_DIM, CELL_DIM, color);
	}
	for (int i = 0; i <= 27; i += 27) {
		drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + 13 * CELL_DIM, double_wall_up, CELL_DIM, CELL_DIM, color);
		drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + 15 * CELL_DIM, double_wall_down, CELL_DIM, CELL_DIM, color);
	}
	drawBitmapAlpha(W_OFFSET, H_OFFSET + 9 * CELL_DIM, corner_left_down, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET, H_OFFSET + 19 * CELL_DIM, corner_left_up, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 27 * CELL_DIM, H_OFFSET + 9 * CELL_DIM, corner_right_down, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 27 * CELL_DIM, H_OFFSET + 19 * CELL_DIM, corner_right_up, CELL_DIM, CELL_DIM, color);
	// Center box
	for (int i = 11; i <= 16; ++i) {
		drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + 16 * CELL_DIM, double_wall_up, CELL_DIM, CELL_DIM, color);
	}
	for (int i = 11; i <= 16; i += 5) {
		drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + 12 * CELL_DIM, double_wall_down, CELL_DIM, CELL_DIM, color);
	}
	for (int j = 13; j <= 15; ++j) {
		drawBitmapAlpha(W_OFFSET + 10 * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_right, CELL_DIM, CELL_DIM, color);
		drawBitmapAlpha(W_OFFSET + 17 * CELL_DIM, H_OFFSET + j * CELL_DIM, double_wall_left, CELL_DIM, CELL_DIM, color);
	}
	drawBitmapAlpha(W_OFFSET + 10 * CELL_DIM, H_OFFSET + 16 * CELL_DIM, double_corner_left_down, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 10 * CELL_DIM, H_OFFSET + 12 * CELL_DIM, double_corner_left_up, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 17 * CELL_DIM, H_OFFSET + 16 * CELL_DIM, double_corner_right_down, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 17 * CELL_DIM, H_OFFSET + 12 * CELL_DIM, double_corner_right_up, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 12 * CELL_DIM, H_OFFSET + 12 * CELL_DIM, double_end_left, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 15 * CELL_DIM, H_OFFSET + 12 * CELL_DIM, double_end_right, CELL_DIM, CELL_DIM, color);
	
	// Walls corners
	for (int j = 9; j <= 15; j += 6) {
		drawBitmapAlpha(W_OFFSET + 5 * CELL_DIM, H_OFFSET + j * CELL_DIM, simple_right_up_corner, CELL_DIM, CELL_DIM, color);
	}
	for (int j = 13; j <= 19; j += 6) {
		drawBitmapAlpha(W_OFFSET + 5 * CELL_DIM, H_OFFSET + j * CELL_DIM, simple_right_down_corner, CELL_DIM, CELL_DIM, color);
	}
	for (int j = 9; j <= 15; j += 6) {
		drawBitmapAlpha(W_OFFSET + 22 * CELL_DIM, H_OFFSET + j * CELL_DIM, simple_left_up_corner, CELL_DIM, CELL_DIM, color);
	}
	for (int j = 13; j <= 19; j += 6) {
		drawBitmapAlpha(W_OFFSET + 22 * CELL_DIM, H_OFFSET + j * CELL_DIM, simple_left_down_corner, CELL_DIM, CELL_DIM, color);
	}
	
	// Maze
	drawBitmapAlpha(W_OFFSET, H_OFFSET + 24 * CELL_DIM, left_lab_part, 3 * CELL_DIM, 2 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 25 * CELL_DIM, H_OFFSET + 24 * CELL_DIM, right_lab_part, 3 * CELL_DIM, 2 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 7 * CELL_DIM, H_OFFSET + 21 * CELL_DIM, h_maze, 5 * CELL_DIM, 2 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 16 * CELL_DIM, H_OFFSET + 21 * CELL_DIM, h_maze, 5 * CELL_DIM, 2 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 13 * CELL_DIM, H_OFFSET + 0 * CELL_DIM, maze_part1, 2 * CELL_DIM, 5 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 7 * CELL_DIM, H_OFFSET + 2 * CELL_DIM, h_maze2, 5 * CELL_DIM, 3 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 16 * CELL_DIM, H_OFFSET + 2 * CELL_DIM, h_maze2, 5 * CELL_DIM, 3 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 2 * CELL_DIM, H_OFFSET + 2 * CELL_DIM, h_maze3, 4 * CELL_DIM, 3 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 22 * CELL_DIM, H_OFFSET + 2 * CELL_DIM, h_maze3, 4 * CELL_DIM, 3 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 2 * CELL_DIM, H_OFFSET + 6 * CELL_DIM, h_maze4, 4 * CELL_DIM, 2 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 22 * CELL_DIM, H_OFFSET + 6 * CELL_DIM, h_maze4, 4 * CELL_DIM, 2 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 7 * CELL_DIM, H_OFFSET + 15 * CELL_DIM, v_maze1, 2 * CELL_DIM, 5 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 19 * CELL_DIM, H_OFFSET + 15 * CELL_DIM, v_maze1, 2 * CELL_DIM, 5 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 13 * CELL_DIM, H_OFFSET + 6 * CELL_DIM, v_maze_part1, 2 * CELL_DIM, 5 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 13 * CELL_DIM, H_OFFSET + 18 * CELL_DIM, v_maze_part1, 2 * CELL_DIM, 5 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 13 * CELL_DIM, H_OFFSET + 24 * CELL_DIM, v_maze_part1, 2 * CELL_DIM, 5 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 7 * CELL_DIM, H_OFFSET + 24 * CELL_DIM, v_maze_part2, 2 * CELL_DIM, 5 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 19 * CELL_DIM, H_OFFSET + 24 * CELL_DIM, v_maze_part2, 2 * CELL_DIM, 5 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 7 * CELL_DIM, H_OFFSET + 6 * CELL_DIM, v_maze_part3, 2 * CELL_DIM, 3 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 19 * CELL_DIM, H_OFFSET + 6 * CELL_DIM, v_maze_part3, 2 * CELL_DIM, 3 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 7 * CELL_DIM, H_OFFSET + 11 * CELL_DIM, v_maze_part4, 2 * CELL_DIM, 3 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 19 * CELL_DIM, H_OFFSET + 11 * CELL_DIM, v_maze_part4, 2 * CELL_DIM, 3 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 9 * CELL_DIM, H_OFFSET + 27 * CELL_DIM, v_maze_part5, 3 * CELL_DIM, 2 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 16 * CELL_DIM, H_OFFSET + 27 * CELL_DIM, v_maze_part6, 3 * CELL_DIM, 2 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 10 * CELL_DIM, H_OFFSET + 6 * CELL_DIM, v_maze_part6, 3 * CELL_DIM, 2 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 15 * CELL_DIM, H_OFFSET + 6 * CELL_DIM, v_maze_part5, 3 * CELL_DIM, 2 * CELL_DIM, color);

	drawBitmapAlpha(W_OFFSET + 10 * CELL_DIM, H_OFFSET + 24 * CELL_DIM, v_maze_part6, 3 * CELL_DIM, 2 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 15 * CELL_DIM, H_OFFSET + 24 * CELL_DIM, v_maze_part5, 3 * CELL_DIM, 2 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 10 * CELL_DIM, H_OFFSET + 18 * CELL_DIM, v_maze_part6, 3 * CELL_DIM, 2 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 15 * CELL_DIM, H_OFFSET + 18 * CELL_DIM, v_maze_part5, 3 * CELL_DIM, 2 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 2 * CELL_DIM, H_OFFSET + 27 * CELL_DIM, v_maze_part7, 5 * CELL_DIM, 2 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 21 * CELL_DIM, H_OFFSET + 27 * CELL_DIM, v_maze_part8, 5 * CELL_DIM, 2 * CELL_DIM, color);

	drawBitmapAlpha(W_OFFSET + 7 * CELL_DIM, H_OFFSET + 9 * CELL_DIM, v_maze_part9, 5 * CELL_DIM, 2 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 16 * CELL_DIM, H_OFFSET + 9 * CELL_DIM, v_maze_part10, 5 * CELL_DIM, 2 * CELL_DIM, color);
	
	drawBitmapAlpha(W_OFFSET + 2 * CELL_DIM, H_OFFSET + 21 * CELL_DIM, v_maze_part13, 2 * CELL_DIM, 2 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 24 * CELL_DIM, H_OFFSET + 21 * CELL_DIM, v_maze_part14, 2 * CELL_DIM, 2 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 4 * CELL_DIM, H_OFFSET + 21 * CELL_DIM, v_maze_part11, 2 * CELL_DIM, 5 * CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 22 * CELL_DIM, H_OFFSET + 21 * CELL_DIM, v_maze_part12, 2 * CELL_DIM, 5 * CELL_DIM, color);
}

void draw_dots(uint16_t color)
{
	for (int i = 1; i <= 26; i++) {
		drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + 5 * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + 29 * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		if (i != 13 && i != 14) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + 1 * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + 20 * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
		if (i != 6 && i != 7 && i != 8 && i != 13  && i != 14 && i != 19 && i != 20 && i != 21) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + 8 * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + 26 * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
	}
	for (int j = 2; j <= 26; j++) {
		if (j != 5 && j != 20) {
			drawBitmapAlpha(W_OFFSET + 6 * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
			drawBitmapAlpha(W_OFFSET + 21 * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
	}
	for (int i = 1; i <= 12 ; i += 11) {
		for (int j = 27; j <= 28; j++) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
	}
	for (int i = 15; i <= 26 ; i += 11) {
		for (int j = 27; j <= 28; j++) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
	}
	for (int i = 3; i <= 9 ; i += 6) {
		for (int j = 24; j <= 25; j++) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
	}
	for (int i = 18; i <= 24; i += 6) {
		for (int j = 24; j <= 25; j++) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
	}
	for (int i = 1; i <= 12; i += 11) {
		for (int j = 21; j <= 22; j++) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
	}
	
	for (int i = 15; i <= 29; i += 11) {
		for (int j = 21; j <= 22; j++) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
	}
	for (int i = 2; i <= 25; i++) {
		if (i != 4 && i != 5 && i != 13 && i != 14 && i != 22 && i != 23) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + 23 * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
	}
	for (int j = 2; j <= 4; j += 2) {
		drawBitmapAlpha(W_OFFSET + 1 * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		drawBitmapAlpha(W_OFFSET + 12 * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		drawBitmapAlpha(W_OFFSET + 15 * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		drawBitmapAlpha(W_OFFSET + 26 * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
	}
	drawBitmapAlpha(W_OFFSET + 12 * CELL_DIM, H_OFFSET + 3 * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 15 * CELL_DIM, H_OFFSET + 3 * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
	
	for (int i = 1; i <= 9; i += 8) {
		for (int j = 6; j <= 7; j++) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
	}
	for (int i = 18; i <= 26; i += 8) {
		for (int j = 6; j <= 7; j++) {
			drawBitmapAlpha(W_OFFSET + i * CELL_DIM, H_OFFSET + j * CELL_DIM, dot, CELL_DIM, CELL_DIM, color);
		}
	}
}