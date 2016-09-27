#include <avr/io.h>
#include <util/delay.h>
#include <avr/boot.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "blink_asdf.inc"

__attribute__ ((section ("boot"), noinline))
void writeStuff(){
	writeAll(0, asdf, asdf_len);
	__asm__("jmp 0");
}
__attribute__ ((section ("boot"), noinline))
void writeAll(uint16_t page, uint8_t* buf, uint16_t len){
	while(len>0){
		uint16_t to_write=SPM_PAGESIZE;
		if(len<SPM_PAGESIZE){
			to_write=len;
		}
		writePage(page, buf, to_write);
		len-=to_write;
		buf+=SPM_PAGESIZE;
		page+=SPM_PAGESIZE;
	}
	boot_rww_enable_safe();
}
__attribute__ ((section ("boot"), noinline))
void writePage(uint16_t page, uint8_t* buf, uint16_t len){
	boot_page_erase_safe (page);
	for (uint16_t i=0;i<SPM_PAGESIZE; i+=2){
		uint16_t w=0;
		if(i<len){
			w=buf[i]|(buf[i+1]<<8);
		}
		boot_page_fill_safe(page + i, w);
	}
	boot_page_write_safe(page);
}

int main(){
	writeStuff();
	DDRB|=1<<5;
	while(1){
		PORTB^=1<<5;
		_delay_ms(50);
	}
}
