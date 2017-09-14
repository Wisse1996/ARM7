/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h>	// standard C definitions
#include <stdbool.h>	// bool C99
#include "MCB2300 evaluationboard.h"	// hardware related functions

/*** Globals ***/
extern int t0,t1,t2,t3;

/*** Reset State ***/
void reset() {
	// reset timers
	// print 00:00:00:00
}

/*** Runnging State ***/
void running() {
	// timers running
	// print time
}

/*** Stop State ***/
void stop() {
	// show time
}

/*** Print lap time ***/
void printLap() {
	// print lap 
}

/*** Main code ***/
int main(void) {
	initEvaluationBoard();	// init the hardware
	initEINT0();	// init the button interrupt
	init_T0();	// init timer0 interrupt
	init_T1();	// init timer1 interrupt
	init_T2();	// init timer2 interrupt
	init_T3();	// init timer3 interrupt

	char textFirst[17]; // declaration of array of 17 characters
	char textSecond[17]; // declaration of array of 17 characters

	// extern var code test
	while (1) {
		sprintf(textFirst,"t0: %d t1: %d", t0, t1); // buf is filled
		set_cursor(0, 0); // cursor position is moved to the upper line
		lcd_print(textFirst); // the text is written to the Lcd-module

		sprintf(textSecond,"t2: %d t3: %d", t2, t3); // buf is filled
		set_cursor(0, 1); // cursor position is moved to the lower line
		lcd_print(textSecond); // the text is written to the Lcd-module
	}
}
