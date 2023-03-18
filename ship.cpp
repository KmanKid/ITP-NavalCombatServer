#include "ship.h"

Ship::Ship()
{
    //Schiff initialisieren mit standartwerten
    this->posX = 0;
    this->posY = 0;
    this->length = 0;
    //Orientation can be 0 for horizontal and 1 for vertical
    this->orientation = 0;
}

Ship::Ship(int posX, int posY, int len, int ori)
{
    //Das Schiff mit benutzerdefinierten werten erzeugen
    this->posX = posX;
    this->posY = posY;
    this->length = len;
    //Orientation can be 0 for horizontal and 1 for vertical
    this->orientation = ori;
}
