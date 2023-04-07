#include "led.h"

#define GPIODEN			(1U << 3)	// 0b 0000 0000 0000 0000 0000 0000 0000 1000
#define LED_ORANGE		(1U << 13)

void led_init(void)
{
	/* Enable clock access to LED port (Port D) */
	RCC->AHB1ENR |= GPIODEN;

	/* Set LED pin as output pin */
	GPIOD->MODER |= (1U << 26);
	GPIOD->MODER &= ~(1U << 27);
}

void led_on(void)
{
	/* Set LED pin to high (PD13) */
	GPIOD->ODR |= LED_ORANGE;
}

void led_off(void)
{
	/* Set LED pin to low (PD13) */
	GPIOD->ODR &= ~LED_ORANGE;
}
