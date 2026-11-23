/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : lcd_defines.h
 * Description  : LCD command and GPIO pin definitions.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 ******************************************************************************/

/*******************************************************************************
 * HD44780 LCD Command Definitions
 ******************************************************************************/

#define CLEAR_LCD           0x01U
#define RET_CUR_HOME        0x02U

#define SHIFT_CUR_RIGHT     0x06U
#define SHIFT_CUR_LEFT      0x07U

#define DSP_OFF             0x08U
#define DSP_ON_CUR_OFF      0x0CU
#define DSP_ON_CUR_ON       0x0EU
#define DSP_ON_CUR_BLINK    0x0FU

#define SHIFT_DISP_LEFT     0x10U
#define SHIFT_DISP_RIGHT    0x14U

#define MODE_81LINE         0x30U
#define MODE_41LINE         0x20U
#define MODE_82LINE         0x38U
#define MODE_42LINE         0x28U

#define GOTO_LINE1_POS0     0x80U
#define GOTO_LINE2_POS0     0xC0U
#define GOTO_LINE3_POS0     0x94U
#define GOTO_LINE4_POS0     0xD4U

#define GOTO_CGRAM_START    0x40U


/*******************************************************************************
 * LCD GPIO Pin Definitions
 *
 * Data pins : P0.8 - P0.15
 * RS        : P0.16
 * RW        : P0.17
 * EN        : P0.18
 ******************************************************************************/

#define LCD_DATA            8U
#define LCD_RS              16U
#define LCD_RW              17U
#define LCD_EN              18U

