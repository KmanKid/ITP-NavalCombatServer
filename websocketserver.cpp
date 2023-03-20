#include "websocketserver.h"

WebSocketServer* WebSocketServer::getInstance(quint16 port, QObject *parent)
{
    static WebSocketServer instance = WebSocketServer(port,parent);
    return &instance;
}

WebSocketServer::WebSocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    socketServer(QStringLiteral("ITP-Project Server"), QWebSocketServer::NonSecureMode, this)
{
    //Die beiden slots mit nullpointern initialisieren
    socketArray[0] = nullptr;
    socketArray[1] = nullptr;

    //Server versucht auf port zu horchen wenn nicht fehlermeldung
    if (!socketServer.listen(QHostAddress::Any, port)) {
        qFatal("Failed to open web socket server.");
    }
    //Ausgabe falls port vergessen
    qDebug() << "WebSocket server listening on port" << socketServer.serverPort() << " URL:" <<socketServer.serverUrl();
    //Die Funktion bei einer neuen Verbindung verknüpfen
    connect(&socketServer, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
}

WebSocketServer::~WebSocketServer() {
    //Den server schließen und die Sockets zurücksetzten
    socketServer.close();
    socketArray[0] = nullptr;
    socketArray[1] = nullptr;
}

//Bei einer neuen VErbindung
void WebSocketServer::onNewConnection() {
    //Der socket ist die nächste Verbindung
    QWebSocket *socket = socketServer.nextPendingConnection();

    //Die Connected Funktion des Spieles aufrufen
    game.playerConnected(socket);

    //Die verschieden Funktionen des Spiels mit den jeweiligen socket signalen verknüpfen
    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onSocketDisconnected);
}

void WebSocketServer::onTextMessageReceived(QString message) {
    //weiterleitung an Game
    game.processMessage(qobject_cast<QWebSocket *>(sender()),message);
}

void WebSocketServer::onSocketDisconnected() {
    //Hier könnte man ein Handling einbauen das eine Reconnection möglich macht
    //NAchricht das Socket disconnected ist
    qDebug() << "Socket Connected";
}
