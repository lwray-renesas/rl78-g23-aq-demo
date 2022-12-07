################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/rltos/rltos_kernel/events/rltos_events.c 

COMPILER_OBJS += \
src/rltos/rltos_kernel/events/rltos_events.obj 

C_DEPS += \
src/rltos/rltos_kernel/events/rltos_events.d 

# Each subdirectory must supply rules for building sources it contributes
src/rltos/rltos_kernel/events/%.obj: ../src/rltos/rltos_kernel/events/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\rltos\rltos_kernel\events\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\rltos\rltos_kernel\events\cDepSubCommand.tmp"
	ccrl -subcommand="src\rltos\rltos_kernel\events\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\rltos\rltos_kernel\events\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\rltos\rltos_kernel\events\cSubCommand.tmp"
	ccrl -subcommand="src\rltos\rltos_kernel\events\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

