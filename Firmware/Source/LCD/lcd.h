/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : lcd.h
 * Description  : Public interface for LCD driver operations.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 * Compiler         : Keil uVision
 ******************************************************************************/

#include "types.h"

/*******************************************************************************
 * LCD Initialization and Data Operations
 ******************************************************************************/

void InitLCD(void);
void WriteLCD(u8 byte);
void CmdLCD(u8 cmd);
void CharLCD(u8 asciiVal);
void StrLCD(s8 *s);

/*******************************************************************************
 * Numeric Display Operations
 ******************************************************************************/

void U32LCD(u32 n);
void S32LCD(s32 n);
void F32LCD(f32 fn, u8 nDP);

/*******************************************************************************
 * Custom Character and LED Status Operations
 ******************************************************************************/

void BuildCGRAM(const u8 *p, u8 nBytes, u8 address);
void DisplayLEDStatus(u8 status);

//void BuildCGRAM(const u8 *p,u8 nBytes);

