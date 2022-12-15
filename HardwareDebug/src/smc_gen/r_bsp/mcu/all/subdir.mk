################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
ASM_SRCS += \
../src/smc_gen/r_bsp/mcu/all/cstart.asm \
../src/smc_gen/r_bsp/mcu/all/r_bsp_common_ccrl.asm 

C_SRCS += \
../src/smc_gen/r_bsp/mcu/all/r_bsp_common.c 

ASSEMBLER_OBJS += \
src/smc_gen/r_bsp/mcu/all/cstart.obj \
src/smc_gen/r_bsp/mcu/all/r_bsp_common_ccrl.obj 

ASM_DEPS += \
src/smc_gen/r_bsp/mcu/all/cstart.d \
src/smc_gen/r_bsp/mcu/all/r_bsp_common_ccrl.d 

COMPILER_OBJS += \
src/smc_gen/r_bsp/mcu/all/r_bsp_common.obj 

C_DEPS += \
src/smc_gen/r_bsp/mcu/all/r_bsp_common.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/mcu/all/%.obj: ../src/smc_gen/r_bsp/mcu/all/%.asm 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Assembler'
	@echo src\smc_gen\r_bsp\mcu\all\asmDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\all\asmDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\mcu\all\asmDepSubCommand.tmp" -asmopt=-MF="$(@:%.obj=%.d)" -asmopt=-MT="$(@:%.obj=%.obj)" -asmopt=-MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_bsp\mcu\all\asmSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\all\asmSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\mcu\all\asmSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)"  "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

src/smc_gen/r_bsp/mcu/all/%.obj: ../src/smc_gen/r_bsp/mcu/all/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_bsp\mcu\all\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\all\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\mcu\all\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_bsp\mcu\all\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\all\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\mcu\all\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

