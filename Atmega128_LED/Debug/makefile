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
Atmega128_LED.lss \

FLASH_IMAGE += \
Atmega128_LED.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: Atmega128_LED.elf secondary-outputs

# Tool invocations
Atmega128_LED.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Atmega128_LED.map -mmcu=atmega128 -o "Atmega128_LED.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Atmega128_LED.lss: Atmega128_LED.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Atmega128_LED.elf  >"Atmega128_LED.lss"
	@echo 'Finished building: $@'
	@echo ' '

Atmega128_LED.hex: Atmega128_LED.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Atmega128_LED.elf  "Atmega128_LED.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Atmega128_LED.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 Atmega128_LED.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: Atmega128_LED.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm128 -cusbasp -Uflash:w:Atmega128_LED.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Atmega128_LED.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
