#include "game.h"

Game::Game()
{
    playerOne.isPlaying = true;
}

void Game::processMessage(QWebSocket* sender,QString message)
{
    QStringList mSplit = message.split("-");

    if(mSplit[0] == "shoot" && playerOne.hasPlacedShips && playerTwo.hasPlacedShips)
    {
        this->shoot(sender,mSplit[1].toInt(),mSplit[2].toInt());
    }

    if(sender == playerOne.socket)
    {
        if(mSplit[0] == "newShip")
        {
            this->playerOne.setShip(mSplit[1].toInt(),mSplit[2].toInt(),mSplit[3].toInt(),mSplit[4].toInt(),mSplit[5].toInt());
            sendShipPositions(&playerOne);
        }
    }
    if(sender==playerTwo.socket)
    {
        if(mSplit[0] == "newShip")
        {
            this->playerTwo.setShip(mSplit[1].toInt(),mSplit[2].toInt(),mSplit[3].toInt(),mSplit[4].toInt(),mSplit[5].toInt());
            sendShipPositions(&playerTwo);
        }
    }
}

void Game::shoot(QWebSocket* sender, int x, int y)
{
    qDebug() << "Player 1 playing: " << playerOne.isPlaying;
    qDebug() << "Player 2 playing: " << playerTwo.isPlaying;
    if(playerOne.isPlaying)
    {
        if(playerTwo.board[x][y] == 1)
        {
            playerTwo.board[x][y] = 2;
            if(playerTwo.isShipDestroyed(x,y))
            {
                playerTwo.destroyed += 1;
                playerOne.score += 100;
                playerOne.renderShipDestroyed(playerTwo.getShipFromCoordinates(x,y));
            }else
            {
                sender->sendTextMessage("setFieldState-right-" + QString::number(x) + "-"+ QString::number(y) + "-4");
            }
        }else if (!(playerTwo.board[x][y] == 2))
        {
            playerTwo.isPlaying = true;
            playerTwo.socket->sendTextMessage("yourTurn-0");
            playerOne.isPlaying = false;
            playerOne.socket->sendTextMessage("notYourTurn-0");
            sender->sendTextMessage("setFieldState-right-" + QString::number(x) + "-"+ QString::number(y) + "-1");
        }
    }else
    if(playerTwo.isPlaying)
    {
        if(playerOne.board[x][y] == 1)
        {
            playerOne.board[x][y] = 2;
            if(playerOne.isShipDestroyed(x,y))
            {
                playerOne.destroyed += 1;
                playerTwo.score += 100;
                playerTwo.renderShipDestroyed(playerOne.getShipFromCoordinates(x,y));
            }else
            {
                sender->sendTextMessage("setFieldState-right-" + QString::number(x) + "-"+ QString::number(y) + "-4");
            }
        }else if (!(playerOne.board[x][y] == 2))
        {
            playerOne.isPlaying = true;
            playerOne.socket->sendTextMessage("yourTurn-0");
            playerTwo.isPlaying = false;
            playerTwo.socket->sendTextMessage("notYourTurn-0");
            sender->sendTextMessage("setFieldState-right-" + QString::number(x) + "-"+ QString::number(y) + "-1");
        }
    }
    playerTwo.socket->sendTextMessage("setText-Destroyed: " + QString::number(playerOne.destroyed));
    playerOne.socket->sendTextMessage("setText-Destroyed: " + QString::number(playerTwo.destroyed));
}

void Game::playerConnected(QWebSocket* socket)
{
    if(playerOne.socket == nullptr)
    {
        qDebug() << "registered Player One";
        playerOne.socket = socket;
        playerOne.socket->sendTextMessage("setText-Please place your ships!");

    }else if(playerTwo.socket == nullptr)
    {
        qDebug() << "registered Player Two";
        playerTwo.socket = socket;
        playerTwo.socket->sendTextMessage("setText-Please place your ships!");
    }
    playerOne.socket->sendTextMessage("yourTurn-0");
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
