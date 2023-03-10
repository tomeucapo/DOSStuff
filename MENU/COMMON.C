#include <conio.h>
#include "common.h"

short KeyboardRead()
{
	char key = getch();

	if (key == 0x00)
	{
	    char next = getch();
	    if (next == 0x48)
		return KEY_UP;
	    if (next == 0x50)
		return KEY_DOWN;
	}

	if (key == 0x0d)
	    return KEY_ENTER;

	if (key == 0x1b)
	    return KEY_ESC;

	return KEY_OTHER;
}

void Fill(char ch)
{
     short x,y;
     for (x=0;x<80;x++)
     {
	for (y=0;y<24;y++)
	{
		putch(ch);
	}
     }
}

void Box(short left, short top, short right, short bottom)
{
     short x=left,y=top;

     for (y=top;y<bottom;y++)
     {
	  gotoxy(x, y);putch(179);
	  gotoxy(x + right, y);putch(179);
     }
}
