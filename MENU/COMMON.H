enum KEYPRESS
{
     KEY_UP,
     KEY_DOWN,
     KEY_ENTER,
     KEY_ESC,
     KEY_OTHER
};

short KeyboardRead();
void Fill(char ch);
void Box(short left, short top, short right, short bottom);