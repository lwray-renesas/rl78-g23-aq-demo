################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/board/generic_rl78_g23/hdwinit.c \
../src/smc_gen/r_bsp/board/generic_rl78_g23/r_bsp_init.c 

ASM_SRCS += \
../src/smc_gen/r_bsp/board/generic_rl78_g23/stkinit.asm 

ASSEMBLER_OBJS += \
src/smc_gen/r_bsp/board/generic_rl78_g23/stkinit.obj 

ASM_DEPS += \
src/smc_gen/r_bsp/board/generic_rl78_g23/stkinit.d 

COMPILER_OBJS += \
src/smc_gen/r_bsp/board/generic_rl78_g23/hdwinit.obj \
src/smc_gen/r_bsp/board/generic_rl78_g23/r_bsp_init.obj 

C_DEPS += \
src/smc_gen/r_bsp/board/generic_rl78_g23/hdwinit.d \
src/smc_gen/r_bsp/board/generic_rl78_g23/r_bsp_init.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/board/generic_rl78_g23/%.obj: ../src/smc_gen/r_bsp/board/generic_rl78_g23/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_bsp\board\generic_rl78_g23\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rl78_g23\cDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\board\generic_rl78_g23\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_bsp\board\generic_rl78_g23\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rl78_g23\cSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\board\generic_rl78_g23\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

src/smc_gen/r_bsp/board/generic_rl78_g23/%.obj: ../src/smc_gen/r_bsp/board/generic_rl78_g23/%.asm 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Assembler'
	@echo src\smc_gen\r_bsp\board\generic_rl78_g23\asmDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rl78_g23\asmDepSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\board\generic_rl78_g23\asmDepSubCommand.tmp" -asmopt=-MF="$(@:%.obj=%.d)" -asmopt=-MT="$(@:%.obj=%.obj)" -asmopt=-MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\smc_gen\r_bsp\board\generic_rl78_g23\asmSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rl78_g23\asmSubCommand.tmp"
	ccrl -subcommand="src\smc_gen\r_bsp\board\generic_rl78_g23\asmSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)"  "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

