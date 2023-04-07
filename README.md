# Real-Time Operating System (RTOS) From Scratch



## Introduction

Developing a real-time operating system (RTOS) from scratch.



## Development Environment

* Board - STM32F407 Discovery board (ARM Cortex-M4 Processor)
* IDE - STM32CubeIDE
* OS - Ubuntu 22.04 LTS



## Lessons Learned

* STM32CubeIDE include paths setting must be specified to the very folder which includes the file to be searched.

* To add a symbol:

  `Project` $\to$ `Properties` $\to$ `C/C++ General` $\to$ `Paths and Symbols` $\to$ `Symbols` $\to$ `Add`

  Had to add `STM32F407xx` to the symbol list to fix the following error:

  > Please select first the target STM32F4xx device used in your application (in stm32f4xx.h file)
  
* CMSIS and Reference Manual naming convention 

  e.g., RCC_AHB1ENR $\to$ "RCC" is the name of the structure, "AHB1ENR" is the name of the member within the structure.
  
* To use any peripheral, enable its clock first.

* Checked "Alternate function mapping" table of the MCU data sheet to find the USART pins.