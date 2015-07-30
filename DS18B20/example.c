#include <avr/io.h>
#include <avr/delay.h>
#include <stdlib.h>
#include "DS18B20.h"
#include "HD44780.h"
#include "macros.h"

int main(){
	LCD_init();
	while(1){
		double temp;
		if(!ds18b20_read_temp(&temp, 3)){
			LCD_clr();
			LCD_goto(0,0);
			LCD_puts("Error");
		}
		else{
			char buff[17];
			dtostrf(temp, 3, 4, buff);
			LCD_clr();
			LCD_goto(0,0);
			LCD_puts(buff);
		}

		_delay_ms(1000);
	}
}

