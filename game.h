#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "player.h"
#include "ncsavefilehandler.h"

class Game
{
public:
    Game();
    Player playerOne;
    Player playerTwo;
    NCSaveFileHandler savefileHandler;
    void processMessage(QWebSocket* sender,QString message);
    void shoot(QWebSocket* sender, int x, int y);
    void playerConnected(QWebSocket* socket);
    void sendShipPositions(Player* player);
};

#endif // GAME_H
