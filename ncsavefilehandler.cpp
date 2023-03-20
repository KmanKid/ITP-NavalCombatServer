#include "ncsavefilehandler.h"

NCSaveFileHandler::NCSaveFileHandler()
{
    //Die Pfade für die Datei setzten
    highscores.setFileName("./highscores.csv");
    //Die Spalten benennen
    highscores.open(QIODevice::Append);
    highscores.write("Player One;Score;Player Two;Score;Time\n");
    highscores.close();
    //Die Pfade für die Datei setzten
    file.setFileName("./savegame.csv");
    //Die Spalten benennen
    file.open(QIODevice::Append);
    file.write("New Game\nPlaying;Shot at X;Shot at Y;Time\n");
    file.close();
}

NCSaveFileHandler::~NCSaveFileHandler()
{
}

void NCSaveFileHandler::saveNewGame(Player one, Player two)
{
    //Get current time
    QDateTime timeNow = QDateTime::currentDateTime();
    //Highscore Datei öfnnen
    highscores.open(QIODevice::Append);
    //NAchricht mit den Namen und den beiden Scores  schreiben
    QString message = one.name + ";" + QString::number(one.score)+ ";"+two.name+";"+QString::number(two.score)+";"+timeNow.toString()+"\n";
    highscores.write(message.toUtf8());
    highscores.close();
}

void NCSaveFileHandler::writeTurn(Player p, int xCoord, int yCoord)
{
    //Get current time
    QDateTime timeNow = QDateTime::currentDateTime();
    //Log Datei öffnen
    file.open(QIODevice::Append);
    //Name und Feld auf das gklickt wurde speichern
    QString message = p.name + ";" + QString::number(xCoord)+ ";"+QString::number(yCoord)+";"+timeNow.toString()+"\n";
    file.write(message.toUtf8());
    file.close();
}
