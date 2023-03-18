#ifndef SHIP_H
#define SHIP_H


class Ship
{
public:
    Ship();
    Ship(int posX, int posY, int len, int ori);
    //X-Koordinate Bug
    int posX;
    //Y-Koordinate Bug
    int posY;
    //Länge
    int length;
    //Orientation ist entweder 0 für Vertikal oder 1 für horizontal
    int orientation;
};

#endif // SHIP_H
