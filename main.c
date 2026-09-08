#include <LPC21xx.H>
#include <string.h>
#include "delays.h"
#include "defines.h"
#include "74LS164.h"
#include "dml.h"


int main()
{
	int i;
	unsigned char *str="   vector india   ";
	IODIR0 = 0x0000ff; //ROWS as output
	Init_74LS164();
	while(1)
	{
	    for(i=0;i<strlen(str)-3;i++)
		//for(i=0;i<26;i++)
		//	display_char('A'+i,2000);
		//display_char('H',500);
		//display_char('E',500);
		//display_char('L',500);
		//display_char('P',500);

		//display_string("HELP");
		display_string(str+i);
	}
}

