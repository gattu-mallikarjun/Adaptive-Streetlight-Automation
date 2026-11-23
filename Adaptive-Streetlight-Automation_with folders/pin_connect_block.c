/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : pin_connect_block.c
 * Description  : Configures alternate functions using LPC2148
 *                Pin Connect Block registers.
 *
 * Microcontroller : LPC2148
 ******************************************************************************/

#include <LPC214x.h>

#include "types.h"
#include "pin_function_defines.h"
#include "pin_connect_block.h"


/*******************************************************************************
 * Function Name : CfgPortPinFunc
 * Description   : Configures the alternate function of a Port 0 pin.
 *
 * Parameters    : portNo  - Port number
 *                 pinNo   - Pin number (0-31)
 *                 pinFunc - Pin function selection (0-3)
 *
 * Return        : None
 ******************************************************************************/

void CfgPortPinFunc(u32 portNo, u32 pinNo, u32 pinFunc)
{
    u32 shift;

    /* PINSEL0 and PINSEL1 configure Port 0 pins */
    if (portNo != PORT0)
    {
        return;
    }

    /* Validate pin number and function selection */
    if ((pinNo > 31U) || (pinFunc > 3U))
    {
        return;
    }

    /* Calculate PINSEL bit position */
    shift = (pinNo % 16U) * 2U;

    /* Configure P0.0 to P0.15 using PINSEL0 */
    if (pinNo <= 15U)
    {
        PINSEL0 = (PINSEL0 & ~(3U << shift))
                | (pinFunc << shift);
    }
    /* Configure P0.16 to P0.31 using PINSEL1 */
    else
    {
        PINSEL1 = (PINSEL1 & ~(3U << shift))
                | (pinFunc << shift);
    }
}

