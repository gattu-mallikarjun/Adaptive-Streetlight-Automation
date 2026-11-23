
/******************************************************************************
 * File Name        : adc.c
 * Description      : ADC driver implementation.
 * Microcontroller  : LPC2148
 * Compiler         : Keil µVision
 *
 * ADC Channels:
 * AIN0 - P0.27
 * AIN1 - P0.28
 * AIN2 - P0.29
 * AIN3 - P0.30
 ******************************************************************************/

#include <LPC21xx.h>
#include "types.h"
#include "adc_defines.h"
#include "delay.h"
#include "pin_function_defines.h"
#include "pin_connect_block.h"

#define ADC_REFERENCE_VOLTAGE       3.3
#define ADC_MAX_DIGITAL_VALUE       1023

/******************************************************************************
 * Function Name : InitADC
 * Description   : Configures ADC pins and enables the ADC peripheral.
 * Arguments     : None
 * Return Value  : None
 ******************************************************************************/
void InitADC(void)
{
    /* Configure P0.27 to P0.30 as ADC alternate-function pins. */
    CfgPortPinFunc(PORT0, 27, PIN_FUNC2);
    CfgPortPinFunc(PORT0, 28, PIN_FUNC2);
    CfgPortPinFunc(PORT0, 29, PIN_FUNC2);
    CfgPortPinFunc(PORT0, 30, PIN_FUNC2);

    /* Enable ADC and configure ADC clock divider. */
    ADCR |= (1 << PDN_BIT) | (CLKDIV_VAL << CLKDIV_BITS);
}

/******************************************************************************
 * Function Name : Read_ADC
 * Description   : Reads the selected ADC channel and calculates voltage.
 * Arguments     : chNo - ADC channel number
 *                 dVal - Pointer to store digital ADC value
 *                 eAR  - Pointer to store equivalent analog voltage
 * Return Value  : None
 ******************************************************************************/
void Read_ADC(u8 chNo, u16 *dVal, f32 *eAR)
{
    /* Check whether output pointers are valid. */
    if ((dVal == 0) || (eAR == 0))
        return;

    /* Clear previous ADC channel selection. */
    ADCR &= 0xFFFFFF00;

    /* Select requested channel and start ADC conversion. */
    ADCR |= (1 << ADC_CONV_START_BIT) | (1 << chNo);

    /* Wait for ADC conversion time. */
    delay_us(3);

    /* Wait until ADC conversion is completed. */
    while (((ADDR >> DONE_BIT) & 1) == 0);

    /* Stop ADC conversion. */
    ADCR &= ~(1 << ADC_CONV_START_BIT);

    /* Extract the 10-bit digital ADC value. */
    *dVal = ((ADDR >> DIGITAL_DATA_BITS) & ADC_MAX_DIGITAL_VALUE);

    /* Convert digital value into equivalent voltage. */
    *eAR = *dVal * (ADC_REFERENCE_VOLTAGE / ADC_MAX_DIGITAL_VALUE);
}
