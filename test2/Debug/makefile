################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

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
libtest2.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: libtest2.a secondary-outputs

# Tool invocations
libtest2.a: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR Archiver'
	avr-ar -r  "libtest2.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

libtest2.lss: libtest2.a
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S libtest2.a  >"libtest2.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: libtest2.a
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 libtest2.a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(ARCHIVES)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) libtest2.a
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
