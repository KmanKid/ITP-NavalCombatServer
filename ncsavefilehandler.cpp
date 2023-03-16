#include "ncsavefilehandler.h"

NCSaveFileHandler::NCSaveFileHandler()
{
    highscores.setFileName("./highscores.csv");
    file.setFileName("./savegame.csv");
    file.open(QIODevice::Append);
    file.write("New Game\nPlaying;Shot at X;Shot at Y\n");
}

NCSaveFileHandler::~NCSaveFileHandler()
{
}

void NCSaveFileHandler::saveNewGame(Player one, Player two)
{
    highscores.open(QIODevice::Append);
    QString message = one.name + ";" + QString::number(one.score)+ ";"+two.name+";"+QString::number(two.score)+"\n";
    highscores.write(message.toUtf8());
    highscores.close();
}

void NCSaveFileHandler::writeTurn(Player p, int xCoord, int yCoord)
{
    file.open(QIODevice::Append);
    QString message = p.name + ";" + QString::number(xCoord)+ ";"+QString::number(yCoord)+"\n";
    file.write(message.toUtf8());
    file.close();
}
