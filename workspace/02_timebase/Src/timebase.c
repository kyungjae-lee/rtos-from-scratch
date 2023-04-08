#include "timebase.h"
#include "stm32f4xx.h"

#define ONE_SEC_LOAD		16000000	// Since default system clock is 16 MHz, 1 sec is 16M cycles.

/* SysTick Control and Status Register bit settings. */
#define CTRL_ENABLE 		(1U << 0)	// Enable the counter.
#define CTRL_TICKINT		(1U << 1)	// Enable SysTick exception request.
#define CTRL_CLKSRC			(1U << 2)	// Clock source = processor clock.
#define CTRL_COUNTFLAG		(1U << 16)	// Return 1 if timer counted to 0 since last time this was read.

#define MAX_DELAY			0xFFFFFFFFU

volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;	// Current tick prime.
volatile uint32_t tick_freq = 1;	// For every SysTick timer expiration, global tick increases this much.

/*
 * Delay in seconds.
 * This function uses the value from SysTick to spinlock the CPU.
 * SysTick is generating 1 s interrupt rate.
 */
void delay(uint32_t delay)
{
	uint32_t tickstart = get_tick();
	uint32_t wait = delay;

	if (wait < MAX_DELAY)
	{
		wait += (uint32_t)(tick_freq);
	}

	while ((get_tick() - tickstart) < wait) {}
}

void tick_increment(void)
{
	g_curr_tick += tick_freq;
}

uint32_t get_tick(void)
{
	__disable_irq();	// Synchronizing access to the global variable.
	g_curr_tick_p = g_curr_tick;
	__enable_irq();

	return g_curr_tick_p;
}

void timebase_init(void)
{
	/* Reload the timer with the number of cycles per second. */
	SysTick->LOAD = ONE_SEC_LOAD - 1;	// Since counting includes 0.

	/* Clear SysTick current value register. */
	SysTick->VAL = 0;

	/* Select internal clock source. */
	SysTick->CTRL |= CTRL_CLKSRC;

	/* Enable SysTick interrupt. */
	SysTick->CTRL |= CTRL_TICKINT;

	/* Enable counter. */
	SysTick->CTRL |= CTRL_ENABLE;

	/* Enable global interrupts. */
	__enable_irq();

}

void SysTick_Handler(void)
{
	tick_increment();
}
