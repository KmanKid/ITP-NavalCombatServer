#include "player.h"

Player::Player()
{
    // for testing resons we will init with ships -> should be send from client
    socket = nullptr;

    this->ships[0] = Ship(0,5,1,0);
    this->ships[1] = Ship(0,7,1,0);
    this->ships[2] = Ship(6,6,1,0);
    this->ships[3] = Ship(8,6,1,0);
    this->ships[4] = Ship(4,3,2,1);
    this->ships[5] = Ship(4,6,2,1);
    this->ships[6] = Ship(6,8,2,1);
    this->ships[7] = Ship(0,9,3,0);
    this->ships[8] = Ship(2,1,3,0);
    this->ships[9] = Ship(0,0,4,1);
}
