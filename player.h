#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"
#include <QWebSocket>


class Player
{
public:
    Player();
    //Name
    QString name;
    //Der Socket
    QWebSocket* socket;
    //Das Sielfeld
    int board[10][10];
    //Der Highscore
    int score;
    //DIe Liste der Schiffe
    Ship ships[10];
    //Ein Schiff setzten
    void setShip(int x, int y,int size, int orientation, int number);
    //Ist der Spieler gerade am Zug
    bool isPlaying = false;
    //Hat der Spieler alle Schiffe platziert
    bool hasPlacedShips = false;
    //Das Schiff anhande der Koordinaten bekommen
    Ship* getShipFromCoordinates(int x, int y);
    //Ist ein Schiff zerstört worden
    bool isShipDestroyed(int x,int y);
    //Das Schiff als zerstört anzeigen lassen
    void renderShipDestroyed(Ship* ship);
    //Wie viele Schiffe wurden schon zerstört
    int destroyed = 0;
};

#endif // PLAYER_H
