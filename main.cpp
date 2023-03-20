#include <QCoreApplication>
#include "websocketserver.h"

int main(int argc, char *argv[])
{
    //Applikation erstellen
    QCoreApplication a(argc, argv);
    //Server erstellen
    WebSocketServer* server = WebSocketServer::getInstance(8888);
    //Ausführen
    return a.exec();
}
