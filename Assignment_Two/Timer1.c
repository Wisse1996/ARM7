#include "MCB2300 evaluationboard.h"  // hardware related functions 
#include <stdbool.h> // bool C99

/*** global ***/
int t1;

/************** interrupt service routine timer1 ******************/ 
__irq void T1_ISR (void) { 
	// program code
	// t1 = !t1;
	t1++;

	// interrupt code
	T1IR        = 1;	// Clear interrupt flag 
	VICVectAddr = 0;	// Update interrupt priority hardware 
} 
 
/********************  initializing timer1 ************************/ 
void init_T1(void) { 
	T1MR0 = 1000000;
	T1MCR = 3;	// Enable interrupt, reset on match register 0 
	T1TCR = 1;	// Enable timer1 
	VICVectAddr5 = (unsigned long)T1_ISR;	// Set interrupt vector 
	VICVectPriority5 = 10;	// Set to priority 10 (arbitrary value) 
	VICIntEnable  = (1 << 5);	// Enable Ttimer1 Interrupt 
} 
