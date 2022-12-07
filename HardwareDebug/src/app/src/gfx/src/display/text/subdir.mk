################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/app/src/gfx/src/display/text/font.c \
../src/app/src/gfx/src/display/text/text.c 

COMPILER_OBJS += \
src/app/src/gfx/src/display/text/font.obj \
src/app/src/gfx/src/display/text/text.obj 

C_DEPS += \
src/app/src/gfx/src/display/text/font.d \
src/app/src/gfx/src/display/text/text.d 

# Each subdirectory must supply rules for building sources it contributes
src/app/src/gfx/src/display/text/%.obj: ../src/app/src/gfx/src/display/text/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\app\src\gfx\src\display\text\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\src\gfx\src\display\text\cDepSubCommand.tmp"
	ccrl -subcommand="src\app\src\gfx\src\display\text\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\app\src\gfx\src\display\text\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\src\gfx\src\display\text\cSubCommand.tmp"
	ccrl -subcommand="src\app\src\gfx\src\display\text\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

