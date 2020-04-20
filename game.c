/*
 * pacman.c
 *
 * Created: 5/19/2019 10:50:33 AM
 * Author : Florin
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "resources.h"
#include "ili9341.h"
#include "ili9341gfx.h"
#include "graphics.h"
#include "sound.h"
#include "game.h"
#include "input.h"

uint8_t lives = MAX_LIVES;

/* Pac-man character state variables */
uint16_t pacman_cell_x = PACMAN_INIT_CELL_X;
uint16_t pacman_cell_y = PACMAN_INIT_CELL_Y;
int16_t pacman_state = LEFT;
int16_t pacman_center_x = PACMAN_INIT_X + CHAR_C_OFF;
int16_t pacman_center_y = PACMAN_INIT_Y + CHAR_C_OFF;
int16_t pacman_frame = 0;

/* State variable for the big four dots on the map */
uint8_t big_dot_gfx_state = 0;



uint8_t redghost_x = RED_GHOST_INIT_X;
uint8_t redghost_y = RED_GHOST_INIT_Y;
uint8_t cyanghost_x = CYAN_GHOST_INIT_X;
uint8_t cyanghost_y = CYAN_GHOST_INIT_Y;
uint8_t magentaghost_x = MAGENTA_GHOST_INIT_X;
uint8_t magentaghost_y = MAGENTA_GHOST_INIT_Y;
uint8_t brownghost_x = BROWN_GHOST_INIT_X;
uint8_t brownghost_y = BROWN_GHOST_INIT_Y;

uint8_t red_state = FRAME1;
uint8_t magenta_state = FRAME1;
uint8_t cyan_state = FRAME1;
uint8_t brown_state = FRAME1;

void timer1_init();

void draw_ghosts(void) {
	if (red_state == FRAME1) {
		drawRGBBitmap(redghost_x, redghost_y, red_ghost1, GHOST_SIZE, GHOST_SIZE);
		red_state = FRAME2;
	} else if (red_state == FRAME2) {
		drawRGBBitmap(redghost_x, redghost_y, red_ghost2, GHOST_SIZE, GHOST_SIZE);
		red_state = FRAME1;
	}

	if (cyan_state == FRAME1) {
		drawRGBBitmap(cyanghost_x, cyanghost_y, cyan_ghost1, GHOST_SIZE, GHOST_SIZE);
		cyan_state = FRAME2;
	} else if (cyan_state == FRAME2) {
		drawRGBBitmap(cyanghost_x, cyanghost_y, cyan_ghost2, GHOST_SIZE, GHOST_SIZE);
		cyan_state = FRAME1;
	}
	
	if (magenta_state == FRAME1) {
		drawRGBBitmap(magentaghost_x, magentaghost_y, mag_ghost1, GHOST_SIZE, GHOST_SIZE);
		magenta_state = FRAME2;
	} else if (magenta_state == FRAME2) {
		drawRGBBitmap(magentaghost_x, magentaghost_y, mag_ghost2, GHOST_SIZE, GHOST_SIZE);
		magenta_state = FRAME1;
	}
	
	if (brown_state == FRAME1) {
		drawRGBBitmap(brownghost_x, brownghost_y, brown_ghost1, GHOST_SIZE, GHOST_SIZE);
		brown_state = FRAME2;
	} else if (brown_state == FRAME2) {
		drawRGBBitmap(brownghost_x, brownghost_y, brown_ghost2, GHOST_SIZE, GHOST_SIZE);
		brown_state = FRAME1;
	}
}

// Function used to draw the game animations

void animate_big_dots() {
	uint16_t color;
	if (big_dot_gfx_state == 0) {
		color = ROSE;
	} else {
		color = BLACK;
	}
	drawBitmapAlpha(W_OFFSET + 1 * CELL_DIM, H_OFFSET + 3 * CELL_DIM, big_dot, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 1 * CELL_DIM, H_OFFSET + 23 * CELL_DIM, big_dot, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 26 * CELL_DIM, H_OFFSET + 3 * CELL_DIM, big_dot, CELL_DIM, CELL_DIM, color);
	drawBitmapAlpha(W_OFFSET + 26 * CELL_DIM, H_OFFSET + 23 * CELL_DIM, big_dot, CELL_DIM, CELL_DIM, color);
	big_dot_gfx_state = (big_dot_gfx_state + 1) % 2;
}

void update_pacman_state(uint8_t state) 
{
	/************************************************************************/
	/* MATRIX USED TO CHECK IF PAC-MAN AND GHOSTS ARE IN A VALID POSITION   */
	/************************************************************************/
	uint8_t map[31][28] = {
		//       0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
		/*0*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		/*1*/   {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		/*2*/	{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
		/*3*/	{0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0},
		/*4*/	{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
		/*5*/	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		/*6*/	{0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
		/*7*/	{0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
		/*8*/	{0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
		/*9*/	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		/*10*/	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		/*11*/	{0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		/*12*/	{0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		/*13*/	{0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		/*14*/	{3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3},
		/*15*/	{0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		/*16*/	{0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		/*17*/	{0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		/*18*/	{0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		/*19*/	{0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		/*20*/	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		/*21*/	{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
		/*22*/	{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
		/*23*/	{0, 2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 2, 0},
		/*24*/	{0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
		/*25*/	{0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
		/*26*/	{0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
		/*27*/	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		/*28*/	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		/*29*/	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		/*30*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};

	
	// Check matrix for changing direction
	switch (state) {
		case DOWN:
			if (map[pacman_cell_x][pacman_cell_y + 1] != 0) {
				pacman_state = state;
			}
			break;
		case UP:
			if (map[pacman_cell_x][pacman_cell_y - 1] != 0) {
				pacman_state = state;
			}
			break;
		case LEFT:
			if (map[pacman_cell_x - 1][pacman_cell_y] != 0) {
				pacman_state = state;
			}
			break;
		case RIGHT:
			if (map[pacman_cell_x + 1][pacman_cell_y] != 0) {
				pacman_state = state;
			}
			break;		
	}
}

void update_pacman_cell()
{
	pacman_cell_x = (pacman_center_x - W_OFFSET) / CELL_DIM; 	
	pacman_cell_y = (pacman_center_y - H_OFFSET) / CELL_DIM;
}

void animate_pacman()
{
	switch (pacman_state) {
		case FULL:
			drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_full, PACMAN_DIM, PACMAN_DIM, YELLOW);
			break;
		case LEFT:
			if (pacman_frame == 0) {
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_eraser_left1, PACMAN_DIM, PACMAN_DIM, BLACK);
				pacman_center_x -= PACMAN_SPEED;
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_left1, PACMAN_DIM, PACMAN_DIM, YELLOW);
			} else {
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_eraser_left2, PACMAN_DIM, PACMAN_DIM, BLACK);
				pacman_center_x -= PACMAN_SPEED;
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_left2, PACMAN_DIM, PACMAN_DIM, YELLOW);
			}
			break;
		case RIGHT:
			if (pacman_frame == 0) {
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_eraser_right1, PACMAN_DIM, PACMAN_DIM, BLACK);
				pacman_center_x += PACMAN_SPEED;
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_right1, PACMAN_DIM, PACMAN_DIM, YELLOW);
				} else {
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_eraser_right2, PACMAN_DIM, PACMAN_DIM, BLACK);
				pacman_center_x += PACMAN_SPEED;
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_right2, PACMAN_DIM, PACMAN_DIM, YELLOW);
			}
			break;	
		case DOWN:
			if (pacman_frame == 0) {
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_eraser_down1, PACMAN_DIM, PACMAN_DIM, BLACK);
				pacman_center_y += PACMAN_SPEED;
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_down1, PACMAN_DIM, PACMAN_DIM, YELLOW);
				} else {
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_eraser_down2, PACMAN_DIM, PACMAN_DIM, BLACK);
				pacman_center_y += PACMAN_SPEED;
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_down2, PACMAN_DIM, PACMAN_DIM, YELLOW);
			}
			break;
		case UP:
			if (pacman_frame == 0) {
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_eraser_up1, PACMAN_DIM, PACMAN_DIM, BLACK);
				pacman_center_y -= PACMAN_SPEED;
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_up1, PACMAN_DIM, PACMAN_DIM, YELLOW);
				} else {
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_eraser_up2, PACMAN_DIM, PACMAN_DIM, BLACK);
				pacman_center_y -= PACMAN_SPEED;
				drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_up2, PACMAN_DIM, PACMAN_DIM, YELLOW);
			}
			break;	
		default:	
			drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_full, PACMAN_DIM, PACMAN_DIM, YELLOW);
	}
	pacman_frame = (pacman_frame + 1) % 2; 
}

/* Initialize a game by drawing the pac-man, the 'READY!' message and the ghosts */
void setup_game() {
	drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_full, PACMAN_DIM, PACMAN_DIM, YELLOW);
}

/*void draw_animations() {	
	
	_delay_ms(1000);
	if (pacman_ante_dir != pacman_dir) {
		drawBitmapAlpha(pacman_x, pacman_y, pacman_full, PACMAN_DIM, PACMAN_DIM, BLACK);
		pacman_ante_dir = pacman_dir;
	}
	// Draw pac-man character and ghosts
	switch (pacman_dir) {
		case UP:
			// Draw ghosts
			draw_ghosts();
			_delay_ms(500);
			draw_ghosts();
			drawBitmapAlpha(pacman_x, pacman_y, pacman_eraser_up, PACMAN_DIM, PACMAN_DIM, BLACK);
			drawBitmapAlpha(pacman_x, pacman_y, pacman_up1, PACMAN_DIM, PACMAN_DIM, YELLOW);
			_delay_ms(1000);
			// Draw ghosts
			draw_ghosts();
			_delay_ms(500);
			draw_ghosts();
			drawBitmapAlpha(pacman_x, pacman_y, pacman_up2, PACMAN_DIM, PACMAN_DIM, YELLOW);
			_delay_ms(1000);
			break;
		case DOWN:
			//drawBitmapAlpha(old_pacman_x, old_pacman_y, pacman_full, PACMAN_DIM, PACMAN_DIM, BLACK);
			//_delay_ms(500);
			// Draw ghost
			draw_ghosts();
			_delay_ms(500);
			draw_ghosts();
			drawBitmapAlpha(pacman_x, pacman_y, pacman_eraser_down, PACMAN_DIM, PACMAN_DIM, BLACK);
			drawBitmapAlpha(pacman_x, pacman_y, pacman_down1, PACMAN_DIM, PACMAN_DIM, YELLOW);
			_delay_ms(1000);
			// Draw ghost
			draw_ghosts();
			_delay_ms(500);
			draw_ghosts();
			drawBitmapAlpha(pacman_x, pacman_y, pacman_down2, PACMAN_DIM, PACMAN_DIM, YELLOW);
			_delay_ms(1000);
			break;
		case LEFT:
			// Draw ghost
			draw_ghosts();
			_delay_ms(500);
			draw_ghosts();
			drawBitmapAlpha(pacman_x, pacman_y, pacman_eraser_left, PACMAN_DIM, PACMAN_DIM, BLACK);
			drawBitmapAlpha(pacman_x, pacman_y, pacman_left1, PACMAN_DIM, PACMAN_DIM, YELLOW);
			_delay_ms(1000);
			// Draw ghost
			draw_ghosts();
			_delay_ms(500);
			draw_ghosts();
			drawBitmapAlpha(pacman_x, pacman_y, pacman_left2, PACMAN_DIM, PACMAN_DIM, YELLOW);
			_delay_ms(1000);
			break;
		case RIGHT:
			// Draw ghost
			draw_ghosts();
			_delay_ms(500);
			draw_ghosts();
			drawBitmapAlpha(pacman_x, pacman_y, pacman_eraser_right, PACMAN_DIM, PACMAN_DIM, BLACK);
			drawBitmapAlpha(pacman_x, pacman_y, pacman_right1, PACMAN_DIM, PACMAN_DIM, YELLOW);
			_delay_ms(1000);
			// Draw ghost
			draw_ghosts();
			_delay_ms(500);
			draw_ghosts();
			drawBitmapAlpha(pacman_x, pacman_y, pacman_right2, PACMAN_DIM, PACMAN_DIM, YELLOW);
			_delay_ms(1000);
			break;
		default:
			// Draw ghost
			draw_ghosts();
			_delay_ms(500);
			draw_ghosts();
			drawBitmapAlpha(pacman_x, pacman_y, pacman_eraser_left, PACMAN_DIM, PACMAN_DIM, BLACK);
			drawBitmapAlpha(pacman_x, pacman_y, pacman_left1, PACMAN_DIM, PACMAN_DIM, YELLOW);
			_delay_ms(1000);
			// Draw ghost
			draw_ghosts();
			_delay_ms(500);
			draw_ghosts();
			drawBitmapAlpha(pacman_x, pacman_y, pacman_left2, PACMAN_DIM, PACMAN_DIM, YELLOW);
			_delay_ms(1000);
	}
}*/

void life_lost(void) {
		lives--;
		// Draw game over on the screen
		if (lives == 0) {
			lives = MAX_LIVES;
		}
		drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_full, PACMAN_DIM, PACMAN_DIM, YELLOW);
		draw_walls(BLACK);
		draw_walls(WHITE);
		_delay_ms(25);
		draw_walls(BLACK);
		drawBitmapAlpha(pacman_center_x - CHAR_C_OFF, pacman_center_y - CHAR_C_OFF, pacman_full, PACMAN_DIM, PACMAN_DIM, BLACK);
		draw_walls(BLUE);
}

void draw_lives(void) {
	if (lives >= 1) { 
		drawBitmapAlpha(LIFE1_X, LIVES_Y, pacman_left1, PACMAN_DIM, PACMAN_DIM, YELLOW);
	}
	if (lives >= 2) {
		drawBitmapAlpha(LIFE2_X, LIVES_Y, pacman_left1, PACMAN_DIM, PACMAN_DIM, YELLOW);
	} 
	if (lives >= 3) {
		drawBitmapAlpha(LIFE3_X, LIVES_Y, pacman_left1, PACMAN_DIM, PACMAN_DIM, YELLOW);
	}
}

void update_lives(void) {
	if (lives == 2) {
		drawBitmapAlpha(LIFE3_X, LIVES_Y, pacman_left1, PACMAN_DIM, PACMAN_DIM, BLACK);
		return;
	}
	if (lives == 1) {
		drawBitmapAlpha(LIFE2_X, LIVES_Y, pacman_left1, PACMAN_DIM, PACMAN_DIM, BLACK);
		return;
	}
	if (lives == 0) {
		drawBitmapAlpha(LIFE1_X, LIVES_Y, pacman_left1, PACMAN_DIM, PACMAN_DIM, BLACK);
		return;
	}
}

void timer1_init(void) 
{
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);
	ICR1 = 1953;
	OCR1B = 1953;
	OCR1A = 1952;
}