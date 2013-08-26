#ifndef COMMON_H
#define COMMON_H
#include <types.h>
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
//void *memset(void *dest, char val, size_t count);
void *memset(void *dest,int val,size_t n);
inline int strcmp (const char *str1,const char *str2);
#endif
