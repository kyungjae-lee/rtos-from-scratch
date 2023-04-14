/*****************************************************************************************
 * @ File name		: kernel.h
 * @ Description	: Interface for kernel
 * @ Author			: Kyungjae Lee
 * @ Date created	: 04/11/2023
 ****************************************************************************************/

#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include "stm32f4xx.h"

/* Initializes kernel */
void kernel_init(void);

/* Starts kernel */
void start_kernel(void);

/* Creates three tasks */
uint8_t create_tasks(void (*task0)(void), void (*task1)(void), void (*task2)(void));

/*
 * Task calling this function will relinquish the CPU and trigger context switch for
 * other task to run.
 */
void task_yield(void);

#endif
