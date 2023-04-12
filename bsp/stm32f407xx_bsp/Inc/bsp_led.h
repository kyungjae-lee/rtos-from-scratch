#ifndef BSP_LED_H
#define BSP_LED_H

#include <stdint.h>
#include "stm32f407xx_bsp.h"

void bsp_led_init(void);

void bsp_led_green_on(void);
void bsp_led_green_off(void);
void bsp_led_green_toggle(void);

void bsp_led_orange_on(void);
void bsp_led_orange_off(void);
void bsp_led_orange_toggle(void);

void bsp_led_red_on(void);
void bsp_led_red_off(void);
void bsp_led_red_toggle(void);

void bsp_led_blue_on(void);
void bsp_led_blue_off(void);
void bsp_led_blue_toggle(void);

#endif
