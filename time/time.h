#ifndef TIME_H_
#define TIME_H_

#include <stdint.h>

// This library gives you a stopwatch - you can reset it, or
// take a reading in us or ms. TIMER2 is used here and its
// overflow interrupt.

uint64_t _time_overflow_cnt;

void time_reset();
uint64_t time_us();
uint64_t time_ms();

#endif
