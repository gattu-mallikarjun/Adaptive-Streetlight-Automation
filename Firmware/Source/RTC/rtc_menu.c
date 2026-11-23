
/******************************************************************************
 * Project           : Adaptive Streetlight Automation System
 * File Name         : rtc_menu.c
 * Description       : Handles RTC configuration, streetlight ON/OFF timing,
 *                     and RTC information display through keypad and LCD.
 * Microcontroller   : LPC2148
 * Compiler          : Keil µVision
 ******************************************************************************/

#include <LPC214x.h>

#include "types.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "kpm_defines.h"
#include "project_var.h"
#include "delay.h"
#include "rtc_menu.h"
#include "rtc_menu_defines.h"

/*******************************************************************************
 * Private Function Declarations
 ******************************************************************************/

/* Time configuration menus */
static void SetTimeMenu(void);
static void ViewTimeMenu(void);
static void SetRTCMenu(void);

/* RTC setting functions */
static void SetHour(void);
static void SetMinute(void);
static void SetSecond(void);
static void SetDay(void);
static void SetDate(void);
static void SetMonth(void);
static void SetYear(void);

/* Streetlight ON/OFF time configuration */
static void SetStreetlightONTime(void);
static void SetStreetlightOFFTime(void);

static void SetONHour(void);
static void SetONMinute(void);
static void SetOFFHour(void);
static void SetOFFMinute(void);

/* Display functions */
static void DisplayRTCInfo(void);
static void DisplayStreetlightONTime(void);
static void DisplayStreetlightOFFTime(void);


/*******************************************************************************
 * Global Streetlight Timing Variables
 ******************************************************************************/

u32 ONhour, ONmin, ONsec;
u32 OFFhour, OFFmin, OFFsec;


/*******************************************************************************
 * Function Name : RTCMenu
 * Description   : Displays the main RTC menu and handles user selections.
 * Arguments     : None
 * Return Value  : None
 ******************************************************************************/

void RTCMenu(void)
{
    u32 op = 0;
    u8 lastKey;

OPTION:

    op = 0;

    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
    StrLCD("1:SET  2:VIEW");

    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("3:EXIT");

    SelOp(&op, &lastKey);

    switch(op)
    {
        case RTC_MENU_SET_TIME:
            SetTimeMenu();
            goto OPTION;

        case RTC_MENU_VIEW_TIME:
            ViewTimeMenu();
            goto OPTION;

        case RTC_MENU_EXIT:
            return;

        default:
            CmdLCD(CLEAR_LCD);
            StrLCD("INVALID OPTION");
            delay_ms(500);
            CmdLCD(CLEAR_LCD);
            goto OPTION;
    }
}


/*******************************************************************************
 * Function Name : SetTimeMenu
 * Description   : Provides options to configure RTC and streetlight timings.
 ******************************************************************************/

static void SetTimeMenu(void)
{
    u32 op = 0;
    u8 lastKey;

SELECT:

    CmdLCD(CLEAR_LCD);
    StrLCD("1.RTC 2.ONTIME");

    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("3.OFFTIME 4.EXIT");

    SelOp(&op, &lastKey);

    switch(op)
    {
        case TIME_MENU_RTC:
            SetRTCMenu();
            goto SELECT;

        case TIME_MENU_ON_TIME:
            SetStreetlightONTime();
            goto SELECT;

        case TIME_MENU_OFF_TIME:
            SetStreetlightOFFTime();
            goto SELECT;

        case TIME_MENU_EXIT:
            return;

        default:
            CmdLCD(CLEAR_LCD);
            StrLCD("INVALID OPTION");
            delay_ms(500);
            goto SELECT;
    }
}


/*******************************************************************************
 * Function Name : SetRTCMenu
 * Description   : Provides options to edit RTC time and date parameters.
 ******************************************************************************/

static void SetRTCMenu(void)
{
    u32 op = 0;
    u8 lastKey;

SELECT:

    CmdLCD(CLEAR_LCD);
    StrLCD("1.H 2.M 3.S 4.D");

    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("5.d 6.m 7.y 8.E");

    SelOp(&op, &lastKey);

    switch(op)
    {
        case RTC_EDIT_HOUR:
            SetHour();
            goto SELECT;

        case RTC_EDIT_MINUTE:
            SetMinute();
            goto SELECT;

        case RTC_EDIT_SECOND:
            SetSecond();
            goto SELECT;

        case RTC_EDIT_DAY:
            SetDay();
            goto SELECT;

        case RTC_EDIT_DATE:
            SetDate();
            goto SELECT;

        case RTC_EDIT_MONTH:
            SetMonth();
            goto SELECT;

        case RTC_EDIT_YEAR:
            SetYear();
            goto SELECT;

        case RTC_EDIT_EXIT:
            return;

        default:
            CmdLCD(CLEAR_LCD);
            StrLCD("INVALID OPTION");
            delay_ms(500);
            CmdLCD(CLEAR_LCD);
            goto SELECT;
    }
}


/*******************************************************************************
 * RTC TIME AND DATE SETTING FUNCTIONS
 ******************************************************************************/

static void SetHour(void)
{
    u32 num = 0;
    u8 lastKey;

SETHOUR:

    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER HOURS");

    ReadNum2(&num, &lastKey);

    if(num >= 24)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID ENTRY");
        delay_ms(500);
        goto SETHOUR;
    }

    HOUR = num;
    return;
}


static void SetMinute(void)
{
    u32 num = 0;
    u8 lastKey;

SETMIN:

    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER MIN");

    ReadNum2(&num, &lastKey);

    if(num >= 60)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID ENTRY");
        delay_ms(500);
        goto SETMIN;
    }

    MIN = num;
    return;
}


static void SetSecond(void)
{
    u32 num = 0;
    u8 lastKey;

SETSEC:

    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER SEC");

    ReadNum2(&num, &lastKey);

    if(num >= 60)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID ENTRY");
        delay_ms(500);
        goto SETSEC;
    }

    SEC = num;
    return;
}


static void SetDay(void)
{
    u32 num = 0;
    u8 lastKey;

SETDAY:

    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER DAY");

    ReadNum2(&num, &lastKey);

    if(num >= 7)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID ENTRY");
        delay_ms(500);
        goto SETDAY;
    }

    DOW = num;
    return;
}


static void SetDate(void)
{
    u32 num = 0;
    u8 lastKey;

SETDATE:

    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER DATE");

    ReadNum2(&num, &lastKey);

    if(num >= 32)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID ENTRY");
        delay_ms(500);
        goto SETDATE;
    }

    DOM = num;
    return;
}


static void SetMonth(void)
{
    u32 num = 0;
    u8 lastKey;

SETMONTH:

    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER MONTH");

    ReadNum2(&num, &lastKey);

    if((num >= 13) || (num == 0))
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID ENTRY");
        delay_ms(500);
        goto SETMONTH;
    }

    MONTH = num;
    return;
}


static void SetYear(void)
{
    u32 num = 0;
    u8 lastKey;

SETYEAR:

    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER YEAR");

    ReadNum2(&num, &lastKey);

    if(num >= 4096)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID ENTRY");
        delay_ms(500);
        goto SETYEAR;
    }

    YEAR = num;
    return;
}


/*******************************************************************************
 * STREETLIGHT ON-TIME CONFIGURATION
 ******************************************************************************/

static void SetStreetlightONTime(void)
{
    u32 op = 0;
    u8 lastKey;

ONTIME:

    CmdLCD(CLEAR_LCD);
    StrLCD("1.ONHOUR 2.ONMIN");

    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("3.EXIT");

    SelOp(&op, &lastKey);

    switch(op)
    {
        case STREETLIGHT_SET_HOUR:
            SetONHour();
            goto ONTIME;

        case STREETLIGHT_SET_MINUTE:
            SetONMinute();
            goto ONTIME;

        case STREETLIGHT_MENU_EXIT:
            return;

        default:
            CmdLCD(CLEAR_LCD);
            StrLCD("INVALID OPTION");
            delay_ms(500);
            CmdLCD(CLEAR_LCD);
            goto ONTIME;
    }
}


static void SetONHour(void)
{
    u32 num = 0;
    u8 lastKey;

SETONHOUR:

    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER ONHOUR");

    ReadNum2(&num, &lastKey);

    if(num >= 24)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID ENTRY");
        delay_ms(500);
        goto SETONHOUR;
    }

    ONhour = num;
    return;
}


static void SetONMinute(void)
{
    u32 num = 0;
    u8 lastKey;

SETONMIN:

    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER ONMIN");

    ReadNum2(&num, &lastKey);

    if(num >= 60)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID ENTRY");
        delay_ms(500);
        goto SETONMIN;
    }

    ONmin = num;
    return;
}


/*******************************************************************************
 * STREETLIGHT OFF-TIME CONFIGURATION
 ******************************************************************************/

static void SetStreetlightOFFTime(void)
{
    u32 op = 0;
    u8 lastKey;

OFFTIME:

    CmdLCD(CLEAR_LCD);
    StrLCD("1.OFFHH 2.OFFMM");

    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("3.EXIT");

    SelOp(&op, &lastKey);

    switch(op)
    {
        case STREETLIGHT_SET_HOUR:
            SetOFFHour();
            goto OFFTIME;

        case STREETLIGHT_SET_MINUTE:
            SetOFFMinute();
            goto OFFTIME;

        case STREETLIGHT_MENU_EXIT:
            return;

        default:
            CmdLCD(CLEAR_LCD);
            StrLCD("INVALID OPTION");
            delay_ms(500);
            CmdLCD(CLEAR_LCD);
            goto OFFTIME;
    }
}


static void SetOFFHour(void)
{
    u32 num = 0;
    u8 lastKey;

SETOFFHOUR:

    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER OFF HOUR");

    ReadNum2(&num, &lastKey);

    if(num >= 24)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID ENTRY");
        delay_ms(500);
        goto SETOFFHOUR;
    }

    OFFhour = num;
    return;
}


static void SetOFFMinute(void)
{
    u32 num = 0;
    u8 lastKey;

SETOFFMIN:

    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER OFFMIN");

    ReadNum2(&num, &lastKey);

    if(num >= 60)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID ENTRY");
        delay_ms(500);
        goto SETOFFMIN;
    }

    OFFmin = num;
    return;
}


/*******************************************************************************
 * VIEW TIME MENU
 ******************************************************************************/

static void ViewTimeMenu(void)
{
    u32 op = 0;
    u8 lastKey;

SELECT:

    CmdLCD(CLEAR_LCD);
    StrLCD("1.RTC 2.ONTIME");

    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("3.OFFTIME 4.EXIT");

    SelOp(&op, &lastKey);

    switch(op)
    {
        case TIME_MENU_RTC:
            DisplayRTCInfo();
            goto SELECT;

        case TIME_MENU_ON_TIME:
            DisplayStreetlightONTime();
            goto SELECT;

        case TIME_MENU_OFF_TIME:
            DisplayStreetlightOFFTime();
            goto SELECT;

        case TIME_MENU_EXIT:
            return;

        default:
            CmdLCD(CLEAR_LCD);
            StrLCD("INVALID OPTION");
            delay_ms(500);
            CmdLCD(CLEAR_LCD);
            goto SELECT;
    }
}


/*******************************************************************************
 * Function Name : DisplayRTCInfo
 * Description   : Displays current RTC time and date on LCD.
 ******************************************************************************/

static void DisplayRTCInfo(void)
{
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);

    CharLCD((HOUR / 10) + '0');
    CharLCD((HOUR % 10) + '0');
    CharLCD(':');
    CharLCD((MIN / 10) + '0');
    CharLCD((MIN % 10) + '0');
    CharLCD(':');
    CharLCD((SEC / 10) + '0');
    CharLCD((SEC % 10) + '0');

    CmdLCD(GOTO_LINE2_POS0);

    CharLCD((DOM / 10) + '0');
    CharLCD((DOM % 10) + '0');
    CharLCD('/');
    CharLCD((MONTH / 10) + '0');
    CharLCD((MONTH % 10) + '0');
    CharLCD('/');
    U32LCD(YEAR);

    delay_s(1);
    CmdLCD(CLEAR_LCD);
}


/*******************************************************************************
 * Function Name : DisplayStreetlightONTime
 * Description   : Displays configured streetlight ON time.
 ******************************************************************************/

static void DisplayStreetlightONTime(void)
{
    CmdLCD(CLEAR_LCD);
    StrLCD("ON TIME");

    CmdLCD(GOTO_LINE2_POS0);

    CharLCD((ONhour / 10) + '0');
    CharLCD((ONhour % 10) + '0');
    CharLCD(':');
    CharLCD((ONmin / 10) + '0');
    CharLCD((ONmin % 10) + '0');

    delay_ms(500);
    CmdLCD(CLEAR_LCD);
}


/*******************************************************************************
 * Function Name : DisplayStreetlightOFFTime
 * Description   : Displays configured streetlight OFF time.
 ******************************************************************************/

static void DisplayStreetlightOFFTime(void)
{
    CmdLCD(CLEAR_LCD);
    StrLCD("OFF TIME");

    CmdLCD(GOTO_LINE2_POS0);

    CharLCD((OFFhour / 10) + '0');
    CharLCD((OFFhour % 10) + '0');
    CharLCD(':');
    CharLCD((OFFmin / 10) + '0');
    CharLCD((OFFmin % 10) + '0');

    delay_ms(500);
    CmdLCD(CLEAR_LCD);
}
