#include "led.h"

int main(void)
{
	led_init();

	while (1)
	{
		led_on();
		for (int i = 0; i < 1000000; i++);
		led_off();
		for (int i = 0; i < 1000000; i++);
	}
}
