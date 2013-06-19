#include <types.h>
#include <textmode.h>
#include <res/strings.h> 
void panic(char* reason);
void halt(char* reason);
int gdt_install();
/*
Draws the bar on the top
*/
void drawBar()
{
	volatile unsigned char *videoram = (unsigned char *)0xB8000;
	//Draw top bar
	int i=0;
	int v=5;
	//Cleans Screen
	tm_clear();
	i=0;
	while(i!=160)
	{
		videoram[i] = ' ';
		videoram[i+1] = 0x70;
		i=i+2;
	}
	i=0;
	videoram[80-(v*2)+i] = 'e';
	i=i+2;
	videoram[80-(v*2)+i] = 'l';
	i=i+2;
	videoram[80-(v*2)+i] = 'e';
	i=i+2;
	videoram[80-(v*2)+i] = 'm';
	i=i+2;
	videoram[80-(v*2)+i] = 'e';
	i=i+2;
	videoram[80-(v*2)+i] = 'n';
	i=i+2;
	videoram[80-(v*2)+i] = 't';
	i=i+2;
	videoram[80-(v*2)+i] = 'O';
	i=i+2;
	videoram[80-(v*2)+i] = 'S';
	i=i+2;
}

void wait(int val)
{
	int i=0;
	while(i!=val)
		i++;
	i=0;
}
/**
Main process init point
**/
int main()
{
	int waittime=500000;
	drawBar();
	tm_clear();
	tm_print(RES_STARTMESSAGE_S);tm_print(RES_VERSION_S);tm_print(" (");tm_print(RES_SOURCE_S);tm_print(")...\n");
	//TODO: Add arch-specific code here.
	tm_print("Compiled for i386-x86\n");
	if(gdt_install()==0)
	{
		log(" OK ",0x02,"Installed GDT\n");
	}
	else
	{
		log("FAIL",0x02,"GDT installation failed. Kernel cannot initialise!\n");
		halt("GDT could not initialise");
	}
	halt("Kernel reached the end of its execution");
	return 0;
}
