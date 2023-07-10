################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_Driver/STM32F103C6_EXTRI_Driver.c \
../STM32F103C6_Driver/STM32F103C6_GPIO_Driver.c 

OBJS += \
./STM32F103C6_Driver/STM32F103C6_EXTRI_Driver.o \
./STM32F103C6_Driver/STM32F103C6_GPIO_Driver.o 

C_DEPS += \
./STM32F103C6_Driver/STM32F103C6_EXTRI_Driver.d \
./STM32F103C6_Driver/STM32F103C6_GPIO_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_Driver/STM32F103C6_EXTRI_Driver.o: ../STM32F103C6_Driver/STM32F103C6_EXTRI_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/MYRTOS/Code/CMSIS_V5" -I"D:/MYRTOS/Code/MYRTOS/inc" -I"D:/MYRTOS/Code/HAL/Inc" -I"D:/MYRTOS/Code/STM32F103C6_Driver/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Driver/STM32F103C6_EXTRI_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Driver/STM32F103C6_GPIO_Driver.o: ../STM32F103C6_Driver/STM32F103C6_GPIO_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/MYRTOS/Code/CMSIS_V5" -I"D:/MYRTOS/Code/MYRTOS/inc" -I"D:/MYRTOS/Code/HAL/Inc" -I"D:/MYRTOS/Code/STM32F103C6_Driver/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Driver/STM32F103C6_GPIO_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

