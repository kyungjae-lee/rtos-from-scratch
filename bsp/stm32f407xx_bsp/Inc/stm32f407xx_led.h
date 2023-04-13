/*****************************************************************************************
 * @ File name		: stm32f407xx_button.h
 * @ Description	: Interface for LED driver
 * @ Author			: Kyungjae Lee
 * @ Date created	: 04/11/2023
 ****************************************************************************************/

#ifndef STM32F407xx_LED_H
#define STM32F407xx_LED_H

#include "stm32f407xx.h"

/* Initializes LEDs */
void led_init(void);

/* Green  LED */
void led_green_on(void);
void led_green_off(void);
void led_green_toggle(void);

/* Green  LED */
void led_orange_on(void);
void led_orange_off(void);
void led_orange_toggle(void);

/* Red  LED */
void led_red_on(void);
void led_red_off(void);
void led_red_toggle(void);

/* Blue  LED */
void led_blue_on(void);
void led_blue_off(void);
void led_blue_toggle(void);

#endif
