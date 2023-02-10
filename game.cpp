#include "game.h"

Game::Game()
{

}

void Game::processMessage(QWebSocket* sender,QString message)
{
    if(sender==playerOne.socket)
    {
        qDebug() << "Player One send: " << message;
    }
    if(sender==playerTwo.socket)
    {
        qDebug() << "Player Two send: " << message;
    }
}

