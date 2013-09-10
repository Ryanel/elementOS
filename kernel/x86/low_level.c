#include <types.h>
#include <low.h>
///Writes value to port.
inline void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}	
//Reads the data from port
inline uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

void *memset(void *dest,int val,size_t n) {
  uint32_t num_dwords = n/4;
  uint32_t num_bytes = n%4;
  uint32_t *dest32 = (uint32_t*)dest;
  uint8_t *dest8 = ((uint8_t*)dest)+num_dwords*4;
  uint8_t val8 = (uint8_t)val;
  uint32_t val32 = val|(val<<8)|(val<<16)|(val<<24);
  uint32_t i;

  for (i=0;i<num_dwords;i++) {
    dest32[i] = val32;
  }
  for (i=0;i<num_bytes;i++) {
    dest8[i] = val8;
  }
  return dest;
}
void *memcpy(void *dest,const void *src,size_t n) {
  uint32_t num_dwords = n/4;
  uint32_t num_bytes = n%4;
  uint32_t *dest32 = (uint32_t*)dest;
  uint32_t *src32 = (uint32_t*)src;
  uint8_t *dest8 = ((uint8_t*)dest)+num_dwords*4;
  uint8_t *src8 = ((uint8_t*)src)+num_dwords*4;
  uint32_t i;

  for (i=0;i<num_dwords;i++) {
    dest32[i] = src32[i];
  }
  for (i=0;i<num_bytes;i++) {
    dest8[i] = src8[i];
  }
  return dest;
}
inline int strcmp (const char *str1,const char *str2)
{
    while (*str1 != 0 && *str2 != 0)
    {
        if (*str1 != *str2)
        {
            return str1 - str2;
        }

        str1++; str2++;
    }

    return 0;
}
