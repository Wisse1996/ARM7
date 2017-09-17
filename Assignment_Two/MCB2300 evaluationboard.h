#ifndef _evaluationboard
#define _evaluationboard

#include <LPC23xx.H>	// LPC23xx definitions
#include "LCD.h"	// lcd header file

#define LEDS FIO2PIN0	// alternative (comprehensive) definition of FIOPIN0
#define INT0 (FIO2PIN1 & 0x04)	// int0 is connected to P2.10 (bit 3 of FIO2PIN1)
#define BUZZER FIO0PIN3	// P0.26 is in 0

// states definition
#define RESET 10
#define RUNNING 11
#define STOP 12


void initEvaluationBoard(void);	// function prototype
void init_T0(void); // function prototype
void init_T1(void); // function prototype
void init_T2(void);	// function prototype
void init_T3(void);	// function prototype
void initEINT0(void);	// function prototype

#endif
