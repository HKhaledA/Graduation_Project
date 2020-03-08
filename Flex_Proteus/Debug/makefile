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
Flex_Proteus.lss \

FLASH_IMAGE += \
Flex_Proteus.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Flex_Proteus.elf secondary-outputs

# Tool invocations
Flex_Proteus.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Flex_Proteus.map -mmcu=atmega32 -o "Flex_Proteus.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Flex_Proteus.lss: Flex_Proteus.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Flex_Proteus.elf  >"Flex_Proteus.lss"
	@echo 'Finished building: $@'
	@echo ' '

Flex_Proteus.hex: Flex_Proteus.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Flex_Proteus.elf  "Flex_Proteus.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Flex_Proteus.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Flex_Proteus.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Flex_Proteus.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
