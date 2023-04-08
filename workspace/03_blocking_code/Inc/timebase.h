#ifndef TIMEBASE_H
#define TIMEBASE_H

#include <stdint.h>

uint32_t get_tick(void);
void timebase_init(void);
void delay(uint32_t delay);


#endif
