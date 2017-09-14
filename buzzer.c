/* ******************** Workshop 1 -- Exercise 2 **************************/
#include <stdio.h> // standard C definitions
#include "MCB2300 evaluationboard.h" // hardware related functions
#include <stdbool.h> // boolean yeah boolean in c

/*** globals ***/
volatile bool armed = false;
volatile int count = 0;

/************* Interrupt service routine for EINT0 ****************************/
__irq void EINT0_ISR(void) { // interrupt service routine
	armed = !armed; // flip the boolean
	count++; // increment the count
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

/************** interrupt service routine timer1 ******************/
__irq void T1_ISR (void) {
	if (armed) {
		LEDS = ~LEDS; // bit flips
	} else {
		LEDS = 0x00; // turn all the leds off
	}
	T1IR = 1; // Clear interrupt flag
	VICVectAddr = 0; // Update interrupt priority hardware
}
/******************** initializing timer1 ************************/
void init_T1(void) {
	T1MR0 = 499999; 
	T1MCR = 3; // Enable interrupt, reset on match register 0
	T1TCR = 1; // Enable timer1
	VICVectAddr5 = (unsigned long)T1_ISR; // Set interrupt vector
	VICVectPriority5 = 10; // Set to priority 10 (arbitrary value)
	VICIntEnable = (1 << 5); // Enable Ttimer1 Interrupt
}

/*** play the morse code for the given time ***/
void playMorseCode(int time) {
	for (int t = 0; t < time; t++) {
		int pwm = 500; // value for the frequency of the buzzer
		
		BUZZER = 0xFF;
		for (int i = 0; i < pwm; i++) {
		}
		
		BUZZER = 0x00;
		for (int i = 0; i < pwm; i++) {
		}
		if(!armed) break; // break out of the for loop
	}
}

/*** pause between each beep ***/
void intervalMorse(int time) {
	// Turn the buzzer off
	BUZZER = 0x00;
	for(int t = 0; t < time; t++) {
		if(!armed) break; // break out of the for loop
	}
}

/*** play morse code 3 times ***/
void beep(int duration, int interval) {
	for (int i = 0; i < 3; i++) {
				playMorseCode(duration);
				intervalMorse(interval);
	}
}

/*** print the first line of the lcd, first clear it ***/
void printFirstLine(char const *string) {
	char empty[17];
	for (int i = 0; i < (sizeof(empty) / sizeof(empty[0])); i++) {
		empty[i] = ' ';
	}
	set_cursor(0, 0);
	lcd_print(empty);
	
	set_cursor(0, 0);
	lcd_print(string);
}

/*** print the second line of the lcd, first clear it ***/
void printSecondLine(char const *string) {
	char empty[17];
	for (int i = 0; i < (sizeof(empty) / sizeof(empty[0])); i++) {
		empty[i] = ' ';
	}
	set_cursor(0, 1);
	lcd_print(empty);
	
	set_cursor(0, 1);
	lcd_print(string);
}

/*** print count to the display ***/
void printCount(char *textbuf) {
	sprintf(textbuf,"count = %d", count); // textbuf is filled
	set_cursor(0, 1); // cursor position is moved to the lower line
	lcd_print(textbuf); // the text is written to the Lcd-module
}


/*** Main code ***/
int main(void) {
	// init the hardware and interrupts
	initEvaluationBoard();
	init_T1();
	initEINT0();
	
	// declare the 'strings'
	char *noAlarm = "no alarm";
	char *armedAlarm = "s.o.s. alarm";
	char textbuf[17]; // declaration of array of 17 characters
	
	// print flags
	bool printAlarm = true;
	bool printRest = true;

	// loop indefinitly
	while (1) {
				
		if (armed) { 		
			// prints to the lcd only once
			if (printAlarm) {
				// print the count on the display
				printCount(textbuf);
				
				printFirstLine(armedAlarm); // empty and print the first line
				//lcd_print(armedAlarm);
				printRest = true;	
				printAlarm = false;
				
			}
			// a duration for the dit and 3 times the dah
			int shortTime = 100;
			int longTime = shortTime*3;
			
			// pause between the beeps
			int time = 200000;
			
			// play all the beeps
			beep(shortTime, time);	// 3x short
			beep(longTime, time);		// 3x long
			beep(shortTime, time);	// 3x short
			
			/* Old code
			// 3x short
			playMorseCode(shortTime);
			intervalMorse(time);
			playMorseCode(shortTime);
			intervalMorse(time);
			playMorseCode(shortTime);
			intervalMorse(time);
			
			// 3x long
			playMorseCode(longTime);
			intervalMorse(time);
			playMorseCode(longTime);
			intervalMorse(time);
			playMorseCode(longTime);
			intervalMorse(time);
			
			// 3x short
			playMorseCode(shortTime);
			intervalMorse(time);
			playMorseCode(shortTime);
			intervalMorse(time);
			playMorseCode(shortTime);
			intervalMorse(time);
			*/
			
			
			// extra pause for new word
			intervalMorse(shortTime * 1000);
		} else {
			// prints to the lcd only once
			if (printRest) {
				// print the count on the display
				printCount(textbuf);

				printFirstLine(noAlarm); // empty and print the first line
				printAlarm = true;
				printRest = false;
			}
		}
	}
		
}
