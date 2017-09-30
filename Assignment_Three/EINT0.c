#include "MCB2300 evaluationboard.h"  // hardware related functions 
#include <stdbool.h>	// bool C99


/*** global ***/


/*** enable/disable all the 4 timers ***/
void setAllTimers(int mode) {
// set all timer's registers
	T0TCR = mode;	// timer0
	T1TCR = mode;	// timer1
	T2TCR = mode;	// timer2
	T3TCR = mode;	// timer3
}

/*** toggle all four timers ***/
void toggleTimers() {
	// toggle all timers when the button is pressed
	T0TCR = !T0TCR;	// Enable timer0
	T1TCR = !T1TCR;	// Enable timer1
	T2TCR = !T2TCR;	// Enable timer2
	T3TCR = !T3TCR;	// Enable timer3
}


/************* Interrupt service routine for EINT0 ****************************/
__irq void EINT0_ISR(void) {	// interrupt service routine

	EXTINT |= 0x01;	// clears EINT0 interrupt flag
	VICVectAddr = 0;	// Update interrupt priority hardware
};

/************* Initializing code for EINT0 ****************************/
void initEINT0(void) {
	PINSEL4 |= (1 << 20); // select EINT0 pin. function
	EXTMODE |= 1; // select level-sensitive EINT0.
	EXTINT |= 0x01;   // clears EINT0 interrupt flag
	VICVectPriority14 = 15; // lowest priority.
	VICIntEnable = (1 << 14); // enable interrupt source 14 (EINT0).
	VICVectAddr14  = (unsigned long) EINT0_ISR; // Address of Interrupt Service Routine
}
