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
ReceiverCode16.lss \

FLASH_IMAGE += \
ReceiverCode16.hex \

EEPROM_IMAGE += \
ReceiverCode16.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ReceiverCode16.elf secondary-outputs

# Tool invocations
ReceiverCode16.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ReceiverCode16.map -mmcu=atmega16 -o "ReceiverCode16.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ReceiverCode16.lss: ReceiverCode16.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ReceiverCode16.elf  >"ReceiverCode16.lss"
	@echo 'Finished building: $@'
	@echo ' '

ReceiverCode16.hex: ReceiverCode16.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ReceiverCode16.elf  "ReceiverCode16.hex"
	@echo 'Finished building: $@'
	@echo ' '

ReceiverCode16.eep: ReceiverCode16.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ReceiverCode16.elf  "ReceiverCode16.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ReceiverCode16.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 ReceiverCode16.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ReceiverCode16.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
