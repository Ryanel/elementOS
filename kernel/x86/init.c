/*
init.c
Has initialisation functions for the kernel, and contains the entry point
*/
//Headers

#include <types.h>
#include <textmode.h>
#include <res/strings.h>
#include <stdio.h>
#include <multiboot.h>
#include <arch/x86.h>
#include <devices/x86.h>
#include <vt.h>
#include <ksyslogd.h>
//Prototypes
//TODO:Add to includes
void panic(char* reason);
void halt(char* reason);
void woah(char* reason);

char kb_readFromBuffer(int index);
char kb_popNextFromBuffer();

//Helper functions


/**
Draws the bar on the top
**/
void drawBar()
{
	volatile unsigned char *videoram = (unsigned char *)0xB8000;
	int i=0;
	int v=40-5; // The place to start drawing (v = vertical). 5 characters before 40
	//Cleans Screen
	tm_clear();
	while(i!=(80*2)) //Draws background
	{
		videoram[i] = ' ';// Space
		videoram[i+1] = 0x70;// Grey
		i=i+2;
	}

	//Draw tite
	i=v*2;
	videoram[i] = 'e';
	i=i+2;
	videoram[i] = 'l';
	i=i+2;
	videoram[i] = 'e';
	i=i+2;
	videoram[i] = 'm';
	i=i+2;
	videoram[i] = 'e';
	i=i+2;
	videoram[i] = 'n';
	i=i+2;
	videoram[i] = 't';
	i=i+2;
	videoram[i] = 'O';
	i=i+2;
	videoram[i] = 'S';
	i=i+2;
	// End title drawing
}

//Init

/**
Main process init point
**/
int kinit_x86(int magic, multiboot_header_t *multiboot)
{
	drawBar();
	tm_clear();

	printf("%^%s v.%s (%s) (%s)...%^\n",0x09,RES_STARTMESSAGE_S,RES_VERSION_S,RES_SOURCE_S,RES_ARCH_S,0x0F);
	printf("%^Codename:\"%s\"%^\n",0x09,RES_CODENAME_S,0x0F);
	ksyslog_setmask(MODE_WARN);
	//Verify Multiboot magic number
	if (magic!=0x2BADB002)
	{
		ksyslog("BOOT",0x00,"Magic number is invalid");
		panic("Booted in inconsistent state!");
	}
	ksyslog("BOOT",MODE_DEBUG,"Multiboot verified");

	//Print memory
	int memtotal = (multiboot->mem_upper)+(multiboot->mem_lower);
	int memtotalmb = memtotal/1024;
	printf("%^%d kb%^ high, %^%d kb%^ low; a total of %^~%d mb%^ %^(%d kb)%^\n",0x03,multiboot->mem_upper,0x0F,0x0C,multiboot->mem_lower,0x0F,0x02,memtotalmb+1,0x0F,0x0A,memtotal,0x0F);

	//Init

	gdt_install();
	ksyslog(" OK ",MODE_INFO,"Installed GDT");

	idt_install();
	ksyslog(" OK ",MODE_INFO,"Installed IDT");

	isrs_install();
	ksyslog(" OK ",MODE_INFO,"Installed ISR's");

	irq_install();
	ksyslog(" OK ",MODE_INFO,"Installed IRQ handlers");

	pit_install();
	pit_phase(1000);
	asm("sti");
	ksyslog(" OK ",MODE_INFO,"Installed PIT");

	kb_install();
	ksyslog(" OK ",MODE_INFO,"Installed Keyboard");

	ksyslog("SYST",MODE_INFO,"System finished initialising\n");

	ksyslog("DECT",MODE_DEBUG,"Detecting Hardware...");
	detect_cpu();

	while(true)
	{
	}
	halt("ended");
	return 0;
}
