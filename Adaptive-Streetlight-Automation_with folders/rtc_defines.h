/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : rtc_defines.h
 * Description  : RTC prescaler calculations and control register definitions.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 ******************************************************************************/

/*******************************************************************************
 * RTC Prescaler Calculation Macros
 *
 * RTC requires a 32.768 kHz clock for 1-second increment.
 *
 * PREINT  = int(PCLK / 32768) - 1
 * PREFRAC = PCLK - ((PREINT + 1) * 32768)
 *
 * Reference: LPC21xx User Manual
 ******************************************************************************/

#define PREINT_VAL  ((int)((PCLK / 32768) - 1))
#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768))


/*******************************************************************************
 * RTC Control Register (CCR) Bit Definitions
 ******************************************************************************/

/* Bit 0: Clock Enable */
#define RTC_ENABLE      (1U << 0)

/* Bit 1: Clock Reset */
#define RTC_RESET       (1U << 1)

/* Bit 4: Clock Source Select (LPC2148) */
#define RTC_CLKSRC      (1U << 4)

