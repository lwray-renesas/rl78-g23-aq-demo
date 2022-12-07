################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/rltos/port/RL78/rltos_port.c 

COMPILER_OBJS += \
src/rltos/port/RL78/rltos_port.obj 

C_DEPS += \
src/rltos/port/RL78/rltos_port.d 

# Each subdirectory must supply rules for building sources it contributes
src/rltos/port/RL78/%.obj: ../src/rltos/port/RL78/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\rltos\port\RL78\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\rltos\port\RL78\cDepSubCommand.tmp"
	ccrl -subcommand="src\rltos\port\RL78\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\rltos\port\RL78\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\rltos\port\RL78\cSubCommand.tmp"
	ccrl -subcommand="src\rltos\port\RL78\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

