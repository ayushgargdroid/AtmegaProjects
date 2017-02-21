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
AcceleroI2C.lss \

FLASH_IMAGE += \
AcceleroI2C.hex \

EEPROM_IMAGE += \
AcceleroI2C.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: AcceleroI2C.elf secondary-outputs

# Tool invocations
AcceleroI2C.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,AcceleroI2C.map -mmcu=atmega32 -o "AcceleroI2C.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

AcceleroI2C.lss: AcceleroI2C.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S AcceleroI2C.elf  >"AcceleroI2C.lss"
	@echo 'Finished building: $@'
	@echo ' '

AcceleroI2C.hex: AcceleroI2C.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex AcceleroI2C.elf  "AcceleroI2C.hex"
	@echo 'Finished building: $@'
	@echo ' '

AcceleroI2C.eep: AcceleroI2C.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex AcceleroI2C.elf  "AcceleroI2C.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: AcceleroI2C.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 AcceleroI2C.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) AcceleroI2C.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
