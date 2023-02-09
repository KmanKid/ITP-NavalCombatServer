#include <QCoreApplication>
#include "websocketserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WebSocketServer server = WebSocketServer(8888);
    return a.exec();
}
