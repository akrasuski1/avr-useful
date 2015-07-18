#include <avr/io.h>
#include "macros.h"

#include "servo.h"

// This library works correctly for ATmega328P - the one commonly used in Arduino UNO.
// I do not guarantee that pins and processor registers are same in other devices.

// This library uses TIMER1 to generate PWM pulses. Hardware allows to do it in 16-bit
// precision only on pins 1 and 2 of PORTB, so this library assumes that case. Using
// this code in other way may cause undesired behavior.

void servos_init(){
	// Set TIMER1 to Fast PWM mode, with prescaler=8
	TCCR1A|=(1<<WGM11);
	TCCR1B|=(1<<WGM12)|(1<<WGM13)|(1<<CS11);
	// Set correct period of PWM.
	ICR1=SERVO_PERIOD*F_CPU/8/1000000; // 8 - prescaler, 1000000 - micro
}

void _servo_set_timer(uint8_t pin, uint8_t enable){
	uint8_t flag;
	if(pin==1){
		flag=COM1A1;
	}
	else if(pin==2){
		flag=COM1B1;
	}
	if(enable){
		SET_HIGH(TCCR1A, flag);
	}
	else{
		SET_LOW(TCCR1A, flag);
	}
}

void set_servo(uint8_t pin, uint16_t pulse){
	_servo_set_timer(pin, pulse>0);
	uint16_t length=(uint64_t)pulse*F_CPU/8/1000000;
	if(pin==1){
		OCR1A=length;
	}
	else if(pin==2){
		OCR1B=length;
	}
}

void add_servo(uint8_t pin){
	SET_OUTPUT(DDRB, pin);
	set_servo(pin, SERVO_DEFAULT_PULSE);
}

void remove_servo(uint8_t pin){
	_servo_set_timer(pin, 0);
}
