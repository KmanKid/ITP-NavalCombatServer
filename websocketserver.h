#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include "game.h"
#include <QObject>
#include <QStringLiteral>

#include <QWebSocket>
#include <QWebSocketServer>

#include <QUuid>

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    static WebSocketServer* getInstance(quint16 port, QObject *parent = 0);
    ~WebSocketServer();
private slots:
    void onTextMessageReceived(QString message);
    void onNewConnection();
    void onSocketDisconnected();
private:
    WebSocketServer(quint16 port, QObject *parent = 0);
    Game game;
    QWebSocketServer socketServer;
    QWebSocket* socketArray[2];
};

#endif // WEBSOCKETSERVER_H
