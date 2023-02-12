#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "player.h"

class Game
{
public:
    Game();
    Player playerOne;
    Player playerTwo;
    void processMessage(QWebSocket* sender,QString message);
    int shoot(QWebSocket* sender, int x, int y);
    void playerConnected(QWebSocket* socket);
    void sendShipPositions(Player* player);
};

#endif // GAME_H
