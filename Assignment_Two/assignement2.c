/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h>	// standard C definitions
#include <stdbool.h>	// bool C99
#include "MCB2300 evaluationboard.h"	// hardware related functions

/*** Globals ***/
extern bool printLapTime;
int t0, t1, t2, t3; // timers testing
int state; // state | RESET, RUNNING, STOP
int lapFlag;
bool print;


/*** print to the lcd, just for timers testing***/
void printLCD() {
	// t0 = 0;
	// t1 = 0;
	// t2 = 0;
	// t3 = 0;
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

/*** print text to lcd ***/
void printLCDText(char const *string1, char const *string2, int mode) {
	char textFirst[17]; // declaration of array of 17 characters
	char textSecond[17]; // declaration of array of 17 characters

	// mode | 0 = both, 1 = up, 2 = bottom
	if ((mode == 0) || (mode == 1)) {
		sprintf(textFirst, string1); // buf is filled
		set_cursor(0, 0); // cursor position is moved to the upper line
		lcd_print(textFirst); // the text is written to the Lcd-module
	}

	if ((mode == 0) || (mode == 2)) {
		sprintf(textSecond, string2); // buf is filled
		set_cursor(0, 1); // cursor position is moved to the lower line
		lcd_print(textSecond); // the text is written to the Lcd-module
	}
}

/*** Print lap time ***/
void printLap() {
	char *string1 = "";
	char *string2 = "LAP: 00:00:00:00";
	printLCDText(string1, string2, 2);
	lapFlag = 0; // reset the flag
}

/*** Reset State ***/
void reset() {
	if (print) { // print only once
		lcd_clear();
		char *string1 = "T  : 00:00:00:00";
		char *string2 = "Press to start";
		printLCDText(string1, string2, 1);
		print = false;
	}
}

/*** Runnging State ***/
void running() {
	char *string1 = "T  : 00:00:00:01";
	char *string2 = "STATE";
	printLCDText(string1, string2, 1);
	if (lapFlag) // button is pressed
		printLap();
}

/*** Stop State ***/
void stop() {
	if (!print) { // print only once
		lcd_clear();
		char *string1 = "T  : 00:00:00:02";
		char *string2 = "";
		printLCDText(string1, string2, 1);
		print = true;
	}
}

/*** Initialize all the variables on reset of the device ***/
void initVar() {
	state = RESET;
	print = true;
	lapFlag = 0;
}


/*** Main code ***/
int main(void) {
	initEvaluationBoard();	// init the hardware
	initEINT0();	// init the button interrupt
	init_T0();	// init timer0 interrupt
	init_T1();	// init timer1 interrupt
	init_T2();	// init timer2 interrupt
	init_T3();	// init timer3 interrupt
	initVar();	// init program variables

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
