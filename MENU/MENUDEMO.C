#include <stddef.h>
#include <conio.h>
#include "menu.h"

#define MAX_OPTS	4
#define MAX_OPTS_2	2

void SubMenu1();

MenuItemRec items[MAX_OPTS] = {
     {"Submenu 1", "This is option 1", &SubMenu1},
     {"Option 2", "This is option 2", NULL},
     {"Option 3", "This is option 3", NULL},
     {"Exit    ", "Exit menu demo", NULL}
};

MenuItemRec items2[MAX_OPTS_2] = {
     {"Suboption 1", "This is option 1", NULL},
     {"Suboption 2", "This is option 2", NULL}
};

MenuPtr CreateMenu()
{
     int i;

     MenuPtr myMenu = MenuInit(30, 10, MAX_OPTS);

     MenuColorRec colorNormal = {WHITE, BLUE};
     MenuColorRec colorSelect = {WHITE, RED};
     MenuColor(myMenu, colorNormal, colorSelect);

     for (i=0;i<MAX_OPTS;i++)
	MenuAddItem(myMenu, items[i]);

     return myMenu;
}

MenuPtr CreateSubmenu()
{
     int i;

     MenuPtr myMenu = MenuInit(50, 10, MAX_OPTS_2);

     MenuColorRec colorNormal = {WHITE, BLUE};
     MenuColorRec colorSelect = {WHITE, RED};
     MenuColor(myMenu, colorNormal, colorSelect);

     for (i=0;i<MAX_OPTS_2;i++)
	MenuAddItem(myMenu, items2[i]);

     return myMenu;
}

void SubMenu1()
{
     MenuPtr menu2 = CreateSubmenu();

     short exit = 0;
     MenuPrint(menu2);

     while (!exit)
     {
	     short select = MenuRead(menu2);
	     switch(select)
	     {
		case -1:exit=1;
		   break;
		default:
		   textbackground(BLUE);
		   gotoxy(1,23);
		   cprintf("You selected %d option", select+10);
	     }
     }

     MenuHide(menu2);
     MenuDispose(menu2);
}

void main(void)
{
     MenuPtr menu;
     short exit = 0;

     menu = CreateMenu();

     textbackground(BLUE);
     clrscr();
     Fill(176);
     MenuPrint(menu);

     while (!exit)
     {
	     short select = MenuRead(menu);
	     switch(select)
	     {
		case -1:
		case 3: exit=1;
		   break;
		default:
		   textbackground(BLUE);
		   gotoxy(1,23);
		   cprintf("You selected %d option", select);
	     }
     }

     MenuDispose(menu);
}