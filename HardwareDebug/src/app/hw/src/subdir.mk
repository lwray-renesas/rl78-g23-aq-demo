################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/app/hw/src/hw.c 

COMPILER_OBJS += \
src/app/hw/src/hw.obj 

C_DEPS += \
src/app/hw/src/hw.d 

# Each subdirectory must supply rules for building sources it contributes
src/app/hw/src/%.obj: ../src/app/hw/src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\app\hw\src\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\hw\src\cDepSubCommand.tmp"
	ccrl -subcommand="src\app\hw\src\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\app\hw\src\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\hw\src\cSubCommand.tmp"
	ccrl -subcommand="src\app\hw\src\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)"  "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

