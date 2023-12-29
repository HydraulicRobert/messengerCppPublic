#ifndef DATENBANKOBJEKT_H
#define DATENBANKOBJEKT_H
#include <iostream>
#include <windows.h>
#include <mysql.h>
class datenbankobjekt
{
    protected:

    private:
        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES* res;
        int absenderID = 0, eingeloggt = 0, auswahl = -1, verzoegerung, qstate, qstate2;
      	std::string name, nameEingeloggt, passwort, passwortEingeloggt, idEingeloggt;
        const char* q;
        const char* q2;
    public:
        datenbankobjekt();
        void ausgabe();
        void einloggen();
        void registrieren();
        void nutzerAusgabe();
        std::string absenderSuchen(int absenderID);
        void nachrichtSenden();
        void nachrichtLoeschen();
        std::string zeitstempelZuDatum(std::string zeit);
        void nachrichtEmpfangen();
        void setConn(MYSQL* conn);
        MYSQL* getConn();
        void setRow(MYSQL_ROW row);
        MYSQL_ROW getRow();
        void setRes(MYSQL_RES* res);
        int getAbsenderID();
        void setAbsenderID(int absenderID);
        int getEingeloggt();
        void setEingeloggt(int eingeloggt);
        int getAuswahl();
        void setAuswahl(int auswahl);
        int getVerzoegerung();
        void setVerzoegerung(int verzoegerung);
        int getQstate();
        void setQstate(int qstate);
        std::string getName();
        void setName(std::string name);
        std::string getNameEingeloggt();
        void setNameEingeloggt(std::string nameEingeloggt);
        std::string getPasswort();
        void setPasswort(std::string passwort);
        std::string getPasswortEingeloggt();
        void setPasswortEingeloggt(std::string passwortEingeloggt);
        std::string getIdEingeloggt();
        void setIdEingeloggt(std::string idEingeloggt);

};

#endif // DATENBANKOBJEKT_H
