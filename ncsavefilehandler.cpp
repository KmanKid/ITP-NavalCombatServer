#include "ncsavefilehandler.h"

NCSaveFileHandler::NCSaveFileHandler()
{
    //Die Pfade für die Dateien setzten
    highscores.setFileName("./highscores.csv");
    file.setFileName("./savegame.csv");
    //Die Spalten benennen
    file.open(QIODevice::Append);
    file.write("New Game\nPlaying;Shot at X;Shot at Y\n");
    file.close();
}

NCSaveFileHandler::~NCSaveFileHandler()
{
}

void NCSaveFileHandler::saveNewGame(Player one, Player two)
{
    //Highscore Datei öfnnen
    highscores.open(QIODevice::Append);
    //NAchricht mit den Namen und den beiden Scores  schreiben
    QString message = one.name + ";" + QString::number(one.score)+ ";"+two.name+";"+QString::number(two.score)+"\n";
    highscores.write(message.toUtf8());
    highscores.close();
}

void NCSaveFileHandler::writeTurn(Player p, int xCoord, int yCoord)
{
    //Log Datei öffnen
    file.open(QIODevice::Append);
    //Name und Feld auf das gklickt wurde speichern
    QString message = p.name + ";" + QString::number(xCoord)+ ";"+QString::number(yCoord)+"\n";
    file.write(message.toUtf8());
    file.close();
}
