/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : project_var.h
 * Description  : Shared external global variable declarations.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 ******************************************************************************/

#include "types.h"


/*******************************************************************************
 * External Interrupt Variables
 ******************************************************************************/

extern volatile u32 eint0_flag;


/*******************************************************************************
 * LED Status Variable
 ******************************************************************************/

extern volatile u32 led_status;


/*******************************************************************************
 * RTC Timing Variables
 ******************************************************************************/

extern u32 ONhour, ONmin, ONsec;
extern u32 OFFhour, OFFmin, OFFsec;


/*******************************************************************************
 * RTC Configuration Flags
 ******************************************************************************/

extern u32 ontime_flag;
extern u32 offtime_flag;
extern u32 initialtime_flag;

