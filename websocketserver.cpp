#include "websocketserver.h"

WebSocketServer::WebSocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    socketServer(QStringLiteral("ITP-Project Server"), QWebSocketServer::NonSecureMode, this)
{
    socketArray[0] = nullptr;
    socketArray[1] = nullptr;

    if (!socketServer.listen(QHostAddress::Any, port)) {
        qFatal("Failed to open web socket server.");
    }
    qDebug() << "WebSocket server listening on port" << socketServer.serverPort() << " URL:" <<socketServer.serverUrl();
    connect(&socketServer, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
}

WebSocketServer::~WebSocketServer() {
    socketServer.close();
    socketArray[0] = nullptr;
    socketArray[1] = nullptr;
}

void WebSocketServer::onNewConnection() {
    QWebSocket *socket = socketServer.nextPendingConnection();

    if(socketArray[0] != nullptr)
    {
        socketArray[1] = socket;
        socket->sendTextMessage(QString("Player:2"));
    }else
    {
        socketArray[0] = socket;
        socket->sendTextMessage(QString("Player:1"));
    }

    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageReceived);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::onBinaryMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onSocketDisconnected);
}

void WebSocketServer::onTextMessageReceived(QString message) {
    // This method has been deprecated.
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
    if(socket == socketArray[0])
    {
        qDebug() << "Player One send:";
    }
    if(socket == socketArray[1])
    {
        qDebug() << "Player Two send:";
    }

    qDebug() << message;
}

void WebSocketServer::onSocketDisconnected() {
    // Get the disconnected socket
    qDebug() << "Socket Connected";
}

void WebSocketServer::onBinaryMessageReceived(QByteArray message)
{

}
