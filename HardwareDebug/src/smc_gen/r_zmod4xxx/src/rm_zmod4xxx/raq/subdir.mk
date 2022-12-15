################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/rm_zmod4450_raq.c 

COMPILER_OBJS += \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/rm_zmod4450_raq.obj 

C_DEPS += \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/rm_zmod4450_raq.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/%.obj: ../src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\raq\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\raq\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\raq\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\raq\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\raq\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\raq\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

