#include <avr/io.h>
#include <util/delay.h>

#include "macros.h"
#include "servo.h"


int main(void){
	servos_init();
	uint8_t servo_pin=2;
	add_servo(servo_pin);
	for(int i=1200;i<1800;i++){
		set_servo(servo_pin,i);
		_delay_ms(10);
	}
	set_servo(servo_pin,0);

	return 0;
}
