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
MotorCodePhaseCorrect.lss \

FLASH_IMAGE += \
MotorCodePhaseCorrect.hex \

EEPROM_IMAGE += \
MotorCodePhaseCorrect.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: MotorCodePhaseCorrect.elf secondary-outputs

# Tool invocations
MotorCodePhaseCorrect.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,MotorCodePhaseCorrect.map -mmcu=atmega32 -o "MotorCodePhaseCorrect.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

MotorCodePhaseCorrect.lss: MotorCodePhaseCorrect.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S MotorCodePhaseCorrect.elf  >"MotorCodePhaseCorrect.lss"
	@echo 'Finished building: $@'
	@echo ' '

MotorCodePhaseCorrect.hex: MotorCodePhaseCorrect.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex MotorCodePhaseCorrect.elf  "MotorCodePhaseCorrect.hex"
	@echo 'Finished building: $@'
	@echo ' '

MotorCodePhaseCorrect.eep: MotorCodePhaseCorrect.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex MotorCodePhaseCorrect.elf  "MotorCodePhaseCorrect.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: MotorCodePhaseCorrect.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 MotorCodePhaseCorrect.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) MotorCodePhaseCorrect.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
