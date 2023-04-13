/*****************************************************************************************
 * @ File name		: stm32f407xx_button.c
 * @ Description	: User button driver
 * @ Author			: Kyungjae Lee
 * @ Date created	: 04/11/2023
 ****************************************************************************************/

#include "stm32f407xx_button.h"

/* Initializes user button */
void button_init(void)
{
	/* Enable clock for GPIOA peripheral */
	RCC_AHB1ENR |= GPIOAEN;

	/* Set button pin mode to input mode */
	/* Clear */
	GPIOA_MODER &= ~(0x03U << 0);	/* Optional since this region will be 0 by default */
}

/* Reads the button input */
uint32_t button_read(void)
{
	return GPIOA_IDR & BUTTON;
}
