################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/threads/ui_thread.c \
../Core/Src/threads/usb_cdc_thread.c 

OBJS += \
./Core/Src/threads/ui_thread.o \
./Core/Src/threads/usb_cdc_thread.o 

C_DEPS += \
./Core/Src/threads/ui_thread.d \
./Core/Src/threads/usb_cdc_thread.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/threads/%.o Core/Src/threads/%.su Core/Src/threads/%.cyclo: ../Core/Src/threads/%.c Core/Src/threads/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32U073xx -c -I../Core/Inc -I../AZURE_RTOS/App -I../USBX/App -I../USBX/Target -I../Drivers/STM32U0xx_HAL_Driver/Inc -I../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/threadx/common/inc -I../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../Middlewares/ST/usbx/common/core/inc -I../Middlewares/ST/usbx/ports/generic/inc -I../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-threads

clean-Core-2f-Src-2f-threads:
	-$(RM) ./Core/Src/threads/ui_thread.cyclo ./Core/Src/threads/ui_thread.d ./Core/Src/threads/ui_thread.o ./Core/Src/threads/ui_thread.su ./Core/Src/threads/usb_cdc_thread.cyclo ./Core/Src/threads/usb_cdc_thread.d ./Core/Src/threads/usb_cdc_thread.o ./Core/Src/threads/usb_cdc_thread.su

.PHONY: clean-Core-2f-Src-2f-threads

