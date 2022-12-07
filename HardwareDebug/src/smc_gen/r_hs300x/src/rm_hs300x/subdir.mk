################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_hs300x/src/rm_hs300x/rm_hs300x.c \
../src/smc_gen/r_hs300x/src/rm_hs300x/rm_hs300x_instance.c 

COMPILER_OBJS += \
src/smc_gen/r_hs300x/src/rm_hs300x/rm_hs300x.obj \
src/smc_gen/r_hs300x/src/rm_hs300x/rm_hs300x_instance.obj 

C_DEPS += \
src/smc_gen/r_hs300x/src/rm_hs300x/rm_hs300x.d \
src/smc_gen/r_hs300x/src/rm_hs300x/rm_hs300x_instance.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_hs300x/src/rm_hs300x/%.obj: ../src/smc_gen/r_hs300x/src/rm_hs300x/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_hs300x\src\rm_hs300x\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_hs300x\src\rm_hs300x\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_hs300x\src\rm_hs300x\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_hs300x\src\rm_hs300x\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_hs300x\src\rm_hs300x\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_hs300x\src\rm_hs300x\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

