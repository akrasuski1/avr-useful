#include "receiver.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include "macros.h"
#include "time.h"

uint64_t pulse_start_time;
uint8_t current_channel;
ISR(RECEIVER_INTERRUPT_VECTOR){
	uint8_t state=IS_LOW(PINC, 5);
	if(state){ // beginning of a pulse
		pulse_start_time=time_us();
	}
	else if (pulse_start_time!=0){ // end of pulse
		uint64_t width=time_us()-pulse_start_time;
		if(width<MIN_CHANNEL*(1-RECEIVE_TOLERANCE) || width>MAX_CHANNEL*(1+RECEIVE_TOLERANCE)){
			current_channel=255;
		}
		if(width<MIN_CHANNEL){width=MIN_CHANNEL;}
		if(width>MAX_CHANNEL && width<=MAX_CHANNEL*(1+RECEIVE_TOLERANCE)){width=MAX_CHANNEL;}
		if(current_channel!=255){
			channels[current_channel]=(width-MIN_CHANNEL)*255.0/(MAX_CHANNEL-MIN_CHANNEL);
			last_updated_at[current_channel]=time_us();
		}

		current_channel++;
		if(current_channel==0 || current_channel==CHANNEL_COUNT){
			current_channel=255;
		}
		if(width>START_PULSE_ON*(1-RECEIVE_TOLERANCE) && width<START_PULSE_ON*(1+RECEIVE_TOLERANCE)){
			current_channel=0;
		}
	}
}

void receiver_init(){
	current_channel=255;
	time_reset();
	SET_RECEIVER_INTERRUPT_FLAGS();
	SET_INPUT(RECEIVER_DDR, RECEIVER_PIN);
}
