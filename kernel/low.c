#include <types.h>
#include <low.h>
void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}	

uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}
int strcmp (char *str1, char *str2)
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