#include <textmode.h>
//#include <error.h>
/**
Called when something errors, but it is NOT recoverable.
**/
void panic(char* reason)
{
	log("!!!!",0x0C,"Kernel Panic! Given reason:"); tm_print(reason); tm_print(".\n");
	tm_print("DEBUG INFO:\n")
	log("!!!!",0x0C,"Debug info:\n");
	log("!!!!",0x0C,"Registers: Failed to retrieve information\n");
	halt("kernel panic");
}
/**
Called when something errors, but it is recoverable.
**/
void oops()
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
/**
Stops the machine
**/
void halt(char* reason)
{
	//tm_print("[ HALT ]Kernel sent SIG_HALT because "); tm_print(reason); tm_print(".\n");
	log("HALT",0x0C,"Kernel sent SIG_HALT because "); tm_print(reason); tm_print(".\n");
	log("HALT",0x0C,"Halting...");
	asm("cli");
	while(1)
	{
		asm("hlt");
	}
}
