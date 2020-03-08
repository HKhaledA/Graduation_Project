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
FINAL_TEST_SAME_CMP_METHOD.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: FINAL_TEST_SAME_CMP_METHOD.elf secondary-outputs

# Tool invocations
FINAL_TEST_SAME_CMP_METHOD.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,FINAL_TEST_SAME_CMP_METHOD.map -mmcu=atmega32 -o "FINAL_TEST_SAME_CMP_METHOD.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

FINAL_TEST_SAME_CMP_METHOD.lss: FINAL_TEST_SAME_CMP_METHOD.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S FINAL_TEST_SAME_CMP_METHOD.elf  >"FINAL_TEST_SAME_CMP_METHOD.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: FINAL_TEST_SAME_CMP_METHOD.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 FINAL_TEST_SAME_CMP_METHOD.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) FINAL_TEST_SAME_CMP_METHOD.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
