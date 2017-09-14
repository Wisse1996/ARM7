#include "MCB2300 evaluationboard.h" // hardware related functions


/************* Interrupt service routine for EINT0 ****************************/
__irq void EINT0_ISR(void) { // interrupt service routine
 /************************************************/
 // Place here your own code
 /************************************************/
 EXTINT |= 0x01; // clears EINT0 interrupt flag
 VICVectAddr = 0; // Update interrupt priority hardware
};
/************* Initializing code for EINT0 ****************************/
void initEINT0(void) {
 PINSEL4 |= (1<<20); // select EINT0 pin. function
 EXTMODE |= 1; // select level-sensitive EINT0.
 EXTINT |= 0x01; // clears EINT0 interrupt flag
 VICVectPriority14=15; // lowest priority.
 VICIntEnable = (1<<14); // enable interrupt source 14 (EINT0).
 VICVectAddr14 = (unsigned long) EINT0_ISR; // Address of Interrupt Service Routine
}
