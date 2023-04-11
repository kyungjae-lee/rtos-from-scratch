#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include "stm32f4xx.h"

#define SR_UIF	(1U << 0)		// TIM2 Status Register (Update Interrupt Flag) bit[0]

void kernelInit(void);
void startKernel(uint32_t quanta);
uint8_t kernelCreateThreads(void (*task0)(void), void (*task1)(void), void (*task2)(void));
void taskYield(void);
void tim2_1hz_interrupt_init(void);


#endif
