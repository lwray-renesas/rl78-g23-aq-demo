################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/rm_zmod4510_oaq_1st_gen.c 

COMPILER_OBJS += \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/rm_zmod4510_oaq_1st_gen.obj 

C_DEPS += \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/rm_zmod4510_oaq_1st_gen.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/%.obj: ../src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\oaq_1st_gen\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\oaq_1st_gen\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\oaq_1st_gen\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\oaq_1st_gen\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\oaq_1st_gen\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\oaq_1st_gen\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

