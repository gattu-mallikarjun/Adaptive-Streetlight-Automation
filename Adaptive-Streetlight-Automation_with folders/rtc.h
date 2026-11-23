/******************************************************************************
 * Project      : Adaptive Streetlight Automation System
 * File Name    : rtc.h
 * Description  : Public function declarations for RTC operations.
 *
 * Microcontroller : LPC2148 (ARM7TDMI)
 ******************************************************************************/

#include "types.h"

/*******************************************************************************
 * RTC Initialization
 ******************************************************************************/
void InitRTC(void);

/*******************************************************************************
 * RTC Time Operations
 ******************************************************************************/
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second);
void DisplayRTCTime(u32 hour, u32 minute, u32 second);
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second);

/*******************************************************************************
 * RTC Date Operations
 ******************************************************************************/
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year);
void DisplayRTCDate(u32 date, u32 month, u32 year);
void SetRTCDateInfo(u32 date, u32 month, u32 year);

/*******************************************************************************
 * RTC Day Operations
 ******************************************************************************/
void GetRTCDay(s32 *day);
void DisplayRTCDay(u32 day);
void SetRTCDay(u32 day);

