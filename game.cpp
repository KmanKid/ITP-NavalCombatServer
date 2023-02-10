#include "game.h"

Game::Game()
{

}

void Game::processMessage(QWebSocket* sender,QString message)
{
    QStringList mSplit = message.split("-");
    if(mSplit[0] == "clk")
    {
        this->getNextFieldState(sender,mSplit[2].toInt(),mSplit[3].toInt());
    }

    if(sender == playerOne.socket)
    {
        sender->sendTextMessage("sFS-left-0-3-3");
        qDebug() << "Player One send: " << message;
    }
    if(sender==playerTwo.socket)
    {
        qDebug() << "Player Two send: " << message;
    }
}

int Game::getNextFieldState(QWebSocket* sender, int x, int y)
{

}
