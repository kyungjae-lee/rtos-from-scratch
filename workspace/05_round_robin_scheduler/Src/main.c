#include <stdio.h>
#include "led.h"
#include "usart.h"
#include "kernel.h"

#define QUANTA 10	/* Round-Robin time quanta 10 ms. */

/* Task profilers to check if each task is running as intended. */
typedef uint32_t taskProfiler;
taskProfiler task0_profiler, task1_profiler, task2_profiler;

void motor_run(void);
void motor_stop(void);
void valve_open(void);
void valve_close(void);

void task0(void)
{
	while (1)
	{
		task0_profiler++;
		//motor_run();
		printf("task0\n\r");
	}
}

void task1(void)
{
	while (1)
	{
		task1_profiler++;
		//valve_open();
	}
}

void task2(void)
{
	while (1)
	{
		task2_profiler++;
	}
}


int main(void)
{
	/* Initialize kernel. */
	kernelInit();

	/* Create tasks. */
	kernelCreateThreads(&task0, &task1, &task2);	/* &task0, &task1, &task2 ? */

	/* Set the Round-Robin time quanta. */
	startKernel(QUANTA);
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
