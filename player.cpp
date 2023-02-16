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

Ship* Player::getShipFromCoordinates(int x, int y)
{
    for(int i = 0; i < 10; i++)
    {
        if(ships[i].orientation == 0)
        {
            if(x >= ships[i].posX && x < ships[i].posX + ships[i].length && ships[i].posY == y)
            {
                return &ships[i];
            }
        }else
        {
            if(y >= ships[i].posY && y < ships[i].posY + ships[i].length && ships[i].posX == x)
            {
                return &ships[i];
            }
        }
    }
    return nullptr;
}

bool Player::isShipDestroyed(int x,int y)
{
    Ship* ship = getShipFromCoordinates(x,y);
    for (int i = 0; i < ship->length; i++)
    {
        if(ship->orientation == 0)
        {
            if(!(board[ship->posX+i][ship->posY] == 2))
            {
                return false;
            }
        }
        if(ship->orientation == 1)
        {
            if(!(board[ship->posX][ship->posY+i] == 2))
            {
                return false;
            }
        }
    }
    return true;
}

void Player::renderShipDestroyed(Ship* ship)
{
    for (int i = 0; i < ship->length; i++)
    {
        if(ship->length == 1)
        {
            socket->sendTextMessage("setFieldState-right-" + QString::number(ship->posX+i) + "-"+ QString::number(ship->posY) + "-10");
        }else
        {
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
