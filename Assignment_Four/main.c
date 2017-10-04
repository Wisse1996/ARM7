/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h>	// standard C definitions
#include <stdbool.h>	// bool C99
#include "MCB2300 evaluationboard.h"	// hardware related functions
#include <LPC23xx.H>                        /* LPC23xx definitions */


/*** globals ***/
bool sineFlag = false;


int value = 0;
int k = 0;
int value;
int a[POINTS];


#define nf 13            // number of bits of fractional part 
//int a1 = (int) (1.987975 * (1 << nf) + 0.5);  // a1=16069 (real value=16069/2^13=1.96157)
int a2 = 1 << nf;         // a2=8192  (real value=8192/2^13=1)

double tones[POINTS] = {1.9759, 1.98928, 1.98485, 1.98092, 1.99149}; // F4, E4, G4, A4, D4
// a--g--f--e--d--d--d--d--d---d-d

int CalculateOutput(int a1) {
	static int y_1 = 1 << (nf - 2);     // initial value of y1=8192 (real value=1)
	static int y_2 = 0;       // initial value of y2=0
	int y  = (a1 * y_1) - (a2 * y_2);    // calculation of new output sample
	y = y >> nf;         // shift nf bits to right
	y_2 = y_1;          // update old output-sample
	y_1 = y;          // update old output-sample
	return y;          // return new output sample
}

void initArray() {
	for (int i = 0; i < 21; i++) {
		a[i] = (int) (tones[i] * (1 << nf) + 0.5);
	}
}

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
	init_T1();
	init_EINT0();
	initArray();

	// infinite loop
	while (1) {

		if (sineFlag) {
			sineFlag = false;
			value = CalculateOutput(a[k]);
			value = value >> 6;
			value += 1000;
			value /= 2;

			DACR = ((value) << 6);
		}

	}
}
