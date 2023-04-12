################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/stm32f407xx_button.c \
../Src/stm32f407xx_delay.c \
../Src/stm32f407xx_led.c \
../Src/stm32f407xx_usart.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/stm32f407xx_button.o \
./Src/stm32f407xx_delay.o \
./Src/stm32f407xx_led.o \
./Src/stm32f407xx_usart.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/stm32f407xx_button.d \
./Src/stm32f407xx_delay.d \
./Src/stm32f407xx_led.d \
./Src/stm32f407xx_usart.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.d ./Src/main.o ./Src/main.su ./Src/stm32f407xx_button.d ./Src/stm32f407xx_button.o ./Src/stm32f407xx_button.su ./Src/stm32f407xx_delay.d ./Src/stm32f407xx_delay.o ./Src/stm32f407xx_delay.su ./Src/stm32f407xx_led.d ./Src/stm32f407xx_led.o ./Src/stm32f407xx_led.su ./Src/stm32f407xx_usart.d ./Src/stm32f407xx_usart.o ./Src/stm32f407xx_usart.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

