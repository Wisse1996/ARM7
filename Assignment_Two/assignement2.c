/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h>	// standard C definitions
#include <stdbool.h>	// bool C99
#include "MCB2300 evaluationboard.h"	// hardware related functions

/*** Globals ***/
extern int t0, t1, t2, t3;
int state;

/*** print to the lcd ***/
void printLCD() {
	char textFirst[17]; // declaration of array of 17 characters
	char textSecond[17]; // declaration of array of 17 characters
	// test
	// print timer0 and timer1 on the first line of the lcd
	sprintf(textFirst, "t0: %d t1: %d", t0, t1); // buf is filled
	set_cursor(0, 0); // cursor position is moved to the upper line
	lcd_print(textFirst); // the text is written to the Lcd-module

	// print timer2 and timer3 on the second line of the lcd
	sprintf(textSecond, "t2: %d t3: %d", t2, t3); // buf is filled
	set_cursor(0, 1); // cursor position is moved to the lower line
	lcd_print(textSecond); // the text is written to the Lcd-module
}


/*** Reset State ***/
void reset() {
	// reset timers
	// print 00:00:00:00

	// test
	t0 = 0;
	t1 = 0;
	t2 = 0;
	t3 = 0;
	//lcd_clear();
	printLCD();
}

/*** Runnging State ***/
void running() {
	// timers running
	// print time
	printLCD();
}

/*** Stop State ***/
void stop() {
	// show time
	printLCD();
}

/*** Print lap time ***/
void printLap() {
	// print lap
}

/*** Initialize all the variables on reset of the device ***/
void initVar() {
	state = RESET;
}


/*** Main code ***/
int main(void) {
	initEvaluationBoard();	// init the hardware
	initEINT0();	// init the button interrupt
	init_T0();	// init timer0 interrupt
	init_T1();	// init timer1 interrupt
	init_T2();	// init timer2 interrupt
	init_T3();	// init timer3 interrupt
	initVar();

	// loop indefinitely
	while (1) {
		switch (state) {
		case RESET:
			reset();
			break;
		case RUNNING:
			running();
			break;
		case STOP:
			stop();
			break;
		}
	}
}
