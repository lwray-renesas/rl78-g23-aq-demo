/*
 * elcl.h
 *
 *  Created on: 22 Apr 2021
 *      Author: Louis Wray
 */

#ifndef DRIVERS_ELCL_H_
#define DRIVERS_ELCL_H_

#include "stdint.h"

/** Typedef for private implementation of ELCL control registers*/
typedef struct Elcl_ctl_t* p_elcl_ctl_t;

/** ELCL control structure*/
extern struct Elcl_ctl_t elcl_ctl;

/** @enum enumerated type representing the ELCL input channel number.*/
typedef enum
{
	ELCL_INPUT_0 = 0U,
	ELCL_INPUT_1,
	ELCL_INPUT_2,
	ELCL_INPUT_3,
	ELCL_INPUT_4,
	ELCL_INPUT_5,
	ELCL_INPUT_6,
	ELCL_INPUT_7,
	ELCL_INPUT_8,
	ELCL_INPUT_9,
	ELCL_INPUT_10,
	ELCL_INPUT_11,
}elcl_input_num_t;

/** @enum enumerated type representing the ELCL input source (consult hw user manual to see supported inputs).
 * @note Be careful to check what input these enumerated types are linking to - the src may differ depending on the input as indicated by enum comments & names*/
typedef enum
{
	ELCL_SRC_TX_SAU0_CH0 = 0U,
	ELCL_SRC_TX_SAU0_CH1,
	ELCL_SRC_SCLK_SAU0_CH0,
	ELCL_SRC_SCLK_SAU0_CH1,
	ELCL_SRC_P11,
	ELCL_SRC_P50,
	ELCL_SRC_SCLK_UARTA0,
	ELCL_SRC_TAU00,
	ELCL_SRC_TAU01,
	ELCL_SRC_TAU02,
	ELCL_SRC_TAU03,
	ELCL_SRC_TAU04,
	ELCL_SRC_TAU05,
	ELCL_SRC_TAU06,
	ELCL_SRC_TAU07,
	ELCL_SRC_P10,
	ELCL_SRC_P51,
	ELCL_SRC_CMP0,
	ELCL_SRC_CMP1,
	ELCL_SRC_TX_UARTA0,
	ELCL_SRC_P12,
	ELCL_SRC_PIN0_611_INTC4, /* 6-11 = INTC4*/
	ELCL_SRC_PIN1_611_INTC5, /* 6-11 = INTC5*/
	ELCL_SRC_INTC0_611_INTC6, /* 6-11 = INTC6*/
	ELCL_SRC_INTC1_611_INTC7, /* 6-11 = INTC7*/
	ELCL_SRC_INTC2_611_INTC8, /* 6-11 = INTC8*/
	ELCL_SRC_INTC3_611_INTC9, /* 6-11 = INTC9*/
	ELCL_SRC_P137_611_FCLK, /* 6-11 = fclk*/
	ELCL_SRC_FLIP_FLOP0_L1_611_FIHP, /* 6-11 = fihp*/
	ELCL_SRC_FLIP_FLOP1_L1_611_FIMP, /* 6-11 = fimp*/
	ELCL_SRC_FLIP_FLOP1_L2_611_FSXP, /* 6-11 = fsxp*/
	ELCL_SRC_FLIP_FLOP1_L3_611_NOT_OK, /* 6-11 = setting prohibited*/
}elcl_input_src_t;

/** @enum enumerated type representing the ELCL logic link select register options*/
typedef enum
{
	ELCL_INPUT_REG_0 = 1U,
	ELCL_INPUT_REG_1,
	ELCL_INPUT_REG_2,
	ELCL_INPUT_REG_3,
	ELCL_INPUT_REG_4,
	ELCL_INPUT_REG_5,
	ELCL_INPUT_REG_6,
	ELCL_INPUT_REG_7,
	ELCL_INPUT_REG_8,
	ELCL_INPUT_REG_9,
	ELCL_INPUT_REG_10,
	ELCL_INPUT_REG_11,
	ELCL_OUTPUT_CELL0_L1,
	ELCL_OUTPUT_CELL1_L1,
	ELCL_OUTPUT_SELECTOR_L1,
	ELCL_OUTPUT_FLIP_FLOP0_L1,
	ELCL_OUTPUT_FLIP_FLOP1_L1,
	ELCL_OUTPUT_CELL0_L2,
	ELCL_OUTPUT_CELL1_L2,
	ELCL_OUTPUT_SELECTOR_L2,
	ELCL_OUTPUT_FLIP_FLOP0_L2,
	ELCL_OUTPUT_FLIP_FLOP1_L2
}elcl_input_link_t;


/** @enum enumerated type representing the ELCL logic blocks*/
typedef enum
{
	ELCL_BLOCK1 = 0U,
	ELCL_BLOCK2,
	ELCL_BLOCK3
}elcl_logic_block_t;

/** @enum enumerated type representing the ELCL logic link register for selection*/
typedef enum
{
	ELCL_LNK_0 = 0U,
	ELCL_LNK_1,
	ELCL_LNK_2,
	ELCL_LNK_3,
	ELCL_LNK_4,
	ELCL_LNK_5,
	ELCL_LNK_6
}elcl_logic_link_reg_t;

/** @enum enumerated type representing the ELCL logic link register for selection*/
typedef enum
{
	ELCL_PASSTHROUGH_CELL_0 = 0U,
	ELCL_AND_CELL_0,
	ELCL_OR_CELL_0,
	ELCL_EXOR_CELL_0,
	ELCL_PASSTHROUGH_CELL_1,
	ELCL_AND_CELL_1,
	ELCL_OR_CELL_1,
	ELCL_EXOR_CELL_1,
	ELCL_ENABLE_FLIPFLOP0,
	ELCL_DISABLE_FLIPFLOP0,
	ELCL_ENABLE_FLIPFLOP1,
	ELCL_DISABLE_FLIPFLOP1
}elcl_ctl_command;

/** @enum enumerated type representing the ELCL logic link select register options for connection to logic*/
typedef enum
{
	ELCL_CELL0_INPUT_0 = 1U,
	ELCL_CELL0_INPUT_1,
	ELCL_CELL1_INPUT_0,
	ELCL_CELL1_INPUT_1,
	ELCL_SELECTOR_CTL,
	ELCL_SELECTOR_INPUT_0,
	ELCL_SELECTOR_INPUT_1,
	ELCL_FLIP_FLOP0_INPUT,
	ELCL_FLIP_FLOP1_INPUT, /* Changes from here*/
	ELCL_FLIP_FLOP0_SET,
	ELCL_FLIP_FLOP0_RESET,
	ELCL_FLIP_FLOP1_SET,
	ELCL_FLIP_FLOP1_RESET,
	ELCL_FLIP_FLOP0_CLK,
	ELCL_FLIP_FLOP1_CLK
}elcl_ctl_link_t;

/** @enum enumerated type representing the ELCL logic inversion state at output*/
typedef enum
{
	ELCL_POSITIVE_LOGIC = 0U,
	ELCL_INVERTED_LOGIC
}elcl_logic_t;

/** @enum enumerated type representing the ELCL logic output registers*/
typedef enum
{
	ELCL_OUTPUT_0 = 0U,
	ELCL_OUTPUT_1,
	ELCL_OUTPUT_2,
	ELCL_OUTPUT_3,
	ELCL_OUTPUT_4,
	ELCL_OUTPUT_5,
	ELCL_OUTPUT_6,
	ELCL_OUTPUT_7,
}elcl_output_num_t;

/** @enum enumerated type representing the ELCL logic output options*/
typedef enum
{
	ELCL_OUTPUT_L1_CELL0 = 1U,
	ELCL_OUTPUT_L1_CELL1,
	ELCL_OUTPUT_L1_SELECTOR,
	ELCL_OUTPUT_L1_FLIP_FLOP0,
	ELCL_OUTPUT_L1_FLIP_FLOP1,
	ELCL_OUTPUT_L2_CELL0,
	ELCL_OUTPUT_L2_CELL1,
	ELCL_OUTPUT_L2_SELECTOR,
	ELCL_OUTPUT_L2_FLIP_FLOP0,
	ELCL_OUTPUT_L2_FLIP_FLOP1,
	ELCL_OUTPUT_L3_CELL0,
	ELCL_OUTPUT_L3_CELL1,
	ELCL_OUTPUT_L3_SELECTOR,
	ELCL_OUTPUT_L3_FLIP_FLOP0,
	ELCL_OUTPUT_L3_FLIP_FLOP1,
}elcl_output_src_t;

/** @enum enumerated type to indicate the state (enabled/disabled) of elcl output*/
typedef enum
{
	ELCL_OUTPUT_DISABLED = 0U,
	ELCL_OUTPUT_ENABLED
}elcl_output_state_t;

/**
 * @brief Set the ELCL inputs
 * @param p_ctl - control block for elcl registers.
 * @param ip_num - input ELCL number
 * @param ip_src - input target source for ELCL
 */
void Elcl_set_input(const p_elcl_ctl_t p_ctl, const elcl_input_num_t ip_num, const elcl_input_src_t ip_src);

/**
 * @brief sets the input link for the register.
 * @param p_ctl - control block for elcl registers.
 * @param link_block - sets the target logic block.
 * @param link_reg - sets the link target register.
 * @param link - sets the target link for the link selection register.
 * @param logic_type - logic inversion state.
 */
void Elcl_link_input(const p_elcl_ctl_t p_ctl, const elcl_logic_block_t link_block, const elcl_logic_link_reg_t link_reg, const elcl_input_link_t link, const elcl_logic_t logic_type);

/**
 * @brief sets the logic configuration for a given logic block.
 * @param p_ctl - control block for elcl registers.
 * @param ctl_block - sets the target logic block.
 * @param cmd - specifies the command for logic control.
 */
void Elcl_set_logic(const p_elcl_ctl_t p_ctl, const elcl_logic_block_t ctl_block, const elcl_ctl_command cmd);

/**
 * @brief sets the logic to link to within the ELCL.
 * @param p_ctl - control block for elcl registers.
 * @param ctl_block - sets the target logic block.
 * @param link_reg - sets the link target register.
 * @param link - sets the target link for the link register.
 */
void Elcl_link_to_logic(const p_elcl_ctl_t p_ctl, const elcl_logic_block_t ctl_block, const elcl_logic_link_reg_t link_reg, const elcl_ctl_link_t link);

/**
 * @brief sets the output of the
 * @param p_ctl - control block for elcl registers.
 * @param op_num - output ELCL number
 * @param op_src - source of output for ELCL
 * @param logic_type - logic inversion state.
 */
void Elcl_set_output(const p_elcl_ctl_t p_ctl, const elcl_output_num_t op_num, const elcl_output_src_t op_src, const elcl_logic_t logic_type);

/**
 * @brief sets the enabled/disabled state of the elcl output.
 * @param p_ctl - control block for elcl registers.
 * @param op_num - output ELCL number
 * @param op_state - state of the elcl output (enabled/disabled).
 */
void Elcl_set_output_state(const p_elcl_ctl_t p_ctl, const elcl_output_num_t op_num, const elcl_output_state_t op_state);

#endif /* DRIVERS_ELCL_ELCL_H_ */
