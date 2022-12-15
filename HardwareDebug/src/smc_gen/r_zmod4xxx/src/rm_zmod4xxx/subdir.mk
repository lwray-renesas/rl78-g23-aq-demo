################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx.c \
../src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx_common.c \
../src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx_instance.c \
../src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx_rl_driver.c 

COMPILER_OBJS += \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx.obj \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx_common.obj \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx_instance.obj \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx_rl_driver.obj 

C_DEPS += \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx.d \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx_common.d \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx_instance.d \
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/rm_zmod4xxx_rl_driver.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/%.obj: ../src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_zmod4xxx\src\rm_zmod4xxx\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

