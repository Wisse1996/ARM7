/* ******************** Workshop 1 -- Assignement2 **************************/
#include <stdio.h>	// standard C definitions
#include <stdbool.h>	// bool C99
#include "MCB2300 evaluationboard.h"	// hardware related functions
#include "LM95071.h"
#include <LPC23xx.H>                        /* LPC23xx definitions */
#include "type.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "demo.h"

#define SCALE 0.03125

/*** globals ***/
volatile bool update = false;
volatile bool newData = false;
volatile unsigned char usb[8]; // string to send


// Function GetInReport() is invoked by the USB ISR when an InReport has been sent.
// The data sent to the USB-host at the next InReport are stored in InReport[]
void GetInReport () {
	if (newData) {
		newData = false;
		// transfer the data to the inreport structure
		for (int i = 0; i < 8; i++) {
			InReport[i] = usb[i];
			usb[i] = 0;
		}
	}
}

void SetOutReport () {
	// do something
}

/*** get a new sample of the sensor ***/
void updateTemperature(unsigned short *temp, unsigned short *sample) {
	*temp = readLM95071SPI();
	(*sample)++;
}

/*** show the temperature on the lcd ***/
void showTemperature(unsigned short *temp, unsigned short *sample) {
	unsigned short buf = *temp; // 2 byte temp value
	float value;
	char textbuf[17];
	char textbuf1[17];

	if (buf & 0x8000) { // signed | last bit 1
		buf = buf >> 2; // lose the first two bits
		buf -= 1;
		buf = ~buf;
		buf ^= 0xc000; // revert the last two bits
		value = buf * SCALE;
		sprintf(textbuf, "   -%4.1f", value);
	} else { //not signed
		buf = buf >> 2; // lose the first two bits
		value = buf * SCALE;
		sprintf(textbuf, "   +%4.1f", value);
	}

	sprintf(textbuf1, "Samples %d", *sample);
	printLCDText(textbuf, textbuf1, 0);
}

/*** send the temperature value to the pc ***/
void sendValueUSB(unsigned short *temp, unsigned short *sample) {
	// create the 7 byte asci string and send this to the usb.
	unsigned short buf = *temp; // 2 byte temp value
	float value;
	char sign;

	// reverse 2s complement
	if (buf & 0x8000) { // signed | last bit 1
		usb[0] = '-';
		buf = buf >> 2; // lose the first two bits
		buf -= 1;
		buf = ~buf;
		buf ^= 0xc000; // revert the last two bits
		value = buf * SCALE;
		sign = '-';
	} else { //not signed
		usb[0] = '+';
		buf = buf >> 2; // lose the first two bits
		value = buf * SCALE;
		sign = '+';
	}
	char textbuf[5];
	sprintf(textbuf, "%05.1f", value);
	for (int i = 0, j = 1; i < 5; i++, j++) {
		usb[j] = textbuf[i];
	}
	usb[0] = sign;

	usb[6] = (*sample >> (8 * 1)) & 0xff;	// MSByte sample
	usb[7] = (*sample >> (8 * 0)) & 0xff;	// LSByte sample

	// set data flag
	newData = true;
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
	init_SPI(); // init SPI for sensor
	USB_Init(); // init USB for InReport
  
  // info print
  lcd_print("Initializing");
  set_cursor(0,1);
  lcd_print("Reading sensor");
  
	// keep'm local
	unsigned short temperatureValue;
	unsigned short sampleNumber;

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
