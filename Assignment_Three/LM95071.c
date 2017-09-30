
#include <stdio.h>
#include "LM95071.h"
#include "MCB2300 evaluationboard.h"

void init_SPI() {
	PINSEL0 |= (1U << 30) | (1U << 31);	// SCK // could be done by (3U<<30) // U -> unsigned compiler...
	PINSEL1 |= (1U << 2) | (1U << 3);	// MISO
	// PINSEL1 |= (1U << 6) | (1U << 7);	// CS
	// SPI register LPC -> DS 461
	S0SPCR |= (1U << 2);	// BitEnebale-bit
	S0SPCR |= (1U << 5);	// MSTR
	S0SPCCR = 120; // DS 463 clock or something?
	IODIR0 |= (1U << 19);	// output GPIO
}

/*** reads the temperature sensor via spi ***/
unsigned short readLM95071SPI() {
	unsigned short result; // buf
	IOCLR0 |= (1U << 19); // clear CS | CS = 0
	S0SPDR = 0;
	unsigned char SPIF = S0SPSR & 0x80;
	while (!SPIF)
		SPIF = S0SPSR & 0x80;
	IOSET0 |= (1u << 19); // set CS | CS = 1
	result = S0SPDR;
	return result;
}

