/*
memory.c
--------
Manages all aspects of the memory.
*/

//Includes
#include <types.h>
#include <stdio.h>

//Self
#include <memory.h>

uint32_t placement_address = 0;

void mem_debug(char* message)
{
	#ifdef ENABLE_DEBUG
	printf("[MEM]:%s\n",message);
	#endif
}

void kmalloc(uint32_t sz, int align, uint32_t *phys)
{
	if (align == 1 && (placement_address & 0xFFFFF000))
	{
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000
	}
	if (phys)
	{
		*phys = placement_address;
	}

	//Do the actuall allocation
	uint32_t tmp = placement_address;
	placement_address += sz;
	return tmp;
}
