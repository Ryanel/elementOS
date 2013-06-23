/*
Paging.c (x86)
Based off (more really just copied and fixed) the tutorial http://wiki.osdev.org/Setting_Up_Paging
I will promise that I will re-write these to make them better after I get everything somewhat stable. It makes crashes that more fun, anyway.
*/

extern end;

unsigned int page_aligned_end;
unsigned int *page_directory;
unsigned int *first_page_table;
void setupPaging()
{
	page_aligned_end = ((unsigned int)((unsigned int*)end) & 0xFFFFF000) + 0x1000;
	*page_directory = (unsigned int*)page_aligned_end;
	*first_page_table = page_directory + 0x1000;
	unsigned i = 0;
	for(i = 0; i < 1024; i++)
	{
		//attribute: supervisor level, read/write, not present.
		page_directory[i] = 0 | 2; 
	}

	unsigned int address = 0; 
	 
	//we will fill all 1024 entries, mapping 4 megabytes
	for(i = 0; i < 1024; i++)
	{
	    first_page_table[i] = address | 3; // attributes: supervisor level, read/write, present.
	    address = address + 4096; //advance the address to the next page boundary
	}

	page_directory[0] = first_page_table; 

	page_directory[0] |= 3;// attributes: supervisor level, read/write, present

	asm volatile("mov %0, %%cr3":: "b"(page_directory));
	unsigned int cr0;
	asm volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "b"(cr0));
}