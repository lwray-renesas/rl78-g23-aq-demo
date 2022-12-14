################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../qe_gen/qe_touch_config.c 

COMPILER_OBJS += \
qe_gen/qe_touch_config.obj 

C_DEPS += \
qe_gen/qe_touch_config.d 

# Each subdirectory must supply rules for building sources it contributes
qe_gen/%.obj: ../qe_gen/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo qe_gen\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "qe_gen\cDepSubCommand.tmp"
	ccrl -subcommand="qe_gen\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo qe_gen\cSubCommand.tmp=
	@sed -e "s/^/ /" "qe_gen\cSubCommand.tmp"
	ccrl -subcommand="qe_gen\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

