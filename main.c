/*
 * main.c
 *
 * Created: 6/21/2019 12:15:26 AM
 *  Author: Florin
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

ISR(TIMER2_COMPA_vect)
{
	//update_tone(pacman_foo, foo_dur, 8);
	update_tone(pacman_beginning, beginning_dur, num_notes_b);
	//update_tone(pacman_chomp, chomp_dur, num_notes_c);
	//update_tone(pacman_death, death_dur, num_notes_d);
	//update_tone(pacman_eatfruit, eatfruit_dur, num_notes_f);
	//update_tone(pacman_eatghost, eatghost_dur, num_notes_g);
}

/*
 * Timer 0 interrupt for button checking.
 */
ISR(TIMER0_COMPA_vect) {
	process_input();
}

ISR(TIMER1_COMPA_vect) {
	animate_pacman();
}

ISR(TIMER1_COMPB_vect) {
	animate_big_dots();
}

// Pac-man position (in order to draw the image)
extern int16_t pacman_x;
extern int16_t pacman_y;

// The anterior frame position of the pac-man
extern int16_t old_pacman_x;
extern int16_t old_pacman_y;

extern uint8_t pacman_cell_x;
extern uint8_t pacman_cell_y;
extern uint8_t pacman_dir;
extern uint8_t pacman_ante_dir;
extern uint8_t pacman_dead;
extern uint8_t big_dot_gfx_state;
extern uint8_t pacman_gfx_state;

extern uint8_t redghost_x;
extern uint8_t redghost_y;
extern uint8_t cyanghost_x;
extern uint8_t magentaghost_x;
extern uint8_t magentaghost_y;
extern uint8_t brownghost_x;
extern uint8_t brownghost_y;

extern uint8_t red_state;
extern uint8_t magenta_state;
extern uint8_t cyan_state;
extern uint8_t brown_state;

void print_digit_to_char(uint16_t val) {
	switch (val) {
		case 0:
			ili9341_write('0');
			break;
		case 1:
			ili9341_write('1');
			break;
		case 2:
			ili9341_write('2');
			break;
		case 3:
			ili9341_write('3');
			break;
		case 4:
			ili9341_write('4');
			break;
		case 5:
			ili9341_write('5');
			break;
		case 6:
			ili9341_write('6');
			break;
		case 7:
			ili9341_write('7');
			break;
		case 8:
			ili9341_write('8');
			break;
		case 9:
			ili9341_write('9');
			break;
	}	
}

int main(void)
{
	//Initialize I/O
	buttons_init();
	speaker_init();
	
	// Activate interrupts
	sei();
	
	// Initial driver setup to drive ili9341
	ili9341_init();
	
	// Fill screen with black color
	ili9341_clear(BLACK);
	
	// Create map
	draw_dots(ROSE);
	draw_walls(BLUE);
	draw_lives();
	setup_game();
	
	// Initialize Timer 1
	timer0_init();
	timer1_init();
	timer2_init();
	/*
	drawBitmapAlpha(pacman_x, pacman_y, pacman_full, PACMAN_DIM, PACMAN_DIM, YELLOW);
	// Play a beginning tone
	//play_tone(pacman_beginning, beginning_dur, num_notes_b, BEGINNING_TONE);
	//_delay_ms(100);
	//play_tone(pacman_chomp, chomp_dur, num_notes_c, CHOMP_TONE);
	drawBitmapAlpha(pacman_x, pacman_y, pacman_full, PACMAN_DIM, PACMAN_DIM, BLACK);

	// Draw objects that need to be animated
	while(1) {
		if (pacman_dead == 1) {
			life_lost();
			update_lives();
			pacman_dead = 0;
		}
		
		old_pacman_x = pacman_x;
		old_pacman_y = pacman_y;
		if (pacman_cell_x == H_CELLS - 2 && pacman_cell_y == V_CELLS - 2 && pacman_dir != RIGHT && pacman_dir != DOWN) {
			goto keep_going;
		}
		if (pacman_cell_x == 1 && pacman_cell_y == V_CELLS - 2 && pacman_dir != LEFT && pacman_dir != DOWN) {
			goto keep_going;
		}
		if (pacman_cell_x == 1 && pacman_cell_y == 1 && pacman_dir != LEFT && pacman_dir != UP) {
			goto keep_going;
		}
		if (pacman_cell_x == H_CELLS - 2 && pacman_cell_y == 1 && pacman_dir != RIGHT && pacman_dir != UP) {
			goto keep_going;
		}
		
		if (pacman_cell_x == 1 && pacman_dir != LEFT) {
			goto keep_going;
		}
		if (pacman_cell_x == H_CELLS - 2 && pacman_dir != RIGHT) {
			goto keep_going;
		}
		if (pacman_cell_y == 1 && pacman_dir != UP) {
			goto keep_going;
		}
		if (pacman_cell_y == V_CELLS - 2 && pacman_dir != DOWN) {
			goto keep_going;
		}
		if (pacman_cell_x > 1 && pacman_cell_x < H_CELLS - 2 && pacman_cell_y > 1 && pacman_cell_y < V_CELLS - 2) {
			keep_going:
			if (pacman_dir == UP) {
				pacman_y -= PACMAN_SPEED;
				pacman_cell_y--;
				} else if (pacman_dir == DOWN) {
				pacman_y += PACMAN_SPEED;
				pacman_cell_y++;
				} else if (pacman_dir == LEFT) {
				pacman_x -= PACMAN_SPEED;
				pacman_cell_x--;
				} else if (pacman_dir == RIGHT) {
				pacman_x += PACMAN_SPEED;
				pacman_cell_x++;
			}
			drawBitmapAlpha(old_pacman_x, old_pacman_y, pacman_full, PACMAN_DIM, PACMAN_DIM, BLACK);
		}
		//draw_animations();
	}*/
	//while (1) {
		
	//}
	
	while(1)
	{
		update_pacman_cell();
		ili9341_settextcolour(CYAN,BLACK);
		ili9341_setcursor(10,10);
		ili9341_settextsize(3);
		print_digit_to_char(pacman_cell_x / 10);
		print_digit_to_char(pacman_cell_x % 10);
		ili9341_write('.');
		print_digit_to_char(pacman_cell_y / 10);
		print_digit_to_char(pacman_cell_y % 10);
		ili9341_write('.');
		
		//print_digit_to_char(pgm_read_byte(&map[11][9]));
	}
}