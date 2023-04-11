#include <stdio.h>
#include "led.h"
#include "usart.h"
#include "kernel.h"

#define QUANTA 10	/* Round-Robin time quanta in ms. */

/* Task profilers to check if each task is running as intended. */
typedef uint32_t taskProfiler;
taskProfiler task0_profiler, task1_profiler, task2_profiler, task_periodic_profiler;

int32_t semaphore1, semaphore2;

void motor_run(void);
void motor_stop(void);
void valve_open(void);
void valve_close(void);

void task0(void)
{
	while (1)
	{
		//task0_profiler++;
		taskYield();	/* Once it increments its profiler, yield. */
	}
}

void task1(void)
{
	while (1)
	{
		//task1_profiler++;
		semaphoreWait(&semaphore1);
		motor_run();
		semaphoreSet(&semaphore2);
	}
}

void task2(void)
{
	while (1)
	{
		//task2_profiler++;
		semaphoreWait(&semaphore2);
		valve_open();
		semaphoreSet(&semaphore1);
	}
}


int main(void)
{
	/* Initialize USART */
	usart_tx_init();

	/* Initialize hardware timer. */
	tim2_1hz_interrupt_init();

	/* Initialize semaphores. */
	semaphoreInit(&semaphore1, 1);
	semaphoreInit(&semaphore2, 0);

	/* Initialize kernel. */
	kernelInit();

	/* Create tasks. */
	kernelCreateThreads(task0, task1, task2);	/* &task0, &task1, &task2 ? */

	/* Set the Round-Robin time quanta. */
	startKernel(QUANTA);
}

void TIM2_IRQHandler(void)
{
	/* Clear interrupt flag. */
	TIM2->SR &= ~SR_UIF;

	/* Do something */
	task_periodic_profiler++;

}

void motor_run(void)
{
	printf("Motor is starting...\n\r");
}

void motor_stop(void)
{
	printf("Motor is stopping...\n\r");
}

void valve_open(void)
{
	printf("Valve is opening...\n\r");
}

void valve_close(void)
{
	printf("Valve is closing...\n\r");
}



