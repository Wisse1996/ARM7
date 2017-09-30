/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h>	// standard C definitions
#include <stdbool.h>	// bool C99
#include "MCB2300 evaluationboard.h"	// hardware related functions
#include "LM95071.h"

/*** globals ***/
volatile bool update;


/*** get a new sample of the sensor ***/
void updateTemperature(unsigned short *temp, int *sample) {
	// get a new sample of the sensor through SPI
	*temp = readLM95071SPI();
	*sample++;
}

/*** show the temperature on the lcd ***/
void showTemperature(unsigned short *temp, int *sample) {
	// create the strings and send them to the lcd using printLCDText
	// upper line = temperatur, bottom line = sample time
}

/*** send the temperature value to the pc ***/
void sendValueUSB(unsigned short *temp, int *sample) {
	// create the 7 byte asci string and send this to the usb.
}

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


/*** Main code ***/
int main(void) {
	initEvaluationBoard();	// init the hardware
	initEINT0();	// init the button interrupt
	init_T0();	// init timer0 interrupt
	init_SPI(); // init SPI for sensor

	// keep'm local
	unsigned short temperatureValue;
	int sampleNumber;

	// infinite loop
	while (1) {
		if (update) { // only update the tempC and update display every sampleTime -> Timer0
			update = false; // update flag
			updateTemperature(&temperatureValue, &sampleNumber);
			showTemperature(&temperatureValue, &sampleNumber);
			sendValueUSB(&temperatureValue, &sampleNumber);
		}
	}


}
