################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Sumo_robot.axf

# Tool invocations
Sumo_robot.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Rickard\Documents\LPCXpresso_4.2.0_264\Sumo_robot\CMSISv2p00_LPC13xx\Debug" -Xlinker -Map="Sumo_robot.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "Sumo_robot_Debug.ld" -o"Sumo_robot.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) Sumo_robot.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Sumo_robot.axf"; # arm-none-eabi-objcopy -O binary "Sumo_robot.axf" "Sumo_robot.bin" ; checksum -p LPC1343 -d "Sumo_robot.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
