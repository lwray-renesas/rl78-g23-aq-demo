################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/app/src/gfx/src/gfx.c 

COMPILER_OBJS += \
src/app/src/gfx/src/gfx.obj 

C_DEPS += \
src/app/src/gfx/src/gfx.d 

# Each subdirectory must supply rules for building sources it contributes
src/app/src/gfx/src/%.obj: ../src/app/src/gfx/src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\app\src\gfx\src\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\src\gfx\src\cDepSubCommand.tmp"
	ccrl -subcommand="src\app\src\gfx\src\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\app\src\gfx\src\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\src\gfx\src\cSubCommand.tmp"
	ccrl -subcommand="src\app\src\gfx\src\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''
