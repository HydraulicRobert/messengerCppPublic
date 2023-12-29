#ifndef FUNKTIONEN_H
#define FUNKTIONEN_H
#include <string.h>

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

