#include <types.h>
#include <low.h>
#include <textmode.h>
#include <vt.h>
uint16_t *video_memory=(uint16_t*)0xB8000;
char cursor_x=0;
char cursor_y=1;
uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
void move_cursor()
{
	// The screen is 80 characters wide...
	uint16_t cursorLocation = cursor_y * 80 + cursor_x;
	outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
	outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
	outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
	outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}
static void scroll()
{
	// Get a space character with the default colour attributes.
	uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

	// Row 25 is the end, this means we need to scroll up
	if(cursor_y >= 25)
	{
	   // Move the current text chunk that makes up the screen
	   // back in the buffer by a line
	   int i;
	   for (i = 1*80; i < 24*80; i++)
	   {
		   video_memory[i] = video_memory[i+80];
	   }

	   // The last line should now be blank. Do this by writing
	   // 80 spaces to it.
	   for (i = 24*80; i < 25*80; i++)
	   {
		   video_memory[i] = blank;
	   }
	   // The cursor should now be on the last line.
	   cursor_y = 24;
	}
}
void tm_putch(char c)
{
// The background colour is black (0), the foreground is white (15).
   // The attribute byte is made up of two nibbles - the lower being the
   // foreground colour, and the upper the background colour.
   // The attribute byte is the top 8 bits of the word we have to send to the
   // VGA board.
   uint16_t attribute = attributeByte << 8;
   uint16_t *location;

   // Handle a backspace, by moving the cursor back one space
   if (c == 0x08 && cursor_x)
   {
       cursor_x--;
   }

   // Handle a tab by increasing the cursor's X, but only to a point
   // where it is divisible by 8.
   else if (c == 0x09)
   {
       cursor_x = (cursor_x+8) & ~(8-1);
   }

   // Handle carriage return
	else if (c == '\r')
	{
	   cursor_x = 0;
	}

	// Handle newline by moving cursor back to left and increasing the row
	else if (c == '\n')
	{
	   cursor_x = 0;
	   cursor_y++;
	}
	// Handle any other printable character.
	else if(c >= ' ')
	{
		location = video_memory + (cursor_y*80 + cursor_x);
		*location = c | attribute;
		cursor_x++;
	}

	// Check if we need to insert a new line because we have reached the end
	// of the screen.
	if (cursor_x >= 80)
	{
		cursor_x = 0;
		cursor_y ++;
	}

	// Scroll the screen if needed.
	scroll();
	// Move the hardware cursor.
	move_cursor();

}
void tm_putch_at(char c,int x,int y)
{
// The background colour is black (0), the foreground is white (15).
   // The attribute byte is made up of two nibbles - the lower being the
   // foreground colour, and the upper the background colour.
   // The attribute byte is the top 8 bits of the word we have to send to the
   // VGA board.
   uint16_t attribute = attributeByte << 8;
   uint16_t *location;
   int o_loc_x=cursor_x;
   int o_loc_y=cursor_y;
   if(x!=255)
   	cursor_x=x;
   if(y!=255)
   	cursor_y=y;
   // Handle a backspace, by moving the cursor back one space
   if (c == 0x08 && cursor_x)
   {
       cursor_x--;
   }

   // Handle a tab by increasing the cursor's X, but only to a point
   // where it is divisible by 8.
   else if (c == 0x09)
   {
       cursor_x = (cursor_x+8) & ~(8-1);
   }

   // Handle carriage return
	else if (c == '\r')
	{
	   cursor_x = 0;
	}

	// Handle newline by moving cursor back to left and increasing the row
	else if (c == '\n')
	{
	   cursor_x = 0;
	   cursor_y++;
	}
	// Handle any other printable character.
	else if(c >= ' ')
	{
		location = video_memory + (cursor_y*80 + cursor_x);
		*location = c | attribute;
		cursor_x++;
	}

	// Check if we need to insert a new line because we have reached the end
	// of the screen.
	if (cursor_x >= 80)
	{
		cursor_x = 0;
		cursor_y ++;
	}

	// Scroll the screen if needed.
	scroll();
	//
	cursor_x=o_loc_x;
	cursor_y=o_loc_y;
}
void tm_clear()
{
   // Make an attribute byte for the default colours
   uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

   int i;
   for (i = 80*1; i < 80*25; i++)
   {
       video_memory[i] = blank;
   }

   // Move the hardware cursor back to the start.
   cursor_x = 0;
   cursor_y = 1;
   move_cursor();
}
void tm_print(const char *c)
{
   int i = 0;
   while (c[i])
   {
       tm_putch(c[i++]);
   }
}
void tm_print_at(const char *c,int x,int y)
{
	int o_loc_x=cursor_x;
	int o_loc_y=cursor_y;
	if(x<81)
		cursor_x=x;
	if(y<25)
		cursor_y=y;
	int i = 0;
	while (c[i])
	{
	   tm_putch(c[i++]);
	}
	cursor_x=o_loc_x;
	cursor_y=o_loc_y;
}
void tm_setAttribute(uint8_t color)
{
	attributeByte=color;
}
void ksyslog(const char *type,uint8_t color,const char *c)
{
    uint8_t attributeByte_o=attributeByte;
    printf("[%^%s%^]:%s",color,type,attributeByte_o,c);
}

void render_vt(vterm_t term)
{
	int startpos=term.y_pos*80+term.x_pos;
	int done=0;
	int todo=term.width*term.height;
	uint16_t attribute = attributeByte << 8;
	uint16_t *location;
	int drawx, drawy=0;
	drawx=term.x_pos;
	drawy=term.y_pos;
	char c;
	while(done!=todo)
	{
		c=term.buffer[done];
		if (c == 0x08 && (drawx - term.x_pos))
		{
			drawx--;
		}

		// Handle a tab by increasing the cursor's X, but only to a point
		// where it is divisible by 8.
		else if (c == 0x09)
		{
			drawx = (drawx+8) & ~(8-1);
		}

		// Handle carriage return
		else if (c == '\r')
		{
			drawx = term.x_pos;
		}

		// Handle newline by moving cursor back to left and increasing the row
		else if (c == '\n')
		{
			int i=0;
			int max=term.width-(drawx-term.x_pos);
			while(i!=max)
			{
				location = video_memory + (drawy*80 +drawx+i);
				*location = ' ' | attribute;
				i++;
			}
			drawx = term.x_pos;
			
			drawy++;
		}
		// Handle any other printable character.
		else if(c >= ' ')
		{
			location = video_memory + (drawy*80 + drawx);
			*location = c | attribute;
			drawx++;
			
		}
		else
		{
			location = video_memory + (drawy*80 + drawx);
			*location = ' ' | attribute;
			drawx++;
		}
		// Check if we need to insert a new line because we have reached the end
		// of the screen.
		if (drawx >= term.width+term.x_pos)
		{
			drawx = term.x_pos;
			drawy++;
		}
		done++;
	}

}
