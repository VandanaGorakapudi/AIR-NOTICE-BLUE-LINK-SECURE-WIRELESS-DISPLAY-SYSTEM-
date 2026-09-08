#include "types.h"
void Init_LCD(void);
void writeLCD(u8);
void CmdLCD(u32);
void CharLCD(u8);
void StrLCD(s8*);
void U32LCD(u32);
void S32LCD(s32);
void F32LCD(f32,u32);
void BuildCGRAM(u8 *,u8);
void binLCD(u32 n);
void hexLCD(u32 n);
void octLCD(u32 n);

