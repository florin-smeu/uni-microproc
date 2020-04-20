/*
 * game.h
 *
 * Created: 6/20/2019 11:55:46 PM
 *  Author: Florin
 */ 


#ifndef GAME_H_
#define GAME_H_

#include "graphics.h"

// Character center offset
#define CHAR_C_OFF 9

// Pac-man states
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define FULL 4

// Initial cell position of pac-man 
#define PACMAN_INIT_CELL_X 14
#define PACMAN_INIT_CELL_Y 23

// Pac-man speed
#define PACMAN_SPEED 3

// Dimension of a pac-man
#define PACMAN_DIM 13

// Initial drawing points of pac-man (upper left corner)
#define PACMAN_INIT_X (W_OFFSET + 14 * CELL_DIM - 3)
#define PACMAN_INIT_Y (H_OFFSET + 23 * CELL_DIM - 3)

// Ghost size and constants
#define GHOST_SIZE 14
#define RED_GHOST_INIT_X (W_OFFSET + 13 * CELL_DIM + 2)
#define RED_GHOST_INIT_Y (H_OFFSET + 11 * CELL_DIM - 3)
#define CYAN_GHOST_INIT_X (W_OFFSET + 11 * CELL_DIM + 1)
#define CYAN_GHOST_INIT_Y (H_OFFSET + 14 * CELL_DIM - 3)
#define MAGENTA_GHOST_INIT_X (W_OFFSET + 13 * CELL_DIM + 1)
#define MAGENTA_GHOST_INIT_Y (H_OFFSET + 14 * CELL_DIM - 3)
#define BROWN_GHOST_INIT_X (W_OFFSET + 15 * CELL_DIM + 1)
#define BROWN_GHOST_INIT_Y (H_OFFSET + 14 * CELL_DIM - 3)

// States of the ghosts
#define FRAME1 0
#define FRAME2 1
#define VULN 2
#define DEAD 3


// The maximum number of lives
#define MAX_LIVES 3

// Lives positions
#define LIVES_Y (H_OFFSET + V_CELLS * CELL_DIM + 2)
#define LIFE1_X W_OFFSET
#define LIFE2_X W_OFFSET + PACMAN_DIM + 2
#define LIFE3_X W_OFFSET + 2 * PACMAN_DIM + 4

void timer1_init(void);
void animate_big_dots(void);
void update_pacman_state(uint8_t state);
void update_pacman_cell(void);
void animate_pacman(void);
void life_lost(void);
void draw_lives(void);
void update_lives(void);
void draw_animations(void);
void draw_ghosts(void);
void setup_game();

#endif /* GAME_H_ */