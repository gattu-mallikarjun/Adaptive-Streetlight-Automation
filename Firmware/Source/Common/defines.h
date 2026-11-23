
/******************************************************************************
 * File Name        : defines.h
 * Description      : Common bit manipulation macros.
 * Microcontroller  : LPC2148
 * Compiler         : Keil µVision
 ******************************************************************************/

/* Write an 8-bit value at the specified bit position. */
#define WRITEBYTE(WORD, STARTBIT, BYTE) \
        (WORD = ((WORD & ~(0xFF << STARTBIT)) | \
                 (BYTE << STARTBIT)))

/* Read a single bit. */
#define READBIT(WORD, BIT) \
        ((WORD >> BIT) & 1)

/* Write a 4-bit value at the specified bit position. */
#define WRITENIBBLE(WORD, STARTBIT, BYTE) \
        (WORD = ((WORD & ~(0xF << STARTBIT)) | \
                 (BYTE << STARTBIT)))

/* Read a 4-bit value. */
#define READNIBBLE(WORD, BIT) \
        ((WORD >> BIT) & 15)

/* Set the specified bit. */
#define SETBIT(WORD, BIT) \
        (WORD |= (1 << BIT))

/* Clear the specified bit. */
#define CLRBIT(WORD, BIT) \
        (WORD &= ~(1 << BIT))

/* Read a 10-bit value. */
#define READ10BIT(WORD, BITPOS) \
        ((WORD >> BITPOS) & 0x3FF)
