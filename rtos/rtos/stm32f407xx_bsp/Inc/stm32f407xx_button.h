/*****************************************************************************************
 * @ File name		: stm32f407xx_button.h
 * @ Description	: Interface for button driver
 * @ Author			: Kyungjae Lee
 * @ Date created	: 04/11/2023
 ****************************************************************************************/

#ifndef BSP_BUTTON_H
#define BSP_BUTTON_H

#include <stm32f407xx_bsp.h>

void button_init(void);
uint32_t button_read(void);

#endif
