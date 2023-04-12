/*****************************************************************************************
 * @ File name		: stm32f407xx_button.c
 * @ Description	: Test program for stm32f407xx board support package (BSP)
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

	/* Initialize LEDs */
	led_init();

	/* Initialize button */
	button_init();

	/* Test USART */
	printf("\n\rBoard support package test!\n\r");
	printf("Press user button (blue) to turn on all four LEDs.\n\r");

	/* Test button and LEDs */
	while (1)
	{
		buttonState = button_read();

		if (buttonState)
		{
			led_green_on();
			led_orange_on();
			led_red_on();
			led_blue_on();
		}
		else
		{
			led_green_off();
			led_orange_off();
			led_red_off();
			led_blue_off();
		}
	}
}
