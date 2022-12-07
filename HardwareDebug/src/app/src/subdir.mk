################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/app/src/app.c 

COMPILER_OBJS += \
src/app/src/app.obj 

C_DEPS += \
src/app/src/app.d 

# Each subdirectory must supply rules for building sources it contributes
src/app/src/%.obj: ../src/app/src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\app\src\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\src\cDepSubCommand.tmp"
	ccrl -subcommand="src\app\src\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\app\src\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\src\cSubCommand.tmp"
	ccrl -subcommand="src\app\src\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

