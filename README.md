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

* To monitor USART message, STM32 Discovery board must be connected to the host machine via USB-to-Serial cable.

* Use **Screen** or **Minicom** utility to monitor USART message.

  Screen:

  ```plain
  screen [device] [baudrate]
  ```

  > e.g., `screen /dev/ttyUSB0 115200`
  >
  > `ctrl` + `a`, `k`, `y` to quit the screen session.

  Minicom

  ```plain
  minicom
  ```

  > `ctrl` + `a`, `x`, `Enter` to quit the minicom session.
  
* `delay` function uses the value from SysTick to spinlock the CPU. Not efficient because it is consuming CPU cycles for doing nothing. Better way is to use **blocking**.

* Context switch, exception entry: See "Exception Model" section of "Cortex-M4 Devices Generic User Guide."

* When analyzing a stack frame by locating it using the stack pointer, ignore the first two lower address words from the stack pointer. Why?

* Stack frame refers to the 8 data words (r0-r3, r12, LR, PC, xPSR) that get pushed onto stack upon stacking.

  (By inserting an address of another function which has an infinite loop in it, you can jump to one infinite loop to another. This is how the RTOS runs multiple tasks with infinite loops concurrently!)
  
* RTOS performance metrics:

  * Deadlines - Deriving the right results within a set time constraint.
  * Reliability - Running in predictable way with a guaranteed response.
  
* ARM assembly atomic instructions (Exclusive access instructions):

  * `ldrex` - Exclusive load
  * `strex` - Exclusive store

* Important registers of SysTick Timer peripheral to set up before using it:

  * SysTick Control and Status Register
    * Enable/disable the SysTick
  * SysTick Reload Value Register
    * Used to load the period of the SysTick; the period of that periodic clock
  * SysTick Current Value Register
    * Used to clear the initial value
  * SysTick Priority Register
    * Used to set the priority of the SysTick

* Steps to follow to used the SysTick Timer:

  1. Disable SysTick
  2. Set period
  3. Clear initial value
  4. Set priority
  5. Enable SysTick
  6. Set clock source
  7. Enable interrupt

* STM32 Discovery board boot sequence (Upon hardware/software reset):

  1. Sets all registers to their reset values (Values are defined in the MCU reference manual.)

  2. Determines boot mode by reading `BOOT0` and `BOOT1` pin values.

     * Depending on the pin values, boot modes can be "Main Flash memory", "System memory", "Embedded SRAM".
     * See the MCU reference manual "Boot configuration" section.

  3. Initialize stack pointer

     * Fetch MSP from the address 0x00000000 (i.e., the very first addressable memory address)

  4. Initialize program counter

     * Fetch PC from the address 0x00000004 (i.e., the second addressable memory address)

     * Stored in the address 0x00000004 is the address of the `Reset_Handler`.

       `Reset_Handler()` is a subroutine implemented in the `startup.S` file of every ARM Cortex project written in assembly code which tells the processor where the entry point (i.e., `main()`) of the program is.

* Since ARM Cortex-M4 processor only supports execution of instructions in **Thumb** state, the bit[0] of the program counter must always be set to 1. (Also, this bit is linked to the T bit of ESPR.)

  See [https://kyungjae.dev/embedded-systems-programming-arm/thumb-state-and-t-bit-of-epsr](https://kyungjae.dev/embedded-systems-programming-arm/thumb-state-and-t-bit-of-epsr)

* Process vs. Thread vs. Task

  * Process - Program in execution
    * Higher context switch overhead than threads
  * Thread - Task in execution
    * Lower context switch overhead than processes since they share resources other than stack which is private to each thread
  * Threads are part of a process, but not the other way around.

* Types of threads in RTOS:

  * Timed threads
    * Sporadic - Runs infrequently or never (e.g., a thread that runs only when a system exception occurs)
    * Periodic - Runs at a fixed time interval
    * Aperiodic - Runs frequently but runtime cannot be anticipated
  * Event triggered threads
    * Flag triggered - Runs depending on the flag state
    * Input triggered - Runs when there's an input available (e.g., a thread reading sensor data)
    * Output triggered - Runs when there's an output available (e.g., a thread sending data out to display) 
  * Main threads
    * These are the threads that runs when there are no threads to execute.

* Some key terms:

  * Non real-time - No guarantee of task execution
  * Real-time - Bounded latency, guarantees execution
  * Soft real-time - Executes on priority bases
  * Latency - Execution delay
  * Blocked state - Waiting state off the CPU

* TCB - Data structure containing information private to each thread
  * A TCB must have at least:
    * Pointer to its stack
    * Pointer to the next thread in the list
  * A TCB may additionally have:
    * Variable to hold thread status
    * Variable to hold thread ID
    * Variable to hold thread Period
    * Variable to hold thread burst time
    * Variable to hold thread priority
    * etc.

* Types of scheduling algorithm

  * Static vs. dynamic
    * Static - Task priorities are determined before the system runs
    * Dynamic - Determines task priorities as the system runs
  * Preemptive vs. Non-preemptive
    * Preemptive - Tasks can be preempted by periodic interrupts or a higher-priority task
      * Preemption is needed to guarantee fairness
      * Preemption needs an interrupt
      * Preemption helps meet deadlines
    * Non-preemptive - A task runs to its completion without getting preempted

  A scheduling algorithm can be any combination of these two categories:

  * Dynamic preemptive
  * Dynamic non-preemptive
  * Static preemptive
  * Static non-preemptive

* An ideal RTOS:

  * Maximizes Throughput
  * Minimizes Turnaround Time
  * Minimizes Response Time
  * Maximizes CPU utilization
  * Minimizes Scheduling Overhead

* Scheduler design considerations

  * Application requirements
    * Number of tasks
    * Resource requirements for each task
    * Release time for each task
    * Deadlines for each task
  * Platform specific requirements
    * Maximum context switching time
    * Maximum interrupt service latency
    * maximum communication delay

* To extend a basic Round-Robin scheduling algorithm to cooperative algorithm, allow tasks to yield execution if they completed their job earlier in the assigned time qunta.
* Naked function contains pure assembly code. The compiler does not generate prologue (disabling interrupts and pushing r4-r11 onto stask) and epilogue (enabling interrupts and popping r4-r11) for naked functions.
