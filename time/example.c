#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "HD44780.h"
#include "time.h"


int main(void){
	char buff[10];

	time_reset();

	LCD_init();
	LCD_clr();
	LCD_puts("Time:");

	while(1){
		LCD_goto(0,1);
		ltoa((long)time_ms(),buff,10);
		char* last=buff;
		while(*last){last++;}
		*last++='m';
		*last++='s';
		*last=0;
		LCD_puts(buff);
		_delay_ms(500);
		if(time_ms()>20000){
			time_reset();
			LCD_goto(0,1);
			for(int i=0;i<10;i++){
				LCD_putc(' ');
			}
		}
	}
	return 0;
}
