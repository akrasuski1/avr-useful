#include <avr/io.h>
#include <avr/delay.h>
#include "DS18B20.h"
#include "macros.h"
#include <util/crc16.h>


#define DS18B20_PORT PORT(DS18B20_DDRX)
#define DS18B20_DDR  DDR(DS18B20_DDRX)
#define DS18B20_PIN  PIN(DS18B20_DDRX)

// Workaround - _delay_us(x) has too big overhead.
#define DS18B20_PRECISE_DELAY(t) _delay_loop_2(F_CPU/4/1000000*t)

uint8_t ds18b20_reset(){
	// reset pulse
	SET_LOW(DS18B20_PORT, DS18B20_DQ);
	SET_OUTPUT(DS18B20_DDR,DS18B20_DQ);
	DS18B20_PRECISE_DELAY(480);

	// presence pulse
	SET_INPUT(DS18B20_DDR, DS18B20_DQ);
	DS18B20_PRECISE_DELAY(100);
	if(IS_HIGH(DS18B20_PIN, DS18B20_DQ)){
		return 0; // not present
	}
	DS18B20_PRECISE_DELAY(380);
	if(IS_LOW(DS18B20_PIN, DS18B20_DQ)){
		return 0; // not present
	}

	return 1;
}

void ds18b20_write_bit(uint8_t bit){
	// synchronize
	SET_OUTPUT(DS18B20_DDR, DS18B20_DQ);
	SET_LOW(DS18B20_PORT, DS18B20_DQ);
	DS18B20_PRECISE_DELAY(2);

	// put bit
	if(bit){
		SET_HIGH(DS18B20_PORT, DS18B20_DQ);
	}
	DS18B20_PRECISE_DELAY(60);

	// release line
	SET_INPUT(DS18B20_DDR, DS18B20_DQ);
	SET_LOW(DS18B20_PORT, DS18B20_DQ);
	DS18B20_PRECISE_DELAY(2);
}

void ds18b20_write_byte(uint8_t byte){
	for(int8_t i=0;i<8;i++){
		ds18b20_write_bit(byte&1);
		byte>>=1;
	}
}

uint8_t ds18b20_read_bit(){
	// synchronize
	SET_LOW(DS18B20_PORT, DS18B20_DQ);
	SET_OUTPUT(DS18B20_DDR, DS18B20_DQ);
	DS18B20_PRECISE_DELAY(2);

	// wait until thermometer puts bit
	SET_INPUT(DS18B20_DDR, DS18B20_DQ);
	DS18B20_PRECISE_DELAY(5);

	// read it
	uint8_t ret=IS_HIGH(DS18B20_PIN, DS18B20_DQ);
	DS18B20_PRECISE_DELAY(60);

	return ret;
}

uint8_t ds18b20_read_byte(){
	uint8_t ret=0;
	for(uint8_t i=0;i<8;i++){
		ret>>=1;
		ret|=ds18b20_read_bit()<<7;
	}
	return ret;
}

uint8_t ds18b20_check_crc(){
	if(!ds18b20_reset()){
		return 0;
	}
	ds18b20_write_byte(DS18B20_SKIP_ROM);
	ds18b20_write_byte(DS18B20_READ_SCRATCHPAD);
	uint8_t crc=0;
	for(int8_t i=0;i<9;i++){
		_crc_ibutton_update(crc,ds18b20_read_byte());
	}
	return !crc;
}

uint8_t ds18b20_set_precision(uint8_t prec){
	if(!ds18b20_reset()){
		return 0;
	}
	ds18b20_write_byte(DS18B20_SKIP_ROM);
	ds18b20_write_byte(DS18B20_WRITE_SCRATCHPAD);
	ds18b20_write_byte(0);
	ds18b20_write_byte(0);
	ds18b20_write_byte((prec<<5)|0x1f);
	//check crc
	if(!ds18b20_check_crc()){
		return 0;
	}

	return 1;
}

uint8_t ds18b20_read_temp(double* temp, uint8_t prec){
	if(!ds18b20_set_precision(prec)){
		return 0;
	}
	if(!ds18b20_reset()){
		return 0;
	}
	ds18b20_write_byte(DS18B20_SKIP_ROM);
	ds18b20_write_byte(DS18B20_CONVERT_T);

	// provide power
	SET_OUTPUT(DS18B20_DDR, DS18B20_DQ);
	SET_HIGH (DS18B20_PORT, DS18B20_DQ);
	for(int8_t i=0;i<(1<<prec);i++){
		_delay_ms(93.75);
	}
	if(!ds18b20_reset()){
		return 0;
	}
	ds18b20_write_byte(DS18B20_SKIP_ROM);
	ds18b20_write_byte(DS18B20_READ_SCRATCHPAD);

	uint8_t crc=0;
	uint8_t l=ds18b20_read_byte();
	_crc_ibutton_update(crc,l);

	uint8_t h=ds18b20_read_byte();
	_crc_ibutton_update(crc,h);

	for(int8_t i=0;i<7;i++){
		_crc_ibutton_update(crc,ds18b20_read_byte());
	}
	if(crc){
		return 0;
	}
	int16_t t=(h<<8)+l;
	*temp=t*0.0625;
	return 1;
}
