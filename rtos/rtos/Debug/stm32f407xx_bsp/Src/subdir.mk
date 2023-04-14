################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32f407xx_bsp/Src/stm32f407xx_button.c \
../stm32f407xx_bsp/Src/stm32f407xx_delay.c \
../stm32f407xx_bsp/Src/stm32f407xx_led.c \
../stm32f407xx_bsp/Src/stm32f407xx_usart.c 

OBJS += \
./stm32f407xx_bsp/Src/stm32f407xx_button.o \
./stm32f407xx_bsp/Src/stm32f407xx_delay.o \
./stm32f407xx_bsp/Src/stm32f407xx_led.o \
./stm32f407xx_bsp/Src/stm32f407xx_usart.o 

C_DEPS += \
./stm32f407xx_bsp/Src/stm32f407xx_button.d \
./stm32f407xx_bsp/Src/stm32f407xx_delay.d \
./stm32f407xx_bsp/Src/stm32f407xx_led.d \
./stm32f407xx_bsp/Src/stm32f407xx_usart.d 


# Each subdirectory must supply rules for building sources it contributes
stm32f407xx_bsp/Src/%.o stm32f407xx_bsp/Src/%.su: ../stm32f407xx_bsp/Src/%.c stm32f407xx_bsp/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407xx -c -I../Inc -I"/home/klee/repos/rtos-from-scratch/rtos/rtos/stm32f407xx_bsp/Inc" -I"/home/klee/repos/rtos-from-scratch/rtos/rtos/chip-headers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/klee/repos/rtos-from-scratch/rtos/rtos/chip-headers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-stm32f407xx_bsp-2f-Src

clean-stm32f407xx_bsp-2f-Src:
	-$(RM) ./stm32f407xx_bsp/Src/stm32f407xx_button.d ./stm32f407xx_bsp/Src/stm32f407xx_button.o ./stm32f407xx_bsp/Src/stm32f407xx_button.su ./stm32f407xx_bsp/Src/stm32f407xx_delay.d ./stm32f407xx_bsp/Src/stm32f407xx_delay.o ./stm32f407xx_bsp/Src/stm32f407xx_delay.su ./stm32f407xx_bsp/Src/stm32f407xx_led.d ./stm32f407xx_bsp/Src/stm32f407xx_led.o ./stm32f407xx_bsp/Src/stm32f407xx_led.su ./stm32f407xx_bsp/Src/stm32f407xx_usart.d ./stm32f407xx_bsp/Src/stm32f407xx_usart.o ./stm32f407xx_bsp/Src/stm32f407xx_usart.su

.PHONY: clean-stm32f407xx_bsp-2f-Src

