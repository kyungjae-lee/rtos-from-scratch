################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/bsp_button.c \
../Src/bsp_delay.c \
../Src/bsp_led.c \
../Src/bsp_usart.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/bsp_button.o \
./Src/bsp_delay.o \
./Src/bsp_led.o \
./Src/bsp_usart.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/bsp_button.d \
./Src/bsp_delay.d \
./Src/bsp_led.d \
./Src/bsp_usart.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/bsp_button.d ./Src/bsp_button.o ./Src/bsp_button.su ./Src/bsp_delay.d ./Src/bsp_delay.o ./Src/bsp_delay.su ./Src/bsp_led.d ./Src/bsp_led.o ./Src/bsp_led.su ./Src/bsp_usart.d ./Src/bsp_usart.o ./Src/bsp_usart.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

