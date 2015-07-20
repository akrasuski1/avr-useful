#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <stdint.h>

// Protocol constants. See explanation in transmitter code.
////////////////////////////////
#define START_PULSE_ON    3000//
#define START_PULSE_OFF   500 //
#define MIN_CHANNEL       1000//
#define MAX_CHANNEL       2000//
#define CHANNEL_COUNT     5   //
////////////////////////////////

// How big deviation from expected minimal/maximal pulse length should
// be tolerated. If bigger deviation occurs, data packet is thrown away.
#define RECEIVE_TOLERANCE 0.1

// Port and pin of data pin of the receiver.
#define RECEIVER_DDR DDRC
#define RECEIVER_PIN 5

// Depending on the choice of pin above, you will have to use different interrupt.
// Please consult the datasheet and fill these values in.
#define SET_RECEIVER_INTERRUPT_FLAGS() \
	PCICR|=1<<PCIE1;                   \
	PCMSK1|=1<<PCINT13

#define RECEIVER_INTERRUPT_VECTOR PCINT1_vect

// Array of last known channel values.
volatile uint8_t  channels[CHANNEL_COUNT];
// Data of last correct packet updating given channel.
volatile uint64_t last_updated_at[CHANNEL_COUNT];


void receiver_init();


#endif
