#ifndef PING_H_
#define PING_H_

// This library allows you to read distance using HC-SR04
// ultrasonic sensor.
// Note: it uses "time.h" library (and resets it), which in
// turn takes ATmega's TIMER2.

#define PING_TRIG_DDR B
#define PING_TRIG_PIN 0

#define PING_ECHO_DDR B
#define PING_ECHO_PIN 1

// Timeout in microseconds (default corresponds to about 6 meters)
#define PING_TIMEOUT 40000ULL


// Functions:

//Initialize the library.
void ping_init();
// Returns distance in millimeters.
// If no object found, returns max range.
// This is a blocking call - will take
// a few milliseconds for standard uses.
float check_ping();


#endif
