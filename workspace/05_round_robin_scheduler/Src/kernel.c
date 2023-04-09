#include "kernel.h"

#define NUM_OF_THREADS	3
#define STACK_SIZE		100

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
	TCB_STACK[i][STACK_SIZE - 1] = (1U << 21);	/* PSR */

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
