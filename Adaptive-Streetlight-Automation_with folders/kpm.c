/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : kpm.c
 * Description  : Matrix keypad initialization, scanning, and key operations.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 * Compiler         : Keil uVision
 ******************************************************************************/

/*******************************************************************************
 * Controller and Peripheral Headers
 ******************************************************************************/

#include <LPC214x.h>

#include "types.h"
#include "defines.h"
#include "kpm_defines.h"
#include "kpm.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"


/*******************************************************************************
 * Keypad Lookup Table
 *
 * Maps the row and column positions to their corresponding key values.
 *
 *             COLUMN
 *          0    1    2    3
 *       +----+----+----+----+
 * ROW 0 |  1 |  2 |  3 |  A |
 *       +----+----+----+----+
 * ROW 1 |  4 |  5 |  6 |  B |
 *       +----+----+----+----+
 * ROW 2 |  7 |  8 |  9 |  C |
 *       +----+----+----+----+
 * ROW 3 |  * |  0 |  = |  D |
 *       +----+----+----+----+
 ******************************************************************************/

u8 kpmLUT[4][4] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '=', 'D'}
};


/*******************************************************************************
 * Function Name : InitKPM
 * Description   : Initializes keypad row pins as outputs.
 ******************************************************************************/

void InitKPM(void)
{
    /* Configure all row lines as outputs and ground them. */
    WRITENIBBLE(IODIR1, ROW0, 15);
}


/*******************************************************************************
 * Function Name : ColScan
 * Description   : Checks whether any keypad key is pressed.
 * Return        : 0 - Key pressed
 *                 1 - No key pressed
 ******************************************************************************/

u8 ColScan(void)
{
    u8 status;

    status = (READNIBBLE(IOPIN1, COL0) < 15) ? 0 : 1;

    return status;
}


/*******************************************************************************
 * Function Name : RowCheck
 * Description   : Identifies the row in which a key is pressed.
 * Return        : Row number (0-3).
 ******************************************************************************/

u8 RowCheck(void)
{
    u8 row;

    for (row = 0; row < 4; row++)
    {
        /* Ground one row at a time while keeping other rows HIGH. */
        WRITENIBBLE(IOPIN1, ROW0, ~(1U << row));

        /* Check whether a key is pressed in the selected row. */
        if (!ColScan())
        {
            break;
        }
    }

    /* Restore all row lines to LOW. */
    WRITENIBBLE(IOPIN1, ROW0, 0);

    return row;
}


/*******************************************************************************
 * Function Name : ColCheck
 * Description   : Identifies the column in which a key is pressed.
 * Return        : Column number (0-3).
 ******************************************************************************/

u8 ColCheck(void)
{
    u8 col;

    for (col = 0; col < 4; col++)
    {
        if (READBIT(IOPIN1, COL0 + col) == 0)
        {
            break;
        }
    }

    return col;
}


/*******************************************************************************
 * Function Name : KeyScan
 * Description   : Scans the keypad and returns the pressed key.
 ******************************************************************************/

u8 KeyScan(void)
{
    u8 row;
    u8 col;
    u8 keyValue;

    /* Wait until a key is pressed. */
    while (ColScan());

    /* Identify the pressed key's row and column. */
    row = RowCheck();
    col = ColCheck();

    /* Retrieve the key value from the lookup table. */
    keyValue = kpmLUT[row][col];

    return keyValue;
}


/*******************************************************************************
 * Function Name : ReadNum
 * Description   : Reads a numeric value until a non-numeric key is pressed.
 * Return        : Entered numeric value.
 ******************************************************************************/

u32 ReadNum(void)
{
    u32 keyValue;
    u32 sum = 0;

    while (1)
    {
        keyValue = KeyScan();

        if ((keyValue >= '0') && (keyValue <= '9'))
        {
            sum = (sum * 10) + (keyValue - '0');

            CmdLCD(GOTO_LINE2_POS0);
            U32LCD(sum);

            /* Wait until the key is released. */
            while (ColScan() == 0);
        }
        else
        {
            if (keyValue == 'C')
            {
                CmdLCD(CLEAR_LCD);
            }

            /* Wait until the key is released. */
            while (ColScan() == 0);

            break;
        }
    }

    return sum;
}


/*******************************************************************************
 * Function Name : ReadNum2
 * Description   : Reads a number with backspace, clear, and confirmation.
 * Parameters    : num     - Stores the entered number.
 *                 lastKey - Stores the most recently pressed key.
 ******************************************************************************/

void ReadNum2(u32 *num, u8 *lastKey)
{
    *num = 0;

    while (1)
    {
        *lastKey = KeyScan();

        delay_ms(500);

        if ((*lastKey >= '0') && (*lastKey <= '9'))
        {
            *num = (*num * 10) + (*lastKey - '0');

            CmdLCD(GOTO_LINE2_POS0);
            U32LCD(*num);

            while (ColScan() == 0);
        }
        else if (*lastKey == 'B')
        {
            CmdLCD(SHIFT_DISP_LEFT);
            CharLCD(' ');
            CmdLCD(SHIFT_DISP_LEFT);

            *num /= 10;
        }
        else if (*lastKey == '=')
        {
            while (ColScan() == 0);

            break;
        }
        else if (*lastKey == '*')
        {
            *num = 0;

            CmdLCD(CLEAR_LCD);

            while (ColScan() == 0);
        }
        else
        {
            while (ColScan() == 0);
        }
    }
}


/*******************************************************************************
 * Function Name : SelOp
 * Description   : Reads a numeric selection with backspace, clear, and enter.
 * Parameters    : num     - Stores the entered number.
 *                 lastKey - Stores the most recently pressed key.
 ******************************************************************************/

void SelOp(u32 *num, u8 *lastKey)
{
    *num = 0;

    while (1)
    {
        *lastKey = KeyScan();

        delay_ms(500);

        if ((*lastKey >= '0') && (*lastKey <= '9'))
        {
            *num = (*num * 10) + (*lastKey - '0');

            CmdLCD(CLEAR_LCD);
            CmdLCD(GOTO_LINE2_POS0);
            U32LCD(*num);

            while (ColScan() == 0);
        }
        else if (*lastKey == '=')
        {
            while (ColScan() == 0);

            break;
        }
        else if (*lastKey == '*')
        {
            *num = 0;

            CmdLCD(CLEAR_LCD);

            while (ColScan() == 0);
        }
        else if (*lastKey == 'B')
        {
            CmdLCD(SHIFT_DISP_LEFT);
            CharLCD(' ');
            CmdLCD(SHIFT_DISP_LEFT);

            *num /= 10;
        }
        else
        {
            while (ColScan() == 0);
        }
    }
}

