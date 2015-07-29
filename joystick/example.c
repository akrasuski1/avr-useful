#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "HD44780.h"
#include "joystick.h"

int main(void){
	char buff[16];

	joystick joy;
	JOYSTICK_INIT(joy, C,0, C,1, B,0);

	LCD_init();
	LCD_clr();
	LCD_puts("Joystick:");

	while(1){
		for(int i=0;i<16;i++){
			buff[i]=' ';
		}
		itoa((int)joystick_x(&joy),buff,10);
		itoa((int)joystick_y(&joy),buff+5,10);
		for(int i=0;i<16;i++){
			if(!buff[i]){
				buff[i]=' ';
			}
		}
		buff[10]=joystick_down(&joy) ? '+' : '-';
		buff[11]=0;

		LCD_goto(0,1);
		LCD_puts(buff);

		_delay_ms(50);
	}
	return 0;
}
