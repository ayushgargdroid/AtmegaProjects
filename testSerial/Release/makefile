################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Source/subdir.mk
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
testSerial.lss \

FLASH_IMAGE += \
testSerial.hex \

EEPROM_IMAGE += \
testSerial.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: testSerial.elf secondary-outputs

# Tool invocations
testSerial.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,testSerial.map -mmcu=atmega32 -o "testSerial.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

testSerial.lss: testSerial.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S testSerial.elf  >"testSerial.lss"
	@echo 'Finished building: $@'
	@echo ' '

testSerial.hex: testSerial.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex testSerial.elf  "testSerial.hex"
	@echo 'Finished building: $@'
	@echo ' '

testSerial.eep: testSerial.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex testSerial.elf  "testSerial.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: testSerial.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 testSerial.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) testSerial.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
