#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd_lib.h"
#include "DHT22int.h"
#include <stdio.h>

// http://moretosprojects.blogspot.de/2014/01/dht22-interrupt-driven-library-for-avr.html

void delay1s(void) {
  for(uint8_t i=0;i<100;i++)
    _delay_ms(10);
}


int main(void)
{
	LCDinit(); //init LCD bit, dual line, cursor right
	LCDclr();  //clears LCD

	DHT22_STATE_t state;
	DHT22_DATA_t sensor_data;
	DHT22_Init();

	while(1) {
	  state = DHT22_StartReading();

	  delay1s();

	  state = DHT22_CheckStatus(&sensor_data);
 
	  if (state == DHT_DATA_READY) {
	    // Do something with the data.
	    int t = sensor_data.temperature_integral;
	    //float t = sensor_data.temperature_decimal;
	    int h = sensor_data.humidity_integral;
	    //float h = sensor_data.humidity_decimal;
	    	    
	    char line1[17];
	    char line2[17];
	    	    
	    snprintf (line1, 16, "h=%4d          ", h);
	    snprintf (line1, 16, "t=%4d          ", t);	    

	    LCDclr();
	    CopyStringtoLCD((uint8_t*)line1, 0, 0);
	    CopyStringtoLCD((uint8_t*)line2, 1, 0);
	    
	  }
	  else if (state == DHT_ERROR_CHECKSUM){
	    // Do something if there is a Checksum error
	  }
	  else if (state == DHT_ERROR_NOT_RESPOND){
	    // Do something if the sensor did not respond
	  }

	}
	return 0;
}
