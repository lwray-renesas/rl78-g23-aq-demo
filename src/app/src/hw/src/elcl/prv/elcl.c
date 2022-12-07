/*
 * elcl.c
 *
 *  Created on: 22 Apr 2021
 *      Author: Louis Wray
 */

#include "elcl_prv.h"

/** In a hosted environment we just point to a dummy structure - otherwise to peripheral memory map*/
#ifdef HOSTED_ENVIRONMENT
volatile elcl_regs_t elcl_regs_dummy; /* Dummy register set for host testing*/
#define ELCL_REGS		&elcl_regs_dummy
#else
#define ELCL_REGS		(elcl_regs_t *)0x0680
#endif

struct Elcl_ctl_t elcl_ctl = {
		.p_regs = ELCL_REGS
};

/**
 * @brief used to set specific ctl register accoring to command received.
 * @param p_reg - register for setting.
 * @param cmd - command to be interpreted for setting register.
 */
static void Elcl_set_ctl_reg(volatile uint8_t * p_reg, const elcl_ctl_command cmd)
{
	switch(cmd)
	{
	case ELCL_PASSTHROUGH_CELL_0:
		*p_reg &= 0xFCU;
		break;
	case ELCL_AND_CELL_0:
		*p_reg &= 0xFDU;
		*p_reg |= 0x01U;
		break;
	case ELCL_OR_CELL_0:
		*p_reg &= 0xFEU;
		*p_reg |= 0x02U;
		break;
	case ELCL_EXOR_CELL_0:
		*p_reg |= 0x03U;
		break;
	case ELCL_PASSTHROUGH_CELL_1:
		*p_reg &= 0xF3U;
		break;
	case ELCL_AND_CELL_1:
		*p_reg &= 0xF7U;
		*p_reg |= 0x04U;
		break;
	case ELCL_OR_CELL_1:
		*p_reg &= 0xFBU;
		*p_reg |= 0x08U;
		break;
	case ELCL_EXOR_CELL_1:
		*p_reg |= 0x0CU;
		break;
	case ELCL_ENABLE_FLIPFLOP0:
		*p_reg |= 0x40U;
		break;
	case ELCL_DISABLE_FLIPFLOP0:
		*p_reg &= 0xBFU;
		break;
	case ELCL_ENABLE_FLIPFLOP1:
		*p_reg |= 0x80U;
		break;
	case ELCL_DISABLE_FLIPFLOP1:
		*p_reg &= 0x7FU;
		break;
	default:
		/* do nothing - invalid*/
		break;
	}
}

void Elcl_set_input(const p_elcl_ctl_t p_ctl, const elcl_input_num_t ip_num, const elcl_input_src_t ip_src)
{
	p_ctl->p_regs->ELISEL[ip_num] = ip_src;
}
/* END OF FUNCTION*/

void Elcl_link_input(const p_elcl_ctl_t p_ctl, const elcl_logic_block_t link_block, const elcl_logic_link_reg_t link_reg, const elcl_input_link_t link, const elcl_logic_t logic_type)
{
	switch(link_block)
	{
	case ELCL_BLOCK1:
		p_ctl->p_regs->ELL1SEL[link_reg] = (link_reg < ELCL_LNK_4) ? link : link - 6U;
		p_ctl->p_regs->ELL1SEL[link_reg] = (logic_type == ELCL_POSITIVE_LOGIC) ? (p_ctl->p_regs->ELL1SEL[link_reg] & 0x7FU) : (p_ctl->p_regs->ELL1SEL[link_reg] | 0x80U);
		break;
	case ELCL_BLOCK2:
		p_ctl->p_regs->ELL2SEL[link_reg] = (link_reg < ELCL_LNK_4) ? link : link - 6U;
		p_ctl->p_regs->ELL2SEL[link_reg] = (logic_type == ELCL_POSITIVE_LOGIC) ? (p_ctl->p_regs->ELL2SEL[link_reg] & 0x7FU) : (p_ctl->p_regs->ELL2SEL[link_reg] | 0x80U);
		break;
	case ELCL_BLOCK3:
		p_ctl->p_regs->ELL3SEL[link_reg] = (link_reg < ELCL_LNK_4) ? link : link - 6U;
		p_ctl->p_regs->ELL3SEL[link_reg] = (logic_type == ELCL_POSITIVE_LOGIC) ? (p_ctl->p_regs->ELL3SEL[link_reg] & 0x7FU) : (p_ctl->p_regs->ELL3SEL[link_reg] | 0x80U);
		break;
	default:
		/* do nothing - invalid*/
		break;
	}
}
/* END OF FUNCTION*/

void Elcl_set_logic(const p_elcl_ctl_t p_ctl, const elcl_logic_block_t ctl_block, const elcl_ctl_command cmd)
{
	switch(ctl_block)
	{
	case ELCL_BLOCK1:
		Elcl_set_ctl_reg(&p_ctl->p_regs->ELL1CTL, cmd);
		break;
	case ELCL_BLOCK2:
		Elcl_set_ctl_reg(&p_ctl->p_regs->ELL2CTL, cmd);
		break;
	case ELCL_BLOCK3:
		Elcl_set_ctl_reg(&p_ctl->p_regs->ELL3CTL, cmd);
		break;
	default:
		/* do nothing - invalid*/
		break;
	}
}
/* END OF FUNCTION*/

void Elcl_link_to_logic(const p_elcl_ctl_t p_ctl, const elcl_logic_block_t ctl_block, const elcl_logic_link_reg_t link_reg, const elcl_ctl_link_t link)
{
	switch(ctl_block)
	{
	case ELCL_BLOCK1:
		if(link > ELCL_FLIP_FLOP1_INPUT)
		{
			switch(link)
			{
			case ELCL_FLIP_FLOP0_SET: p_ctl->p_regs->ELL1LNK[link_reg] |= 1U;	break;
			case ELCL_FLIP_FLOP0_RESET:	p_ctl->p_regs->ELL1LNK[link_reg] |= 2U;	break;
			case ELCL_FLIP_FLOP1_SET: p_ctl->p_regs->ELL1LNK[link_reg] |= 4U;	break;
			case ELCL_FLIP_FLOP1_RESET:	p_ctl->p_regs->ELL1LNK[link_reg] |= 8U;	break;
			case ELCL_FLIP_FLOP0_CLK: p_ctl->p_regs->ELL1LNK[link_reg] |= 1U;	break;
			case ELCL_FLIP_FLOP1_CLK: p_ctl->p_regs->ELL1LNK[link_reg] |= 2U;	break;
			default:
				/* Do nothing - invalid*/
				break;
			}
		}
		else
		{
			p_ctl->p_regs->ELL1LNK[link_reg] = link;
		}
		break;
	case ELCL_BLOCK2:
		if(link > ELCL_FLIP_FLOP1_INPUT)
		{
			switch(link)
			{
			case ELCL_FLIP_FLOP0_SET: p_ctl->p_regs->ELL2LNK[link_reg] = link;	break;
			case ELCL_FLIP_FLOP0_RESET:	p_ctl->p_regs->ELL2LNK[link_reg] = link;	break;
			case ELCL_FLIP_FLOP1_SET: p_ctl->p_regs->ELL2LNK[link_reg] |= 1U;	break;
			case ELCL_FLIP_FLOP1_RESET:	p_ctl->p_regs->ELL2LNK[link_reg] |= 1U;	break;
			case ELCL_FLIP_FLOP0_CLK: p_ctl->p_regs->ELL2LNK[link_reg] |= 1U;	break;
			case ELCL_FLIP_FLOP1_CLK: p_ctl->p_regs->ELL2LNK[link_reg] |= 2U;	break;
			default:
				/* Do nothing - invalid*/
				break;
			}
		}
		else
		{
			p_ctl->p_regs->ELL2LNK[link_reg] = link;
		}
		break;
	case ELCL_BLOCK3:
		if(link > ELCL_FLIP_FLOP1_INPUT)
		{
			switch(link)
			{
			case ELCL_FLIP_FLOP0_SET: p_ctl->p_regs->ELL3LNK[link_reg] = link;	break;
			case ELCL_FLIP_FLOP0_RESET:	p_ctl->p_regs->ELL3LNK[link_reg] = link;	break;
			case ELCL_FLIP_FLOP1_SET: p_ctl->p_regs->ELL3LNK[link_reg] |= 1U;	break;
			case ELCL_FLIP_FLOP1_RESET:	p_ctl->p_regs->ELL3LNK[link_reg] |= 1U;	break;
			case ELCL_FLIP_FLOP0_CLK: p_ctl->p_regs->ELL3LNK[link_reg] |= 1U;	break;
			case ELCL_FLIP_FLOP1_CLK: p_ctl->p_regs->ELL3LNK[link_reg] |= 2U;	break;
			default:
				/* Do nothing - invalid*/
				break;
			}
		}
		else
		{
			p_ctl->p_regs->ELL3LNK[link_reg] = link;
		}
		break;
	default:
		/* do nothing - invalid*/
		break;
	}
}
/* END OF FUNCTION*/

void Elcl_set_output(const p_elcl_ctl_t p_ctl, const elcl_output_num_t op_num, const elcl_output_src_t op_src, const elcl_logic_t logic_type)
{
	p_ctl->p_regs->ELOSEL[op_num] = op_src;
	p_ctl->p_regs->ELOSEL[op_num] = (logic_type == ELCL_POSITIVE_LOGIC) ? (p_ctl->p_regs->ELOSEL[op_num] & 0x7FU) : (p_ctl->p_regs->ELOSEL[op_num] | 0x80U);
}
/* END OF FUNCTION*/

void Elcl_set_output_state(const p_elcl_ctl_t p_ctl, const elcl_output_num_t op_num, const elcl_output_state_t op_state)
{
	if(ELCL_OUTPUT_ENABLED == op_state)
	{
		p_ctl->p_regs->ELOENCTL |= (1 << op_num);
	}
	else
	{
		p_ctl->p_regs->ELOENCTL &= ~(1 << op_num);
	}
}
/* END OF FUNCTION*/
