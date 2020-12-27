################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HAL/WIFI_lOCAL.c 

OBJS += \
./src/HAL/WIFI_lOCAL.o 

C_DEPS += \
./src/HAL/WIFI_lOCAL.d 


# Each subdirectory must supply rules for building sources it contributes
src/HAL/%.o: ../src/HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/Users/amd/workbench/work/BOOT___LOADER4/StdPeriph_Driver/inc" -I"C:/Users/amd/workbench/work/BOOT___LOADER4/inc" -I"C:/Users/amd/workbench/work/BOOT___LOADER4/CMSIS/device" -I"C:/Users/amd/workbench/work/BOOT___LOADER4/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


