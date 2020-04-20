/*
 * sound.c
 *
 * Created: 6/20/2019 10:27:21 AM
 *  Author: Florin
 */ 

#include "sound.h"
#include "resources.h"
#include <avr/io.h>
#include <util/delay.h>


// Different delays for tones
const double delay_beginning_tone = 110;
const double delay_other_tones = 50;

// Number of the note in the tone
int note_num = 0;
// Duration of playing  the note
int dur = 0;

void speaker_init()
{
	// Speaker output
	DDRD |= (1 << PD6);
}

// Update tone function
int update_tone(const uint16_t frequencies[], const uint16_t durations[], uint8_t num_notes)
{
	dur -= 25;
	if (dur < 25) {
		uint16_t note = pgm_read_word(&frequencies[note_num]);
		if (note < 4) {
			DDRD &= ~(1 << PD6);
		} else {
			DDRD |= (1 << PD6);
		}
		OCR2A = 255 / note;
		OCR2B = OCR2A / 2;
		TCNT2 = 0;
		dur = pgm_read_word(&durations[note_num]);
		note_num = (note_num + 1) % num_notes;
		
	}
	return note_num;
}

// Function that plays a tone
void play_tone(const uint16_t frequencies[], const uint16_t durations[], uint8_t num_notes, uint8_t tone) {
	dur = 0;
	note_num = 0;
	OCR1A = 0xFFFF;
	while(1)
	{
		if (update_tone(frequencies, durations, num_notes) == num_notes - 1) break;
		if (tone == BEGINNING_TONE) {
			_delay_ms(delay_beginning_tone);
			} else {
			_delay_ms(delay_other_tones);
		}
	}
	OCR1A = 0;
	_delay_ms(1000);
}

void timer2_init()
{
	TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22) | (1 << WGM22); 
	TIMSK2 |= (1 << OCIE2A);
	TCCR2A |= (1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
}

