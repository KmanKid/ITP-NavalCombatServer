#include "server.h"

#include <QDateTime>

Server::Server(QObject* parent): QObject(parent)
{
    client=NULL;
    server=new QTcpServer;

  connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
  server->listen(QHostAddress::LocalHost, 8888);
}

Server::~Server()
{
  server->close();
  if(client != NULL)
     client->close();
  server->deleteLater();
}

void Server::acceptConnection()
{
  //Verbindung annehmen
    client = server->nextPendingConnection();
    connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
}

void Server::startRead(){

  QTcpSocket *socket = (QTcpSocket* ) QObject::sender();

  if ( socket->canReadLine() )
  {
        QTextStream os( socket );
        os.setAutoDetectUnicode( true );
        QString message = socket->readLine();
        qDebug() << message;
        os << "Du hast mir: " << message << "gesendet";
        socket->close();
        if ( socket->state() == QTcpSocket::UnconnectedState )
        {
            delete socket;
        }
  }
}
