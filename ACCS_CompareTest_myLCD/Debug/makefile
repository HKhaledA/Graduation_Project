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
ACCS_CompareTest_myLCD.lss \

FLASH_IMAGE += \
ACCS_CompareTest_myLCD.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: ACCS_CompareTest_myLCD.elf secondary-outputs

# Tool invocations
ACCS_CompareTest_myLCD.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ACCS_CompareTest_myLCD.map -mmcu=atmega32 -o "ACCS_CompareTest_myLCD.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ACCS_CompareTest_myLCD.lss: ACCS_CompareTest_myLCD.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ACCS_CompareTest_myLCD.elf  >"ACCS_CompareTest_myLCD.lss"
	@echo 'Finished building: $@'
	@echo ' '

ACCS_CompareTest_myLCD.hex: ACCS_CompareTest_myLCD.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ACCS_CompareTest_myLCD.elf  "ACCS_CompareTest_myLCD.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ACCS_CompareTest_myLCD.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ACCS_CompareTest_myLCD.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: ACCS_CompareTest_myLCD.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -Uflash:w:ACCS_CompareTest_myLCD.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ACCS_CompareTest_myLCD.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
