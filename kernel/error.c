//#include <lsys/text.h>
//#include <sys/error.h>
void tmprints(char* message)
{
	
}
void panic()
{
	
}
void oops()
{
	
}
void woah(char* reason)
{
	tmprints("WOAH! "); tmprints(reason); tmprints("!\n"); 
}
void halt(char* reason)
{
	tmprints("Kernel sent SIG_HALT because "); tmprints(reason); tmprints(".\n Halting...");
	while(1)
	{
		asm("hlt");
	}
	
}