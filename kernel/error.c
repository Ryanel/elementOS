#include <textmode.h>
#include <stdio.h>
volatile unsigned char *videoram = (unsigned char *)0xB8000; //For pip
//#include <error.h>

/**
Stops the machine
**/
void halt(char* reason)
{
	//tm_print("[ HALT ]Kernel sent SIG_HALT because "); tm_print(reason); tm_print(".\n");
	log("HALT",0x0C,"Kernel sent SIG_HALT because "); printf("%s.\n",reason);
	log("HALT",0x0C,"Halting...");
	asm("cli");
	videoram[0]='!';
	while(1)
	{
		asm("hlt");
		videoram[2]='~'; // If it can't halt, then display a ~ after the !
	}
}

/**
Called when something errors, but it is NOT recoverable.
**/
void panic(char* reason)
{
	log("PANIC",0x0C,"Kernel Panic! Given reason:"); printf("%s.\n",reason); //tm_print(reason); tm_print(".\n");
	log("PANIC",0x0C,"Debug info:\n");
	log("PANIC",0x0C,"Registers: Failed to retrieve information\n");
	halt("kernel panic");
}

/**
Called when something errors, but it is recoverable.
**/
void oops(char* reason)
{
	log("OOPS",0x0C,"Kernel "); tm_print(reason); tm_print("!\n");
}

/**
Called when something unexpected happens.
**/
void woah(char* reason)
{
	//tm_print("WOAH! "); tm_print(reason); tm_print("!\n"); 
	log("WOAH",0x0C,"Kernel "); tm_print(reason); tm_print("!\n");
}

