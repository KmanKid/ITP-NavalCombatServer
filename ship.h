#ifndef SHIP_H
#define SHIP_H


class Ship
{
public:
    Ship();
    int posX;
    int posY;
    int length;
    //Orientation can be 0 for horizontal and 1 for vertical
    int orientation;
};

#endif // SHIP_H
