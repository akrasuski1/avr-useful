#include <avr/io.h>
#include <util/delay.h>
#include "HD44780.h"

int main(void)
{
	LCD_init();
	LCD_clr();
	_delay_ms(1000);
	LCD_cmd(HD44780_CGRAM_SET);
	LCD_putc(0b00000);
	LCD_putc(0b00100);
	LCD_putc(0b00010);
	LCD_putc(0b11111);
	LCD_putc(0b00010);
	LCD_putc(0b00100);
	LCD_putc(0b00000);
	LCD_putc(0b00000);
	LCD_home();
	LCD_putc(0);
	_delay_ms(1000);
	LCD_puts("Testing chars:");
	for(int i=0;i<256;i++){
		LCD_goto(i%16,1);
		LCD_putc(i);
		_delay_ms(50);
	}
	return 0;
}
