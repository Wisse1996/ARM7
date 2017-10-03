/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h>	// standard C definitions
#include <stdbool.h>	// bool C99
#include "MCB2300 evaluationboard.h"	// hardware related functions
#include <LPC23xx.H>                        /* LPC23xx definitions */


/*** globals ***/


/*** print text to lcd ***/
void printLCDText(char const *string1, char const *string2, int mode) {
	char textFirst[17]; // declaration of array of 17 characters
	char textSecond[17]; // declaration of array of 17 characters
  
  lcd_clear();

	// mode | 0 = both, 1 = up, 2 = bottom
	if ((mode == 0) || (mode == 1)) {
		sprintf(textFirst, string1); // buf is filled
		set_cursor(0, 0); // cursor position is moved to the upper line
		lcd_print(textFirst); // the text is written to the Lcd-module
		lcd_putchar(0x07);
		lcd_print("C");
	}

	if ((mode == 0) || (mode == 2)) {
		sprintf(textSecond, string2); // buf is filled
		set_cursor(0, 1); // cursor position is moved to the lower line
		lcd_print(textSecond); // the text is written to the Lcd-module
	}
}


/*** Main code ***/
int main(void) {
	initEvaluationBoard();	// init the hardware
	init_T0();	// init timer0 interrupt
	init_EINT0();

	// infinite loop
	while (1) {

	}
}
