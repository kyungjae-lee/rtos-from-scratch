#include <stdio.h>
#include "led.h"
#include "usart.h"
#include "timebase.h"

int main(void)
{
	led_init();
	usart_tx_init();
	timebase_init();

	while (1)
	{
		delay(1);
		printf("A second just occurred!\n\r");
	}
}
