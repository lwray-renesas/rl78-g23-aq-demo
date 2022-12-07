/*
 * elcl_prv.h
 *
 *  Created on: 22 Apr 2021
 *      Author: Louis Wray
 */

#ifndef DRIVERS_ELCL_PRV_H_
#define DRIVERS_ELCL_PRV_H_

#include "../elcl.h"

/** Struct defining layout of ELCL registers*/
typedef struct
{
	volatile uint8_t ELISEL[12]; 	/* 0xF0680*/
	volatile const uint8_t rsv0[4];
	volatile uint8_t ELL1SEL[7]; 	/* 0xF0690*/
	volatile uint8_t ELL1CTL; 		/* 0xF0697*/
	volatile uint8_t ELL1LNK[7]; 	/* 0xF0698*/
	volatile const uint8_t rsv1;
	volatile uint8_t ELL2SEL[7]; 	/* 0xF06A0*/
	volatile uint8_t ELL2CTL; 		/* 0xF06A7*/
	volatile uint8_t ELL2LNK[7]; 	/* 0xF06A8*/
	volatile const uint8_t rsv2;
	volatile uint8_t ELL3SEL[7]; 	/* 0xF06B0*/
	volatile uint8_t ELL3CTL; 		/* 0xF06B7*/
	volatile uint8_t ELL3LNK[7]; 	/* 0xF06B8*/
	volatile const uint8_t rsv3;
	volatile uint8_t ELOSEL[8]; 	/* 0xF06C0*/
	volatile uint8_t ELOENCTL; 		/* 0xF06C8*/
	const volatile uint8_t ELOMONI; /* 0xF06C9*/
}elcl_regs_t;

/** Struct defining ELCL control data*/
struct Elcl_ctl_t
{
	volatile elcl_regs_t * const p_regs;
};

#endif /* DRIVERS_ELCL_PRV_H_ */
