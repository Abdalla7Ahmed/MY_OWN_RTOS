################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MYRTOS/CortexMx_OS_Porting.c \
../MYRTOS/MY_RTOS_FIFO.c \
../MYRTOS/Scheduler.c 

OBJS += \
./MYRTOS/CortexMx_OS_Porting.o \
./MYRTOS/MY_RTOS_FIFO.o \
./MYRTOS/Scheduler.o 

C_DEPS += \
./MYRTOS/CortexMx_OS_Porting.d \
./MYRTOS/MY_RTOS_FIFO.d \
./MYRTOS/Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
MYRTOS/CortexMx_OS_Porting.o: ../MYRTOS/CortexMx_OS_Porting.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/MYRTOS/Code/CMSIS_V5" -I"D:/MYRTOS/Code/MYRTOS/inc" -I"D:/MYRTOS/Code/HAL/Inc" -I"D:/MYRTOS/Code/STM32F103C6_Driver/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MYRTOS/CortexMx_OS_Porting.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MYRTOS/MY_RTOS_FIFO.o: ../MYRTOS/MY_RTOS_FIFO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/MYRTOS/Code/CMSIS_V5" -I"D:/MYRTOS/Code/MYRTOS/inc" -I"D:/MYRTOS/Code/HAL/Inc" -I"D:/MYRTOS/Code/STM32F103C6_Driver/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MYRTOS/MY_RTOS_FIFO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MYRTOS/Scheduler.o: ../MYRTOS/Scheduler.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/MYRTOS/Code/CMSIS_V5" -I"D:/MYRTOS/Code/MYRTOS/inc" -I"D:/MYRTOS/Code/HAL/Inc" -I"D:/MYRTOS/Code/STM32F103C6_Driver/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MYRTOS/Scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

