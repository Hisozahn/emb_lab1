################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/Igor/Desktop/cubemx_1/Core/Inc" -I"C:/Users/Igor/Desktop/cubemx_1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Igor/Desktop/cubemx_1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Igor/Desktop/cubemx_1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Igor/Desktop/cubemx_1/Drivers/CMSIS/Include" -I"C:/Users/Igor/Desktop/cubemx_1/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/Igor/Desktop/cubemx_1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/Users/Igor/Desktop/cubemx_1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


