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
int main()
{
   int waittime=1000000;
	drawBar();
	tm_clear();
	log("KERN",0x0F,"Hello, World!\n");
   wait(waittime);
   log("CLOR",0xf0,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0x5d,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0x4c,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0x1F,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0xeA,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0x52,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0x13,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0xb6,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0xd3,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0xae,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0xef,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0xd1,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0xc8,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0x4d,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0xab,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0xcd,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0xef,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0x34,"RAINBOW!\n");
   wait(waittime);
   log("CLOR",0x9F,"RAINBOW!\n");
   wait(waittime*2);

   halt("TOO MUCH RAINBOW");
	return 0;
}