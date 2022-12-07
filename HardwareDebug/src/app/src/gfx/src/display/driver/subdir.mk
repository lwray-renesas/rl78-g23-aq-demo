################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/app/src/gfx/src/display/driver/st7735s.c 

COMPILER_OBJS += \
src/app/src/gfx/src/display/driver/st7735s.obj 

C_DEPS += \
src/app/src/gfx/src/display/driver/st7735s.d 

# Each subdirectory must supply rules for building sources it contributes
src/app/src/gfx/src/display/driver/%.obj: ../src/app/src/gfx/src/display/driver/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\app\src\gfx\src\display\driver\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\src\gfx\src\display\driver\cDepSubCommand.tmp"
	ccrl -subcommand="src\app\src\gfx\src\display\driver\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\app\src\gfx\src\display\driver\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\src\gfx\src\display\driver\cSubCommand.tmp"
	ccrl -subcommand="src\app\src\gfx\src\display\driver\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

