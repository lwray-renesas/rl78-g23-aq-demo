################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/app/threads/event_thread.c \
../src/app/threads/gui_thread.c 

COMPILER_OBJS += \
src/app/threads/event_thread.obj \
src/app/threads/gui_thread.obj 

C_DEPS += \
src/app/threads/event_thread.d \
src/app/threads/gui_thread.d 

# Each subdirectory must supply rules for building sources it contributes
src/app/threads/%.obj: ../src/app/threads/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\app\threads\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\threads\cDepSubCommand.tmp"
	ccrl -subcommand="src\app\threads\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\app\threads\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\threads\cSubCommand.tmp"
	ccrl -subcommand="src\app\threads\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

