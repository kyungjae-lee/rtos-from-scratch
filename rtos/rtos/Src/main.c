#include <stdio.h>
#include "stm32f407xx_led.h"
#include "stm32f407xx_usart.h"
#include "kernel.h"

void task0_handler(void);
void task1_handler(void);
void task2_handler(void);

int main(void)
{
	/* Initialize USART */
	usart_tx_init();
	printf("Initializing USART...\n\r");

	/* Initialize USART */
	led_init();
	printf("Initializing LEDs...\n\r");

	/* Initialize kernel */
	kernel_init();
	printf("Initializing kernel...\n\r");

	/* Create tasks */
	create_tasks(task0_handler, task1_handler, task2_handler);
	printf("Creating tasks...\n\r");

	/* Start kernel */
	start_kernel();
	printf("Starting kernel...\n\r");
}

void task0_handler(void)
{
	while (1)
	{
		//printf("task0\n\r");
		led_green_off();
		led_blue_on();
	}
}

void task1_handler(void)
{
	while (1)
	{
		//printf("task1\n\r");
		led_blue_off();
		led_red_on();
	}
}

void task2_handler(void)
{
	while (1)
	{
		//printf("task2\n\r");
		led_red_off();
		led_green_on();
	}
}
