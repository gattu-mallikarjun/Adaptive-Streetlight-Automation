
/******************************************************************************
 * Project           : Adaptive Streetlight Automation System
 * File Name         : adc.h
 * Description       : Public interface for the ADC driver.
 *
 * Microcontroller   : LPC2148
 * Compiler          : Keil µVision
 ******************************************************************************/

/*******************************************************************************
 * Header Files
 ******************************************************************************/

#include "types.h"


/*******************************************************************************
 * ADC Driver Function Declarations
 ******************************************************************************/

/*
 * Function Name : InitADC
 * Description   : Initializes the ADC peripheral.
 * Parameters    : None
 * Return Value  : None
 */
void InitADC(void);


/*
 * Function Name : Read_ADC
 * Description   : Reads ADC conversion data from the selected channel.
 *
 * Parameters    : chNo - ADC channel number.
 *                 dVal - Pointer to store digital ADC value.
 *                 eAR  - Pointer to store analog input voltage.
 *
 * Return Value  : None
 */
void Read_ADC(u8 chNo, u16 *dVal, f32 *eAR);


