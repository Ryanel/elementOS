#ifndef VIDEO_TEXTMODE
#define VIDEO_TEXTMODE
#include <types.h>
void tm_putch(char c);
void tm_clear();
void tm_print(const char *c);
void log(const char *type,uint8_t color,const char *c);
extern char cursor_x;
extern char cursor_y;
#endif
