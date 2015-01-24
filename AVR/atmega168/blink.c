/**
 * Test program to ensure the ATMEGA168 is running correctly on the PCB
 * Chip: ATmega168
 * Blinks each of the 4 "Signal*" LEDs on the PCB in sequence, once per second
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "../leah_library/pin_macros.h"

#define true 1

// Turn on specified LED [0-3] i.e. LEDs labeled Signal[1-4] on the PCB while turning all the others off
void ledStep(int s){
  if(s==0) d1High(); else d1Low();
  if(s==1) d2High(); else d2Low();
  if(s==2) d3High(); else d3Low();
  if(s==3) d4High(); else d4Low();
}

int main (void)
{
  d1Output();
  d2Output();
  d3Output();
  d4Output();

  int s = 0;
  while(true) {	
    ledStep(s);
    _delay_ms(250);
    s = (s+1) %4;
  }

  return 0;
}
