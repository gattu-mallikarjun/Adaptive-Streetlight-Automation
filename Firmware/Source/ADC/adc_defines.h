
/******************************************************************************
 * Project           : Adaptive Streetlight Automation System
 * File Name         : adc_defines.h
 * Description       : ADC clock configuration, register bit positions,
 *                     and ADC pin function definitions.
 *
 * Microcontroller   : LPC2148
 * Compiler          : Keil µVision
 ******************************************************************************/

/*******************************************************************************
 * Clock Configuration
 *
 * FOSC    : External oscillator frequency (12 MHz).
 * CCLK    : CPU clock frequency (FOSC multiplied by 5).
 * PCLK    : Peripheral clock frequency (CCLK divided by 4).
 * ADC_CLK : Required ADC clock frequency (3 MHz).
 ******************************************************************************/

#define FOSC                12000000U
#define CCLK                (FOSC * 5U)
#define PCLK                (CCLK / 4U)
#define ADC_CLK             3000000U


/*******************************************************************************
 * ADCR - ADC Control Register Definitions
 ******************************************************************************/

/* ADC clock divider bit position */
#define CLKDIV_BITS         8U

/* ADC power-down control bit */
#define PDN_BIT             21U

/* ADC conversion start control bit */
#define ADC_CONV_START_BIT  24U

/* ADC clock divider calculation */
#define CLKDIV_VAL          ((PCLK / ADC_CLK) - 1U)


/*******************************************************************************
 * ADDR - ADC Data Register Definitions
 ******************************************************************************/

/* Starting bit position of 10-bit digital conversion result */
#define DIGITAL_DATA_BITS   6U

/* ADC conversion completion status bit */
#define DONE_BIT            31U


/*******************************************************************************
 * ADC Pin Function Definitions
 *
 * AIN0 : ADC channel 0
 * AIN1 : ADC channel 1
 * AIN2 : ADC channel 2
 * AIN3 : ADC channel 3
 ******************************************************************************/

#define AIN0_FUNC           0x00400000U
#define AIN1_FUNC           0x01000000U
#define AIN2_FUNC           0x04000000U
#define AIN3_FUNC           0x10000000U
