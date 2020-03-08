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
FinalYear_GeaduationProject_Atmega128.lss \

FLASH_IMAGE += \
FinalYear_GeaduationProject_Atmega128.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: FinalYear_GeaduationProject_Atmega128.elf secondary-outputs

# Tool invocations
FinalYear_GeaduationProject_Atmega128.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,FinalYear_GeaduationProject_Atmega128.map -mmcu=atmega128 -o "FinalYear_GeaduationProject_Atmega128.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

FinalYear_GeaduationProject_Atmega128.lss: FinalYear_GeaduationProject_Atmega128.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S FinalYear_GeaduationProject_Atmega128.elf  >"FinalYear_GeaduationProject_Atmega128.lss"
	@echo 'Finished building: $@'
	@echo ' '

FinalYear_GeaduationProject_Atmega128.hex: FinalYear_GeaduationProject_Atmega128.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex FinalYear_GeaduationProject_Atmega128.elf  "FinalYear_GeaduationProject_Atmega128.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: FinalYear_GeaduationProject_Atmega128.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 FinalYear_GeaduationProject_Atmega128.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: FinalYear_GeaduationProject_Atmega128.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm128 -cusbasp -Uflash:w:FinalYear_GeaduationProject_Atmega128.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) FinalYear_GeaduationProject_Atmega128.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
