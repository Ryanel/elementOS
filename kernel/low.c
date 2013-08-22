#include <types.h>
#include <low.h>
inline void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}	

inline uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

inline void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}
void memset_64(void *dest, uint8 sval, uint64 count)
{
  uint64 val = (sval & 0xFF); // create a 64-bit version of 'sval'
  val |= ((val << 8) & 0xFF00);
  val |= ((val << 16) & 0xFFFF0000);
  val |= ((val << 32) & 0xFFFFFFFF00000000);
    
  if(!count){return;} // nothing to copy?
  while(count >= 8){ *(uint64*)dest = (uint64)val; memset_transfers_64++; dest += 8; count -= 8; }
  while(count >= 4){ *(uint32*)dest = (uint32)val; memset_transfers_32++; dest += 4; count -= 4; }
  while(count >= 2){ *(uint16*)dest = (uint16)val; memset_transfers_16++; dest += 2; count -= 2; }
  while(count >= 1){ *(uint8*)dest = (uint8)val; memset_transfers_8++; dest += 1; count -= 1; }
  return; 
}
void memcpy_64(void *dest, void *src, uint64 count)
{
  if(!count){return;} // nothing to copy?
  while(count >= 8){ *(uint64*)dest = *(uint64*)src; memcpy_transfers_64++; dest += 8; src += 8; count -= 8; }
  while(count >= 4){ *(uint32*)dest = *(uint32*)src; memcpy_transfers_32++; dest += 4; src += 4; count -= 4; }
  while(count >= 2){ *(uint16*)dest = *(uint16*)src; memcpy_transfers_16++; dest += 2; src += 2; count -= 2; }
  while(count >= 1){ *(uint8*)dest = *(uint8*)src; memcpy_transfers_8++; dest += 1; src += 1; count -= 1; }
  return;
}
inline int strcmp (char *str1, char *str2)
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
