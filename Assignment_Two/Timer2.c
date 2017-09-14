#include "MCB2300 evaluationboard.h"  // hardware related functions 
#include <stdbool.h> // bool C99

/*** global ***/
int t2;

/************** interrupt service routine timer2 ******************/ 
__irq void T2_ISR (void) {  
	// program code
	// t2 = !t2;
	t2++;

	// interrupt code
	T2IR        = 1;	// Clear interrupt flag 
	VICVectAddr = 0;	// Update interrupt priority hardware 
} 
 
/********************  initializing timer2 ************************/ 
void init_T2(void) { 
	T2MR0 = 2000000;
	T2MCR = 3;	// Enable interrupt, reset on match register 0 
	T2TCR = 1;	// Enable timer2
	VICVectAddr26 = (unsigned long)T2_ISR;	// Set interrupt vector 
	VICVectPriority26 = 8;	// Set to priority 10 (arbitrary value) 
	VICIntEnable  = (1 << 26);	// Enable Ttimer2 Interrupt 
} 
