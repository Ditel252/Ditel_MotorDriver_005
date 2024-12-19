################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/D-M-005/Console/Console.c \
../Core/Src/D-M-005/Console/Ditel_Printf.c 

OBJS += \
./Core/Src/D-M-005/Console/Console.o \
./Core/Src/D-M-005/Console/Ditel_Printf.o 

C_DEPS += \
./Core/Src/D-M-005/Console/Console.d \
./Core/Src/D-M-005/Console/Ditel_Printf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/D-M-005/Console/%.o Core/Src/D-M-005/Console/%.su Core/Src/D-M-005/Console/%.cyclo: ../Core/Src/D-M-005/Console/%.c Core/Src/D-M-005/Console/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-D-2d-M-2d-005-2f-Console

clean-Core-2f-Src-2f-D-2d-M-2d-005-2f-Console:
	-$(RM) ./Core/Src/D-M-005/Console/Console.cyclo ./Core/Src/D-M-005/Console/Console.d ./Core/Src/D-M-005/Console/Console.o ./Core/Src/D-M-005/Console/Console.su ./Core/Src/D-M-005/Console/Ditel_Printf.cyclo ./Core/Src/D-M-005/Console/Ditel_Printf.d ./Core/Src/D-M-005/Console/Ditel_Printf.o ./Core/Src/D-M-005/Console/Ditel_Printf.su

.PHONY: clean-Core-2f-Src-2f-D-2d-M-2d-005-2f-Console

