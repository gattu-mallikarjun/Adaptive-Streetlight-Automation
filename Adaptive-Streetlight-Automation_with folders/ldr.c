
/******************************************************************************
 * Project           : Adaptive Streetlight Automation System
 * File Name         : ldr.c
 * Description       : LDR sensor driver implementation.
 *
 * Microcontroller   : LPC2148
 * Compiler          : Keil µVision
 *
 * Hardware Details:
 *      ADC Channel       : ADC0.1
 *      LDR Supply        : 3.3V
 *      Fixed Resistor    : 5K Ohms
 ******************************************************************************/

/*******************************************************************************
 * Header Files
 ******************************************************************************/

#include <math.h>

#include "types.h"
#include "adc.h"
#include "ldr.h"


/*******************************************************************************
 * LDR Hardware Configuration
 ******************************************************************************/

/* ADC channel connected to LDR */
#define LDR_ADC_CHANNEL              1U

/* Voltage divider configuration */
#define LDR_SUPPLY_VOLTAGE           3.3
#define LDR_FIXED_RESISTANCE         5000.0

/* LDR calibration parameters */
#define LDR_GAMMA                    0.7
#define LDR_CALIBRATION_CONSTANT     500000.0


/*******************************************************************************
 * Function Name : Read_ldr
 * Description   : Reads ADC data and calculates LDR resistance and
 *                 illumination level in lux.
 *
 * Parameters    : lux  - Pointer to calculated illumination value.
 *                 rldr - Pointer to calculated LDR resistance.
 *                 dval - Pointer to raw ADC digital value.
 *                 ear  - Pointer to ADC input voltage.
 *
 * Return Value  : None
 ******************************************************************************/

void Read_ldr(f32 *lux, f32 *rldr, u16 *dval, f32 *ear)
{
    /* Local variables */
    u16 adc_value;
    f32 adc_voltage;


    /***************************************************************************
     * Validate Output Pointers
     **************************************************************************/

    if ((lux == 0) || (rldr == 0) ||
        (dval == 0) || (ear == 0))
    {
        return;
    }


    /***************************************************************************
     * Initialize Output Values
     **************************************************************************/

    *lux = 0;
    *rldr = 0;
    *dval = 0;
    *ear = 0;


    /***************************************************************************
     * Read ADC Data
     **************************************************************************/

    Read_ADC(LDR_ADC_CHANNEL, &adc_value, &adc_voltage);


    /* Store raw ADC readings */
    *dval = adc_value;
    *ear = adc_voltage;


    /***************************************************************************
     * ADC Voltage Validation
     **************************************************************************/

    if ((adc_voltage <= 0) ||
        (adc_voltage >= LDR_SUPPLY_VOLTAGE))
    {
        return;
    }


    /***************************************************************************
     * Calculate LDR Resistance
     *
     * Voltage divider equation:
     *
     * Rldr = Rfixed * ((Vcc - Vadc) / Vadc)
     **************************************************************************/

    *rldr = LDR_FIXED_RESISTANCE *
            ((LDR_SUPPLY_VOLTAGE - adc_voltage) / adc_voltage);


    /***************************************************************************
     * Calculate Illumination in Lux
     **************************************************************************/

    if (*rldr > 0)
    {
        *lux = pow((LDR_CALIBRATION_CONSTANT / *rldr),
                   (1.0 / LDR_GAMMA));
    }
}
