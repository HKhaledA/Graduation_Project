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
ACC_and_GYRO.lss \

FLASH_IMAGE += \
ACC_and_GYRO.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: ACC_and_GYRO.elf secondary-outputs

# Tool invocations
ACC_and_GYRO.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ACC_and_GYRO.map -mmcu=atmega32 -o "ACC_and_GYRO.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ACC_and_GYRO.lss: ACC_and_GYRO.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ACC_and_GYRO.elf  >"ACC_and_GYRO.lss"
	@echo 'Finished building: $@'
	@echo ' '

ACC_and_GYRO.hex: ACC_and_GYRO.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ACC_and_GYRO.elf  "ACC_and_GYRO.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ACC_and_GYRO.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ACC_and_GYRO.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: ACC_and_GYRO.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -Uflash:w:ACC_and_GYRO.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ACC_and_GYRO.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
