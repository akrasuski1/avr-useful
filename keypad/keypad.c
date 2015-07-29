#include "keypad.h"
#include <util/delay.h>


#define KEYPAD_X_DDR    B
uint8_t keypad_x_pins[] = {3,2,1,0};

#define KEYPAD_Y_DDR    C
uint8_t keypad_y_pins[] = {1,2,3,4};

// Characters on the keypad, read left to right, up, to down.
const char PROGMEM keypad_characters[]="123A456B789C*0#D";

// Signal needs some tiny amount of time to go through the circuit -
// delay length of 1 (that is, of order of 1us) solves the issue of
// not registering inputs.
#define KEYPAD_DELAY_LENGTH 1


// Implementation:

void keypad_init(){
	for(int i=0;i<sizeof(keypad_x_pins)/sizeof(uint8_t);i++){
		SET_OUTPUT(DDR(KEYPAD_X_DDR), keypad_x_pins[i]);
		SET_HIGH(PORT (KEYPAD_X_DDR), keypad_x_pins[i]);
	}
	for(int i=0;i<sizeof(keypad_y_pins)/sizeof(uint8_t);i++){
		SET_HIGH(PORT(KEYPAD_Y_DDR), keypad_y_pins[i]);
	}
}

uint8_t keypad_is_pressed(uint8_t x, uint8_t y){
	SET_LOW(PORT(KEYPAD_X_DDR),  keypad_x_pins[x]);
	_delay_loop_1(KEYPAD_DELAY_LENGTH); // for some reason, small delay is needed here.
	uint8_t r=IS_LOW(PIN(KEYPAD_Y_DDR), keypad_y_pins[y]);
	SET_HIGH(PORT(KEYPAD_X_DDR), keypad_x_pins[x]);
	return r;
}

char keypad_get_button(){
	for(int x=0;x<sizeof(keypad_x_pins)/sizeof(uint8_t);x++){
		for(int y=0;y<sizeof(keypad_y_pins)/sizeof(uint8_t);y++){
			if(keypad_is_pressed(x,y)){
				return pgm_read_byte_near(
						keypad_characters+
						y*sizeof(keypad_y_pins)/sizeof(uint8_t)+
						x);
			}
		}
	}
	return 0; // no match
}
