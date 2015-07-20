#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

#include <avr/io.h>


// There are five channels by default.
// Communication  protocol:
// 1. Start pulse - ON for 3ms, OFF for 0.5ms
// 2. Five channels, each encoded as:
//    - ON  for 1-2ms
//    - OFF for 2-1ms
//      (the exact number corresponds to analog value of that channel)

// DEFINES:

// Synchronize pulse width. Should be at least 30% bigger than MAX_CHANNEL
// - otherwise the receiver won't be able to differentiate between start signal
// and normal one.
#define START_PULSE_ON  3000
// This one does not have to be very wide - it only has to be readily recognizable
// by the receiver.
#define START_PULSE_OFF 500
// Pulse widths corresponding to minimal and maximum values of channel.
#define MIN_CHANNEL     1000
#define MAX_CHANNEL     2000

// Number of independent channels.
#define CHANNEL_COUNT   5

// Transmitter data pin port and pin.
#define TRANSMITTER_DDRX D
#define TRANSMITTER_PIN 2

// GLOBAL VARIABLES:

// This is an array containing values of channels.
volatile uint8_t channels[CHANNEL_COUNT];
// You might notice a slight lag in either transmitter or receiver, hardware or software.
// Regardless of source of this discrepancy, I created a variable allowing to dynamically
// fine tune the HIGH pulse width. In my case, value of 30 improves the accuracy by about 10%.
volatile int16_t pulse_fine_tune;

// FUNCTIONS:

void init_transmission();

#endif
