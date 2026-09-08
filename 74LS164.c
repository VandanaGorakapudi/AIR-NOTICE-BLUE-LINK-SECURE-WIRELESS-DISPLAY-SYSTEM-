                       /* 74LS164.c */
#include "defines.h"
#include "delays.h"
#include <LPC21xx.h>


#define SIN1  8     //p0.8
#define CP1   9    //p0.9

#define SIN2  10     //p0.10
#define CP2   11     //p0.11

#define SIN3  12    //p0.12
#define CP3   13     //p0.13

#define SIN4  14    //p0.14
#define CP4   15     //p0.15

//#define SIN  8     //p0.8
//#define CP   12     //p0.9

void Init_74LS164(void)
{
	IODIR0 |= (1<<CP1|1<<SIN1)|(1<<CP2|1<<SIN2)|(1<<CP3|1<<SIN3)|(1<<CP4|1<<SIN4);
}

/*void SIPO_74LS164(unsigned char sDat) //Serial In Parallel Out(SIPO) Operations

{

   unsigned char i;

   //SCLRBIT(IOCLR0,_MR);

   //delay_us(1);

   //SSETBIT(IOSET0,_MR);

   //delay_us(1);

	

   for(i=0;i<8;i++)

   {

		   WRITEBIT(IOPIN0,SIN1,((sDat>>(7-i))&1));

		   SSETBIT(IOSET0,CP1);

		   delay_us(1);

		   SCLRBIT(IOCLR0,CP1);

		   delay_us(1);

   }
}	*/

void SIPO_74LS164(unsigned int SIN,unsigned int CP,unsigned char sDat) //Serial In Parallel Out(SIPO) Operations
{
   unsigned char i;
   //SCLRBIT(IOCLR0,_MR);
   //delay_us(1);
   //SSETBIT(IOSET0,_MR);
   //delay_us(1);
	
   for(i=0;i<8;i++)
   {
		   WRITEBIT(IOPIN0,SIN,((sDat>>(7-i))&1));
		   SSETBIT(IOSET0,CP);
		   delay_us(1);
		   SCLRBIT(IOCLR0,CP);
		   delay_us(1);
   }

   
 }
