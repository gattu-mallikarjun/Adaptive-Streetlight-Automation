
/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : lcd_startup.c
 * Description  : Handles the LCD startup sequence of the streetlight system.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 ******************************************************************************/

/*******************************************************************************
 * Header Files
 ******************************************************************************/

#include <LPC214x.h>

#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"

#include "lcd_startup.h"


/*******************************************************************************
 * Function Name : DisplayStartup
 * Description   : Displays system initialization and ready messages on LCD.
 * Parameters    : None
 * Return        : None
 ******************************************************************************/

void DisplayStartup(void)
{
    /* Display system initialization message */
    CmdLCD(CLEAR_LCD);
    StrLCD("[ON] SYSTEM");

    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("INITIALIZING...");

    delay_s(1);


    /* Display project name and system ready message */
    CmdLCD(CLEAR_LCD);
    StrLCD("ADAPTIVE LIGHT");

    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("SYSTEM READY...");

    delay_s(1);


    /* Clear LCD before entering the main application */
    CmdLCD(CLEAR_LCD);
}
