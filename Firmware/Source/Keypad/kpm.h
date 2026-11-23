/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : kpm.h
 * Description  : Public interface for matrix keypad operations.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 * Compiler         : Keil uVision
 ******************************************************************************/

#include "types.h"

/*******************************************************************************
 * Keypad Initialization and Scanning
 ******************************************************************************/

void InitKPM(void);

u8 ColScan(void);
u8 RowCheck(void);
u8 ColCheck(void);
u8 KeyScan(void);

/*******************************************************************************
 * Keypad Numeric Input Operations
 ******************************************************************************/

u32 ReadNum(void);

void ReadNum2(u32 *num, u8 *lastKey);

void SelOp(u32 *num, u8 *lastKey);

