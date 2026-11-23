/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : delay.h
 * Description  : Public interface for software delay functions.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 ******************************************************************************/

#include "types.h"

/*******************************************************************************
 * Delay Function Prototypes
 ******************************************************************************/

void delay_us(u32 dlyUS);
void delay_ms(u32 dlyMS);
void delay_s(u32 dlyS);

