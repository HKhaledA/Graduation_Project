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
TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.lss \

FLASH_IMAGE += \
TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.elf secondary-outputs

# Tool invocations
TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.map -mmcu=atmega32 -o "TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.lss: TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.elf  >"TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.lss"
	@echo 'Finished building: $@'
	@echo ' '

TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.hex: TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.elf  "TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -Uflash:w:TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) TESSSSSSSSSSSSSST_LCD_MINE_AOPTS_NDEP_ACC_and_FLEX_STRUCT.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
