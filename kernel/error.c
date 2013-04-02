#include <textmode.h>
//#include <error.h>
/**
Called when something errors, but it is NOT recoverable.
**/
void panic()
{
	
}
/**
Called when something errors, but it is recoverable.
**/
void oops()
{
	
}
/**
Called when something unexpected happens.
**/
void woah(char* reason)
{
	tm_print("WOAH! "); tm_print(reason); tm_print("!\n"); 
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
	{
		asm("hlt");
	}
}