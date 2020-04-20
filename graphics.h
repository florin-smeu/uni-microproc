/*
 * draw.h
 *
 * Created: 6/19/2019 7:15:52 PM
 *  Author: Florin
 */ 


#ifndef DRAW_H_
#define DRAW_H_

#include <avr/io.h>
#include <util/delay.h>

// Dimensions of a cell on the map
#define CELL_DIM (uint16_t) 8
#define W_OFFSET (int16_t) 7
#define H_OFFSET (int16_t) 35
#define H_CELLS (int16_t) 28
#define V_CELLS (int16_t) 31

void draw_dots(uint16_t color);
void draw_walls(uint16_t color);

#endif /* DRAW_H_ */