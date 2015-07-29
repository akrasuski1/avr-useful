#include "joystick.h"

#include <avr/io.h>

void joystick_init(){
	// enable analog converter with prescaler=128 (f=125kHz if F_CPU=16MHz)
	ADMUX|=(1<<REFS0)|(1<<ADLAR);
	ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
}
int8_t joystick_read_analog(uint8_t channel){
	ADMUX = (ADMUX & 0xf8)|channel;
	ADCSRA|=(1<<ADSC);
	while((ADCSRA)&(1<<ADSC));
	return ADCH-128;
}
int8_t joystick_x(joystick* joy){
	return joystick_read_analog(joy->pinx);
}
int8_t joystick_y(joystick* joy){
	return joystick_read_analog(joy->piny);
}
unsigned char joystick_down(joystick* joy){
	return IS_LOW(*(joy->pin_d), joy->pind);
}
