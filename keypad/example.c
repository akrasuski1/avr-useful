#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "macros.h"
#include "HD44780.h"
#include "keypad.h"


int main(void){
	LCD_init();
	LCD_puts("Keypad:");

	keypad_init();

	while(1){
		LCD_goto(15,0);
		char pressed=keypad_get_button();
		LCD_putc(pressed?pressed:' ');
		LCD_goto(0,1);
		for(int y=0;y<4;y++){
			for(int x=0;x<4;x++){
				LCD_putc(keypad_is_pressed(x, y)?'+':'-');
			}
		}
	}

	return 0;
}
