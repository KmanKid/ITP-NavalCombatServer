#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"
#include <QWebSocket>


class Player
{
public:
    Player();
    // 0 means water, 1 means my Ship, 2 means my Ship hit -> enum ?
    QWebSocket* socket;
    int board[10][10];
    int score;
    Ship ships[10];
    void setShip(int x, int y,int size, int orientation, int number);
    bool isPlaying = false;
    bool hasPlacedShips = false;
    Ship* getShipFromCoordinates(int x, int y);
    bool isShipDestroyed(int x,int y);
    void renderShipDestroyed(Ship* ship);
    int destroyed = 0;
};

#endif // PLAYER_H
