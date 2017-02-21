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
BlinkTest.lss \

FLASH_IMAGE += \
BlinkTest.hex \

EEPROM_IMAGE += \
BlinkTest.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: BlinkTest.elf secondary-outputs

# Tool invocations
BlinkTest.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,BlinkTest.map -mmcu=atmega32 -o "BlinkTest.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BlinkTest.lss: BlinkTest.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S BlinkTest.elf  >"BlinkTest.lss"
	@echo 'Finished building: $@'
	@echo ' '

BlinkTest.hex: BlinkTest.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex BlinkTest.elf  "BlinkTest.hex"
	@echo 'Finished building: $@'
	@echo ' '

BlinkTest.eep: BlinkTest.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex BlinkTest.elf  "BlinkTest.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: BlinkTest.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 BlinkTest.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) BlinkTest.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
