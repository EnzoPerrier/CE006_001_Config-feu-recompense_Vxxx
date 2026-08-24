################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/system_stm32u0xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32u0xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32u0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32u0xx.o: C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/system_stm32u0xx.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32U073xx -c -I"C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Inc/drivers" -I../Core/inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS

clean-Drivers-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/system_stm32u0xx.cyclo ./Drivers/CMSIS/system_stm32u0xx.d ./Drivers/CMSIS/system_stm32u0xx.o ./Drivers/CMSIS/system_stm32u0xx.su

.PHONY: clean-Drivers-2f-CMSIS

