#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "HD44780.h"
#include "ping.h"


int main(void){
	char buff[10];

	ping_init();

	LCD_init();
	LCD_clr();
	LCD_puts("Echo");


	while(1){
		LCD_goto(0,1);
		itoa((int)check_ping(),buff,10);
		char* last=buff;
		while(*last){last++;}
		*last++=' ';
		*last++=' ';
		*last=0;
		LCD_puts(buff);
		_delay_ms(50);
	}
	return 0;
}
