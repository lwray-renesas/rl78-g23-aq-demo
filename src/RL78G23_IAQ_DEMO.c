/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
*  File Name    : RL78G23_IAQ_DEMO.c
*  Description  : Main Program
*  Creation Date: 2023-07-11
*  This file was generated by Smart Configurator.
***********************************************************************************************************************/
#include "r_smc_entry.h"
#if 0
#include "smc_gen/r_config/rm_touch_config.h"
#endif
#include "app.h"

/** Macro definition for applications task stack sizes*/
#define DEFAULT_TASK_STACK_SIZE	(1024U)

/***********************************************************
 * THREADS
 **********************************************************/
/** GUI thread*/
rltos_task_t gui_thread;
stack_type gui_task_stack[DEFAULT_TASK_STACK_SIZE] = {0U};
extern void Gui_thread_main(void);

/** Event thread*/
rltos_task_t event_thread;
stack_type event_task_stack[DEFAULT_TASK_STACK_SIZE] = {0U};
extern void Event_thread_main(void);

/***********************************************************
 * MUTEX'S
 **********************************************************/
/** Sensor Data Mutex*/
rltos_mutex_t sensor_mutex;
/** Alarm Sensor Data Mutex*/
rltos_mutex_t alarm_sensor_mutex;

/***********************************************************
 * EVENT FLAG's
 **********************************************************/
/** GUI Event Flags*/
rltos_events_t gui_events;
/** GUI Return Signal Event Flags*/
rltos_events_t gui_return_events;

#ifdef TOUCH_CFG_UART_TUNING_SUPPORT
extern void qe_touch_main(void);
#endif

void main(void)
{
    EI();

#ifdef TOUCH_CFG_UART_TUNING_SUPPORT
    qe_touch_main();
#else

    /* Disable UART input buffer*/
    PDIDIS7_bit.no1 = 1U;
    PDIDIS7_bit.no2 = 1U;

	/* Initialise RLTOS hardware requirements*/
	Rltos_port_start_tick_timer = R_Config_TAU0_2_Start;
	Rltos_port_stop_tick_timer = R_Config_TAU0_2_Stop;

	/* Initialise the hardware*/
	Hw_init();

	/* Create the threads*/
	Rltos_task_create(&gui_thread, &gui_task_stack[DEFAULT_TASK_STACK_SIZE-1U], Gui_thread_main, true);
	Rltos_task_create(&event_thread, &event_task_stack[DEFAULT_TASK_STACK_SIZE-1U], Event_thread_main, true);

	/* Create the mutex's*/
	Rltos_mutex_create(&sensor_mutex, RLTOS_FALSE, NULL);
	Rltos_mutex_create(&alarm_sensor_mutex, RLTOS_FALSE, NULL);

	/* Create the event's*/
	Rltos_events_create(&gui_events, 0U);
	Rltos_events_create(&gui_return_events, 0U);

	/* Enter rltos Kernel*/
	Rltos_kernel_enter();
#endif
}
