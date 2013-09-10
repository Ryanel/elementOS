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
///Prints a debug message
void mem_debug(char* message)
{
	#ifdef ENABLE_DEBUG
	printf("[MEM]:%s\n",message);
	#endif
}

uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys)
{
	if (align == 1 && (placement_address & 0xFFFFF000))
	{
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000;
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
/**
 * Standards complient malloc
**/
 
uint32_t kmalloc(uint32_t sz)
{
	return kmalloc_int(sz,0,0);
}
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys)
{
	return kmalloc_int(sz,0,phys);
}

uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys)
{
	return kmalloc_int(sz,1,phys);
}

uint32_t kmalloc_a(uint32_t sz)
{
	return kmalloc_int(sz,1,0);
}
