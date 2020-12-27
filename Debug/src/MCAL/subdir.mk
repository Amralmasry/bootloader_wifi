################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MCAL/CAN.c \
../src/MCAL/GPIO.c \
../src/MCAL/RCC.c \
../src/MCAL/SoftSPI.c \
../src/MCAL/TIM3_PWM.c \
../src/MCAL/TIMER_5.c \
../src/MCAL/TIMER_6.c \
../src/MCAL/TIMER_7.c \
../src/MCAL/UART_1.c \
../src/MCAL/UART_2.c \
../src/MCAL/UART_3.c \
../src/MCAL/UART_4.c 

OBJS += \
./src/MCAL/CAN.o \
./src/MCAL/GPIO.o \
./src/MCAL/RCC.o \
./src/MCAL/SoftSPI.o \
./src/MCAL/TIM3_PWM.o \
./src/MCAL/TIMER_5.o \
./src/MCAL/TIMER_6.o \
./src/MCAL/TIMER_7.o \
./src/MCAL/UART_1.o \
./src/MCAL/UART_2.o \
./src/MCAL/UART_3.o \
./src/MCAL/UART_4.o 

C_DEPS += \
./src/MCAL/CAN.d \
./src/MCAL/GPIO.d \
./src/MCAL/RCC.d \
./src/MCAL/SoftSPI.d \
./src/MCAL/TIM3_PWM.d \
./src/MCAL/TIMER_5.d \
./src/MCAL/TIMER_6.d \
./src/MCAL/TIMER_7.d \
./src/MCAL/UART_1.d \
./src/MCAL/UART_2.d \
./src/MCAL/UART_3.d \
./src/MCAL/UART_4.d 


# Each subdirectory must supply rules for building sources it contributes
src/MCAL/%.o: ../src/MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/Users/amd/workbench/work/BOOT___LOADER4/StdPeriph_Driver/inc" -I"C:/Users/amd/workbench/work/BOOT___LOADER4/inc" -I"C:/Users/amd/workbench/work/BOOT___LOADER4/CMSIS/device" -I"C:/Users/amd/workbench/work/BOOT___LOADER4/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


