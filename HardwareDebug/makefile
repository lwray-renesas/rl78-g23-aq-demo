################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.h *.bls *.libelf *.rel *.lbk *.abs *.prn *.mi *.fsy *.ud *.udm 1st/*.abs 1st/*.fsy

# All of the sources participating in the build are defined here
-include sources.mk
-include src/smc_gen/general/subdir.mk
-include src/smc_gen/r_bsp/mcu/rl78_g23/subdir.mk
-include src/rltos/rltos_kernel/mutex/subdir.mk
-include src/smc_gen/Config_IICA1/subdir.mk
-include src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_2nd_gen/subdir.mk
-include src/smc_gen/Config_TAU0_3/subdir.mk
-include src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/subdir.mk
-include qe_gen/subdir.mk
-include src/app/src/hw/src/subdir.mk
-include src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/subdir.mk
-include src/smc_gen/rm_touch/subdir.mk
-include src/rltos/port/RL78/CCRL/subdir.mk
-include src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen_ulp/subdir.mk
-include src/smc_gen/r_bsp/board/generic_rl78_g23/subdir.mk
-include src/smc_gen/r_pincfg/subdir.mk
-include src/smc_gen/Config_TAU0_0/subdir.mk
-include src/smc_gen/Config_TAU0_4/subdir.mk
-include src/smc_gen/Config_CSI30/subdir.mk
-include src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_1st_gen/subdir.mk
-include src/app/src/hw/src/elcl/prv/subdir.mk
-include src/subdir.mk
-include src/app/src/gfx/src/display/text/subdir.mk
-include src/app/src/gfx/src/display/draw/subdir.mk
-include src/smc_gen/Config_ITL000/subdir.mk
-include src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen/subdir.mk
-include src/smc_gen/r_hs300x/src/rm_hs300x/subdir.mk
-include src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/subdir.mk
-include src/app/src/gfx/src/subdir.mk
-include src/smc_gen/Config_TAU0_1/subdir.mk
-include src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/subdir.mk
-include src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/sulfur_odor/subdir.mk
-include src/rltos/rltos_kernel/events/subdir.mk
-include src/app/src/subdir.mk
-include src/app/threads/subdir.mk
-include src/app/src/gfx/src/display/driver/subdir.mk
-include src/smc_gen/r_ctsu/subdir.mk
-include src/rltos/rltos_kernel/semaphore/subdir.mk
-include src/smc_gen/Config_PORT/subdir.mk
-include src/smc_gen/r_bsp/mcu/all/subdir.mk
-include src/smc_gen/Config_TAU0_2/subdir.mk
-include src/smc_gen/Config_LVD1/subdir.mk
-include src/smc_gen/Config_RTC/subdir.mk
-include src/app/src/sensor/src/subdir.mk
-include src/rltos/rltos_kernel/core/task_scheduler/subdir.mk
-include src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/subdir.mk
-include src/rltos/port/RL78/subdir.mk
-include src/rltos/rltos_kernel/core/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif 
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif 
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif 
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif 
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif 
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif 
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif 
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif 
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif 
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif 
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif 
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif 
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif 
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif 
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif


-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LINKER_OUTPUT_OUTPUTS += \
wow_demo_rltos.abs

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)

$(COMPILER_OBJS): $(SMS_ASSEMBLER_H)

# All Target
all: $(LINKER_OUTPUT_OUTPUTS) wow_demo_rltos.x wow_demo_rltos.udm

	@echo 'Build complete.'

wow_demo_rltos.abs: $(OBJS)  $(ALL_ASMS)  \
C:\Users\a5126135\Dev\wow\wow_demo_rltos\src\smc_gen\r_zmod4xxx\lib\S3-core\iaq_2nd_gen\ccrl\lib_iaq_2nd_gen.lib
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	@echo Linkerwow_demo_rltos.tmp=
	@sed -e "s/^/    /" "Linkerwow_demo_rltos.tmp"
	rlink -subcommand="Linkerwow_demo_rltos.tmp"
	@echo 'Finished building target:'
	@echo ''


wow_demo_rltos.x: wow_demo_rltos.abs
		-C:\Users\a5126135\.eclipse\com.renesas.platform_633456566\Utilities\\ccrl\renesas_cc_converter wow_demo_rltos.abs wow_demo_rltos.x

wow_demo_rltos.udm: $(LINKER_OUTPUT_OUTPUTS)
	udcollector -subcommand=udSubcommand.tmp -output=wow_demo_rltos.udm

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS)
	-rm -rf $(SMS_ASSEMBLER_H)
ifneq ($(strip $(OBJS)),)
	-$(file > clean_OBJS.tmp, $(OBJS))
	-@xargs -s 4000 -t -a clean_OBJS.tmp rm -rf
	-@rm -rf clean_OBJS.tmp
endif
ifneq ($(strip $(C_DEPS)),)
	-$(file > clean_C_DEPS.tmp, $(C_DEPS))
	-@xargs -s 4000 -t -a clean_C_DEPS.tmp rm -rf
	-@rm -rf clean_C_DEPS.tmp
endif
ifneq ($(strip $(CPP_DEPS)),)
	-$(file > clean_CPP_DEPS.tmp, $(CPP_DEPS))
	-@xargs -s 4000 -t -a clean_CPP_DEPS.tmp rm -rf
	-@rm -rf clean_CPP_DEPS.tmp
endif
ifneq ($(strip $(ASM_DEPS)),)
	-$(file > clean_ASM_DEPS.tmp, $(ASM_DEPS))
	-@xargs -s 4000 -t -a clean_ASM_DEPS.tmp rm -rf
	-@rm -rf clean_ASM_DEPS.tmp
endif
ifneq ($(strip $(DSP_DEPS)),)
	-$(file > clean_DSP_DEPS.tmp, $(DSP_DEPS))
	-@xargs -s 4000 -t -a clean_DSP_DEPS.tmp rm -rf
	-@rm -rf clean_DSP_DEPS.tmp
endif
	-rm -rf src/smc_gen/general/*.asm src/smc_gen/general/*.p src/smc_gen/general/*.pp src/smc_gen/general/*.src src/smc_gen/general/*.jmp src/smc_gen/general/*.lst src/smc_gen/general/*.prn src/smc_gen/general/*.i src/smc_gen/general/*.ud 
	-rm -rf src/smc_gen/r_bsp/mcu/rl78_g23/*.asm src/smc_gen/r_bsp/mcu/rl78_g23/*.p src/smc_gen/r_bsp/mcu/rl78_g23/*.pp src/smc_gen/r_bsp/mcu/rl78_g23/*.src src/smc_gen/r_bsp/mcu/rl78_g23/*.jmp src/smc_gen/r_bsp/mcu/rl78_g23/*.lst src/smc_gen/r_bsp/mcu/rl78_g23/*.prn src/smc_gen/r_bsp/mcu/rl78_g23/*.i src/smc_gen/r_bsp/mcu/rl78_g23/*.ud 
	-rm -rf src/rltos/rltos_kernel/mutex/*.asm src/rltos/rltos_kernel/mutex/*.p src/rltos/rltos_kernel/mutex/*.pp src/rltos/rltos_kernel/mutex/*.src src/rltos/rltos_kernel/mutex/*.jmp src/rltos/rltos_kernel/mutex/*.lst src/rltos/rltos_kernel/mutex/*.prn src/rltos/rltos_kernel/mutex/*.i src/rltos/rltos_kernel/mutex/*.ud 
	-rm -rf src/smc_gen/Config_IICA1/*.asm src/smc_gen/Config_IICA1/*.p src/smc_gen/Config_IICA1/*.pp src/smc_gen/Config_IICA1/*.src src/smc_gen/Config_IICA1/*.jmp src/smc_gen/Config_IICA1/*.lst src/smc_gen/Config_IICA1/*.prn src/smc_gen/Config_IICA1/*.i src/smc_gen/Config_IICA1/*.ud 
	-rm -rf src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_2nd_gen/*.asm src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_2nd_gen/*.p src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_2nd_gen/*.pp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_2nd_gen/*.src src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_2nd_gen/*.jmp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_2nd_gen/*.lst src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_2nd_gen/*.prn src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_2nd_gen/*.i src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_2nd_gen/*.ud 
	-rm -rf src/smc_gen/Config_TAU0_3/*.asm src/smc_gen/Config_TAU0_3/*.p src/smc_gen/Config_TAU0_3/*.pp src/smc_gen/Config_TAU0_3/*.src src/smc_gen/Config_TAU0_3/*.jmp src/smc_gen/Config_TAU0_3/*.lst src/smc_gen/Config_TAU0_3/*.prn src/smc_gen/Config_TAU0_3/*.i src/smc_gen/Config_TAU0_3/*.ud 
	-rm -rf src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/*.asm src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/*.p src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/*.pp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/*.src src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/*.jmp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/*.lst src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/*.prn src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/*.i src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/raq/*.ud 
	-rm -rf qe_gen/*.asm qe_gen/*.p qe_gen/*.pp qe_gen/*.src qe_gen/*.jmp qe_gen/*.lst qe_gen/*.prn qe_gen/*.i qe_gen/*.ud 
	-rm -rf src/app/src/hw/src/*.asm src/app/src/hw/src/*.p src/app/src/hw/src/*.pp src/app/src/hw/src/*.src src/app/src/hw/src/*.jmp src/app/src/hw/src/*.lst src/app/src/hw/src/*.prn src/app/src/hw/src/*.i src/app/src/hw/src/*.ud 
	-rm -rf src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/*.asm src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/*.p src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/*.pp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/*.src src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/*.jmp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/*.lst src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/*.prn src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/*.i src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/odor/*.ud 
	-rm -rf src/smc_gen/rm_touch/*.asm src/smc_gen/rm_touch/*.p src/smc_gen/rm_touch/*.pp src/smc_gen/rm_touch/*.src src/smc_gen/rm_touch/*.jmp src/smc_gen/rm_touch/*.lst src/smc_gen/rm_touch/*.prn src/smc_gen/rm_touch/*.i src/smc_gen/rm_touch/*.ud 
	-rm -rf src/rltos/port/RL78/CCRL/*.asm src/rltos/port/RL78/CCRL/*.p src/rltos/port/RL78/CCRL/*.pp src/rltos/port/RL78/CCRL/*.src src/rltos/port/RL78/CCRL/*.jmp src/rltos/port/RL78/CCRL/*.lst src/rltos/port/RL78/CCRL/*.prn src/rltos/port/RL78/CCRL/*.i src/rltos/port/RL78/CCRL/*.ud 
	-rm -rf src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen_ulp/*.asm src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen_ulp/*.p src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen_ulp/*.pp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen_ulp/*.src src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen_ulp/*.jmp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen_ulp/*.lst src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen_ulp/*.prn src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen_ulp/*.i src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen_ulp/*.ud 
	-rm -rf src/smc_gen/r_bsp/board/generic_rl78_g23/*.asm src/smc_gen/r_bsp/board/generic_rl78_g23/*.p src/smc_gen/r_bsp/board/generic_rl78_g23/*.pp src/smc_gen/r_bsp/board/generic_rl78_g23/*.src src/smc_gen/r_bsp/board/generic_rl78_g23/*.jmp src/smc_gen/r_bsp/board/generic_rl78_g23/*.lst src/smc_gen/r_bsp/board/generic_rl78_g23/*.prn src/smc_gen/r_bsp/board/generic_rl78_g23/*.i src/smc_gen/r_bsp/board/generic_rl78_g23/*.ud 
	-rm -rf src/smc_gen/r_pincfg/*.asm src/smc_gen/r_pincfg/*.p src/smc_gen/r_pincfg/*.pp src/smc_gen/r_pincfg/*.src src/smc_gen/r_pincfg/*.jmp src/smc_gen/r_pincfg/*.lst src/smc_gen/r_pincfg/*.prn src/smc_gen/r_pincfg/*.i src/smc_gen/r_pincfg/*.ud 
	-rm -rf src/smc_gen/Config_TAU0_0/*.asm src/smc_gen/Config_TAU0_0/*.p src/smc_gen/Config_TAU0_0/*.pp src/smc_gen/Config_TAU0_0/*.src src/smc_gen/Config_TAU0_0/*.jmp src/smc_gen/Config_TAU0_0/*.lst src/smc_gen/Config_TAU0_0/*.prn src/smc_gen/Config_TAU0_0/*.i src/smc_gen/Config_TAU0_0/*.ud 
	-rm -rf src/smc_gen/Config_TAU0_4/*.asm src/smc_gen/Config_TAU0_4/*.p src/smc_gen/Config_TAU0_4/*.pp src/smc_gen/Config_TAU0_4/*.src src/smc_gen/Config_TAU0_4/*.jmp src/smc_gen/Config_TAU0_4/*.lst src/smc_gen/Config_TAU0_4/*.prn src/smc_gen/Config_TAU0_4/*.i src/smc_gen/Config_TAU0_4/*.ud 
	-rm -rf src/smc_gen/Config_CSI30/*.asm src/smc_gen/Config_CSI30/*.p src/smc_gen/Config_CSI30/*.pp src/smc_gen/Config_CSI30/*.src src/smc_gen/Config_CSI30/*.jmp src/smc_gen/Config_CSI30/*.lst src/smc_gen/Config_CSI30/*.prn src/smc_gen/Config_CSI30/*.i src/smc_gen/Config_CSI30/*.ud 
	-rm -rf src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_1st_gen/*.asm src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_1st_gen/*.p src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_1st_gen/*.pp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_1st_gen/*.src src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_1st_gen/*.jmp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_1st_gen/*.lst src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_1st_gen/*.prn src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_1st_gen/*.i src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_1st_gen/*.ud 
	-rm -rf src/app/src/hw/src/elcl/prv/*.asm src/app/src/hw/src/elcl/prv/*.p src/app/src/hw/src/elcl/prv/*.pp src/app/src/hw/src/elcl/prv/*.src src/app/src/hw/src/elcl/prv/*.jmp src/app/src/hw/src/elcl/prv/*.lst src/app/src/hw/src/elcl/prv/*.prn src/app/src/hw/src/elcl/prv/*.i src/app/src/hw/src/elcl/prv/*.ud 
	-rm -rf src/*.asm src/*.p src/*.pp src/*.src src/*.jmp src/*.lst src/*.prn src/*.i src/*.ud 
	-rm -rf src/app/src/gfx/src/display/text/*.asm src/app/src/gfx/src/display/text/*.p src/app/src/gfx/src/display/text/*.pp src/app/src/gfx/src/display/text/*.src src/app/src/gfx/src/display/text/*.jmp src/app/src/gfx/src/display/text/*.lst src/app/src/gfx/src/display/text/*.prn src/app/src/gfx/src/display/text/*.i src/app/src/gfx/src/display/text/*.ud 
	-rm -rf src/app/src/gfx/src/display/draw/*.asm src/app/src/gfx/src/display/draw/*.p src/app/src/gfx/src/display/draw/*.pp src/app/src/gfx/src/display/draw/*.src src/app/src/gfx/src/display/draw/*.jmp src/app/src/gfx/src/display/draw/*.lst src/app/src/gfx/src/display/draw/*.prn src/app/src/gfx/src/display/draw/*.i src/app/src/gfx/src/display/draw/*.ud 
	-rm -rf src/smc_gen/Config_ITL000/*.asm src/smc_gen/Config_ITL000/*.p src/smc_gen/Config_ITL000/*.pp src/smc_gen/Config_ITL000/*.src src/smc_gen/Config_ITL000/*.jmp src/smc_gen/Config_ITL000/*.lst src/smc_gen/Config_ITL000/*.prn src/smc_gen/Config_ITL000/*.i src/smc_gen/Config_ITL000/*.ud 
	-rm -rf src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen/*.asm src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen/*.p src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen/*.pp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen/*.src src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen/*.jmp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen/*.lst src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen/*.prn src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen/*.i src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/iaq_2nd_gen/*.ud 
	-rm -rf src/smc_gen/r_hs300x/src/rm_hs300x/*.asm src/smc_gen/r_hs300x/src/rm_hs300x/*.p src/smc_gen/r_hs300x/src/rm_hs300x/*.pp src/smc_gen/r_hs300x/src/rm_hs300x/*.src src/smc_gen/r_hs300x/src/rm_hs300x/*.jmp src/smc_gen/r_hs300x/src/rm_hs300x/*.lst src/smc_gen/r_hs300x/src/rm_hs300x/*.prn src/smc_gen/r_hs300x/src/rm_hs300x/*.i src/smc_gen/r_hs300x/src/rm_hs300x/*.ud 
	-rm -rf src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/*.asm src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/*.p src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/*.pp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/*.src src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/*.jmp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/*.lst src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/*.prn src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/*.i src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/*.ud 
	-rm -rf src/app/src/gfx/src/*.asm src/app/src/gfx/src/*.p src/app/src/gfx/src/*.pp src/app/src/gfx/src/*.src src/app/src/gfx/src/*.jmp src/app/src/gfx/src/*.lst src/app/src/gfx/src/*.prn src/app/src/gfx/src/*.i src/app/src/gfx/src/*.ud 
	-rm -rf src/smc_gen/Config_TAU0_1/*.asm src/smc_gen/Config_TAU0_1/*.p src/smc_gen/Config_TAU0_1/*.pp src/smc_gen/Config_TAU0_1/*.src src/smc_gen/Config_TAU0_1/*.jmp src/smc_gen/Config_TAU0_1/*.lst src/smc_gen/Config_TAU0_1/*.prn src/smc_gen/Config_TAU0_1/*.i src/smc_gen/Config_TAU0_1/*.ud 
	-rm -rf src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/*.asm src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/*.p src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/*.pp src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/*.src src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/*.jmp src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/*.lst src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/*.prn src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/*.i src/smc_gen/r_comms_i2c_rl/src/rm_comms_i2c/*.ud 
	-rm -rf src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/sulfur_odor/*.asm src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/sulfur_odor/*.p src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/sulfur_odor/*.pp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/sulfur_odor/*.src src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/sulfur_odor/*.jmp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/sulfur_odor/*.lst src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/sulfur_odor/*.prn src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/sulfur_odor/*.i src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/sulfur_odor/*.ud 
	-rm -rf src/rltos/rltos_kernel/events/*.asm src/rltos/rltos_kernel/events/*.p src/rltos/rltos_kernel/events/*.pp src/rltos/rltos_kernel/events/*.src src/rltos/rltos_kernel/events/*.jmp src/rltos/rltos_kernel/events/*.lst src/rltos/rltos_kernel/events/*.prn src/rltos/rltos_kernel/events/*.i src/rltos/rltos_kernel/events/*.ud 
	-rm -rf src/app/src/*.asm src/app/src/*.p src/app/src/*.pp src/app/src/*.src src/app/src/*.jmp src/app/src/*.lst src/app/src/*.prn src/app/src/*.i src/app/src/*.ud 
	-rm -rf src/app/threads/*.asm src/app/threads/*.p src/app/threads/*.pp src/app/threads/*.src src/app/threads/*.jmp src/app/threads/*.lst src/app/threads/*.prn src/app/threads/*.i src/app/threads/*.ud 
	-rm -rf src/app/src/gfx/src/display/driver/*.asm src/app/src/gfx/src/display/driver/*.p src/app/src/gfx/src/display/driver/*.pp src/app/src/gfx/src/display/driver/*.src src/app/src/gfx/src/display/driver/*.jmp src/app/src/gfx/src/display/driver/*.lst src/app/src/gfx/src/display/driver/*.prn src/app/src/gfx/src/display/driver/*.i src/app/src/gfx/src/display/driver/*.ud 
	-rm -rf src/smc_gen/r_ctsu/*.asm src/smc_gen/r_ctsu/*.p src/smc_gen/r_ctsu/*.pp src/smc_gen/r_ctsu/*.src src/smc_gen/r_ctsu/*.jmp src/smc_gen/r_ctsu/*.lst src/smc_gen/r_ctsu/*.prn src/smc_gen/r_ctsu/*.i src/smc_gen/r_ctsu/*.ud 
	-rm -rf src/rltos/rltos_kernel/semaphore/*.asm src/rltos/rltos_kernel/semaphore/*.p src/rltos/rltos_kernel/semaphore/*.pp src/rltos/rltos_kernel/semaphore/*.src src/rltos/rltos_kernel/semaphore/*.jmp src/rltos/rltos_kernel/semaphore/*.lst src/rltos/rltos_kernel/semaphore/*.prn src/rltos/rltos_kernel/semaphore/*.i src/rltos/rltos_kernel/semaphore/*.ud 
	-rm -rf src/smc_gen/Config_PORT/*.asm src/smc_gen/Config_PORT/*.p src/smc_gen/Config_PORT/*.pp src/smc_gen/Config_PORT/*.src src/smc_gen/Config_PORT/*.jmp src/smc_gen/Config_PORT/*.lst src/smc_gen/Config_PORT/*.prn src/smc_gen/Config_PORT/*.i src/smc_gen/Config_PORT/*.ud 
	-rm -rf src/smc_gen/r_bsp/mcu/all/*.asm src/smc_gen/r_bsp/mcu/all/*.p src/smc_gen/r_bsp/mcu/all/*.pp src/smc_gen/r_bsp/mcu/all/*.src src/smc_gen/r_bsp/mcu/all/*.jmp src/smc_gen/r_bsp/mcu/all/*.lst src/smc_gen/r_bsp/mcu/all/*.prn src/smc_gen/r_bsp/mcu/all/*.i src/smc_gen/r_bsp/mcu/all/*.ud 
	-rm -rf src/smc_gen/Config_TAU0_2/*.asm src/smc_gen/Config_TAU0_2/*.p src/smc_gen/Config_TAU0_2/*.pp src/smc_gen/Config_TAU0_2/*.src src/smc_gen/Config_TAU0_2/*.jmp src/smc_gen/Config_TAU0_2/*.lst src/smc_gen/Config_TAU0_2/*.prn src/smc_gen/Config_TAU0_2/*.i src/smc_gen/Config_TAU0_2/*.ud 
	-rm -rf src/smc_gen/Config_LVD1/*.asm src/smc_gen/Config_LVD1/*.p src/smc_gen/Config_LVD1/*.pp src/smc_gen/Config_LVD1/*.src src/smc_gen/Config_LVD1/*.jmp src/smc_gen/Config_LVD1/*.lst src/smc_gen/Config_LVD1/*.prn src/smc_gen/Config_LVD1/*.i src/smc_gen/Config_LVD1/*.ud 
	-rm -rf src/smc_gen/Config_RTC/*.asm src/smc_gen/Config_RTC/*.p src/smc_gen/Config_RTC/*.pp src/smc_gen/Config_RTC/*.src src/smc_gen/Config_RTC/*.jmp src/smc_gen/Config_RTC/*.lst src/smc_gen/Config_RTC/*.prn src/smc_gen/Config_RTC/*.i src/smc_gen/Config_RTC/*.ud 
	-rm -rf src/app/src/sensor/src/*.asm src/app/src/sensor/src/*.p src/app/src/sensor/src/*.pp src/app/src/sensor/src/*.src src/app/src/sensor/src/*.jmp src/app/src/sensor/src/*.lst src/app/src/sensor/src/*.prn src/app/src/sensor/src/*.i src/app/src/sensor/src/*.ud 
	-rm -rf src/rltos/rltos_kernel/core/task_scheduler/*.asm src/rltos/rltos_kernel/core/task_scheduler/*.p src/rltos/rltos_kernel/core/task_scheduler/*.pp src/rltos/rltos_kernel/core/task_scheduler/*.src src/rltos/rltos_kernel/core/task_scheduler/*.jmp src/rltos/rltos_kernel/core/task_scheduler/*.lst src/rltos/rltos_kernel/core/task_scheduler/*.prn src/rltos/rltos_kernel/core/task_scheduler/*.i src/rltos/rltos_kernel/core/task_scheduler/*.ud 
	-rm -rf src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/*.asm src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/*.p src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/*.pp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/*.src src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/*.jmp src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/*.lst src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/*.prn src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/*.i src/smc_gen/r_zmod4xxx/src/rm_zmod4xxx/oaq_1st_gen/*.ud 
	-rm -rf src/rltos/port/RL78/*.asm src/rltos/port/RL78/*.p src/rltos/port/RL78/*.pp src/rltos/port/RL78/*.src src/rltos/port/RL78/*.jmp src/rltos/port/RL78/*.lst src/rltos/port/RL78/*.prn src/rltos/port/RL78/*.i src/rltos/port/RL78/*.ud 
	-rm -rf src/rltos/rltos_kernel/core/*.asm src/rltos/rltos_kernel/core/*.p src/rltos/rltos_kernel/core/*.pp src/rltos/rltos_kernel/core/*.src src/rltos/rltos_kernel/core/*.jmp src/rltos/rltos_kernel/core/*.lst src/rltos/rltos_kernel/core/*.prn src/rltos/rltos_kernel/core/*.i src/rltos/rltos_kernel/core/*.ud 
	@echo ''
	@echo 'Clean complete.'

.PHONY: all clean 
-include ../makefile.targets
.NOTPARALLEL: $(SMS_ASSEMBLER_H)
.SECONDARY: $(SMS_ASSEMBLER_H)