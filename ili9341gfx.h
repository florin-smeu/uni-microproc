#ifndef ILI9341GFX_H
#define ILI9341GFX_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include<stdio.h>
#include<stdbool.h>
#include<inttypes.h>

int16_t ili9341_putchar_printf(char var, FILE *stream);
void ili9341_drawchar(int16_t x, int16_t y, unsigned char c,uint16_t color, uint16_t bg, uint8_t size);
void ili9341_setcursor(uint16_t x,uint16_t y);
void ili9341_settextcolour(uint16_t x,uint16_t y);
void ili9341_settextsize(uint8_t s);
void ili9341_write(uint8_t c);
void backuplocationvset(void);
void backuplocationvactual(void);
void backuplocationiset(void);
void backuplocationiactual(void);
void display_init(void);


/**************************************************************************/
/*!
   @brief   Draw a PROGMEM-resident 16-bit image (RGB 5/6/5) at the specified (x,y) position.  
   For 16-bit display devices; no color reduction performed.
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with 16-bit color bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Height of bitmap in pixels
*/
void drawRGBBitmap(uint16_t x, uint16_t y, const uint16_t bitmap[], uint16_t w, uint16_t h);


/**************************************************************************/
/*!
   @brief      Draw a PROGMEM-resident 1-bit image at the specified (x,y) position,
    using the specified foreground (for set bits) and background (unset bits) colors.
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with monochrome bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Height of bitmap in pixels
    @param    color 16-bit 5-6-5 Color to draw pixels with
    @param    bg 16-bit 5-6-5 Color to draw background with
*/
/**************************************************************************/
void drawBitmap(uint16_t x, uint16_t y, const uint8_t bitmap[], uint16_t w, uint16_t h, uint16_t color, uint16_t bg);


/**************************************************************************/
/*!
   @brief      Draw a PROGMEM-resident 1-bit image at the specified (x,y) position, using the specified foreground color (unset bits are transparent).
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with monochrome bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Height of bitmap in pixels
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void drawBitmapAlpha(uint16_t x, uint16_t y, const uint8_t bitmap[], uint16_t w, uint16_t h, uint16_t color);


/**************************************************************************/
/*!
   @brief   Draw a PROGMEM-resident 16-bit image (RGB 5/6/5) with a 1-bit mask (set bits = opaque, unset bits = clear) at the specified (x,y) position. BOTH buffers (color and mask) must be PROGMEM-resident. For 16-bit display devices; no color reduction performed.
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with 16-bit color bitmap
    @param    mask  byte array with monochrome mask bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Height of bitmap in pixels
*/
/**************************************************************************/
void drawRGBBitmapAlpha(uint16_t x, uint16_t y, const uint16_t bitmap[], const uint8_t mask[], uint16_t w, uint16_t h);

#endif