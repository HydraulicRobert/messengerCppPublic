#include "kommandobruecke.h"
kommandobruecke::kommandobruecke(const char* host, const char* nutzername, const char* passwort, const char* tabelle, unsigned int port, const char* unix_socket, unsigned long flags, const int verzoegerung)
{
    funktion(host, nutzername, passwort, tabelle, port, unix_socket, flags, verzoegerung);
}
void kommandobruecke::funktion(const char* host, const char* nutzername, const char* passwort, const char* tabelle, unsigned int port, const char* unix_socket, unsigned long flags, const int verzoegerung)
{
    funktionen werkzeuge;
    datenbankobjekt datei;
    datei.setVerzoegerung(verzoegerung);
    datei.setAuswahl(-1);
    datei.setConn(mysql_init(0));
    datei.setConn(mysql_real_connect(datei.getConn(), host, nutzername, passwort, tabelle, port, unix_socket, flags));
    if(datei.getConn())
    {
        while(datei.getAuswahl() != 0)
        {
            if(datei.getEingeloggt() == 0)
            {
                werkzeuge.ausgabe(werkzeuge.getMenueZahl(), datei.getVerzoegerung(), 0);
                werkzeuge.ausgabe(") Einloggen", datei.getVerzoegerung(), 1);
                werkzeuge.ausgabe(werkzeuge.getMenueZahl(), datei.getVerzoegerung(), 0);
                werkzeuge.ausgabe(") Registrieren", datei.getVerzoegerung(), 1);
            }
            if(datei.getEingeloggt() > 0)
            {
                werkzeuge.ausgabe(werkzeuge.getMenueZahl(), datei.getVerzoegerung(), 0);
                werkzeuge.ausgabe(") Nutzerliste ausgeben", datei.getVerzoegerung(), 1);
                werkzeuge.ausgabe(werkzeuge.getMenueZahl(), datei.getVerzoegerung(), 0);
                werkzeuge.ausgabe(") Nachrichten ausgeben", datei.getVerzoegerung(), 1);
                werkzeuge.ausgabe(werkzeuge.getMenueZahl(), datei.getVerzoegerung(), 0);
                werkzeuge.ausgabe(") Nachricht verschicken", datei.getVerzoegerung(), 1);
                werkzeuge.ausgabe(werkzeuge.getMenueZahl(), datei.getVerzoegerung(), 0);
                werkzeuge.ausgabe(") Nachrichten loeschen", datei.getVerzoegerung(), 1);
            }
            werkzeuge.ausgabe(werkzeuge.getMenueZahl(), datei.getVerzoegerung(), 0);
            werkzeuge.ausgabe(") Auswahl treffen: ", datei.getVerzoegerung(), 0);
            werkzeuge.setMenueZahl(1);
            std::cin >>eingabe;
            datei.setAuswahl(eingabe);
            werkzeuge.cls();
            switch(datei.getAuswahl())
            {
                case 1:
                    if(datei.getEingeloggt() == 0)
                    {
                        datei.einloggen();
                    }else if(datei.getEingeloggt() == 1)
                    {
                        datei.nutzerAusgabe();
                    }
                    break;
                case 2:
                    if(datei.getEingeloggt() == 0)
                    {
                        datei.registrieren();
                    }else if(datei.getEingeloggt() == 1)
                    {
                        datei.nachrichtEmpfangen();
                    }
                    break;
                case 3:
                    if(datei.getEingeloggt() == 1)
                    {
                        datei.nachrichtSenden();
                    }
                    break;
                case 4:
                    if(datei.getEingeloggt() == 1)
                    {
                        datei.nachrichtLoeschen();
                    }
                    break;
            }
        }
    }else
    {
        cout << "Abfrageproblem: " << mysql_error(datei.getConn()) <<endl;
    }
}
