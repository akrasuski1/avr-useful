#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "macros.h"
#include <avr/pgmspace.h>

// Note: all the macros, such as pin setup, are defined in keypad.c file.

// Functions:
void keypad_init();
uint8_t keypad_is_pressed(uint8_t x, uint8_t y);
char keypad_get_button();

#endif
