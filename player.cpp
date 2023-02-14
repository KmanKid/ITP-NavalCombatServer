#include "player.h"

Player::Player()
{
    socket = nullptr;
}

void Player::setShip(int x, int y,int size, int orientation, int number)
{
    this->ships[number] = Ship(x,y,size,orientation);
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
