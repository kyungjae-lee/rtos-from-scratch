#ifndef BSP_BUTTON_H
#define BSP_BUTTON_H

#include "stm32f407xx_bsp.h"

void bsp_button_init(void);
uint32_t bsp_button_read(void);

#endif
