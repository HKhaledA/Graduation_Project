################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../ADXL345.c \
../Music_Player.c \
../i2c.c \
../lcd.c \
../main.c \
../uart.c 

OBJS += \
./ADC.o \
./ADXL345.o \
./Music_Player.o \
./i2c.o \
./lcd.o \
./main.o \
./uart.o 

C_DEPS += \
./ADC.d \
./ADXL345.d \
./Music_Player.d \
./i2c.d \
./lcd.d \
./main.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=12000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


