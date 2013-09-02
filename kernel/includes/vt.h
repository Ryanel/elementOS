#ifndef VT_H
#define VT_H
///Defines the properties of a virtual terminal.
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
/// Initalises a terminal
int tty_create(int no);
/// Prints one character to TTYno
int tty_putch(int no, char c);
/// Sets the position relative to the root window the VT is drawn.
void tty_setscrnpos(int no,int x, int y);
/// Sets the resolution of the VT
void tty_setdim(int no, int width, int height);
/// Prints a string to a VT
void tty_print(int no, const char *c);
//void tty_puts(int no, char *s);
#endif
