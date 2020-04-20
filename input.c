/*
 * input.c
 *
 * Created: 6/20/2019 11:24:08 PM
 *  Author: Florin
 */ 
#include "input.h"
#include "game.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int8_t button_ports[NUM_BTN] = { PA0, PA1, PA2, PA3, PA4, PA5 };
int8_t button_state = -1;
int8_t button_type = -1;

extern uint8_t pacman_ante_dir;
extern uint8_t pacman_dir;

/*
 * Change the position of the pac-man only at the release of the button
 */
void process_input(void) {
	if ((PINA & (1 << button_ports[DOWN_BUTTON])) == 0) {
		//button_state = 0;
		//button_type = DOWN_BUTTON;
		update_pacman_state(DOWN);
	} else if ((PINA & (1 << button_ports[UP_BUTTON])) == 0) {
		//button_state = 0;
		//button_type = UP_BUTTON;
		update_pacman_state(UP);
	} else if ((PINA & (1 << button_ports[LEFT_BUTTON])) == 0) {
		//button_state = 0;
		//button_type = LEFT_BUTTON;
		update_pacman_state(LEFT);
	} else if ((PINA & (1 << button_ports[RIGHT_BUTTON])) == 0) {
		//button_state = 0;
		//button_type = RIGHT_BUTTON;
		update_pacman_state(RIGHT);
	} else if ((PINA & (1 << button_ports[OK_BUTTON])) == 0) {
		//button_state = 0;
		//button_type = OK_BUTTON;
	} else if ((PINA & (1 << button_ports[BACK_BUTTON])) == 0) {
		//button_state = 0;
		//button_type = BACK_BUTTON;
	}/* else if (!button_state) {
		//button_state = 1;
	} else {
		button_state = -1;
		button_type = -1;
	}*/

	/*if (button_state == 1) {
		switch (button_type) {
			case DOWN_BUTTON:
				update_pacman_state(DOWN);
				break;
			case UP_BUTTON:
				update_pacman_state(UP);
				break;
			case LEFT_BUTTON:
				update_pacman_state(LEFT);
				break;
			case RIGHT_BUTTON:
				update_pacman_state(RIGHT);
				break;
			case OK_BUTTON:
				break;
			case BACK_BUTTON:
				break;
		}
	}*/
}



void timer0_init()
{
	OCR0A = 240;
	TIMSK0 = (1 << OCIE0A);
	TCCR0B |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	TCCR0A |= (1 << WGM01);
}

void buttons_init()
{
	// Buttons input + pull-up resistor
	PORTA = 0;
	for (int i = 0; i < NUM_BTN; ++i) {
		DDRA &= ~(1 << button_ports[i]);
		PORTA |= (1 << button_ports[i]);
	}
}