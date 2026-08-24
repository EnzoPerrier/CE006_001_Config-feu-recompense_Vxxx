################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/USBX/UX\ Device\ CoreStack/subdir.mk
-include Middlewares/USBX/UX\ Device\ Controllers/subdir.mk
-include Middlewares/USBX/UX\ Device\ Class\ CDC\ ACM/subdir.mk
-include Middlewares/USBX/Core\ System/subdir.mk
-include Middlewares/ThreadX/Core/subdir.mk
-include Drivers/STM32U0xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Application/User/USBX/App/subdir.mk
-include Application/User/Startup/subdir.mk
-include Application/User/Core/subdir.mk
-include Application/User/AZURE_RTOS/App/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := CE006_Config feu recompense
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
CE006_Config\ feu\ recompense.elf \

MAP_FILES += \
CE006_Config\ feu\ recompense.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
CE006_Config\ feu\ recompense.list \


# All Target
all: main-build

# Main-build Target
main-build: CE006_Config\ feu\ recompense.elf secondary-outputs

# Tool invocations
CE006_Config\ feu\ recompense.elf CE006_Config\ feu\ recompense.map: $(OBJS) $(USER_OBJS) C:\Users\sav02\Documents\CE006_001_Config-feu-recompense_Vxxx\STM32CubeIDE\STM32U073C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "CE006_Config feu recompense.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"C:\Users\sav02\Documents\CE006_001_Config-feu-recompense_Vxxx\STM32CubeIDE\STM32U073C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="CE006_Config feu recompense.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

CE006_Config\ feu\ recompense.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "CE006_Config feu recompense.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) CE006_Config\ feu\ recompense.elf CE006_Config\ feu\ recompense.list CE006_Config\ feu\ recompense.map CE006_Config\\ feu\\ recompense.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
