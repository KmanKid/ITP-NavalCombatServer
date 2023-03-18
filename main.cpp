#include <QCoreApplication>
#include "websocketserver.h"

int main(int argc, char *argv[])
{
    //Applikation erstellen
    QCoreApplication a(argc, argv);
    //Server erstellen
    WebSocketServer server = WebSocketServer(8888);
    //Ausführen
    return a.exec();
}
