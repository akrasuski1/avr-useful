#include "time.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void time_reset(){
	TCCR2A=0; // no pin output,
	TCCR2B=(1<<CS20); // no prescaler
	TIMSK2=1<<TOIE2; // interrupt on overflow (256 cycles)
	sei();
	TCNT2=0; // reset timer to 0
	_time_overflow_cnt=0;
}

ISR(TIMER2_OVF_vect){
	_time_overflow_cnt++;
}

// This assumes round clock (full Mhz, e.g. 16Mhz).
// If your clock is not round, use f.p. calculations, commented
// below.
uint64_t time_us(){
	//return (_time_overflow_cnt*256 + TCNT2)/(F_CPU/1000000.0);
	return (_time_overflow_cnt*256 + TCNT2)/(F_CPU/1000000);
}

uint64_t time_ms(){
	return time_us()/1000;
}
