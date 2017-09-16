/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h>	// standard C definitions
#include <stdbool.h>	// bool C99
#include "MCB2300 evaluationboard.h"	// hardware related functions

/*** Globals ***/
int t0, t1, t2, t3;
extern bool printLapTime;
int state; // state | RESET, RUNNING, STOP
int printLapCount;
bool print;


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

/*** print text to lcd ***/
void printLCDText(char const *string1, char const *string2) {
	char textFirst[17]; // declaration of array of 17 characters
	char textSecond[17]; // declaration of array of 17 characters

	sprintf(textFirst, string1); // buf is filled
	set_cursor(0, 0); // cursor position is moved to the upper line
	lcd_print(textFirst); // the text is written to the Lcd-module

	sprintf(textSecond, string2); // buf is filled
	set_cursor(0, 1); // cursor position is moved to the lower line
	lcd_print(textSecond); // the text is written to the Lcd-module
}

/*** Print lap time ***/
void printLap() {
	// print lap
	lcd_clear();
	char *string1 = "00:00:00:00";
	char *string2 = "LAPTIME!!!";
	printLCDText(string1, string2);
	for (int i = 0; i < 1000000; i++) { // testing

	}

	printLapCount = 0;
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
	// printLCD();
	if (print) {
		lcd_clear();
		char *string1 = "RESET";
		char *string2 = "STATE";
		printLCDText(string1, string2);
		print = false;
	}
}

/*** Runnging State ***/
void running() {
	// timers running
	// print time
	char *string1 = "00:00:00:00";
	char *string2 = "00:00:00:00";
	printLCDText(string1, string2);
	if (printLapCount == 2) // button is pressed twice
		printLap();
}

/*** Stop State ***/
void stop() {
	// show time
	// printLCD();
	if (!print) {
		lcd_clear();
		char *string1 = "STOP";
		char *string2 = "STATE";
		printLCDText(string1, string2);
		print = true;
	}
}

/*** Initialize all the variables on reset of the device ***/
void initVar() {
	state = RESET;
	print = true;
	printLapCount = 0;
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
