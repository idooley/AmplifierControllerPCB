/**
 * Driver code for a controller that switches the power transformer relay on/off based on an input trigger line
 *
 * LED1 = Debounced trigger input state
 * LED2 = Transformer switched on
 * LED3 = 
 * LED4 = Fault indicator
 *
 *
 *
 * TODO:
 *   Reduce power consumption using techniques described in https://www.garlicsoftware.com/articles/files/0662584a661f5b1cdb84dc2c17935537-1.php
 *   Implement temperature fault detection
 *   Implement over-current fault detection
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include "../leah_library/pin_macros.h"

#define true 1
#define false 0


// States
enum state_t {
  NORMAL_ON,  // power transformer will be on
  NORMAL_OFF, // power transformer will be off
  FAULT,      // A terminal state where the power transformer is shutoff
};


/** Check if trigger input is present (with 25ms debounce check) */
int isTriggerOn() {
  // Do basic debounce check that input is still the same after 25ms
  if (c4IsHigh()){
    d1Low(); // LED
    return false; 
  } 
  _delay_ms(25);
  if(c4IsLow()){
    d1High();
    return true;
  } else {
    d1Low();
    return false;
  }
}

/** Set the output pin values to match the specified state */
updateOutputs(enum state_t s){
  switch (s) {
  case NORMAL_ON:
    powerTransformerOn();
    d4Low(); // Fault LED
    break;

  case NORMAL_OFF:
    powerTransformerOff();
    d4Low(); // Fault LED
    break;

  case FAULT:
    powerTransformerOff();
    d4High(); // Fault LED
    break;

  }

}


void powerTransformerOn() {
  c1High(); // Darlington1 output
  d2High(); // Transformer LED
}

void powerTransformerOff() {
  c1Low(); // Darlington1 output
  d2Low(); // Transformer LED
}


void configurePins() {
  // Opto-isolated in 1 = Input Trigger
  c4Input();

  // darlington1 output = power transformer switching
  c1Output();

  // LED
  d1Output();
  d2Output();
  d3Output();
  d4Output();
}

int isOverTemp() {
  // TODO implement this once the temperature sensor is attached
  return false;
}

int main (void) {
  enum state_t s = NORMAL_OFF;

  while(true) {
    // Do any necessary state transitions
    switch (s) {
    case NORMAL_ON:
      if(isOverTemp())
	s = FAULT;
      if(!isTriggerOn())
	s = NORMAL_OFF;
      break;

    case NORMAL_OFF:
      if(isOverTemp())
	s = FAULT;
      if(isTriggerOn())
	s = NORMAL_ON;
      break;

    case FAULT:
      // Never leave this terminal state
      break;
    }

    // Update output pins to match current/new state
    updateOutputs(s);
  }
  
  return 0;
}
