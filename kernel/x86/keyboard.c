// Keyboard
#include <textmode.h>
#include <types.h>
#include <low.h>
#include <arch/x86.h>
#include <stdio.h>
unsigned char kbdus[256] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};		
unsigned char kbdus_sft[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
 '"', '~',   0,		/* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};		
bool keystat_crtl, keystat_shift, keystat_alt;
bool keystat_numlock, keystat_capslock, keystat_scrolllock;

char character_buffer[1024];
int buffer_pointer=0;
/**
Sends a command to the keyboard, and returns the output.
**/
uint8_t kb_sendCommand(uint8_t command)
{
	while(true)
		if ((inb(0x64) & 2) == 0) break;
	return 0;
}

void kb_addToBuffer(char c)
{
	if(buffer_pointer<1024)
	{
		character_buffer[buffer_pointer]=c;
		buffer_pointer++;
	}
}

char kb_readFromBuffer(int index)
{
	return character_buffer[index];
}
char input=0;
char kb_waitForInput()
{
	while(input==0)
	{

	}
  char ret=input;
  input=0;
	return ret;
}

char kb_popNextFromBuffer()
{
	int i;
	char result = character_buffer[0];
	for (i = 0; i < 256; i++)
	{
		character_buffer[i] = character_buffer[i+1];
	}
	if(buffer_pointer!=0)
		buffer_pointer--;
	return result;
}
void keyboard_handler(struct regs *r)
{
    unsigned char scancode;
    /* Read from the keyboard's data buffer */
    scancode = inb(0x60);
    if (scancode & 0x80)
    {
  		switch(scancode-0x80)
  		{
  			case 0x2a:
  				keystat_shift = false;
  				break;
  			case 0x36:
  				keystat_shift = false;
  				break;
  			default:;
  				//Misc' breakcode
  		}
    }
	else
	{
		switch(scancode)
		{
			case 0x2a: //Shift
				keystat_shift = true;
				break;
			case 0x36:
				keystat_shift = true;
				break;
			case 69: //lol | Numlock
				keystat_numlock = true;
				break;
			case 58: //Capslock
				keystat_capslock=!keystat_capslock; //Make it flip later
				break;
			default:
				if(keystat_shift)
				{
					printf("%c",kbdus_sft[scancode]);
					kb_addToBuffer(kbdus_sft[scancode]);
					input=kbdus_sft[scancode];
				}
				else
				{
					printf("%c",kbdus[scancode]);
					kb_addToBuffer(kbdus[scancode]);
					input=kbdus[scancode];
				}
				break;

		}
	}
}

void kb_install()
{
	irq_install_handler(1, keyboard_handler);
	inb(0x60);
}
