#ifndef SERVO_H_
#define SERVO_H_

// This library works correctly for ATmega328P - the one commonly used in Arduino UNO.
// I do not guarantee that pins and processor registers are same in other devices.

// This library uses TIMER1 to generate PWM pulses. Hardware allows to do it in 16-bit
// precision only on pins 1 and 2 of PORTB, so this library assumes that case. Using
// this code in other way may cause undesired behavior.


// All times are in microseconds:
#define SERVO_DEFAULT_PULSE 0
#define SERVO_PERIOD 20000ULL



void servos_init();

void add_servo(uint8_t pin);
void remove_servo(uint8_t pin);

// In many servos, settings are:
// a) 1000-2000 - normal work, 1000 being the leftmost setting,
//    and 2000 the rightmost.
// b) 0 - disabling the servo.
void set_servo(uint8_t pin, uint16_t pulse);


#endif
