/*
 * sound.h
 *
 * Created: 6/20/2019 10:27:36 AM
 *  Author: Florin
 */ 


#ifndef SOUND_H_
#define SOUND_H_

#include <avr/io.h>
#include <util/delay.h>

// Identification of tones by an integer
#define BEGINNING_TONE 0
#define EATFRUIT_TONE 1
#define EATGHOST_TONE 2
#define CHOMP_TONE 3
#define DEATH_TONE 4

// Number of notes in the death tone
#define num_notes_d 29
// Number of notes in the chomp tone
#define num_notes_c 29
// Number of notes in the eat ghost tone
#define num_notes_g 18
// Number of notes in the eat fruit tone
#define num_notes_f 16
// Number of notes in the beginning tone
#define num_notes_b 64

void speaker_init();
void timer2_init();
int update_tone(const uint16_t frequencies[], const uint16_t durations[], uint8_t num_notes);
void play_tone(const uint16_t frequencies[], const uint16_t durations[], uint8_t num_notes, uint8_t tone);





#endif /* SOUND_H_ */