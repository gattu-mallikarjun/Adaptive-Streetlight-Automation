/******************************************************************************
 * Project          : Adaptive Streetlight Automation System
 * File Name        : led_symbol.c
 * Description      : Creates custom LED ON and OFF symbols in LCD CGRAM.
 *
 * Microcontroller  : LPC2148 (ARM7TDMI)
 * Compiler         : Keil uVision
 ******************************************************************************/

#include <LPC214x.h>

#include "types.h"
#include "lcd.h"
#include "led_symbol.h"


/*******************************************************************************
 * LED ON Symbol Pattern
 *
 * Each array element represents one row of the 5x8 LCD character.
 ******************************************************************************/

const u8 ledON[8] =
{
    0x04,
    0x0E,
    0x1F,
    0x1F,
    0x0E,
    0x04,
    0x00,
    0x00
};


/*******************************************************************************
 * LED OFF Symbol Pattern
 *
 * Each array element represents one row of the 5x8 LCD character.
 ******************************************************************************/

const u8 ledOFF[8] =
{
    0x04,
    0x0A,
    0x11,
    0x11,
    0x0A,
    0x04,
    0x00,
    0x00
};


/*******************************************************************************
 * Function Name : InitLEDSymbols
 * Description   : Stores LED ON and OFF symbols in LCD CGRAM.
 ******************************************************************************/

void InitLEDSymbols(void)
{
    /* Store LED ON symbol at CGRAM address 0x40. */
    BuildCGRAM(ledON, 8, 0x40);

    /* Store LED OFF symbol at CGRAM address 0x48. */
    BuildCGRAM(ledOFF, 8, 0x48);
}

