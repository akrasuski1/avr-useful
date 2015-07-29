#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "HD44780.h"
#include "time.h"
#include "macros.h"
#include "receiver.h"


void print_at(uint8_t x, uint8_t y, uint8_t channel){
	char buff[17];
	buff[16]=0;

	uint64_t threshold=1000000ULL; //1s

	LCD_goto(x,y);
	LCD_putc(time_us()-last_updated_at[channel]<threshold ? 'v' : 'x');
	LCD_puts(itoa((int)channels[channel],buff,10));
	LCD_putc(' ');
	LCD_putc(' ');
}

int main(void){
	LCD_init();
	LCD_clr();

	receiver_init();

	while(1){
		print_at(0, 0,0);
		print_at(5, 0,1);
		print_at(10,0,2);
		print_at(0, 1,3);
		print_at(10,1,4);
		_delay_ms(100);
	}

	return 0;
}
