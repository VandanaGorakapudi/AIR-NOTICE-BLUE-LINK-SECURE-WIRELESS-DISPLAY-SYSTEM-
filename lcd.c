#include<lpc21xx.h>
#include"types.h"
#include"defines.h"
#include"delay.h"
#include"lcd_defines.h"
#include"lcd.h"


void writeLCD(u8 byte)
{
    IOCLR0|=1<<LCD_RW;
	WRITEBYTE(IOPIN0,LCD_DATA,byte);
	IOSET0=1<<LCD_EN;
	delayUS(1);
	IOCLR0=1<<LCD_EN;
	delayMS(2);
}

void CmdLCD(u32 CmdByte)
{
   IOCLR0=1<<LCD_RS;
   writeLCD(CmdByte);
}

void Init_LCD(void)
{
   IODIR0|=((0XFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
   delayMS(15);
   CmdLCD(0X30);
   delayMS(4);
   delayUS(100);
   CmdLCD(0x30);
   delayUS(100);
   CmdLCD(0x30);
   CmdLCD(MODE_8BIT_2LINE);
   CmdLCD(DSP_ON_CUR_ON);
   CmdLCD(CLEAR_LCD);
   CmdLCD(SHIFT_CUR_RIGHT);
}

void CharLCD(u8 asciival)
{
     IOSET0=1<<LCD_RS;
	 writeLCD(asciival);
}

void StrLCD(s8 *str)
{
   while(*str)
      CharLCD(*str++);
}

void U32LCD(u32 n)
{
   s32 i=0;
   u8 a[10];
   if(n==0)
   {
       CharLCD('0');
   }
   else
   {
       while(n>0)
	   {
	       a[i++]=(n%10)+48;
		   n/=10;
	   }
	   for(--i;i>=0;i--)
	      CharLCD(a[i]);
	}
}

void S32LCD(s32 num)
{
   if(num<0)
   {
       CharLCD('-');
	   num=-num;
   }
   U32LCD(num);
}

void F32LCD(f32 fnum,u32 nDP)
{
    u32 num,i;
    if(fnum<0.0)
    {
       CharLCD('-');
       fnum=-fnum;
    }
    num=fnum;
    U32LCD(num);
    CharLCD('.');
    for(i=0;i<nDP;i++)
    {
       fnum=(fnum-num)*10;
       num=fnum;
       CharLCD(num+48);
    }
}

void BuildCGRAM(u8 *p,u8  nBytes)
{
    u32 i;
    CmdLCD(GOTO_CGRAM_START);
    IOSET0=1<<LCD_RS;
    for(i=0;i<nBytes;i++)
    {
       writeLCD(p[i]);
    }
    CmdLCD(GOTO_LINE1_POS0+2);
}

void binLCD(u32 n)
{
   s8 bit=15;
   while(bit>=0)
   {
        CharLCD(((n>bit)&1)+48);
		bit--;
   }
}

void hexLCD(u32 n)
{
    s32 i=0,digit;
	u8 a[8];
	if(n==0)
	    CharLCD('0');
	else
	{    
	    while(n)
		{
		    digit=n%16;
			digit=(digit>9)?((digit-10)+'A'):(digit+48);
			a[i++]=digit;
			n=n/16;
		}
		for(--i;i>=0;i--)
		{
		    CharLCD(a[i]);
	    }
	}
}

void octLCD(u32 n)
{
    u8 a[15];
	s32 i=0,x;
	if(n==0)
	    CharLCD('0');
	else
	{
	    while(n)
		{
		     x=n%8;
			 a[i++]=x+48;
			 n=n/8;
		}
		for(--i;i>=0;i--)
		    CharLCD(a[i]);
	}
}
