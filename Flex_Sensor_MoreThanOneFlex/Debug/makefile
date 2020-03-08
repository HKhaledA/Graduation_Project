################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Flex_Sensor_MoreThanOneFlex.lss \

FLASH_IMAGE += \
Flex_Sensor_MoreThanOneFlex.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Flex_Sensor_MoreThanOneFlex.elf secondary-outputs

# Tool invocations
Flex_Sensor_MoreThanOneFlex.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Flex_Sensor_MoreThanOneFlex.map -mmcu=atmega32 -o "Flex_Sensor_MoreThanOneFlex.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Flex_Sensor_MoreThanOneFlex.lss: Flex_Sensor_MoreThanOneFlex.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Flex_Sensor_MoreThanOneFlex.elf  >"Flex_Sensor_MoreThanOneFlex.lss"
	@echo 'Finished building: $@'
	@echo ' '

Flex_Sensor_MoreThanOneFlex.hex: Flex_Sensor_MoreThanOneFlex.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Flex_Sensor_MoreThanOneFlex.elf  "Flex_Sensor_MoreThanOneFlex.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Flex_Sensor_MoreThanOneFlex.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Flex_Sensor_MoreThanOneFlex.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Flex_Sensor_MoreThanOneFlex.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
