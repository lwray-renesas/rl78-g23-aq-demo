################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/rm_zmod4410_odor.c 

COMPILER_OBJS += \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/rm_zmod4410_odor.obj 

C_DEPS += \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/rm_zmod4410_odor.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/%.obj: ../src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\odor\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\odor\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\odor\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\odor\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\odor\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\odor\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

