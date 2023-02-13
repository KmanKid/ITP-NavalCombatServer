#include "player.h"

Player::Player()
{
    socket = nullptr;
}

void Player::setShip(int x, int y,int size, int orientation, int number)
{
    this->ships[number] = Ship(x,y,size,orientation);
}
