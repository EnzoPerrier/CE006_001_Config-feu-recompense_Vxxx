################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/drivers/encoder_driver.c \
../Core/Src/drivers/usb_cdc_driver.c 

OBJS += \
./Core/Src/drivers/encoder_driver.o \
./Core/Src/drivers/usb_cdc_driver.o 

C_DEPS += \
./Core/Src/drivers/encoder_driver.d \
./Core/Src/drivers/usb_cdc_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/drivers/%.o Core/Src/drivers/%.su Core/Src/drivers/%.cyclo: ../Core/Src/drivers/%.c Core/Src/drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32U073xx -c -I../Core/Inc -I../AZURE_RTOS/App -I../USBX/App -I../USBX/Target -I../Drivers/STM32U0xx_HAL_Driver/Inc -I../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/threadx/common/inc -I../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../Middlewares/ST/usbx/common/core/inc -I../Middlewares/ST/usbx/ports/generic/inc -I../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-drivers

clean-Core-2f-Src-2f-drivers:
	-$(RM) ./Core/Src/drivers/encoder_driver.cyclo ./Core/Src/drivers/encoder_driver.d ./Core/Src/drivers/encoder_driver.o ./Core/Src/drivers/encoder_driver.su ./Core/Src/drivers/usb_cdc_driver.cyclo ./Core/Src/drivers/usb_cdc_driver.d ./Core/Src/drivers/usb_cdc_driver.o ./Core/Src/drivers/usb_cdc_driver.su

.PHONY: clean-Core-2f-Src-2f-drivers

