#include <textmode.h>
#include <stdio.h>
#include <res/strings.h> 
volatile unsigned char *videoram = (unsigned char *)0xB8000; //For pip
//#include <error.h>

/**
Stops the machine
**/
void halt(char* reason)
{
	//tm_print("[ HALT ]Kernel sent SIG_HALT because "); tm_print(reason); tm_print(".\n");
	printf("================================================================================");//Line of 80 characters
	ksyslog(RES_ERROR_HALT_S,0x0C,RES_ERROR_HALTMSG_SIGHALT_S); printf("%s.\n",reason);

	ksyslog(RES_ERROR_HALT_S,0x0C,RES_ERROR_HALTMSG_S);
	
	asm("cli");
	videoram[0]=RES_PIP_HALTED_C;
	while(1)
	{
		asm("hlt");
		videoram[2]=RES_PIP_HALTED_FAILED_C; // If it can't halt, then display a ~ after the !
	}
}

/**
Called when something errors, but it is NOT recoverable.
**/
void panic(char* reason)
{
	ksyslog("PANIC",0x0C,"Kernel Panic! Given reason:"); printf("%s!\n",reason); //tm_print(reason); tm_print(".\n");
	ksyslog("PANIC",0x0C,"Debug info:\n");
	ksyslog("PANIC",0x0C,"Registers: Failed to retrieve information\n");
	halt("kernel panic");
}

/**
Called when something errors, but it is recoverable.
**/
void oops(char* reason)
{
	ksyslog("OOPS",0x0C,"Kernel "); tm_print(reason); tm_print("!\n");
}

/**
Called when something unexpected happens.
**/
void woah(char* reason)
{
	//tm_print("WOAH! "); tm_print(reason); tm_print("!\n"); 
	ksyslog("WOAH",0x0C,"Kernel "); tm_print(reason); tm_print("!\n");
}

