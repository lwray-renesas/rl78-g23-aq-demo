################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/mcu/rl78_g23/mcu_clocks.c 

COMPILER_OBJS += \
src/smc_gen/r_bsp/mcu/rl78_g23/mcu_clocks.obj 

C_DEPS += \
src/smc_gen/r_bsp/mcu/rl78_g23/mcu_clocks.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/mcu/rl78_g23/%.obj: ../src/smc_gen/r_bsp/mcu/rl78_g23/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_bsp\mcu\rl78_g23\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\rl78_g23\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\mcu\rl78_g23\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_bsp\mcu\rl78_g23\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\rl78_g23\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\mcu\rl78_g23\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

