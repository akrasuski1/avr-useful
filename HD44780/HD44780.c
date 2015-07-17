// Author : Radoslaw Kwiecien
// Source : http://radzio.dxp.pl/hd44780/

// Refactored by akrasuski1 to shorten lengthy function names

// This library assumes only four data pins are connected, and RW pin is grounded.

#include "HD44780.h"

#define PORT_(port) PORT ## port
#define DDR_(port)  DDR  ## port

#define PORT(port) PORT_(port)
#define DDR(port)  DDR_(port)

#define LCD_RS_DIR		DDR(LCD_RS_DDR)
#define LCD_RS_PORT 	PORT(LCD_RS_DDR)
#define LCD_E_DIR		DDR(LCD_E_DDR)
#define LCD_E_PORT		PORT(LCD_E_DDR)
#define LCD_DB4_DIR		DDR(LCD_DB4_DDR)
#define LCD_DB4_PORT	PORT(LCD_DB4_DDR)
#define LCD_DB5_DIR		DDR(LCD_DB5_DDR)
#define LCD_DB5_PORT	PORT(LCD_DB5_DDR)
#define LCD_DB6_DIR		DDR(LCD_DB6_DDR)
#define LCD_DB6_PORT	PORT(LCD_DB6_DDR)
#define LCD_DB7_DIR		DDR(LCD_DB7_DDR)
#define LCD_DB7_PORT	PORT(LCD_DB7_DDR)

void LCD_put_nibble(unsigned char nibbleToWrite)
{
	if(nibbleToWrite & 0x01)
		LCD_DB4_PORT |= LCD_DB4;
	else
		LCD_DB4_PORT  &= ~LCD_DB4;

	if(nibbleToWrite & 0x02)
		LCD_DB5_PORT |= LCD_DB5;
	else
		LCD_DB5_PORT  &= ~LCD_DB5;

	if(nibbleToWrite & 0x04)
		LCD_DB6_PORT |= LCD_DB6;
	else
		LCD_DB6_PORT  &= ~LCD_DB6;

	if(nibbleToWrite & 0x08)
		LCD_DB7_PORT |= LCD_DB7;
	else
		LCD_DB7_PORT  &= ~LCD_DB7;
}

void LCD_raw(unsigned char dataToWrite)
{
	LCD_E_PORT |= LCD_E;
	LCD_put_nibble(dataToWrite >> 4);
	LCD_E_PORT &= ~LCD_E;
	LCD_E_PORT |= LCD_E;
	LCD_put_nibble(dataToWrite);
	LCD_E_PORT &= ~LCD_E;
	_delay_us(50);
}

void LCD_cmd(unsigned char commandToWrite)
{
	LCD_RS_PORT &= ~LCD_RS;
	LCD_raw(commandToWrite);
}

void LCD_putc(unsigned char dataToWrite)
{
	LCD_RS_PORT |= LCD_RS;
	LCD_raw(dataToWrite);
}

void LCD_puts(char * text)
{
	while(*text)
		LCD_putc(*text++);
}

void LCD_goto(unsigned char x, unsigned char y)
{
	LCD_cmd(HD44780_DDRAM_SET | (x + (0x40 * y)));
}

void LCD_clr(void)
{
	LCD_cmd(HD44780_CLEAR);
	_delay_ms(2);
}

void LCD_home(void)
{
	LCD_cmd(HD44780_HOME);
	_delay_ms(2);
}

void LCD_init(void)
{
	unsigned char i;
	LCD_DB4_DIR |= LCD_DB4; // Konfiguracja kierunku pracy wyprowadze�
	LCD_DB5_DIR |= LCD_DB5; //
	LCD_DB6_DIR |= LCD_DB6; //
	LCD_DB7_DIR |= LCD_DB7; //
	LCD_E_DIR 	|= LCD_E;   //
	LCD_RS_DIR 	|= LCD_RS;  //
	_delay_ms(15); // oczekiwanie na ustalibizowanie si� napiecia zasilajacego
	LCD_RS_PORT &= ~LCD_RS; // wyzerowanie linii RS
	LCD_E_PORT &= ~LCD_E;  // wyzerowanie linii E

	for(i = 0; i < 3; i++) // trzykrotne powt�rzenie bloku instrukcji
	{
		LCD_E_PORT |= LCD_E; //  E = 1
		LCD_put_nibble(0x03); // tryb 8-bitowy
		LCD_E_PORT &= ~LCD_E; // E = 0
		_delay_ms(5); // czekaj 5ms
	}

	LCD_E_PORT |= LCD_E; // E = 1
	LCD_put_nibble(0x02); // tryb 4-bitowy
	LCD_E_PORT &= ~LCD_E; // E = 0

	_delay_ms(1); // czekaj 1ms
	LCD_cmd(HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT); // interfejs 4-bity, 2-linie, znak 5x7
	LCD_cmd(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF); // wy��czenie wyswietlacza
	LCD_cmd(HD44780_CLEAR); // czyszczenie zawartos�i pamieci DDRAM
	_delay_ms(2);
	LCD_cmd(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);// inkrementaja adresu i przesuwanie kursora
	LCD_cmd(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK); // w��cz LCD, bez kursora i mrugania
}
