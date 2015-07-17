#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "macros.h"

typedef struct joystick{
	uint8_t pinx;
	uint8_t piny;
	reg_t  pin_d;
	uint8_t pind;
} joystick;

#define JOYSTICK_INIT(JOY,PORT_X, PIN_X, PORT_Y, PIN_Y, PORT_D, PIN_D) \
	JOY=(joystick){   \
		PIN_X,        \
		PIN_Y,        \
		&PIN(PORT_D), \
		PIN_D         \
	};                \
	SET_INPUT(DDR(PORT_X), PIN_X); \
	SET_INPUT(DDR(PORT_Y), PIN_Y); \
	SET_INPUT(DDR(PORT_D), PIN_D); \
	SET_HIGH(PORT(PORT_D), PIN_D); \
	joystick_init();

void joystick_init();
int8_t joystick_x(joystick* joy);
int8_t joystick_y(joystick* joy);
unsigned char joystick_down(joystick* joy);

#endif
