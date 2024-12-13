################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/D-M-005/7Seg.c 

OBJS += \
./Core/Src/D-M-005/7Seg.o 

C_DEPS += \
./Core/Src/D-M-005/7Seg.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/D-M-005/%.o Core/Src/D-M-005/%.su Core/Src/D-M-005/%.cyclo: ../Core/Src/D-M-005/%.c Core/Src/D-M-005/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-D-2d-M-2d-005

clean-Core-2f-Src-2f-D-2d-M-2d-005:
	-$(RM) ./Core/Src/D-M-005/7Seg.cyclo ./Core/Src/D-M-005/7Seg.d ./Core/Src/D-M-005/7Seg.o ./Core/Src/D-M-005/7Seg.su

.PHONY: clean-Core-2f-Src-2f-D-2d-M-2d-005

