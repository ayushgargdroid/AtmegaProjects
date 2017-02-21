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
TWItest1.lss \

FLASH_IMAGE += \
TWItest1.hex \

EEPROM_IMAGE += \
TWItest1.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: TWItest1.elf secondary-outputs

# Tool invocations
TWItest1.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,TWItest1.map -mmcu=atmega32 -o "TWItest1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

TWItest1.lss: TWItest1.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S TWItest1.elf  >"TWItest1.lss"
	@echo 'Finished building: $@'
	@echo ' '

TWItest1.hex: TWItest1.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex TWItest1.elf  "TWItest1.hex"
	@echo 'Finished building: $@'
	@echo ' '

TWItest1.eep: TWItest1.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex TWItest1.elf  "TWItest1.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: TWItest1.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 TWItest1.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) TWItest1.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
