/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h>	// standard C definitions
#include <stdbool.h>	// bool C99
#include "MCB2300 evaluationboard.h"	// hardware related functions
#include <LPC23xx.H>                        /* LPC23xx definitions */

#define A 3
#define D 4
#define E 1
#define F 0
#define G 2

// play with these numbers to get the right timing
#define TIME 1197505 
#define PAUSE 1850000

#define ONE ((TIME * 1) - 1) //   1500000 - 1 // duration of one time unit
#define TWO ((TIME * 2) - 1) // 3000000 - 1 // duration of two time units
#define THREE ((TIME * 3) - 1) // 4500000 - 1 // duration of three time units

#define nf 13            // number of bits of fractional part

#define TONES 5	// different values for a
#define NOTES 11	// number of notes in melody

/*** globals ***/
bool sineFlag = false;
bool timeFlag = false;
bool resetY = false;
bool enabled = true;
int freq[TONES];
int musicOrder[NOTES] = {A, G, F, E, D, D, D, D, D, D, D};
int time[NOTES] = {TWO, TWO, TWO, TWO, TWO,
                   TWO, TWO, TWO, THREE, ONE, ONE
                  };
char notes[NOTES] = {'A', 'G', 'F', 'E', 'D', 'D', 'D', 'D', 'D', 'D', 'D'};

//int a1 = (int) (1.987975 * (1 << nf) + 0.5);  // a1=16069 (real value=16069/2^13=1.96157)
int a2 = 1 << nf;         // a2=8192  (real value=8192/2^13=1)
double tones[TONES] = {1.9759, 1.98928, 1.98485, 1.98092, 1.99149}; // F4, E4, G4, A4, D4

/*** calculate the next sample ***/
int calculateOutput(int a1) {
	static int y_1 = 1 << (nf - 2);     // initial value of y1=8192 (real value=1)
	static int y_2 = 0;       // initial value of y2=0
	if (resetY) {
		resetY = false;
		y_1 = 1 << (nf - 2);
		y_2 = 0;
	}
	int y  = (a1 * y_1) - (a2 * y_2);    // calculation of new output sample
	y = y >> nf;         // shift nf bits to right
	y_2 = y_1;          // update old output-sample
	y_1 = y;          // update old output-sample
	return y;          // return new output sample
}

void initArray() {
	for (int i = 0; i < TONES; i++) {
		freq[i] = (int) (tones[i] * (1 << nf) + 0.5);
	}
}


/*** Main code ***/
int main(void) {
	initEvaluationBoard();	// init the hardware
	init_T0();	// init timer0 interrupt
	// pre init timer1
	T1MR0 = time[0];
	init_T1();	// init timer1 interrupt
	init_EINT0();	// init INT0 interrupt
	initArray();	// init the frequency array

	bool delay = true;
	bool toggle = true;
  
  int k = 0;

	// print the first note already
	set_cursor(0, 0);
	lcd_putchar(notes[k]);

	// infinite loop
	while (1) {

		// tone duration
		if (timeFlag) {
			timeFlag = false;
			if (delay) {
				T0TCR = 0;
				T1MR0 = PAUSE;
				delay = false;
			} else {
				delay = true;
				T0TCR = 1;
				resetY = true;
				if (k == (NOTES - 1)) {
					k = 0;
				} else {
					k++;
				}
				T1MR0 = time[k];
				set_cursor(0, 0);
				lcd_putchar(notes[k]);
			}
		}

		// sample timer @ 20kHz
		if (sineFlag) {
			if (enabled) {
				sineFlag = false;
				int value;
				value = calculateOutput(freq[musicOrder[k]]);
				value = value >> 6;
				value += 1000;
				value /= 2;

				DACR = ((value) << 6);
			} else {
				DACR = ((2) << 6);
			}
		}

		// print state ON/OFF
		if (enabled && toggle) {
			toggle = false; // do this one time
			set_cursor(0, 1);
			lcd_print("enabled   ");
		} else if (!enabled && !toggle) {
			toggle = true; // do this one time
			lcd_clear();
			set_cursor(0, 1);
			lcd_print("disabled   ");
		}

	}

}
