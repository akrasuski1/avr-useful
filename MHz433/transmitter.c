#include "transmitter.h"
#include <avr/interrupt.h>
#include "macros.h"

#define TRANSMITTER_DDR  DDR(TRANSMITTER_DDRX)
#define TRANSMITTER_PORT PORT(TRANSMITTER_DDRX)

void set_wait(uint16_t us){
	ICR1=(uint64_t)(us+pulse_fine_tune)*F_CPU/8/1000000; // 8- prescaler, 1000000 - micro
}

uint8_t transmission_place;
ISR(TIMER1_OVF_vect){
	transmission_place%=2*CHANNEL_COUNT+2;
	++transmission_place;
	if(transmission_place==1){
		SET_HIGH(TRANSMITTER_PORT, TRANSMITTER_PIN);
		set_wait(START_PULSE_ON);
	}
	else if(transmission_place==2){
		SET_LOW(TRANSMITTER_PORT, TRANSMITTER_PIN);
		set_wait(START_PULSE_OFF);
	}
	else{ // sending individual pulses
		int channel=(transmission_place-3)/2;
		if(transmission_place%2==1){
			SET_HIGH(TRANSMITTER_PORT, TRANSMITTER_PIN);
			set_wait(
				MIN_CHANNEL+(MAX_CHANNEL-MIN_CHANNEL)*(double)channels[channel]/255
			);
		}
		else{
			SET_LOW(TRANSMITTER_PORT, TRANSMITTER_PIN);
			set_wait(
				MIN_CHANNEL+(MAX_CHANNEL-MIN_CHANNEL)*(double)(255-channels[channel])/255
			);
		}
	}
}

// This is serial version, that does not use any timers. It needs to be called often in a loop,
// and will block during that time. Left there for historical reasons.
/*void transmit(reg_t port, uint8_t pin, uint8_t channels[CHANNEL_COUNT]){
	SET_HIGH(*port, pin);
	_delay_us(START_PULSE_ON);
	SET_LOW(*port, pin);
	_delay_us(START_PULSE_OFF);
	for(int i=0;i<CHANNEL_COUNT;i++){
		SET_HIGH(*port, pin);
		_delay_us(MIN_CHANNEL+(MAX_CHANNEL-MIN_CHANNEL)*(double)channels[i]/256);
		SET_LOW(*port, pin);
		_delay_us(MIN_CHANNEL+(MAX_CHANNEL-MIN_CHANNEL)*(double)(256-channels[i])/256);
	}
}*/

void init_transmission(){
	SET_OUTPUT(TRANSMITTER_DDR, TRANSMITTER_PIN);

	TIMSK1|=1<<TOIE1; // enable overflow interrupt on TIMER1
	sei();
	// Set TIMER1 to Fast PWM mode, prescaler=8
	TCCR1A|=(1<<WGM11);
	TCCR1B|=(1<<WGM12)|(1<<WGM13)|(1<<CS11);
	set_wait(1); // virtually instant interrupt
}
