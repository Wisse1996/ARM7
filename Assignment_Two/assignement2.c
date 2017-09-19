/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h>	// standard C definitions
#include <stdbool.h>	// bool C99
#include "MCB2300 evaluationboard.h"	// hardware related functions
#include "time.h"

/*** Globals ***/

bool mainTimerActive;   // this is a bool to check if the mainTimer is active
bool labTimerActive;     // this is a bool to check if the labtimer is active
bool wait;
int t0, t1, t2, t3; // timers testing
int state; // state | RESET, RUNNING, STOP
int lapFlag;
bool print;
struct Time *ptrMainTime;
struct Time *ptrLabTime;
struct Time mainTime;
struct Time labTime;


/*** print text to lcd ***/
void printLCDText(char const *string1, char const *string2, int mode) {
	char textFirst[17]; // declaration of array of 17 characters
	char textSecond[17]; // declaration of array of 17 characters

	// mode | 0 = both, 1 = up, 2 = bottom
	if ((mode == 0) || (mode == 1)) {
		sprintf(textFirst, string1); // buf is filled
		set_cursor(0, 0); // cursor position is moved to the upper line
		lcd_print(string1); // the text is written to the Lcd-module
	}

	if ((mode == 0) || (mode == 2)) {
		sprintf(textSecond, string2); // buf is filled
		set_cursor(0, 1); // cursor position is moved to the lower line
		lcd_print(string2); // the text is written to the Lcd-module
	}
}

/*** Print lap time ***/
void printLap() {
	char buf[17]; // declaration of array of 17 characters
	char buf1[17]; // declaration of array of 17 characters
	timeString(ptrLabTime, buf1);

	printLCDText(buf, buf1, 2);
	resetTime(ptrLabTime);
	lapFlag = 0; // reset the flag
}

/*** Reset State ***/
void reset() {
	if (print) { // print only once
		lcd_clear();
		resetTime(ptrMainTime);
		resetTime(ptrLabTime);
		labTimerActive = false;
		mainTimerActive = false;

		const char *string1 = "00:00:00:00";
		const char *string2 = "00:00:00:00";
		printLCDText(string1, string2, 0);
		print = false;
	}
}

/*** Runnging State ***/
void running() {
	char buf[17]; // declaration of array of 17 characters
	char buf1[17]; // declaration of array of 17 characters
	timeString(ptrMainTime, buf);

	if (!wait)
		printLCDText(buf, buf1, 1);
	if (lapFlag) // button is pressed
		printLap();
}

/*** Stop State ***/
void stop() {
	if (!print) { // print only once
		mainTimerActive = false;
		labTimerActive = false;
		print = true;
	}
}

/*** Initialize all the variables on reset of the device ***/
void initVar() {
	state = RESET;
	print = true;
	lapFlag = 0;
	labTimerActive = false;
	wait = false;

	// pointers
	ptrMainTime = &mainTime;
	ptrLabTime = &labTime;
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
