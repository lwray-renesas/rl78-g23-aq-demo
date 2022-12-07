################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/Config_DTC/Config_DTC.c \
../src/smc_gen/Config_DTC/Config_DTC_user.c 

COMPILER_OBJS += \
src/smc_gen/Config_DTC/Config_DTC.obj \
src/smc_gen/Config_DTC/Config_DTC_user.obj 

C_DEPS += \
src/smc_gen/Config_DTC/Config_DTC.d \
src/smc_gen/Config_DTC/Config_DTC_user.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/Config_DTC/%.obj: ../src/smc_gen/Config_DTC/%.c src/smc_gen/Config_DTC/Compiler.sub
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\Config_DTC\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\Config_DTC\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\Config_DTC\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\Config_DTC\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\Config_DTC\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\Config_DTC\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

