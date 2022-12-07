################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/rltos/rltos_kernel/core/rltos_task.c 

COMPILER_OBJS += \
src/rltos/rltos_kernel/core/rltos_task.obj 

C_DEPS += \
src/rltos/rltos_kernel/core/rltos_task.d 

# Each subdirectory must supply rules for building sources it contributes
src/rltos/rltos_kernel/core/%.obj: ../src/rltos/rltos_kernel/core/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\rltos\rltos_kernel\core\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\rltos\rltos_kernel\core\cDepSubCommand.tmp"
	ccrl -subcommand="src\rltos\rltos_kernel\core\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\rltos\rltos_kernel\core\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\rltos\rltos_kernel\core\cSubCommand.tmp"
	ccrl -subcommand="src\rltos\rltos_kernel\core\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

