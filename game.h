#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "player.h"
#include "ncsavefilehandler.h"

class Game
{
public:
    Game();
    //Player Objekte für die beden Spieler
    Player playerOne;
    Player playerTwo;
    //Der Filehandler für die CSV-Datei
    NCSaveFileHandler savefileHandler;
    //Abarbeiten der Client-Nachricht
    void processMessage(QWebSocket* sender,QString message);
    //Schussfunktion
    void shoot(QWebSocket* sender, int x, int y);
    //Wenn ein Spieler die Verbindung aufbaut
    void playerConnected(QWebSocket* socket);
    //Die Schiffpositionen schicken
    void sendShipPositions(Player* player);
};

#endif // GAME_H
