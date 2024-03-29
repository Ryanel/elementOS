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
	//Setup
	drawBar();
	tm_clear();

	//Print start info
	printf("%^%s v.%s (%s) (%s)...%^\n",0x09,RES_STARTMESSAGE_S,RES_VERSION_S,RES_SOURCE_S,RES_ARCH_S,0x0F);
	printf("%^Codename:\"%s\"%^\n",0x09,RES_CODENAME_S,0x0F);

	//Verify Multiboot magic number
	if (magic!=0x2BADB002)
	{
		ksyslog("BOOT",0x02,"Magic number unverified!\n");
		panic("Booted in inconsistent state");
	}
	printf("%^%s booted elementOS up properly!%^\n",0x04,multiboot->boot_loader_name,0x0F);

	//Print memory
	int memtotal = (multiboot->mem_upper)+(multiboot->mem_lower);
	int memtotalmb = memtotal/1024;
	printf("%^%d kb%^ high, %^%d kb%^ low; a total of %^~%d mb%^ %^(%d kb)%^\n",0x03,multiboot->mem_upper,0x0F,0x0C,multiboot->mem_lower,0x0F,0x02,memtotalmb+1,0x0F,0x0A,memtotal,0x0F);

	//System initialising
	printf("--------------------------------------------------------------------------------");
	printf("Initialising system...\n");

	//For x86

	//GDT
	if(gdt_install()==0)
	{
		ksyslog(" OK ",0x02,"Installed GDT\n");
	}
	else
	{
		ksyslog("FAIL",0x02,"GDT installation failed. Kernel cannot initialise!\n");
		halt("GDT could not initialise");
	}

	if(idt_install()==0)
	{
		ksyslog(" OK ",0x02,"Installed IDT\n");
	}
	else
	{
		ksyslog("FAIL",0x02,"IDT installation failed. Kernel cannot initialise!\n");
		halt("IDT could not initialise");
	}

	if(isrs_install()==0)
	{
		ksyslog(" OK ",0x02,"Installed ISR's\n");
	}
	else
	{
		ksyslog("FAIL",0x02,"ISR installation failed. Kernel cannot initialise!\n");
		halt("ISR's could not initialise");
	}

	if(irq_install()==0)
	{
		ksyslog(" OK ",0x02,"Installed IRQ handlers\n");
	}
	else
	{
		ksyslog("FAIL",0x02,"IRQ handlers installation failed. Kernel cannot initialise!\n");
		halt("IRQ handlers could not initialise");
	}

	//PIT Setup
	{
		//volatile unsigned char *videoram = (unsigned char *)0xB8000;
		pit_install();
		//pit_phase(1000);
		asm("sti");
		printf("Waiting for %^78%^ ticks to see if %^IRQ's%^ and %^PIT%^ are setup...\n",0x02,0x0F,0x03,0x0F,0x04,0x0F);
		#ifndef OPT_NO_PROGRESS_BARS
		tm_putch_at('[',0,255);tm_putch_at(']',80-1,255);
		#endif
		int i=0;
		int count_inc=0;
		#ifndef OPT_NO_PROGRESS_BARS
		cursor_x=1;
		#endif
		pit_has_ticked();// Resets counter basicaly.
		while(i<78)
		{
			count_inc=pit_has_ticked();
			if(count_inc)
			{
				i+=count_inc;
				#ifndef OPT_NO_PROGRESS_BARS
				if(cursor_x!=1)
					tm_putch_at('=',cursor_x-1,255);
				if(cursor_x!=80)
					tm_putch_at('>',cursor_x,255);
				cursor_x+=count_inc;
				#endif
			}
			move_cursor();
		}
		#ifndef OPT_NO_PROGRESS_BARS
		cursor_x=0;
		cursor_y++;
		#endif
		ksyslog(" OK ",0x02,"Installed PIT\n");
		ksyslog("PASS",0x02,"Verified IRQ's\n");
	}
	kb_install();
	ksyslog(" OK ",0x02,"Installed Keyboard\n");
	detect_cpu();
	while(true)
	{
	}
	halt("ended");
	return 0;
}
