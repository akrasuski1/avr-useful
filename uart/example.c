#include <avr/io.h>
#include <avr/delay.h>
#include <stdlib.h>
#include "HD44780.h"
#include "uart.h"

int main(){
	uart_init(9600);
	LCD_init();
	while(1){
		char buff[17];
		uart_getline(buff);
		LCD_goto(0,0);
		LCD_puts(buff);
		uart_puts(buff);
		uart_putc('x');
		uart_putc('\n');
	}
}
