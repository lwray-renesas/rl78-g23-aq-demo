################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/app/event_thread.c \
../src/app/gui_thread.c 

COMPILER_OBJS += \
src/app/event_thread.obj \
src/app/gui_thread.obj 

C_DEPS += \
src/app/event_thread.d \
src/app/gui_thread.d 

# Each subdirectory must supply rules for building sources it contributes
src/app/%.obj: ../src/app/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\app\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\cDepSubCommand.tmp"
	ccrl -subcommand="src\app\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\app\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\cSubCommand.tmp"
	ccrl -subcommand="src\app\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

