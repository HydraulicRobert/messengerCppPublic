#ifndef KOMMANDOBRUECKE_H_INCLUDED
#define KOMMANDOBRUECKE_H_INCLUDED

class kommandobruecke{
    protected:
        int eingabe;
    private:
    public:
        kommandobruecke(const char* host, const char* nutzername, const char* passwort, const char* tabelle, unsigned int port, const char* unix_socket, unsigned long flags, const int verzoegerung);
        void funktion(const char* host, const char* nutzername, const char* passwort, const char* tabelle, unsigned int port, const char* unix_socket, unsigned long flags, const int verzoegerung);
};

#endif // KOMMANDOBRUECKE_H_INCLUDED
