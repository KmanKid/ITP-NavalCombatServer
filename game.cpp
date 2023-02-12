#include "game.h"

Game::Game()
{

}

void Game::processMessage(QWebSocket* sender,QString message)
{
    QStringList mSplit = message.split("-");
    if(mSplit[0] == "shot")
    {
        this->shoot(sender,mSplit[1].toInt(),mSplit[2].toInt());
    }

    if(sender == playerOne.socket)
    {
        //sender->sendTextMessage("setFieldState-left-0-3-3");
        qDebug() << "Player One send: " << message;
    }
    if(sender==playerTwo.socket)
    {
        qDebug() << "Player Two send: " << message;
    }
}

int Game::shoot(QWebSocket* sender, int x, int y)
{

}

void Game::playerConnected(QWebSocket* socket)
{
    if(playerOne.socket == nullptr)
    {
        playerOne.socket = socket;
        sendShipPositions(&playerOne);
        //playerOne.socket->sendTextMessage("setFieldState-left-0-3-3");
    }
    if(playerTwo.socket == nullptr)
    {
        playerTwo.socket = socket;
        sendShipPositions(&playerTwo);
        //playerTwo.socket->sendTextMessage("setFieldState-left-0-3-3");
    }
}

void Game::sendShipPositions(Player* player)
{
    for (int i = 0; i < 10; i++)
    {
        if (&player->ships[i] == NULL)
        {
            continue;
        }
        Ship* currentShip = &player->ships[i];
        qDebug() << "processing:" << currentShip->length;

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
