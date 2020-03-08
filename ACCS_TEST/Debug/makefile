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
ACCS_TEST.lss \

FLASH_IMAGE += \
ACCS_TEST.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: ACCS_TEST.elf secondary-outputs

# Tool invocations
ACCS_TEST.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ACCS_TEST.map -mmcu=atmega32 -o "ACCS_TEST.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ACCS_TEST.lss: ACCS_TEST.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ACCS_TEST.elf  >"ACCS_TEST.lss"
	@echo 'Finished building: $@'
	@echo ' '

ACCS_TEST.hex: ACCS_TEST.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ACCS_TEST.elf  "ACCS_TEST.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ACCS_TEST.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ACCS_TEST.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: ACCS_TEST.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -Uflash:w:ACCS_TEST.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ACCS_TEST.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
