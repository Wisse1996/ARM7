/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h> // standard C definitions
#include <stdbool.h> 
#include "MCB2300 evaluationboard.h" // hardware related functions

/*** globals ***/
// global var
extern bool testBool; 

void resetState() {
	// reset timers
	// print 00:00:00:00
}

void runningState() {
	// timers running
	// print time
}

void stopState() {
	// show time
	// 
}

void printLap() {
	// print lap 
}

/*** Main code ***/
int main(void) {
	// init the hardware and interrupts
        // here we should write the code for the stopwacht
        // yet another comment
	initEvaluationBoard();
	init_EINT0(); 
	init_T1();
	if (testBool) 
		LEDS = 0x00;
	else 
		LEDS = 0xFF;
}
