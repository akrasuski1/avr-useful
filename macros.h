#ifndef MACROS_H_
#define MACROS_H_

#include <stdint.h>

// Generic port, ddr and pin:
#define PORT_(port) PORT ## port
#define DDR_(port)  DDR  ## port
#define PIN_(port)  PIN  ## port

#define PORT(port) PORT_(port)
#define DDR(port)  DDR_(port)
#define PIN(port)  PIN_(port)


// General SETs and READs
#define SET_LOW(D, P)     D&=~_BV(P)
#define SET_HIGH(D, P)    D|=_BV(P)

#define IS_LOW(D, P)     (!(D&_BV(P)))
#define IS_HIGH(D, P)    (!IS_LOW(D,P))

#define SET_OUTPUT(D, P) SET_HIGH(D, P)
#define SET_INPUT(D, P)  SET_LOW(D, P)

typedef volatile uint8_t* reg_t;

#endif
