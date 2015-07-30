#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

// Baud in bps
void uart_init(uint32_t baud);
void uart_putc(char c);
uint8_t uart_getc();
uint8_t uart_getline(char* buff);
void uart_puts(char* buff);

#endif
