#include <iostream>
#include "datenbankobjekt.h"
#include "funktionen.h"
#include <ctime>
#include <conio.h>

using namespace std;
funktionen werkzeugeDatenobjekt;
datenbankobjekt::datenbankobjekt()
{
}
void datenbankobjekt::einloggen()
{
        werkzeugeDatenobjekt.ausgabe("Name: ", verzoegerung, 1);
        cin >> name;
        werkzeugeDatenobjekt.cls();
        werkzeugeDatenobjekt.ausgabe("Passwort: ", verzoegerung, 1);
        cin >> passwort;
        werkzeugeDatenobjekt.cls();
        string query = "select * from nutzer where Name = '"+name+"' and Passwort = '"+passwort+"'";

        const char* q = query.c_str();

        qstate = mysql_query(conn, q);

        if(!qstate)
        {
            res = mysql_store_result(conn);

            while(row=mysql_fetch_row(res))
            {
                nameEingeloggt = row[0];
                passwortEingeloggt = row[1];
                idEingeloggt = row[2];
                werkzeugeDatenobjekt.ausgabe("Willkommen zurueck, "+nameEingeloggt, verzoegerung, 1);
                eingeloggt++;
            }
        }else
        {
            std::cout << "Abfrageproblem: " <<mysql_error(conn)<<endl;
        }
}
void datenbankobjekt::registrieren()
{
    werkzeugeDatenobjekt.ausgabe("Registrieren", verzoegerung, 1);
    werkzeugeDatenobjekt.ausgabe("Name: ", verzoegerung, 1);
    std::cin >> name;
    werkzeugeDatenobjekt.cls();
    werkzeugeDatenobjekt.ausgabe("Passwort", verzoegerung, 1);
    std::cin >> passwort;
    werkzeugeDatenobjekt.cls();
    std::string query = "insert into nutzer(Name, Passwort) values('"+name+"', '"+passwort+"')";
    std::string pruefeDoppeltenLogin = "SELECT Name FROM nutzer WHERE Name = '"+name+"'";
    q = pruefeDoppeltenLogin.c_str();
    qstate = mysql_query(conn, q);
    int doppenPruefZahl = 0;
    if(!qstate)
    {
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
            {
                if(row[0] == name)
                {
                    werkzeugeDatenobjekt.ausgabe("benutzer existiert bereits. ",getVerzoegerung(), 1);
                    doppenPruefZahl++;
                }
            }
            if(doppenPruefZahl == 0)
            {
                q2 = query.c_str();
                qstate2 = mysql_query(conn, q2);
                if(!qstate)
                {
                    res = mysql_store_result(conn);
                }
                werkzeugeDatenobjekt.ausgabe("erfolgreich registriert!",getVerzoegerung(), 1);
            }
        doppenPruefZahl = 0;
    }
}

void datenbankobjekt::nutzerAusgabe()
{
    string query = "SELECT Name, NutzerID FROM nutzer", pausierer;
    const char* q = query.c_str();

    qstate = mysql_query(conn, q);
    if(!qstate)
    {
        res = mysql_store_result(conn);
        while(row = mysql_fetch_row(res))
        {
            werkzeugeDatenobjekt.ausgabe("Id: "+std::string(row[1]), verzoegerung, 0);
            werkzeugeDatenobjekt.ausgabe("; Name: "+std::string(row[0]), verzoegerung, 1);
        }
    }
    std::cin >> pausierer;
    werkzeugeDatenobjekt.cls();
}

std::string datenbankobjekt::absenderSuchen(int absenderID){
    string absenderQuery = "SELECT Name FROM Nutzer WHERE Nutzer.NutzerID = '"+std::to_string(absenderID)+"'", absender, pausierer;
    const char* q2 = absenderQuery.c_str();
    MYSQL_ROW row2;
    MYSQL_RES* res2;
    int qstate2;
    qstate2 = mysql_query(conn, q2);
    if(!qstate2)
    {
        res2 = mysql_store_result(conn);
        while(row2 = mysql_fetch_row(res2))
        {
            absender = row2[0];
        }
    }
    return absender;
}

void datenbankobjekt::nachrichtSenden()
{
    int empfaengerID;
    std::string nachricht = " ", pausierer;
    std::time_t t = std::time(0);
    werkzeugeDatenobjekt.ausgabe("An wem? ", verzoegerung, 1);
    std::cin >> empfaengerID;
    werkzeugeDatenobjekt.ausgabe("Nachricht: ",verzoegerung, 1);
    std::cin.ignore();
    getline(std::cin, nachricht, '\n');
    std::string query = "insert into empfangenenachricht(AbsenderID, EmpfaengerID, Nachricht, Zeit) values('"+idEingeloggt+"','"+std::to_string(empfaengerID)+"','"+nachricht+"','"+std::to_string(t)+"')";

        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

        if(!qstate)
        {
            werkzeugeDatenobjekt.cls();
            werkzeugeDatenobjekt.ausgabe("Nachricht erfolgreich abgeschickt!", verzoegerung, 1);
        }else
        {
            werkzeugeDatenobjekt.cls();
            werkzeugeDatenobjekt.ausgabe("\nAbfrageproblem: "+std::string(mysql_error(conn)),verzoegerung, 1);
        }
    std::cin >> pausierer;
    werkzeugeDatenobjekt.cls();
}

void datenbankobjekt::nachrichtLoeschen()
{
    char jep;
    std::string pausierer;
    werkzeugeDatenobjekt.ausgabe("\nSicher? (y/n) ", verzoegerung, 1);
    std::cin >> jep;
    if(jep == 'y')
    {
        std::string query = "DELETE FROM empfangenenachricht WHERE EmpfaengerID = '"+idEingeloggt+"'";

        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

        if(!qstate){
            werkzeugeDatenobjekt.cls();
            werkzeugeDatenobjekt.ausgabe("Nachrichten erfolgreich geloescht!", verzoegerung, 1);
        }else{
            werkzeugeDatenobjekt.cls();
            werkzeugeDatenobjekt.ausgabe("Abfrageproblem "+std::string(mysql_error(conn)), verzoegerung, 1);
        }
    }
    std::cin >> pausierer;
    werkzeugeDatenobjekt.cls();
}
std::string datenbankobjekt::zeitstempelZuDatum(std::string zeit)
{
            time_t zeit2 = std::stoi(zeit);
            struct tm * dt;
            char buffer [30];
            dt = localtime(&zeit2);
            strftime(buffer, sizeof(buffer), "Am %d.%m.%Y um %H:%M:%S Uhr", dt);
            return std::string(buffer);
}

void datenbankobjekt::nachrichtEmpfangen()
{
    int qstate2;
    std::string query = "SELECT * FROM EmpfangeneNachricht WHERE EmpfangeneNachricht.EmpfaengerID = '"+idEingeloggt+"'";

    std::string absender, pausierer;
    const char* q = query.c_str();

    qstate = mysql_query(conn, q);
    if(!qstate)
        {
        res = mysql_store_result(conn);
        while(row = mysql_fetch_row(res)){
            absenderID = std::stoi(row[0]);
            absender = absenderSuchen(absenderID);
            werkzeugeDatenobjekt.ausgabe(zeitstempelZuDatum(std::string(row[2]))+" Von "+absender, verzoegerung, 1);
            werkzeugeDatenobjekt.ausgabe(std::string(row[3])+"\n", verzoegerung, 1);
        }
    }
    std::cin >> pausierer;
    werkzeugeDatenobjekt.cls();
}
void datenbankobjekt::setConn(MYSQL* conn)
{
    this->conn = conn;
}

MYSQL* datenbankobjekt::getConn()
{
    return conn;
}

void datenbankobjekt::setRow(MYSQL_ROW row)
{
    this->row = row;
}

MYSQL_ROW datenbankobjekt::getRow()
{
    return row;
}

void datenbankobjekt::setRes(MYSQL_RES* res)
{
    this->res = res;
}

int datenbankobjekt::getAbsenderID()
{
    return absenderID;
}

void datenbankobjekt::setAbsenderID(int absenderID)
{
    this->absenderID = absenderID;
}

int datenbankobjekt::getEingeloggt()
{
    return eingeloggt;
}

void datenbankobjekt::setEingeloggt(int eingeloggt)
{
    this->eingeloggt = eingeloggt;
}

int datenbankobjekt::getAuswahl()
{
    return auswahl;
}

void datenbankobjekt::setAuswahl(int auswahl)
{
    this->auswahl = auswahl;
}

int datenbankobjekt::getVerzoegerung()
{
    return verzoegerung;
}

void datenbankobjekt::setVerzoegerung(int verzoegerung)
{
    this->verzoegerung = verzoegerung;
}

int datenbankobjekt::getQstate()
{
    return qstate;
}

void datenbankobjekt::setQstate(int qstate)
{
    this->qstate = qstate;
}

std::string datenbankobjekt::getName()
{
    return name;
}

void datenbankobjekt::setName(std::string name)
{
    this->name = name;
}

std::string datenbankobjekt::getNameEingeloggt()
{
    return nameEingeloggt;
}

void datenbankobjekt::setNameEingeloggt(std::string nameEingeloggt)
{
    this->nameEingeloggt = nameEingeloggt;
}

std::string datenbankobjekt::getPasswort()
{
    return passwort;
}

void datenbankobjekt::setPasswort(std::string passwort)
{
    this->passwort = passwort;
}

string datenbankobjekt::getPasswortEingeloggt()
{
    return passwortEingeloggt;
}

void datenbankobjekt::setPasswortEingeloggt(std::string passwortEingeloggt)
{
    this->passwortEingeloggt = passwortEingeloggt;
}

string datenbankobjekt::getIdEingeloggt()
{
    return idEingeloggt;
}

void datenbankobjekt::setIdEingeloggt(std::string idEingeloggt)
{
    this->idEingeloggt = idEingeloggt;
}
