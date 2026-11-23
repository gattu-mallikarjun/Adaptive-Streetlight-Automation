/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : streetlight_main.c
 * Description  : Main application for adaptive streetlight automation.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 * Compiler         : Keil uVision
 *
 * Peripherals Used:
 *      1. LCD
 *      2. Matrix Keypad
 *      3. Real Time Clock (RTC)
 *      4. Analog-to-Digital Converter (ADC)
 *      5. LDR Sensor
 *      6. External Interrupt (EINT0)
 *      7. GPIO LED
 *
 * Author      :
 * Date        :
 ******************************************************************************/

/*******************************************************************************
 * Controller and Common Headers
 ******************************************************************************/

#include <LPC214x.h>

#include "types.h"
#include "defines.h"
#include "project_var.h"

/*******************************************************************************
 * Pin Configuration Headers
 ******************************************************************************/

#include "pin_function_defines.h"
#include "pin_connect_block.h"

/*******************************************************************************
 * Peripheral Driver Headers
 ******************************************************************************/

#include "lcd.h"
#include "lcd_defines.h"
#include "led_symbol.h"

#include "kpm.h"
#include "kpm_defines.h"

#include "adc.h"
#include "adc_defines.h"
#include "ldr.h"
#include "ldr_defines.h"

#include "rtc.h"
#include "rtc_defines.h"

#include "led_defines.h"

/*******************************************************************************
 * Application Module Headers
 ******************************************************************************/

#include "lcd_startup.h"
#include "time_window.h"
#include "eint.h"
#include "rtc_menu.h"

/*******************************************************************************
 * Local Function Declarations
 ******************************************************************************/

void DisplayLEDStatus(u8 status);


/*******************************************************************************
 * Global Variables
 ******************************************************************************/

/* LDR sensor measurement variables */
f32 lux;
f32 rldr;
f32 ear;
u16 dval;

/* Shared LED status */
volatile u32 led_status = 0;


/*******************************************************************************
 * Function Name : main
 * Description   : Initializes peripherals and executes the streetlight
 *                 automation application.
 * Parameters    : None
 * Return Value  : int
 ******************************************************************************/

int main(void)
{
    /***************************************************************************
     * GPIO Initialization
     **************************************************************************/

    /* Configure P0.7 as GPIO */
    CfgPortPinFunc(PORT0, LED_PIN, PIN_FUNC1);

    /* Configure P0.7 as output */
    SETBIT(IODIR0, LED_PIN);

    /* Initially turn OFF the streetlight */
    LED_OFF;


    /***************************************************************************
     * Peripheral Initialization
     **************************************************************************/

    /* Initialize LCD */
    InitLCD();

    /* Initialize RTC */
    InitRTC();

    /* Set initial RTC time and date for testing */
    SetRTCTimeInfo(11, 11, 57);
    SetRTCDateInfo(11, 11, 2026);

    /* Initialize matrix keypad */
    InitKPM();

    /* Initialize ADC */
    InitADC();

    /* Initialize external interrupt */
    InitEINT();

    /* Initialize LCD custom symbols */
    InitLEDSymbols();


    /***************************************************************************
     * System Startup
     **************************************************************************/

    DisplayStartup();


    /***************************************************************************
     * Main Application Loop
     **************************************************************************/

    while (1)
    {
        /* Display current RTC time on LCD line 1 */
        CmdLCD(GOTO_LINE1_POS0);
        DisplayRTCTime(HOUR, MIN, SEC);


        /* Display RTC date on LCD line 2 */
        CmdLCD(GOTO_LINE2_POS0);
        DisplayRTCDate(DOM, MONTH, YEAR);


        /* Display streetlight status at the right side of LCD line 2 */
        CmdLCD(GOTO_LINE2_POS0 + 15);

        if (READBIT(IOPIN0, LED_PIN) == 1)
        {
            DisplayLEDStatus(1);
        }
        else
        {
            DisplayLEDStatus(0);
        }


        /***********************************************************************
         * External Interrupt Handling
         **********************************************************************/

        if (eint0_flag == 1)
        {
            /* Clear external interrupt flag */
            eint0_flag = 0;

            /* Open RTC configuration menu */
            RTCMenu();
        }


        /***********************************************************************
         * Time-Based and LDR-Based Streetlight Control
         **********************************************************************/

        if (IsWithinTime())
        {
            /* Read ambient light intensity */
            Read_ldr(&lux, &rldr, &dval, &ear);

            /* Control streetlight according to LDR threshold */
            if (lux > LDR_THRESHOLD)
            {
                LED_OFF;
            }
            else
            {
                LED_ON;
            }
        }
        else
        {
            /* Turn OFF streetlight outside the configured time window */
            LED_OFF;
        }
    }
}


