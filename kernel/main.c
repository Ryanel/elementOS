#include <types.h>
#include <textmode.h>
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
int main()
{
	drawBar();
	tm_clear();
	tm_print("Hello, World!");
	return 0;
}