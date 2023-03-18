#ifndef NCSAVEFILEHANDLER_H
#define NCSAVEFILEHANDLER_H
#include <QFile>
#include <player.h>


class NCSaveFileHandler
{
public:
    NCSaveFileHandler();
    //Ein neues spiel Speichern
    void saveNewGame(Player one, Player two);
    //Ein neuen Spielzug loggen
    void writeTurn(Player p, int xCoord, int yCoord);
    //Falls ein Event auftritt diese loggen
    void writeEvent(Player p, QString eventDefinition);
    ~NCSaveFileHandler();
private:
    //Die Haupt-Logfile
    QFile file;
    //Die Highscore File
    QFile highscores;
};

#endif // NCSAVEFILEHANDLER_H
