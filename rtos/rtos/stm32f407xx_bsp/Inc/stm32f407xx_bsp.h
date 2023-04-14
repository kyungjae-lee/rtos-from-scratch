/*****************************************************************************************
 * @ File name		: stm32f407xx_bsp.h
 * @ Description	: Header file for stm32f407xx board support package.
 * @ Author			: Kyungjae Lee
 * @ Date created	: 04/11/2023
 ****************************************************************************************/

#ifndef STM32F407xx_H
#define STM32F407xx_H

#include <stdint.h>

/* User LEDs */
#define LED_GREEN			(1U << 12)	/* PD12 */
#define LED_ORANGE			(1U << 13)	/* PD13 */
#define	LED_RED				(1U << 14)	/* PD14 */
#define LED_BLUE			(1U << 15)	/* PD15 */

#define LED_GREEN_MODE_OUTPUT		(1U << 24)
#define LED_ORANGE_MODE_OUTPUT		(1U << 26)
#define LED_RED_MODE_OUTPUT			(1U << 28)
#define LED_BLUE_MODE_OUTPUT		(1U << 30)

/* User button */
#define BUTTON				(1U << 0)	/* PA0 */

/* RCC */
#define RCC_BASE			0x40023800U
#define RCC_AHB1ENR			(*(uint32_t volatile *)(RCC_BASE + 0x30U))
#define RCC_APB1ENR			(*(uint32_t volatile *)(RCC_BASE + 0x40U))

/* GPIO */
#define GPIOA_BASE			0x40020000U
#define GPIOA_MODER			(*(uint32_t volatile *)(GPIOA_BASE + 0x00U))
#define GPIOA_IDR			(*(uint32_t volatile *)(GPIOA_BASE + 0x10U))
#define GPIOA_AFRL			(*(uint32_t volatile *)(GPIOA_BASE + 0x20U))

#define GPIOD_BASE			0x40020C00U
#define GPIOD_MODER			(*(uint32_t volatile *)(GPIOD_BASE + 0x00U))
#define GPIOD_ODR			(*(uint32_t volatile *)(GPIOD_BASE + 0x14U))

#define GPIOAEN				(1U << 0)	/* IO port A clock enable */
#define GPIODEN				(1U << 3)	/* IO port D clock enable */

/* Timer */
#define TIM3_BASE			0x40000400U
#define TIM3_CR1			(*(uint32_t volatile *)(TIM3_BASE + 0x00U))
#define TIM3_SR				(*(uint32_t volatile *)(TIM3_BASE + 0x10U))
#define TIM3_CNT			(*(uint32_t volatile *)(TIM3_BASE + 0x24U))
#define TIM3_PSC			(*(uint32_t volatile *)(TIM3_BASE + 0x28U))
#define TIM3_ARR			(*(uint32_t volatile *)(TIM3_BASE + 0x2CU))
#define CEN					(1U << 0)
#define TIM3EN				(1U << 1)	/* Timer 3 clock enable */

/* USART */
#define USART2_BASE		0x40004400U
#define USART2			(*(uint32_t volatile *)USART2_BASE)
#define USART2_SR		(*(uint32_t volatile *)(USART2_BASE + 0x00U))
#define USART2_DR		(*(uint32_t volatile *)(USART2_BASE + 0x04U))
#define USART2_BRR		(*(uint32_t volatile *)(USART2_BASE + 0x08U))
#define USART2_CR1		(*(uint32_t volatile *)(USART2_BASE + 0x0CU))
#define TE				(1U << 3)	// USART Control Register transmitter enable
#define UE				(1U << 13)	// USART Control Register USART enable
#define TXE				(1U << 7)	// USART Status Register Transmit data reg empty
#define USART2EN		(1U << 17)
#define USART_BAUDRATE	115200		// Desired USART baudrate (standard value)

/* Clock */
#define SYS_FREQ		16000000	// MCU data sheet "Clocks and Startup"
#define APB1_CLK		SYS_FREQ


/*****************************************************************************************
 * Enable / disable IRQ interrupts
 ****************************************************************************************/

/*
 * Enable IRQ interrupts (CMSIS)
 * Enables IRQ interrupts by clearing the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
/*
void __enable_irq(void)
{
  __asm volatile("cpsie i");
}
*/

/*
 * Disable IRQ interrupts (CMSIS)
 * Disables IRQ interrupts by clearing the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
/*
void __disable_irq(void)
{
  __asm volatile("cpsid i");
}
*/

#endif
