
/******************************************************************************
 * Project           : Adaptive Streetlight Automation System
 * File Name         : ldr.h
 * Description       : Public interface for the LDR sensor driver.
 *
 * Microcontroller   : LPC2148
 * Compiler           : Keil µVision
 ******************************************************************************/

/*******************************************************************************
 * Header Files
 ******************************************************************************/

#include "types.h"


/*******************************************************************************
 * Function Declaration
 ******************************************************************************/

/*
 * Function Name : Read_ldr
 * Description   : Reads ADC values and calculates LDR resistance and lux.
 *
 * Parameters    : lux  - Pointer to illumination value.
 *                 rldr - Pointer to LDR resistance.
 *                 dval - Pointer to ADC digital value.
 *                 ear  - Pointer to ADC input voltage.
 *
 * Return Value  : None
 */

void Read_ldr(f32 *lux, f32 *rldr, u16 *dval, f32 *ear);


