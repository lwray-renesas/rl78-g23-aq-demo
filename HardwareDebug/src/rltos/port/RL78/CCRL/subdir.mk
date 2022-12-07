################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
ASM_SRCS += \
../src/rltos/port/RL78/CCRL/rltos_scheduler_asm.asm 

ASSEMBLER_OBJS += \
src/rltos/port/RL78/CCRL/rltos_scheduler_asm.obj 

ASM_DEPS += \
src/rltos/port/RL78/CCRL/rltos_scheduler_asm.d 

# Each subdirectory must supply rules for building sources it contributes
src/rltos/port/RL78/CCRL/%.obj: ../src/rltos/port/RL78/CCRL/%.asm 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Assembler'
	@echo src\rltos\port\RL78\CCRL\asmDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\rltos\port\RL78\CCRL\asmDepSubCommand.tmp"
	ccrl -subcommand="src\rltos\port\RL78\CCRL\asmDepSubCommand.tmp" -asmopt=-MF="$(@:%.obj=%.d)" -asmopt=-MT="$(@:%.obj=%.obj)" -asmopt=-MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\rltos\port\RL78\CCRL\asmSubCommand.tmp=
	@sed -e "s/^/ /" "src\rltos\port\RL78\CCRL\asmSubCommand.tmp"
	ccrl -subcommand="src\rltos\port\RL78\CCRL\asmSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)"  "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

