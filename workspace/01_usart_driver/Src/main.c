#include <stdio.h>
#include "led.h"
#include "usart.h"

int main(void)
{
	led_init();
	usart_tx_init();

	while (1)
	{
		printf("Hello from STM32F4.....\n");
	}
}
