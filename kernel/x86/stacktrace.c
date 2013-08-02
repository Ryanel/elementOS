#include <stdio.h>
#include <types.h>
#include <elf.h>

extern multiboot_header_t *mb;
void print_stack_trace (unsigned int MaxFrames)
{
  unsigned int * ebp = &MaxFrames - 2;
  printf("Stack trace:\n");
  for(unsigned int frame = 0; frame < MaxFrames; ++frame)
  {
      unsigned int eip = ebp[1];
      if(eip == 0)
          // No caller on stack
          break;
      // Unwind to previous stack frame
      ebp = (unsigned int *)(ebp[0]);
      unsigned int * arguments = &ebp[2];
      printf("[0x%n]: Frame %d\n",eip,frame);
  }
}
