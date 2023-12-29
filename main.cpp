#include <iostream>
#include <windows.h>
#include "kommandobruecke.h"
#include "mysql.h"
#include "main.h"
using namespace std;
int main()
{
    const char* host = "localhost";
    const char* nutzername = "root";
    const char* passwort = "";
    const char* tabelle = "nutzerdaten";
    unsigned int port = 0;
    const char* unix_socket = "NULL";
    const int verzoegerung = 10;
    unsigned long flags = 0;
    kommandobruecke enterprise(host, nutzername, passwort, tabelle, port, unix_socket, flags, verzoegerung);
    return 0;
}
