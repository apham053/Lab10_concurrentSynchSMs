/*	Author: apham053
 *  Partner(s) Name: Steven Rodriguez
 *	Lab Section:
 *	Assignment: Lab #10  Exercise #1
 *      Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <timer.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM { START, LED1, LED2, LED3 } state;
enum SM2 { START2, ON, OFF } state2;
enum SM3 { START3, COMBINE  } state3;

#define output (~PINA & 0x00);
#define output2 (~PINA & 0x00);

void tick() {
  switch(state) {
    case START:
    state = LED1;
    break;
    case LED1:
    state = LED2;
    break;
    case LED2:
    state = LED3;
    break;
    case LED3:
    state = LED1;
    break;
  }
  switch(state) {
    case START:
    break;
    case LED1:
    output = 0x01;
    break;
    case LED2:
    output = 0x02;
    break;
    case LED3:
    output = 0x04;
    break;
  }
}

void tick2() {
  switch(state2) {
    case START2:
    state2 = OFF;
    break;
    case ON:
    state2 = OFF;
    break;
    case OFF:
    state2 = ON;
    break;
  }
  switch(state2) {
    case START2:
    output2 = 0x00;
    break;
    case ON:
    output2 = 0x08;
    break;
    case OFF:
    output2 = 0x00;
    break;
  }
}

void tick3() {
  switch(state3) {
    case START3:
    state3 = COMBINE;
    break;
    case COMBINE:
    state3 = COMBINE;
    break;
  }
  switch(state3) {
    case START3:
    PORTB = 0x00;
    break;
    case COMBINE:
    PORTB = (output2 | output);
    break;
  }
}




int main(void) {
    
    DDRB = 0xFF;
    PORTB = 0x00;
    TimerSet(125); 
    TimerOn(); 
    state = START; 
    SM2 = START2;

    while (1) {
      tick();
      tick2();
      tick3();
      while (!TimerFlag) {

      }
      TimerFlag = 0;
    }
    return 1;
}
