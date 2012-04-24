################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc.c \
../src/cr_startup_lpc13.c \
../src/drive.c \
../src/gpio.c \
../src/main.c \
../src/reflex_sensor.c \
../src/sharp_sensor.c 

OBJS += \
./src/adc.o \
./src/cr_startup_lpc13.o \
./src/drive.o \
./src/gpio.o \
./src/main.o \
./src/reflex_sensor.o \
./src/sharp_sensor.o 

C_DEPS += \
./src/adc.d \
./src/cr_startup_lpc13.d \
./src/drive.d \
./src/gpio.d \
./src/main.d \
./src/reflex_sensor.d \
./src/sharp_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC13xx -I"C:\Users\Rickard\Documents\LPCXpresso_4.2.0_264\Sumo_robot\CMSISv2p00_LPC13xx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc13.o: ../src/cr_startup_lpc13.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC13xx -I"C:\Users\Rickard\Documents\LPCXpresso_4.2.0_264\Sumo_robot\CMSISv2p00_LPC13xx\inc" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc13.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


