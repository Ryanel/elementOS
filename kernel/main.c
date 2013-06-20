#include <types.h>
#include <textmode.h>
#include <res/strings.h> 
#include <stdio.h>
#include <multiboot.h>
void panic(char* reason);
void halt(char* reason);
int gdt_install();
int idt_install();
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
	while(i!=(80*2)) //80 characters, 80 color
	{
		videoram[i] = ' ';//Char
		videoram[i+1] = 0x70;//
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
int main(int magic, multiboot_header_t *multiboot)
{
	//Setup
	drawBar();
	tm_clear();

	//Print start info
	printf("%s v.%s (%s)...\n",RES_STARTMESSAGE_S,RES_VERSION_S,RES_SOURCE_S);
	printf("Codename:\"%s\"\n",RES_CODENAME_S);
	printf("Arch:%s\n",RES_ARCH_S);

	//Verify Multiboot magic number
	if (magic==0x2BADB002)
		log("BOOT",0x02,"Magic number verified\n");
	else {
		log("BOOT",0x02,"Magic number unverified!\n");
		panic("Booted in incosistant state");
	}

	//Print memory
	int memtotal = (multiboot->mem_upper)+(multiboot->mem_lower);
	int memtotalmb = memtotal/1024;
	printf("Memory:%d kb high, %d kb low; a total of %dmb\n",multiboot->mem_upper,multiboot->mem_lower,memtotalmb+1);


	//Systen initialising
	printf("--------------------------------------------------------------------------------");
	printf("Initialising system...\n");

	//For x86
	if(gdt_install()==0)
	{
		log(" OK ",0x02,"Installed GDT\n");
	}
	else
	{
		log("FAIL",0x02,"GDT installation failed. Kernel cannot initialise!\n");
		halt("GDT could not initialise");
	}

	if(idt_install()==0)
	{
		log(" OK ",0x02,"Installed IDT\n");
	}
	else
	{
		log("FAIL",0x02,"IDT installation failed. Kernel cannot initialise!\n");
		halt("IDT could not initialise");
	}
	memtotal = (multiboot->mem_upper)+(multiboot->mem_lower);
	memtotalmb = memtotal/0;
	printf("Memory:%d kb high, %d kb low; a total of %dmb\n",multiboot->mem_upper,multiboot->mem_lower,memtotalmb+1);
	halt("Kernel reached the end of its execution");
	return 0;
}