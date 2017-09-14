/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h> // standard C definitions
#include <stdbool.h> // standard C bool 
#include "MCB2300 evaluationboard.h" // hardware related functions

/*** Globals ***/
// global var
extern bool t0,t1,t2,t3;

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

	// extern var code test
	while (1) {
		if (t0)			
			LEDS = 0x00;
		else 
			LEDS = 0xFF;
	}
}
