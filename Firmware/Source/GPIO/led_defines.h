/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : led_defines.h
 * Description  : LED pin configuration and control definitions.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 ******************************************************************************/

/*******************************************************************************
 * LED Pin Configuration
 ******************************************************************************/

#define LED_PIN             7U


/*******************************************************************************
 * LED Control Macros
 * LED is Active HIGH.
 ******************************************************************************/

#define LED_ON              (IOSET0 = (1U << LED_PIN))
#define LED_OFF             (IOCLR0 = (1U << LED_PIN))

