#include <textmode.h>
#include <stdio.h>
#include <res/strings.h>
#include <ksyslogd.h>
volatile unsigned char *videoram = (unsigned char *)0xB8000; //For pip
//#include <error.h>

/**
Stops the machine
**/
void halt(char* reason)
{
	//tm_print("[ HALT ]Kernel sent SIG_HALT because "); tm_print(reason); tm_print(".\n");
	ksyslog("HALT",MODE_PANIC,"Halting!");

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
	ksyslog("PANIC",MODE_PANIC,"Kernel Panic!");
	printf("Reason:%s!\n",reason); //tm_print(reason); tm_print(".\n");
	ksyslog("PANIC",MODE_PANIC,"Registers: Failed to retrieve information");
	halt("kernel panic");
}

/**
Called when something errors, but it is recoverable.
**/
void oops(char* reason)
{
	ksyslog("OOPS",MODE_CRIT,reason);
}

/**
Called when something unexpected happens.
**/
void woah(char* reason)
{
	//tm_print("WOAH! "); tm_print(reason); tm_print("!\n");
	ksyslog("WOAH",MODE_WARN,reason);
}

