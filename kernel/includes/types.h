#ifndef TYPE_H
#define TYPE_H
typedef char bool;
#define true 1
#define false 0
// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   uint32_t;
typedef          int   sint32_t;
typedef unsigned short uint16_t;
typedef          short sint16_t;
typedef unsigned char  uint8_t;
typedef          char  sint8_t;

#endif