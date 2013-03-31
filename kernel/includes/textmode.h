#ifndef VIDEO_TEXTMODE
#define VIDEO_TEXTMODE
void tm_putch(char c);
void tm_clear();
void tm_print(const char *c);
extern char cursor_x;
extern char cursor_y;
#endif
