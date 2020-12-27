################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Services_layers/Queue.c \
../src/Services_layers/Special_Uart_wifi_local.c \
../src/Services_layers/Speical_Timer.c \
../src/Services_layers/String_Queue.c \
../src/Services_layers/debug.c \
../src/Services_layers/delay.c \
../src/Services_layers/utility.c 

OBJS += \
./src/Services_layers/Queue.o \
./src/Services_layers/Special_Uart_wifi_local.o \
./src/Services_layers/Speical_Timer.o \
./src/Services_layers/String_Queue.o \
./src/Services_layers/debug.o \
./src/Services_layers/delay.o \
./src/Services_layers/utility.o 

C_DEPS += \
./src/Services_layers/Queue.d \
./src/Services_layers/Special_Uart_wifi_local.d \
./src/Services_layers/Speical_Timer.d \
./src/Services_layers/String_Queue.d \
./src/Services_layers/debug.d \
./src/Services_layers/delay.d \
./src/Services_layers/utility.d 


# Each subdirectory must supply rules for building sources it contributes
src/Services_layers/%.o: ../src/Services_layers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/Users/amd/workbench/work/BOOT___LOADER4/StdPeriph_Driver/inc" -I"C:/Users/amd/workbench/work/BOOT___LOADER4/inc" -I"C:/Users/amd/workbench/work/BOOT___LOADER4/CMSIS/device" -I"C:/Users/amd/workbench/work/BOOT___LOADER4/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


