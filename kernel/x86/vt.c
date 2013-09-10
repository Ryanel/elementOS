#include <vt.h>
#include <textmode.h>
/*
vt.c
------
Creates virtual terminals
*/
#define MAX_TTYS 4 //Subtract one for array's starting by 0

//End Configuration
vterm_t term[MAX_TTYS];

//Returns no if sucessfull, otherwise returns of type ERR
int tty_create(int no)
{
	if(no>=MAX_TTYS)
	{
		return 6; //TODO: Implement ERR
	}
	else
	{
		term[no].no=no; //Set console number to it. Also NONONO
		term[no].width=30;
		term[no].height=11;
		return 0;
	}
}
//Prints a character to tty no, with character 
int tty_putch(int no, char c)
{
	term[no].buffer[term[no].x]=c;
	term[no].x=term[no].x+1;
	return 0;
}
//Prints a string to tty no
void tty_print(int no, const char *c)
{
   int i = 0;
   while (c[i])
   {
       tty_putch(no,c[i++]);
   }
}
void tty_setscrnpos(int no,int x, int y)
{
	term[no].x_pos=x;
	term[no].y_pos=y;
}
void tty_render(int no)
{
	render_vt(term[no]);
}
void tty_setdim(int no, int width, int height)
{
	term[no].width=width;
	term[no].height=height;
}
