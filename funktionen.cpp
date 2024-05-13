#include "funktionen.h"
funktionen::funktionen()
{
};

//windows exklusiver cls. von http://www.cplusplus.com/forum/beginner/73214/. grob verstanden wofuer alles steht
void funktionen::cls()
{
  DWORD n;
  DWORD size;
  COORD coord = {0};
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
  GetConsoleScreenBufferInfo ( h, &csbi );
  size = csbi.dwSize.X * csbi.dwSize.Y;
  FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
  GetConsoleScreenBufferInfo ( h, &csbi );
  FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );
  SetConsoleCursorPosition ( h, coord );
}
void funktionen::sleep(int millisekunden)
{
    Sleep(millisekunden);
}
void funktionen::ausgabe(std::string ausgabeWort1, int ausgabeZaehler, bool zeilenumbruch)
{
    std::string& ausgabeWort = ausgabeWort1;
    for(int i = 0; i != ausgabeWort.length(); i++)
    {
        std::cout<<ausgabeWort[i];
        Sleep(ausgabeZaehler);
    }
    if(zeilenumbruch == true)
    {
        cout<<"\n";
    }
}
std::string funktionen::getMenueZahl()
{
    return std::to_string(menueZahl++);
}
void funktionen::setMenueZahl(int menueZahl)
{
    this->menueZahl = menueZahl;
}
