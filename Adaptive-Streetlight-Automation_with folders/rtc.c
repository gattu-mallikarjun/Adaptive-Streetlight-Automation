/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : rtc.c
 * Description  : RTC initialization, time, date, and day operations.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 ******************************************************************************/

#include <LPC214x.h>

#include "types.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "lcd.h"
#include "lcd_defines.h"

/*******************************************************************************
 * Controller Selection
 ******************************************************************************/
#define LPC2129  0
#define LPC2148  1

#define CPU      LPC2148

/*******************************************************************************
 * Weekday Names
 *
 * DOW values:
 * 0 - Sunday
 * 1 - Monday
 * 2 - Tuesday
 * 3 - Wednesday
 * 4 - Thursday
 * 5 - Friday
 * 6 - Saturday
 ******************************************************************************/
static char week[][4] =
{
    "SUN",
    "MON",
    "TUE",
    "WED",
    "THU",
    "FRI",
    "SAT"
};

/*******************************************************************************
 * Function Name : InitRTC
 * Description   : Initializes the RTC peripheral.
 ******************************************************************************/
void InitRTC(void)
{
    CCR = RTC_RESET;

#if (CPU == LPC2129)

    PREINT  = PREINT_VAL;
    PREFRAC = PREFRAC_VAL;

    CCR = RTC_ENABLE;

#elif (CPU == LPC2148)

    CCR = RTC_ENABLE | RTC_CLKSRC;

#endif

    AMR = 0xF8;
}

/*******************************************************************************
 * Function Name : GetRTCTimeInfo
 * Description   : Reads the current RTC time.
 ******************************************************************************/
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
    *hour   = HOUR;
    *minute = MIN;
    *second = SEC;
}

/*******************************************************************************
 * Function Name : DisplayRTCTime
 * Description   : Displays RTC time on LCD line 1.
 ******************************************************************************/
void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
    CmdLCD(GOTO_LINE1_POS0);

    CharLCD((hour / 10) + '0');
    CharLCD((hour % 10) + '0');
    CharLCD(':');

    CharLCD((minute / 10) + '0');
    CharLCD((minute % 10) + '0');
    CharLCD(':');

    CharLCD((second / 10) + '0');
    CharLCD((second % 10) + '0');
}

/*******************************************************************************
 * Function Name : GetRTCDateInfo
 * Description   : Reads the current RTC date.
 ******************************************************************************/
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
    *date  = DOM;
    *month = MONTH;
    *year  = YEAR;
}

/*******************************************************************************
 * Function Name : DisplayRTCDate
 * Description   : Displays RTC date on LCD line 2.
 ******************************************************************************/
void DisplayRTCDate(u32 date, u32 month, u32 year)
{
    CmdLCD(GOTO_LINE2_POS0);

    CharLCD((date / 10) + '0');
    CharLCD((date % 10) + '0');
    CharLCD('/');

    CharLCD((month / 10) + '0');
    CharLCD((month % 10) + '0');
    CharLCD('/');

    U32LCD(year);
}

/*******************************************************************************
 * Function Name : SetRTCTimeInfo
 * Description   : Sets the RTC time.
 ******************************************************************************/
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
    HOUR = hour;
    MIN  = minute;
    SEC  = second;
}

/*******************************************************************************
 * Function Name : SetRTCDateInfo
 * Description   : Sets the RTC date.
 ******************************************************************************/
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
    DOM   = date;
    MONTH = month;
    YEAR  = year;
}

/*******************************************************************************
 * Function Name : GetRTCDay
 * Description   : Reads the current weekday value.
 ******************************************************************************/
void GetRTCDay(s32 *day)
{
    *day = DOW;
}

/*******************************************************************************
 * Function Name : DisplayRTCDay
 * Description   : Displays the weekday on LCD line 1.
 ******************************************************************************/
void DisplayRTCDay(u32 day)
{
    if (day < 7U)
    {
        CmdLCD(GOTO_LINE1_POS0 + 11);
        StrLCD((s8 *)week[day]);
    }
}

/*******************************************************************************
 * Function Name : SetRTCDay
 * Description   : Sets the RTC weekday.
 ******************************************************************************/
void SetRTCDay(u32 day)
{
    DOW = day;
}

