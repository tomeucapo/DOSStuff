#ifndef __MENU
#define __MENU

typedef struct MenuColor
{
	short text, background;
} MenuColorRec;

struct MenuItem
{
	char optionText[20];
	char msgStatus[60];
	void (*action)();
};

typedef struct MenuItem MenuItemRec, *MenuItemPtr;

struct Menu
{
	MenuItemPtr items, firstItem;

	short x, y;
	short numItems, maxItems;
	short selectedItem;

	MenuColorRec colorNormal;
	MenuColorRec colorSelected;

	char back[4096];
};

typedef struct Menu MenuRec, *MenuPtr;

enum DIRECTIONS
{
     GO_UP,
     GO_DOWN
};

MenuPtr MenuInit(short x, short y, short maxItems);
void MenuAddItem(MenuPtr menu, MenuItemRec item);
void MenuPrint(MenuPtr menu);
void MenuColor(MenuPtr menu, MenuColorRec normal, MenuColorRec select);
short MenuRead(MenuPtr menu);
void MenuHide(MenuPtr menu);
void MenuDispose(MenuPtr menu);

#endif