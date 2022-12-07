################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/app/src/hw/src/elcl/prv/elcl.c 

COMPILER_OBJS += \
src/app/src/hw/src/elcl/prv/elcl.obj 

C_DEPS += \
src/app/src/hw/src/elcl/prv/elcl.d 

# Each subdirectory must supply rules for building sources it contributes
src/app/src/hw/src/elcl/prv/%.obj: ../src/app/src/hw/src/elcl/prv/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\app\src\hw\src\elcl\prv\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\src\hw\src\elcl\prv\cDepSubCommand.tmp"
	ccrl -subcommand="src\app\src\hw\src\elcl\prv\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\app\src\hw\src\elcl\prv\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\app\src\hw\src\elcl\prv\cSubCommand.tmp"
	ccrl -subcommand="src\app\src\hw\src\elcl\prv\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

