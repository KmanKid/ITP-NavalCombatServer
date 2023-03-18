#include "player.h"

Player::Player()
{
    //Ohne Socket initialisieren
    socket = nullptr;
    //Score startet bei 0
    score = 0;
}

//Das Schiff setzten
void Player::setShip(int x, int y,int size, int orientation, int number)
{
    //Ein neues Schiff erstellen und dem eigenen Array zuweisen
    this->ships[number] = Ship(x,y,size,orientation);
    //Für die Größe des Schiffes alle Felder durchgehen und auf das Board schreiben
    for(int i = 0; i < size; i++)
    {
        //horizontal
        if(orientation == 0)
        {
            board[x+i][y] = 1;
        }else
            //vertical
        if(orientation == 1)
        {
            board[x][y+i] = 1;
        }
    }
    if(number == 9)
    {
        this->hasPlacedShips = true;
    }
}

//Das Schiff anhand von Koordinaten zurückgeben
Ship* Player::getShipFromCoordinates(int x, int y)
{
    //Alle Schiffe durchgehen
    for(int i = 0; i < 10; i++)
    {
        //Prüfen ob vertikal
        if(ships[i].orientation == 0)
        {
            //Wenn die Koordinaten passen das Schiff zurückgeben
            if(x >= ships[i].posX && x < ships[i].posX + ships[i].length && ships[i].posY == y)
            {
                return &ships[i];
            }
        }
        //Wenn horizontal
        else
        {
            //Wenn die Koorinaten passen das Schiff zurückgeben
            if(y >= ships[i].posY && y < ships[i].posY + ships[i].length && ships[i].posX == x)
            {
                return &ships[i];
            }
        }
    }
    //Fallback nullpointer zurückgeben
    return nullptr;
}

//Gibt true zurück wenn das Schiff zerstört wurde
bool Player::isShipDestroyed(int x,int y)
{
    //Schiffobjekt bekommen
    Ship* ship = getShipFromCoordinates(x,y);
    //Für die gesamte länge...
    for (int i = 0; i < ship->length; i++)
    {
        //.. prüfen ob horizontal oder vertikal
        if(ship->orientation == 0)
        {
            //Abbrechen wenn es kein kaputtes Schiff ist
            if(!(board[ship->posX+i][ship->posY] == 2))
            {
                return false;
            }
        }
        if(ship->orientation == 1)
        {
            //Abbrechen wenn es kein kaputtes Schiff ist
            if(!(board[ship->posX][ship->posY+i] == 2))
            {
                return false;
            }
        }
    }
    //Das Schiff ist scheinbar zerstört
    return true;
}

//Das Schiff als zerstört anzeigen
void Player::renderShipDestroyed(Ship* ship)
{
    //Für die Schifflänge
    for (int i = 0; i < ship->length; i++)
    {
        //Entweder das 1er Schiff als zerstört anzeigen
        if(ship->length == 1)
        {
            socket->sendTextMessage("setFieldState-right-" + QString::number(ship->posX+i) + "-"+ QString::number(ship->posY) + "-10");
        }else
        {
            //Abhängig der Orientierung das schiff mit horizontalen oder vertikalen icons rendern
            //jeweils dem socket das Feld schicken
            if(ship->orientation == 0)
            {
                socket->sendTextMessage("setFieldState-right-" + QString::number(ship->posX+i) + "-"+ QString::number(ship->posY) + "-8");
            }else
            {
                socket->sendTextMessage("setFieldState-right-" + QString::number(ship->posX) + "-"+ QString::number(ship->posY+i) + "-9");
            }
        }
    }
}
