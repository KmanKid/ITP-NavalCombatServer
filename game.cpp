#include "game.h"

Game::Game()
{
    playerOne.isPlaying = true;
}

//Die Nachricht wir bearbeitet
void Game::processMessage(QWebSocket* sender,QString message)
{
    //Die Nachricht wird an - geteilt
    QStringList mSplit = message.split("-");

    //Abhängig des ertsen Wortes werden verschiedene Funktionen aufgerufen
    if(mSplit[0] == "shoot" && playerOne.hasPlacedShips && playerTwo.hasPlacedShips)
    {
        //Schießen
        this->shoot(sender,mSplit[1].toInt(),mSplit[2].toInt());
    }

    if(sender == playerOne.socket)
    {
        if(mSplit[0] == "newShip")
        {
            //neues Schiff setzten
            this->playerOne.setShip(mSplit[1].toInt(),mSplit[2].toInt(),mSplit[3].toInt(),mSplit[4].toInt(),mSplit[5].toInt());
            sendShipPositions(&playerOne);
        }
    }
    if(sender==playerTwo.socket)
    {
        if(mSplit[0] == "newShip")
        {
            //neues Schiff setzten
            this->playerTwo.setShip(mSplit[1].toInt(),mSplit[2].toInt(),mSplit[3].toInt(),mSplit[4].toInt(),mSplit[5].toInt());
            sendShipPositions(&playerTwo);
        }
    }
}

//Der sender schießt auf das Spielfeld des jeweils anderen Spielers
void Game::shoot(QWebSocket* sender, int x, int y)
{
    //Wenn spieler 1 spielt
    if(playerOne.isPlaying)
    {
        //Den Zug aufschreiben
        savefileHandler.writeTurn(playerOne,x,y);
        //Wenn auf den Koordinaten ein Schiff ist
        if(playerTwo.board[x][y] == 1)
        {
            //Das Feld als getroffen markieren
            playerTwo.board[x][y] = 2;
            //Wenn das Schiff zerstört wurde
            if(playerTwo.isShipDestroyed(x,y))
            {
                //Eins mehr zerstört
                playerTwo.destroyed += 1;
                //Abhängig der länge den Score erhöhen
                playerOne.score += playerTwo.getShipFromCoordinates(x,y)->length*25;
                //Das Schiff als zerstört anzeigen
                playerOne.renderShipDestroyed(playerTwo.getShipFromCoordinates(x,y));
                //Dem Client sagen, dass das Feld getroffen wurde
                playerTwo.socket->sendTextMessage("setFieldState-left-" + QString::number(x) + "-"+ QString::number(y) + "-3");
            }else
            {
                //Wenn nicht zerstört beiden Spielern den Treffer anzeigen
                playerOne.socket->sendTextMessage("setFieldState-right-" + QString::number(x) + "-"+ QString::number(y) + "-4");
                playerTwo.socket->sendTextMessage("setFieldState-left-" + QString::number(x) + "-"+ QString::number(y) + "-3");
            }
        }
        //Wenn nichts getroffen wurde
        else if (!(playerTwo.board[x][y] == 2))
        {
            //Spieler 2 ist nun an der Reihe
            playerTwo.isPlaying = true;
            playerTwo.socket->sendTextMessage("yourTurn-0");
            //Spieler 1 ist nicht mher an der Reihe
            playerOne.isPlaying = false;
            playerOne.socket->sendTextMessage("notYourTurn-0");
            //Den beiden Spielern sagen sie sollen das verfehlen einzeichnen
            playerOne.socket->sendTextMessage("setFieldState-right-" + QString::number(x) + "-"+ QString::number(y) + "-1");
            playerTwo.socket->sendTextMessage("setFieldState-left-" + QString::number(x) + "-"+ QString::number(y) + "-1");
        }
    }else
    //Wenn spieler 2 spielt
    if(playerTwo.isPlaying)
    {
        //Den Zug aufschreiben
        savefileHandler.writeTurn(playerTwo,x,y);
        //Wenn auf den Koordinaten ein Schiff ist
        if(playerOne.board[x][y] == 1)
        {
            //Das Feld als getroffen markieren
            playerOne.board[x][y] = 2;
            //Wenn das Schiff zerstört wurde
            if(playerOne.isShipDestroyed(x,y))
            {
                //Eins mehr zerstört
                playerOne.destroyed += 1;
                //Abhängig der Länge den score erhöhen
                playerTwo.score += playerOne.getShipFromCoordinates(x,y)->length*25;
                //Das schiff als zerstört anzeigen lassen
                playerTwo.renderShipDestroyed(playerOne.getShipFromCoordinates(x,y));
                //Dem Client sagen, dass das Feld getroffen wurde
                playerOne.socket->sendTextMessage("setFieldState-left-" + QString::number(x) + "-"+ QString::number(y) + "-3");
            }else
            {
                //Wenn nicht zerstört beiden Spielern den Treffer anzeigen
                playerTwo.socket->sendTextMessage("setFieldState-right-" + QString::number(x) + "-"+ QString::number(y) + "-4");
                playerOne.socket->sendTextMessage("setFieldState-left-" + QString::number(x) + "-"+ QString::number(y) + "-3");
            }
        }else if (!(playerOne.board[x][y] == 2))
        {
            //Spieler 1 ist nun an der Reihe
            playerOne.isPlaying = true;
            playerOne.socket->sendTextMessage("yourTurn-0");
            //Spieler 2 ist nun nicht mehr an der Reihe
            playerTwo.isPlaying = false;
            playerTwo.socket->sendTextMessage("notYourTurn-0");
            //Beiden Spielern den Fehlschuss anzeigen lassen
            playerTwo.socket->sendTextMessage("setFieldState-right-" + QString::number(x) + "-"+ QString::number(y) + "-1");
            playerOne.socket->sendTextMessage("setFieldState-left-" + QString::number(x) + "-"+ QString::number(y) + "-1");
        }
    }
    //Die beiden Scores updaten
    playerOne.socket->sendTextMessage("setText-Score: " + QString::number(playerOne.score));
    playerTwo.socket->sendTextMessage("setText-Score: " + QString::number(playerTwo.score));
    //Wenn Spieler 1 alle Schiffe zertört hat
    if(playerTwo.destroyed==10)
    {
        //DIe beidien Spieler benachrichtigen
        playerTwo.socket->sendTextMessage("setText-You Lost");
        playerOne.socket->sendTextMessage("setText-You Won");
        //Das Ergebnis in der highscore csv speichern
        savefileHandler.saveNewGame(playerOne,playerTwo);
    }
    //Wenn Spieler 2 alle Schiffe zerstört hat
    if(playerOne.destroyed==10)
    {
        //Die beiden Spieler benachrichtigen
        playerTwo.socket->sendTextMessage("setText-You Won");
        playerOne.socket->sendTextMessage("setText-You Lost");
        //Das Ergebnis in der highscore csv speichern
        savefileHandler.saveNewGame(playerTwo,playerOne);
    }
}

//Bei Verbindungsaufbau
void Game::playerConnected(QWebSocket* socket)
{
    //Wenn es noch keinen Spieler 1 gab
    if(playerOne.socket == nullptr)
    {
        //Den socket dem Spieler zuweisen
        playerOne.socket = socket;
        //Anweisungen an den Spieler geben
        playerOne.socket->sendTextMessage("setText-Please place your ships!");
        //Default Namen geben
        playerOne.name = "Player One";

    }else
    //Wenn es noch keinen Spieler 2 gab
    if(playerTwo.socket == nullptr)
    {
        //Den socket dem Spieler zuweisen
        playerTwo.socket = socket;
        //Anweisungen an den Spieler geben
        playerTwo.socket->sendTextMessage("setText-Please place your ships!");
        //Default Namen geben
        playerTwo.name = "Player Two";
    }
    //Spieler 1 ist zuerst dran
    playerOne.socket->sendTextMessage("yourTurn-0");
}

//Die Schiffspositionen zum rendern an den Client schicken
void Game::sendShipPositions(Player* player)
{
    //Für jedes Schiff
    for (int i = 0; i < 10; i++)
    {
        //Wenn es kein Schiff gibt dann überspringen
        if (&player->ships[i] == NULL)
        {
            continue;
        }
        //Das Schiff auswählen
        Ship* currentShip = &player->ships[i];

        //Für die länge des Schiffes die Koordinaten dem Spieler senden
        for (int ii = 0; ii < currentShip->length; ii++)
        {
            if(currentShip->orientation == 0)
            {
                player->socket->sendTextMessage("setFieldState-left-" + QString::number(currentShip->posX + ii) + "-"+ QString::number(currentShip->posY) + "-2");
            }else
            {
                player->socket->sendTextMessage("setFieldState-left-" + QString::number(currentShip->posX) + "-"+ QString::number(currentShip->posY + ii) + "-2");
            }
        }
    }
}
