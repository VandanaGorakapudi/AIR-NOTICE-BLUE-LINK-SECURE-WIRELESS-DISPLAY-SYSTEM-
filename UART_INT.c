#include <LPC21xx.H>  /* LPC21xx definitions         */
#include <string.h>
#include "types.h"
#include "spi.h"
#include "spi_eeprom.h"
#include "spi_eeprom_defines.h"

#define UART_INT_ENABLE 1

void InitUART0 (void); /* Initialize Serial Interface       */ 
void UART0_Tx(char ch);  
char UART0_Rx(void);
void Init_74LS164(void);
  void display_string(u8 *string);    

 unsigned char buff[200]="   waiting for input  ",dummy;
static int i=0;
unsigned char ch,r_flag;
char temp[100];
 unsigned char rxData[26] __attribute__((at(0x40001000)));
void UART0_isr(void) __irq
{
  if((U0IIR & 0x04)) //check if receive interrupt
  {
		ch = U0RBR;	/* Read to Clear Receive Interrupt */
		if(ch !='@')
		{
			buff[i++] = ch;
			}
		/*	else if(ch==32)
			{
			   buff[i++]=ch;
			 }*/ 
		else
		{
		  buff[i]='\0';
			i=0;
			r_flag = 1;
		}
  }
  
      dummy=U0IIR; //Read to Clear transmit interrupt
  
   VICVectAddr = 0; /* dummy write */
}

void InitUART0 (void) /* Initialize Serial Interface       */ 
{  
            		
  PINSEL0 = 0x00000005; /* Enable RxD0 and TxD0              */
  U0LCR = 0x83;         /* 8 bits, no Parity, 1 Stop bit     */
  U0DLL = 97;           /* 9600 Baud Rate @ CCLK/4 VPB Clock  */
  U0LCR = 0x03;         /* DLAB = 0  */
  
  #if UART_INT_ENABLE > 0

  VICIntSelect = 0x00000000; // IRQ
  VICVectAddr0 = (unsigned)UART0_isr;
  VICVectCntl0 = 0x20 | 6; /* UART0 Interrupt */
  VICIntEnable = 1 << 6;   /* Enable UART0 Interrupt */
 
 // U0IIR = 0xc0;
 // U0FCR = 0xc7;
  U0IER = 0x03;       /* Enable UART0 RX and THRE Interrupts */   
             
  #endif
						
}

void UART0_Tx(char ch)  /* Write character to Serial Port    */  
{
  U0THR = ch;                 
  while (!(U0LSR & 0x20));

}

char UART0_Rx(void)    /* Read character from Serial Port   */
{                     
  while (!(U0LSR & 0x01));
  return (U0RBR);
}

void UART0_Str(char *s)
{
   while(*s)
       UART0_Tx(*s++);
}

void UART0_Int(unsigned int n)
{
  unsigned char a[10]={0,0,0,0,0,0,0,0,0,0};
  int i=0;
  if(n==0)
  {
    UART0_Tx('0');
	return;
  }
  else
  {
     while(n>0)
	 {
	   a[i++]=(n%10)+48;
	   n=n/10;
	 }
	 --i;
	 for(;i>=0;i--)
	 {
	   UART0_Tx(a[i]);
	 }
   }
}

void UART0_Float(float f)
{
  int x;
  float temp;
  x=f;
  UART0_Int(x);
  UART0_Tx('.');
  temp=(f-x)*100;
  x=temp;
  UART0_Int(x);
}

void  DelayS(unsigned int  dly)
{  unsigned int  i;

   for(; dly>0; dly--) 
      for(i=1200000; i>0; i--);
}

  void display_passkey(unsigned char*str)
  {
     int i=0,j=0;
     while(str[i]!='\0')
	 {
	   if(str[i]>=65&&str[i]<=90||str[i]>=97&&str[i]<=122)
	   {
	     str[j++]=str[i];
		 }	 
		 str[j]='\0';
     	}
  }

 int checkpasskey(char* data, char *temp)
 {
     char passkey[20]="$$789";
	 if(strstr(data,passkey))
	 {
			int len=strlen(data);
			int i,j;
			if(data[len-1]=='$' && data[len-2]=='$')
			{
				for(i=0;i<3;i++)
                {
                     temp[j++]=' ';
                }

			    for(i=5;i<strlen(data)-2;i++)
		        {
		                temp[j++]=data[i];
			    }
				for(i=0;i<3;i++)
                {
                  temp[j++]=' ';
                }

				temp[j]='\0';
		   }
		   return 1;
		}
	  else
			return 0;
 }
 char wbuff[200],c;				
 int l;				
int main()
{
unsigned int j=0;
  InitUART0();
   IODIR0|=0XFF<<16;
	 Init_SPI0();
	 Init_74LS164();
		
   	  /*PageWrite_25LC512(0x0000,buff);
	  memset(wbuff,'\0',200);
		strcpy(wbuff,(const char *)buff);
		memset(buff,'\0',200);																																																																																												    
		ByteWrite_25LC512(0x0050,strlen(wbuff));*/
		//ByteWrite_25LC512(0x0060,'^');
		//c=ByteRead_25LC512(0x0060);
		l=ByteRead_25LC512(0x0050);
		UART0_Int(l);
		if(l==255)
		{
			memset(rxData,'\0',200);
			 strcpy(rxData,"   waiting for input   ");
		}
		else
		{
		for(i=0;i<l;i++)
	 	{
     		rxData[j]=ByteRead_25LC512(0x0000+i);
		 	j++;
		 }
		 }
  while(1)
  {		j=0;
		i=0;r_flag=0;                                                                                                       
	/*	memset(wbuff,'\0',200);
		strcpy(wbuff,(const char *)buff);
		memset(buff,'\0',200); 
		for(i=0;i<strlen(wbuff);i++)
	 	{
     		rxData[j]=ByteRead_25LC512(0x0000+i);
		 	j++;
		 }	*/
		do
		{
		  i=0;
			for(j=0;j<strlen((const char *)rxData)-3;j++)
		 	{												 
					display_string(rxData+j);
					if(r_flag==1)
					break;
			}

		}
		while(r_flag == 0);
		r_flag=0;
		j=0;
		 UART0_Str((char *)buff);
		 //memset(rxData,'\0',200);
     //PageWrite_25LC512(0x0000,buff);
		if(checkpasskey(buff,temp))
		{ 	
		     memset(rxData,'\0',200);
		     PageWrite_25LC512(0x0000,temp);
						//	memset(rxData,'\0',200);
		 
		   for(j=0;j<strlen(temp);j++)
	 	  {
     		rxData[j]=ByteRead_25LC512(0x0000+j);														 	
		  }
		  rxData[j]='\0';
		  //strcpy(wbuff,(const char *)buff);
		  ByteWrite_25LC512(0x0050,strlen(temp));
		//l=ByteRead_25LC512(0x0050);
		}
		 //checkpasskey(rxData);
			
  }
}

