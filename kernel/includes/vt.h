#ifndef VT_H
#define VT_H
typedef struct {
	int no;
	unsigned char buffer[4096];
	int x;
	int y;
	int x_pos;
	int y_pos;
	int width;
	int height;
	int isActive;
} vterm_t;

int tty_create(int no);
int tty_putch(int no, char c);
void tty_setscrnpos(int no,int x, int y);
void tty_setdim(int no, int width, int height);
void tty_print(int no, const char *c);
//void tty_puts(int no, char *s);
#endif
