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
    int getNextFieldState(QWebSocket* sender, int x, int y);
};

#endif // GAME_H
