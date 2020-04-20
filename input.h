/*
 * IncFile1.h
 *
 * Created: 6/20/2019 11:23:52 PM
 *  Author: Florin
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Buttons constants
#define NUM_BTN 6
#define UP_BUTTON 2
#define DOWN_BUTTON 5
#define RIGHT_BUTTON 4
#define LEFT_BUTTON 3
#define OK_BUTTON 1
#define BACK_BUTTON 0

void process_input(void);
void timer0_init();
void buttons_init();



#endif /* INCFILE1_H_ */