#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include "stm32f4xx.h"

void kernelInit(void);
void startKernel(uint32_t quanta);
uint8_t kernelCreateThreads(void (*task0)(void), void (*task1)(void), void (*task2)(void));
void taskYield(void);

#endif
