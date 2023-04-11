#include "kernel.h"

#define NUM_OF_THREADS	3
#define STACK_SIZE		400

#define BUS_FREQ		16000000

/* SysTick Control and Status Register bit settings. */
#define CTRL_ENABLE 		(1U << 0)	// Enable the counter.
#define CTRL_TICKINT		(1U << 1)	// Enable SysTick exception request.
#define CTRL_CLKSRC			(1U << 2)	// Clock source = processor clock.
#define CTRL_COUNTFLAG		(1U << 16)	// Return 1 if timer counted to 0 since last time this was read.
#define SYSTICK_RST			0

/* Interrupt Control and State Register */
#define ICSR 				(*((volatile uint32_t *)0xE000ED04))
#define PEND_SYSTICK		(1U << 26)

#define TIM2EN				(1U << 0)
#define CR1_CEN				(1U << 0)	// Timer2 CR1 CEN (Counter Enable) bit[0]
#define DIER_UIE			(1U << 0)	// DMA/Interrupt enable register - Update interrupt enable (UIE) bit[0]

void startScheduler(void);

uint32_t MILLIS_PRESCALER;

typedef struct tcb {
	int32_t *pStack;
	struct tcb *pNext;
} tcbType;

tcbType tcbs[NUM_OF_THREADS];

tcbType *pCurr;

/* Each thread will have stack of size 100, i.e., 400 bytes */
int32_t TCB_STACK[NUM_OF_THREADS][STACK_SIZE];

void kernelStackInit(int i)
{
	/* ARM Cortex-M processor's stack model is "Full Descending". */
	/* Stack frame: {r0, r1, r2, r3, r12, LR, PC, xPSR} */

	/* Initialize stack pointer. */
	tcbs[i].pStack = &TCB_STACK[i][STACK_SIZE - 16];	/* Top of stack */

	/* Initialize PSR (Set bit[21] (T-bit) to operate in Thumb mode). */
	TCB_STACK[i][STACK_SIZE - 1] = (1U << 24);	/* PSR */

	/* PC will be initialized somewhere else. */

	/* The following is for debugging purpose only. Stack initialization will still work
	 * without this part. */
	/* Initialize the rest of the stack content to easily recognizable data. */
	TCB_STACK[i][STACK_SIZE - 3] = 	0xAAAAAAAA;	/* r14 (LR) */
	TCB_STACK[i][STACK_SIZE - 4] = 	0xAAAAAAAA;	/* r12 */
	TCB_STACK[i][STACK_SIZE - 5] = 	0xAAAAAAAA;	/* r3 */
	TCB_STACK[i][STACK_SIZE - 6] = 	0xAAAAAAAA;	/* r2 */
	TCB_STACK[i][STACK_SIZE - 7] = 	0xAAAAAAAA;	/* r1 */
	TCB_STACK[i][STACK_SIZE - 8] = 	0xAAAAAAAA;	/* r0 */

	TCB_STACK[i][STACK_SIZE - 9] = 	0xAAAAAAAA;	/* r11 */
	TCB_STACK[i][STACK_SIZE - 10] =	0xAAAAAAAA;	/* r10 */
	TCB_STACK[i][STACK_SIZE - 11] =	0xAAAAAAAA;	/* r9 */
	TCB_STACK[i][STACK_SIZE - 12] =	0xAAAAAAAA;	/* r8 */
	TCB_STACK[i][STACK_SIZE - 13] =	0xAAAAAAAA;	/* r7 */
	TCB_STACK[i][STACK_SIZE - 14] =	0xAAAAAAAA;	/* r6 */
	TCB_STACK[i][STACK_SIZE - 15] =	0xAAAAAAAA;	/* r5 */
	TCB_STACK[i][STACK_SIZE - 16] =	0xAAAAAAAA;	/* r4 */
}

uint8_t kernelCreateThreads(void (*task0)(void), void (*task1)(void), void (*task2)(void))
{
	/* Disable global interrupts. */
	__disable_irq();

	/* Initialize next pointers of each TCB. */
	tcbs[0].pNext = &tcbs[1];
	tcbs[1].pNext = &tcbs[2];
	tcbs[2].pNext = &tcbs[0];

	/* Initialize stack for thread0. */
	kernelStackInit(0);
	/* Initialize PC */
	TCB_STACK[0][STACK_SIZE - 2] = (uint32_t)task0;

	/* Initialize stack for thread0. */
	kernelStackInit(1);
	/* Initialize PC */
	TCB_STACK[1][STACK_SIZE - 2] = (uint32_t)task1;

	/* Initialize stack for thread0. */
	kernelStackInit(2);
	/* Initialize PC */
	TCB_STACK[2][STACK_SIZE - 2] = (uint32_t)task2;

	/* Start scheduling with thread0. */
	pCurr = &tcbs[0];

	/* Enable global interrupts. */
	__enable_irq();

	return 1;
}

void kernelInit(void)
{
	MILLIS_PRESCALER = (BUS_FREQ / 1000);	/* Seconds to milliseconds */
}

void startKernel(uint32_t quanta)
{
	/* Reset SysTick. */
	SysTick->CTRL = SYSTICK_RST;

	/* Clear SysTick Current Value Register. */
	SysTick->VAL = 0;

	/* Load quanta. */
	SysTick->LOAD = (quanta * MILLIS_PRESCALER) - 1;

	/* Set SysTick to low priority. */
	NVIC_SetPriority(SysTick_IRQn, 15);

	/* Enable SysTick interrupt, select internal clock. */
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	/* Enable SysTick interrupt. */
	SysTick->CTRL |= CTRL_TICKINT;

	/* Launch scheduler. */
	startScheduler();
}

/*
 * If a function is defined as a "Naked" function, the prologue and epilogue
 * will not be generated during compilation. This function is defined as a
 * naked function since we want to keep the stack pointer as is when entering
 * this function.
 */
 __attribute__((naked)) void SysTick_Handler(void)
{
	 /*
	  * Switch-out current task.
	  */

	 /* Disable global interrupts. */
	 __asm("cpsid i");

	 /* Push r4-r11 on to stack since they are not part of those registers (stack frame)
	  * that get pushed onto stack automatically by the processor as an exception entry
	  * sequence. */
	 __asm("push {r4-r11}");

	 /* Load r0 with the address of the pCurr (&pCurr). */
	 __asm("ldr r0, =pCurr");

	 /* Load r1 with pCurr. */
	 __asm("ldr r1, [r0]");

	 /* Store the sp into the current TCB's pStack. This works because pStack is the
	  * first member of a TCB struct. Start address of a TCB is the same as the address
	  * of its pStack. */
	 __asm("str sp, [r1]");


	 /*
	  * Switch-in next task.
	  */

	 /* Load r1 with pCurr->pNext. [r1] <- [[r1] + 4];  */
	 __asm("ldr r1, [r1, #4]");

	 /* Store r1 into the address r0 points to. pCurr = pCurr->next; Advance pCurr. */
	 __asm("str r1, [r0]");

	 /* Load SP with r1 value. Load SP with the SP of the next task to run. */
	 __asm("ldr sp, [r1]");

	 /* Pop (restore) r4-r11 from stack. Rest of the registers will be automatically popped
	  * by the processor as an exception exit sequence. */
	 __asm("pop {r4-r11}");

	 /* Enable global interrupts. */
	 __asm("cpsie i");

	 /* Return from the subroutine. */
	 __asm("bx lr");

	 /* At the exit of exception, registers r0-r3, r12, lr, pc, psr will be automatically
	  * restored from stack by the processor. */
}

/*
 * Launches the very first task by updating the processor's SP to the first task's SP, and
 * restoring the first task's context.
 */
void startScheduler(void)
{
	/* Disable global interrupts. */
	// __asm("cpsid i");	// Do we need synchronization here?

	/* Load r0 with the address of pCurr. */
	__asm("ldr r0, =pCurr");

	/* Load r2 with pCurr. [r2] <- [[r0]]; */
	__asm("ldr r2, [r0]");

	/* Load sp with [r2]. sp = pCurr->pStack. */
	__asm("ldr sp, [r2]");

	/* Pop (restore) r4-r11 from stack. */
	__asm("pop {r4-r11}");

	/* Pop (restore) r0-r3 from stack. */
	__asm("pop {r0-r3}");

	/* Pop (restore) r12 from stack. */
	__asm("pop {r12}");

	/* Skip LR in the stack. */
	__asm("add sp, sp, #4");

	/* Update processor's LR with the PC value in the stack. */
	__asm("pop {lr}");

	/* Skip PSR in the stack. */
	__asm("add sp, sp, #4");

	/* Enable global interrupts. */
	// __asm("cpsie i");	// why enable when we didn't even disable in the first place?

	 /* Return from the subroutine.*/
	 __asm("bx lr");

}

void taskYield(void)
{
	/* Clear SysTick Current Value Register. */
	SysTick->VAL = 0;

	/* Trigger SysTick.
	 * Interrupt Control and State Register -> bit[26]: SysTick exception set-pending bit.
	 * Set bit[26] to 1. */
	ICSR |= PEND_SYSTICK;
	/* OR? or assign? Teaching assistant is saying, we are forcing SysTick to generate
	 * exception in order to switch to the next thread so, we are clearing everything
	 * and generate only SysTick exception. */
}

void tim2_1hz_interrupt_init(void)
{
	/* Enable clock access to tim2. */
	RCC->APB1ENR |= TIM2EN;

	/* Set timer prescaler. */
	TIM2->PSC = 1600 - 1;	/* (Default clock = 16 MHz) / (PSC+1 = 1600) = 10 000 */

	/* Set auto-reload value. */
	TIM2->ARR = 10000 - 1; 	/* (10000 / 10000) = 1 Hz */

	/* Clear counter. */
	TIM2->CNT = 0;

	/* Enable timer. */
	TIM2->CR1 |= CR1_CEN;

	/* Enable timer interrupt. */
	TIM2->DIER |= DIER_UIE;

	/* Enable timer interrupt in NVIC. */
	NVIC_EnableIRQ(TIM2_IRQn);
}











