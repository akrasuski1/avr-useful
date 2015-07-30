#include "uart.h"

#include "macros.h"

// Baud in bps
void uart_init(uint32_t baud){
	// set baudrate:
	uint16_t ubrr=F_CPU/8/baud - 1;
	UBRR0H = (uint8_t)(ubrr>>8);
	UBRR0L = (uint8_t)ubrr;
	// enable tx and rx:
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	// 8-bit characters:
	UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00);
}

void uart_putc(char c){
	while(IS_LOW(UCSR0A, UDRE0));
	UDR0 = c;
}

uint8_t uart_getc(){
	while (IS_LOW(UCSR0A,RXC0));
	return UDR0;
}

uint8_t uart_getline(char* buff){
	uint8_t cnt=0;
	while(1){
		char c=uart_getc();
		if(c=='\r'){
			continue;
		}
		if(c=='\n'){
			break;
		}
		cnt++;
		*buff++=c;
	}
	*buff=0;
	return cnt;
}

void uart_puts(char* buff){
	while(*buff){
		uart_putc(*buff++);
	}
}
