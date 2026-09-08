                       /* main.c */
#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "spi.h"
#include "spi_eeprom.h"
#include "spi_eeprom_defines.h"
#include "dml.h"
#include "74LS164.h"
#include<string.h>

#define GLED (1<<16)
#define RLED (1<<17)
u8  rxData[26] __attribute__((at(0x40001000)));

int main(void)
{
	 u8 i,j=0,t;
	 unsigned char *str="HELP";
	 IODIR0 = 0xFF<<16; //ROWS as output
	Init_74LS164();
	 Init_SPI0();
	while(1)
	{
	     /*for(i=0;i<26;i++)
		 {
		     ByteWrite_25LC512(i,'A'+i);
             t=ByteRead_25LC512(i);
             rxData[i]=t;
			 display_char(rxData[i],1000);
		 } */

		    
   
		 PageWrite_25LC512(0x00000,str);
		 for(i=0;i<strlen(str);i++)
		 {
		     rxData[j++]=ByteRead_25LC512(0x0000+i);
		  }
			 rxData[j]='\0';
			 display_string(rxData);
			  
     

	} 
}   	 
          /* end of main25LC512.c */   
		  
		                                             
  
