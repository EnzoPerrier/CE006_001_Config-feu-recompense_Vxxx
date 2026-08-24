################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/app_threadx.c \
C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/main.c \
C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/stm32u0xx_hal_msp.c \
C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/stm32u0xx_hal_timebase_tim.c \
C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/stm32u0xx_it.c \
../Application/User/Core/syscalls.c \
../Application/User/Core/sysmem.c 

S_UPPER_SRCS += \
C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/tx_initialize_low_level.S 

OBJS += \
./Application/User/Core/app_threadx.o \
./Application/User/Core/main.o \
./Application/User/Core/stm32u0xx_hal_msp.o \
./Application/User/Core/stm32u0xx_hal_timebase_tim.o \
./Application/User/Core/stm32u0xx_it.o \
./Application/User/Core/syscalls.o \
./Application/User/Core/sysmem.o \
./Application/User/Core/tx_initialize_low_level.o 

S_UPPER_DEPS += \
./Application/User/Core/tx_initialize_low_level.d 

C_DEPS += \
./Application/User/Core/app_threadx.d \
./Application/User/Core/main.d \
./Application/User/Core/stm32u0xx_hal_msp.d \
./Application/User/Core/stm32u0xx_hal_timebase_tim.d \
./Application/User/Core/stm32u0xx_it.d \
./Application/User/Core/syscalls.d \
./Application/User/Core/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/app_threadx.o: C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/app_threadx.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32U073xx -c -I"C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Inc/drivers" -I../Core/inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/main.o: C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/main.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32U073xx -c -I"C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Inc/drivers" -I../Core/inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/stm32u0xx_hal_msp.o: C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/stm32u0xx_hal_msp.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32U073xx -c -I"C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Inc/drivers" -I../Core/inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/stm32u0xx_hal_timebase_tim.o: C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/stm32u0xx_hal_timebase_tim.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32U073xx -c -I"C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Inc/drivers" -I../Core/inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/stm32u0xx_it.o: C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/stm32u0xx_it.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32U073xx -c -I"C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Inc/drivers" -I../Core/inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/%.o Application/User/Core/%.su Application/User/Core/%.cyclo: ../Application/User/Core/%.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32U073xx -c -I"C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Inc/drivers" -I../Core/inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/tx_initialize_low_level.o: C:/Users/sav02/Documents/CE006_001_Config-feu-recompense_Vxxx/Core/Src/tx_initialize_low_level.S Application/User/Core/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -DTX_SINGLE_MODE_NON_SECURE=1 -c -I../../Core/Inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../Drivers/CMSIS/Include -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Application-2f-User-2f-Core

clean-Application-2f-User-2f-Core:
	-$(RM) ./Application/User/Core/app_threadx.cyclo ./Application/User/Core/app_threadx.d ./Application/User/Core/app_threadx.o ./Application/User/Core/app_threadx.su ./Application/User/Core/main.cyclo ./Application/User/Core/main.d ./Application/User/Core/main.o ./Application/User/Core/main.su ./Application/User/Core/stm32u0xx_hal_msp.cyclo ./Application/User/Core/stm32u0xx_hal_msp.d ./Application/User/Core/stm32u0xx_hal_msp.o ./Application/User/Core/stm32u0xx_hal_msp.su ./Application/User/Core/stm32u0xx_hal_timebase_tim.cyclo ./Application/User/Core/stm32u0xx_hal_timebase_tim.d ./Application/User/Core/stm32u0xx_hal_timebase_tim.o ./Application/User/Core/stm32u0xx_hal_timebase_tim.su ./Application/User/Core/stm32u0xx_it.cyclo ./Application/User/Core/stm32u0xx_it.d ./Application/User/Core/stm32u0xx_it.o ./Application/User/Core/stm32u0xx_it.su ./Application/User/Core/syscalls.cyclo ./Application/User/Core/syscalls.d ./Application/User/Core/syscalls.o ./Application/User/Core/syscalls.su ./Application/User/Core/sysmem.cyclo ./Application/User/Core/sysmem.d ./Application/User/Core/sysmem.o ./Application/User/Core/sysmem.su ./Application/User/Core/tx_initialize_low_level.d ./Application/User/Core/tx_initialize_low_level.o

.PHONY: clean-Application-2f-User-2f-Core

