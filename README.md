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
