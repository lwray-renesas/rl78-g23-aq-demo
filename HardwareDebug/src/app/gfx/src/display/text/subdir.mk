################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/app/gfx/src/display/text/font.c \
../src/app/gfx/src/display/text/text.c 

COMPILER_OBJS += \
src/app/gfx/src/display/text/font.obj \
src/app/gfx/src/display/text/text.obj 

C_DEPS += \
src/app/gfx/src/display/text/font.d \
src/app/gfx/src/display/text/text.d 

# Each subdirectory must supply rules for building sources it contributes
src/app/gfx/src/display/text/%.obj: ../src/app/gfx/src/display/text/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\app\gfx\src\display\text\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\gfx\src\display\text\cDepSubCommand.tmp"
	ccrl -subcommand="src\app\gfx\src\display\text\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\app\gfx\src\display\text\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\gfx\src\display\text\cSubCommand.tmp"
	ccrl -subcommand="src\app\gfx\src\display\text\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)"  "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

