################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/rm_comms_i2c.c \
../src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/rm_comms_i2c_driver_rl.c \
../src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/rm_comms_i2c_rl78_instance.c 

COMPILER_OBJS += \
src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/rm_comms_i2c.obj \
src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/rm_comms_i2c_driver_rl.obj \
src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/rm_comms_i2c_rl78_instance.obj 

C_DEPS += \
src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/rm_comms_i2c.d \
src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/rm_comms_i2c_driver_rl.d \
src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/rm_comms_i2c_rl78_instance.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/%.obj: ../src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_comms_i2c_rl\src\rm_comms_i2c\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_comms_i2c_rl\src\rm_comms_i2c\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_comms_i2c_rl\src\rm_comms_i2c\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_comms_i2c_rl\src\rm_comms_i2c\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_comms_i2c_rl\src\rm_comms_i2c\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_comms_i2c_rl\src\rm_comms_i2c\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

