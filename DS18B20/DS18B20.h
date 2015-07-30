#ifndef DS18B20_H_
#define DS18B20_H_

// This library is used to read temperature from DS18B20 sensor. I created it, because none of the
// libraries I checked seemed to work. I struggled to make this do its job - and now I guess I know
// what caused the other libraries to fail - it's avr's _delay_us function. Thanks to my logic analyzer
// I managed to debug the problem - it turned out there is an overhead in that function, so that
// _delay_us(1) would actually take over 40us! As a workaround, I used assembly function as a macro.

// Pinout:
#define DS18B20_DDRX D
#define DS18B20_DQ   2

// DS18B20 commands from datasheet:
#define DS18B20_SEARCH_ROM 0xF0
#define DS18B20_READ_ROM 0x33
#define DS18B20_MATCH_ROM 0x55
#define DS18B20_SKIP_ROM 0xCC
#define DS18B20_ALARM_SEARCH 0xEC

#define DS18B20_CONVERT_T 0x44
#define DS18B20_READ_SCRATCHPAD 0xBE
#define DS18B20_WRITE_SCRATCHPAD 0x4E
#define DS18B20_COPY_SCRATCHPAD 0x48
#define DS18B20_RECALL_E2 0xB8
#define DS18B20_READ_POWER_SUPPLY 0xB4

// Functions:
// (return 1 on success, 0 on failure)

// prec | resolution        | conversion time
// =====+===================+================
//    0 | 9 bits      0.5*C | 93.75ms
//    1 | 10 bits    0.25*C | 187.5ms
//    2 | 11 bits   0.125*C | 375ms
//    3 | 12 bits  0.0625*C | 750ms
uint8_t ds18b20_set_precision(uint8_t prec);
uint8_t ds18b20_read_temp(double* temp, uint8_t prec);

#endif
