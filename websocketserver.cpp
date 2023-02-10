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

    if(game.playerOne.socket == nullptr)
    {
        game.playerOne.socket = socket;
        socket->sendTextMessage(QString("Player:1"));
    }else if (game.playerTwo.socket == nullptr)
    {
        game.playerTwo.socket = socket;
        socket->sendTextMessage(QString("Player:2"));
    }

    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageReceived);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::onBinaryMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onSocketDisconnected);
}

void WebSocketServer::onTextMessageReceived(QString message) {
    // This method has been deprecated.
    game.processMessage(qobject_cast<QWebSocket *>(sender()),message);
}

void WebSocketServer::onSocketDisconnected() {
    // Get the disconnected socket
    qDebug() << "Socket Connected";
}

void WebSocketServer::onBinaryMessageReceived(QByteArray message)
{

}
