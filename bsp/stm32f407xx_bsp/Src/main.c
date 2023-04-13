/*****************************************************************************************
 * @ File name		: stm32f407xx_button.c
 * @ Description	: Test program for stm32f407xx peripheral drivers
 * @ Author			: Kyungjae Lee
 * @ Date created	: 04/11/2023
 ****************************************************************************************/

#include <stdio.h>
#include "stm32f407xx_button.h"
#include "stm32f407xx_delay.h"
#include "stm32f407xx_led.h"
#include "stm32f407xx_usart.h"

uint32_t buttonState;

int main(int argc, char *argv[])
{
	/* Initialize USART */
	usart_tx_init();
	printf("\rInitializing USART...\n\r");
	delay_ms(500); /* Inserted to test delay_ms function */

	/* Initialize LEDs */
	led_init();
	printf("Initializing LEDs...\n\r");
	delay_ms(500);

	/* Initialize button */
	button_init();
	printf("Initializing User Button...\n\r");
	delay_ms(500);

	/* Test USART */
	printf("Board support package test program running...\n\r");
	delay_ms(500);
	printf("Press user button (blue) to turn on all four LEDs.\n\r");

	/* Test button and LEDs */
	while (1)
	{
		/* Read in button state */
		buttonState = button_read();

		/* Button pressed */
		if (buttonState)
		{
			led_green_on();
			led_orange_on();
			led_red_on();
			led_blue_on();
		}
		/* Button released */
		else
		{
			led_green_off();
			led_orange_off();
			led_red_off();
			led_blue_off();
		}
	}
}
