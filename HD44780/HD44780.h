// Author : Radoslaw Kwiecien
// Source : http://radzio.dxp.pl/hd44780/

// Refactored by akrasuski1 to shorten lengthy function names

// This library assumes only four data pins are connected, and RW pin is grounded.

#include <avr/io.h>
#include <util/delay.h>

// Hardware:

// default port
#define LCD_DDR         D

// if you need to have custom ports, define it like: B for PORTB
#define LCD_RS_DDR      LCD_DDR
#define LCD_RS			(1 << 6)

#define LCD_E_DDR       LCD_DDR
#define LCD_E			(1 << 7)

#define LCD_DB4_DDR     LCD_DDR
#define LCD_DB4			(1 << 2)

#define LCD_DB5_DDR     LCD_DDR
#define LCD_DB5			(1 << 3)

#define LCD_DB6_DDR     LCD_DDR
#define LCD_DB6			(1 << 4)

#define LCD_DB7_DDR     LCD_DDR
#define LCD_DB7			(1 << 5)



// Functions:

// The argument is one of the instructions defined below.
void LCD_cmd(unsigned char);
// Put a character in current position.
void LCD_putc(unsigned char);
// Put string in current position.
void LCD_puts(char *);
// Change cursor to position (x,y).
void LCD_goto(unsigned char, unsigned char);
// Clear screen.
void LCD_clr(void);
// Go to home position.
void LCD_home(void);
// Initialize controller.
void LCD_init(void);

// HD44780 instructions:

#define HD44780_CLEAR					0x01

#define HD44780_HOME					0x02

#define HD44780_ENTRY_MODE				0x04
	#define HD44780_EM_SHIFT_CURSOR		0
	#define HD44780_EM_SHIFT_DISPLAY	1
	#define HD44780_EM_DECREMENT		0
	#define HD44780_EM_INCREMENT		2

#define HD44780_DISPLAY_ONOFF			0x08
	#define HD44780_DISPLAY_OFF			0
	#define HD44780_DISPLAY_ON			4
	#define HD44780_CURSOR_OFF			0
	#define HD44780_CURSOR_ON			2
	#define HD44780_CURSOR_NOBLINK		0
	#define HD44780_CURSOR_BLINK		1

#define HD44780_DISPLAY_CURSOR_SHIFT	0x10
	#define HD44780_SHIFT_CURSOR		0
	#define HD44780_SHIFT_DISPLAY		8
	#define HD44780_SHIFT_LEFT			0
	#define HD44780_SHIFT_RIGHT			4

#define HD44780_FUNCTION_SET			0x20
	#define HD44780_FONT5x7				0
	#define HD44780_FONT5x10			4
	#define HD44780_ONE_LINE			0
	#define HD44780_TWO_LINE			8
	#define HD44780_4_BIT				0
	#define HD44780_8_BIT				16

#define HD44780_CGRAM_SET				0x40
#define HD44780_DDRAM_SET				0x80
