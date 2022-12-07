################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/app/gfx/src/display/draw/draw.c 

COMPILER_OBJS += \
src/app/gfx/src/display/draw/draw.obj 

C_DEPS += \
src/app/gfx/src/display/draw/draw.d 

# Each subdirectory must supply rules for building sources it contributes
src/app/gfx/src/display/draw/%.obj: ../src/app/gfx/src/display/draw/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\app\gfx\src\display\draw\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\gfx\src\display\draw\cDepSubCommand.tmp"
	ccrl -subcommand="src\app\gfx\src\display\draw\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\app\gfx\src\display\draw\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\gfx\src\display\draw\cSubCommand.tmp"
	ccrl -subcommand="src\app\gfx\src\display\draw\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)"  "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

