#include <stddef.h>
#include <conio.h>
#include "menu.h"
#include "common.h"

MenuPtr MenuInit(short x, short y, short maxItems)
{
     MenuPtr menu;

     menu = (MenuPtr) malloc(sizeof(MenuRec)+1);
     menu->x = x;
     menu->y = y;
     menu->numItems = 0;
     menu->selectedItem = 0;
     menu->maxItems = maxItems;

     menu->colorNormal.text = WHITE;
     menu->colorNormal.background = BLACK;
     menu->colorSelected.text = BLACK;
     menu->colorSelected.background = WHITE;

     menu->items = (MenuItemPtr) malloc((sizeof(MenuItemRec)+1)*maxItems);
     menu->firstItem = menu->items;

     return menu;
}

void MenuAddItem(MenuPtr menu, MenuItemRec item)
{
     if (menu->numItems >= menu->maxItems)
	 return;

     *menu->items++ = item;
     menu->numItems++;
}

void MenuPrint(MenuPtr menu)
{
     MenuItemPtr it = menu->firstItem;
     int i;

     gettext(menu->x, menu->y, menu->x+21, menu->y+menu->maxItems+1, menu->back);

     Box(menu->x, menu->y, menu->x+21, menu->y+menu->maxItems+1);
     textcolor(menu->colorNormal.text);
     textbackground(menu->colorNormal.background);

     for(i=0;i<menu->numItems;i++)
     {
	  gotoxy(menu->x, menu->y+i);
	  if (it->action != NULL)
	     cprintf("%-19s>", it->optionText);
	  else
	     cprintf("%-20s", it->optionText);

	  it++;
     }
}

void MenuHide(MenuPtr menu)
{
     puttext(menu->x, menu->y, menu->x+21, menu->y+menu->maxItems+1, menu->back);
}

void MenuNavigate(MenuPtr menu, short direction)
{
     if (direction == GO_DOWN)
     {
	menu->selectedItem++;
	if (menu->selectedItem > menu->numItems-1)
	    menu->selectedItem = 0;
     } else if (direction == GO_UP) {
	menu->selectedItem--;
	if (menu->selectedItem < 0)
	    menu->selectedItem = menu->numItems-1;
     }
}

void MenuSelectItem(MenuPtr menu, short select)
{
     MenuItemPtr selOpt = (menu->firstItem + menu->selectedItem);

     if (select)
     {
	textcolor(menu->colorSelected.text);
	textbackground(menu->colorSelected.background);
     } else {
	textcolor(menu->colorNormal.text);
	textbackground(menu->colorNormal.background);
     }

     gotoxy(menu->x, menu->y+menu->selectedItem);
     if(selOpt->action != NULL)
	cprintf("%-19s>", selOpt->optionText);
     else
	cprintf("%-20s", selOpt->optionText);
}

void MenuShowMessage(MenuPtr menu)
{
     MenuItemPtr selOpt = (menu->firstItem + menu->selectedItem);

     textbackground(WHITE);
     textcolor(BLACK);
     gotoxy(1,25);cprintf("%-79s", selOpt->msgStatus);
}

void MenuColor(MenuPtr menu, MenuColorRec normal, MenuColorRec select)
{
     menu->colorNormal = normal;
     menu->colorSelected = select;
}

short MenuExecuteAction(MenuPtr menu)
{
	MenuItemPtr selOpt = (menu->firstItem + menu->selectedItem);
	if (selOpt->action != NULL)
	{
	   (*selOpt->action)();
	   return 1;
	}
	return 0;
}

short MenuRead(MenuPtr menu)
{
    short exit = 0;
    short selectedItem = -1;
    while (!exit)
    {
	    MenuShowMessage(menu);
	    MenuSelectItem(menu, 1);
	    switch(KeyboardRead())
	    {
		case KEY_UP:
			MenuSelectItem(menu, 0);
			MenuNavigate(menu, GO_UP);
			break;
		case KEY_DOWN:
			MenuSelectItem(menu, 0);
			MenuNavigate(menu, GO_DOWN);
			break;
		case KEY_ENTER:
			if (!MenuExecuteAction(menu))
			{
				exit = 1;
				selectedItem = menu->selectedItem;
			} else {
				break;
			}
		case KEY_ESC:
			exit = 1;
	    }
    }
    return selectedItem;
}

void MenuDispose(MenuPtr menu)
{
     free(menu);
}
