#include "ping.h"
#include "macros.h"
#include "time.h"
#include <avr/io.h>
#include <util/delay.h>


#define PING_TRIG_DDRX   DDR (PING_TRIG_DDR)
#define PING_TRIG_PORT   PORT(PING_TRIG_DDR)
#define PING_TRIG_PINX   PIN (PING_TRIG_DDR)
#define PING_ECHO_DDRX   DDR (PING_ECHO_DDR)
#define PING_ECHO_PORT   PORT(PING_ECHO_DDR)
#define PING_ECHO_PINX   PIN (PING_ECHO_DDR)
#define PING_CONST       5.8772


void ping_init(){
	SET_OUTPUT(PING_TRIG_DDRX, PING_TRIG_PIN);
	SET_INPUT(PING_ECHO_DDRX, PING_ECHO_PIN);
	time_reset();
}

float check_ping(){
	SET_HIGH(PING_TRIG_PORT, PING_TRIG_PIN); // make a pulse
	_delay_us(10); // 10us wide
	SET_LOW(PING_TRIG_PORT, PING_TRIG_PIN); // turn it off
	long t=time_us(); // wait for echo signal
	while(IS_LOW(PING_ECHO_PINX, PING_ECHO_PIN)){
		if(time_us()-t>PING_TIMEOUT){ // timeout
			return PING_TIMEOUT/PING_CONST; // no data
		}
	}
	t=time_us();
	while(IS_HIGH(PING_ECHO_PINX, PING_ECHO_PIN)){ // wait until echo is OFF
		if(time_us()-t>PING_TIMEOUT){ // timeout
			// If timed out, reset the sensor by manually putting LOW on
			// the ECHO pin - that's workaround for cheap devices not
			// implementing timeout or doing it poorly.
			SET_OUTPUT(PING_ECHO_DDRX, PING_ECHO_PIN);
			SET_LOW(PING_ECHO_PORT, PING_ECHO_PIN);
			_delay_ms(3);
			SET_INPUT(PING_ECHO_DDRX, PING_ECHO_PIN);
			return PING_TIMEOUT/PING_CONST; // no data
		}
	}
	t=time_us()-t;
	return t/PING_CONST;
}
