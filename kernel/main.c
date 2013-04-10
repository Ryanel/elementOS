#include <types.h>
#include <textmode.h>
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
void halt(char* reason);
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
   #if ARCH=i386-elf-linux-gnu
	drawBar(); // TODO: Adapt drawBar to ARM
   #endif
	tm_clear();
   tm_print("Starting elementOS...");
   #if ARCH=i386-elf-linux-gnu
   tm_print("Architecture: x86(Generic)");
   #endif
   #if ARCH=i386-elf-linux-gnu
   tm_print("Architecture: ARM(Raspberry Pi)");
   #endif
   //TODO: Add arch-specific code here.
   //halt("TOO MUCH RAINBOW");
	return 0;
}