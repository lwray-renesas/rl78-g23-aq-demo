################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_ctsu/r_ctsu.c 

SMSASM_SRCS += \
../src/smc_gen/r_ctsu/r_ctsu_sms_asm.smsasm \
../src/smc_gen/r_ctsu/r_ctsu_sms_asm_mutual.smsasm 

SMS_ASSEMBLER_H += \
src/smc_gen/r_ctsu/r_ctsu_sms_asm.h \
src/smc_gen/r_ctsu/r_ctsu_sms_asm_mutual.h 

COMPILER_OBJS += \
src/smc_gen/r_ctsu/r_ctsu.obj 

C_DEPS += \
src/smc_gen/r_ctsu/r_ctsu.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_ctsu/%.obj: ../src/smc_gen/r_ctsu/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_ctsu\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_ctsu\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_ctsu\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_ctsu\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_ctsu\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_ctsu\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

src/smc_gen/r_ctsu/%.h: ../src/smc_gen/r_ctsu/%.smsasm 
	@echo 'Building file: $<'
	@echo 'Invoking: SMS Assembler'
	@echo src\smc_gen\r_ctsu\smsasmSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_ctsu\smsasmSubCommand.tmp"
	smsasm @"src\smc_gen\r_ctsu\smsasmSubCommand.tmp" -o "$@"   "$<"
	@echo 'Finished Building: $<'
	@echo ''

