#ifndef FUNKTIONEN_H
#define FUNKTIONEN_H
#include <string.h>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <string.h>
using namespace std;
class funktionen
{
    protected:

    private:
        int menueZahl = 1;

    public:
        funktionen();
        void cls();
       	void sleep(int millisekunden);
       	void ausgabe(std::string ausgabeWort1, int ausgabeZaehler, bool zeilenumbruch);
       	std::string getMenueZahl();
        void setMenueZahl(int menueZahl);
};

#endif // FUNKTIONEN_H

