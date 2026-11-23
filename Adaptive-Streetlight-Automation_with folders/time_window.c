
/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : time_window.c
 * Description  : Implements RTC-based streetlight operating time validation.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 ******************************************************************************/

/*******************************************************************************
 * Header Files
 ******************************************************************************/

#include <LPC214x.h>

#include "types.h"
#include "project_var.h"
#include "rtc.h"
#include "rtc_defines.h"

#include "time_window.h"


/*******************************************************************************
 * Function Name : IsWithinTime
 * Description   : Checks whether the current RTC time falls within the
 *                 configured streetlight ON and OFF schedule.
 *
 * Parameters    : None
 *
 * Return        : 1 - Current time is within the configured schedule.
 *                 0 - Current time is outside the configured schedule.
 ******************************************************************************/

unsigned int IsWithinTime(void)
{
    unsigned int currentTime;
    unsigned int startTime;
    unsigned int endTime;

    /* Convert current RTC time into minutes */
    currentTime = (HOUR * 60U) + MIN;

    /* Convert configured ON and OFF timings into minutes */
    startTime = (ONhour * 60U) + ONmin;
    endTime   = (OFFhour * 60U) + OFFmin;


    /* Case 1: Schedule does not cross midnight */
    if (startTime < endTime)
    {
        if ((currentTime >= startTime) && (currentTime < endTime))
        {
            return 1;
        }
    }

    /* Case 2: Schedule crosses midnight */
    else if (startTime > endTime)
    {
        if ((currentTime >= startTime) || (currentTime < endTime))
        {
            return 1;
        }
    }

    /* Current time is outside the configured schedule */
    return 0;
}
