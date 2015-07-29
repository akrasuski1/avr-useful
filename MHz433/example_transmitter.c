#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "macros.h"
#include "transmitter.h"


int main(void){
	// The following four lines are due to my laziness about breadboard.
	SET_OUTPUT(DDRD,3); // +5v
	SET_HIGH(PORTD,3);  // +5V
	SET_OUTPUT(DDRD,4); // GND
	SET_LOW(PORTD,4);   // GND

	// Initial values of channels.
	channels[0]=25;
	channels[1]=75;
	channels[2]=125;
	channels[3]=175;
	channels[4]=225;

	// Set to taste. Start with 0 initially.
	pulse_fine_tune=30;

	// Start.
	init_transmission();
	while(1){
		// Changing channels
		channels[0]++;
		_delay_ms(100);
	}

	return 0;
}
