#ifndef BSP_BUTTON_H
#define BSP_BUTTON_H

#include <stm32f407xx.h>

void button_init(void);
uint32_t button_read(void);

#endif
