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
ButtonChutiyapa.lss \

FLASH_IMAGE += \
ButtonChutiyapa.hex \

EEPROM_IMAGE += \
ButtonChutiyapa.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ButtonChutiyapa.elf secondary-outputs

# Tool invocations
ButtonChutiyapa.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ButtonChutiyapa.map -mmcu=atmega32 -o "ButtonChutiyapa.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ButtonChutiyapa.lss: ButtonChutiyapa.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ButtonChutiyapa.elf  >"ButtonChutiyapa.lss"
	@echo 'Finished building: $@'
	@echo ' '

ButtonChutiyapa.hex: ButtonChutiyapa.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ButtonChutiyapa.elf  "ButtonChutiyapa.hex"
	@echo 'Finished building: $@'
	@echo ' '

ButtonChutiyapa.eep: ButtonChutiyapa.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ButtonChutiyapa.elf  "ButtonChutiyapa.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ButtonChutiyapa.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ButtonChutiyapa.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ButtonChutiyapa.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
