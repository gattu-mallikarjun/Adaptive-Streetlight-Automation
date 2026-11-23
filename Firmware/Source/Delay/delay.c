/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : delay.c
 * Description  : Software-based microsecond, millisecond, and second delays.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 * Compiler         : Keil uVision
 *
 * Clock Frequency  : CCLK = 60 MHz
 ******************************************************************************/

#include "types.h"


/*******************************************************************************
 * Function Name : delay_us
 * Description   : Generates an approximate microsecond delay.
 * Parameter     : dlyUS - Delay duration in microseconds.
 ******************************************************************************/

void delay_us(u32 dlyUS)
{
    volatile u32 count;

    /* Approximately 1 us per iteration at CCLK = 60 MHz. */
    count = dlyUS * 12U;

    while (count > 0U)
    {
        count--;
    }
}


/*******************************************************************************
 * Function Name : delay_ms
 * Description   : Generates an approximate millisecond delay.
 * Parameter     : dlyMS - Delay duration in milliseconds.
 ******************************************************************************/

void delay_ms(u32 dlyMS)
{
    volatile u32 count;

    /* Approximately 1 ms per 12000 iterations at CCLK = 60 MHz. */
    count = dlyMS * 12000U;

    while (count > 0U)
    {
        count--;
    }
}


/*******************************************************************************
 * Function Name : delay_s
 * Description   : Generates an approximate second delay.
 * Parameter     : dlyS - Delay duration in seconds.
 ******************************************************************************/

void delay_s(u32 dlyS)
{
    volatile u32 count;

    /* Approximately 1 second per 12000000 iterations at CCLK = 60 MHz. */
    count = dlyS * 12000000U;

    while (count > 0U)
    {
        count--;
    }
}

