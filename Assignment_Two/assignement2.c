/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h> // standard C definitions
#include <stdbool.h> // standard C bool 
#include "MCB2300 evaluationboard.h" // hardware related functions

/*** Globals ***/
// global var
extern bool testBool; 

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
	init_T1();	// init timer1 interrupt

	// extern var code test
	while (1) {
		if (testBool)			
			LEDS = 0x00;
		else 
			LEDS = 0xFF;
	}
}
