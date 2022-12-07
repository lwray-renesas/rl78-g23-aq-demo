################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/rltos/rltos_kernel/queue/rltos_queue.c 

COMPILER_OBJS += \
src/rltos/rltos_kernel/queue/rltos_queue.obj 

C_DEPS += \
src/rltos/rltos_kernel/queue/rltos_queue.d 

# Each subdirectory must supply rules for building sources it contributes
src/rltos/rltos_kernel/queue/%.obj: ../src/rltos/rltos_kernel/queue/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\rltos\rltos_kernel\queue\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\rltos\rltos_kernel\queue\cDepSubCommand.tmp"
	ccrl -subcommand="src\rltos\rltos_kernel\queue\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\rltos\rltos_kernel\queue\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\rltos\rltos_kernel\queue\cSubCommand.tmp"
	ccrl -subcommand="src\rltos\rltos_kernel\queue\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

