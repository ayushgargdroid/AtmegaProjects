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
PWM1alpha.lss \

FLASH_IMAGE += \
PWM1alpha.hex \

EEPROM_IMAGE += \
PWM1alpha.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: PWM1alpha.elf secondary-outputs

# Tool invocations
PWM1alpha.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,PWM1alpha.map -mmcu=atmega32 -o "PWM1alpha.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

PWM1alpha.lss: PWM1alpha.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S PWM1alpha.elf  >"PWM1alpha.lss"
	@echo 'Finished building: $@'
	@echo ' '

PWM1alpha.hex: PWM1alpha.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex PWM1alpha.elf  "PWM1alpha.hex"
	@echo 'Finished building: $@'
	@echo ' '

PWM1alpha.eep: PWM1alpha.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex PWM1alpha.elf  "PWM1alpha.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: PWM1alpha.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 PWM1alpha.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) PWM1alpha.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
