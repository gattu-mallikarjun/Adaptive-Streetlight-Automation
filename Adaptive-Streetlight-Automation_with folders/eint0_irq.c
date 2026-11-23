/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : eint0_irq.c
 * Description  : EINT0 configuration and IRQ interrupt service routine.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 * Compiler         : Keil uVision
 ******************************************************************************/

/*******************************************************************************
 * Controller and Common Headers
 ******************************************************************************/

#include <LPC214x.h>

#include "types.h"
#include "defines.h"
#include "project_var.h"

/*******************************************************************************
 * Pin Configuration Headers
 ******************************************************************************/

#include "pin_function_defines.h"
#include "pin_connect_block.h"

/*******************************************************************************
 * EINT Configuration Headers
 ******************************************************************************/

#include "eint_defines.h"
#include "eint.h"

/*******************************************************************************
 * Internal Function Declaration
 ******************************************************************************/

/* EINT0 interrupt service routine */
static void eint0_isr(void) __irq;


/*******************************************************************************
 * Global Variables
 ******************************************************************************/

/* Indicates occurrence of EINT0 interrupt */
volatile u32 eint0_flag = 0;


/*******************************************************************************
 * Function Name : InitEINT
 * Description   : Configures P0.1 as EINT0 and enables its IRQ interrupt.
 ******************************************************************************/

void InitEINT(void)
{
    /* Configure P0.1 for EINT0 functionality */
    CfgPortPinFunc(PORT0, EINT0_PIN, PIN_FUNC4);

    /* Configure EINT0 as an IRQ interrupt */
    VICIntSelect &= ~(1U << EINT0_VIC_CHN);

    /* Configure EINT0 as edge-triggered interrupt */
    SETBIT(EXTMODE, EINT0_INTERRUPT_BIT);

    /* Select falling-edge triggering */
    CLRBIT(EXTPOLAR, EINT0_INTERRUPT_BIT);

    /* Clear any pending EINT0 interrupt */
    EXTINT = (1U << EINT0_INTERRUPT_BIT);

    /* Configure EINT0 as vectored interrupt, priority slot 0 */
    VICVectCntl0 = (1U << 5) | EINT0_VIC_CHN;

    /* Load ISR address into VIC vector slot */
    VICVectAddr0 = (unsigned)eint0_isr;

    /* Enable EINT0 interrupt in VIC */
    VICIntEnable = (1U << EINT0_VIC_CHN);
}


/*******************************************************************************
 * Function Name : eint0_isr
 * Description   : Handles the EINT0 external interrupt.
 ******************************************************************************/

static void eint0_isr(void) __irq
{
    /* Notify main application about the interrupt */
    eint0_flag = 1;

    /* Clear EINT0 interrupt status */
    EXTINT = (1U << EINT0_INTERRUPT_BIT);

    /* Acknowledge interrupt to VIC */
    VICVectAddr = 0;
}

