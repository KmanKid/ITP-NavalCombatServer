#ifndef NCSAVEFILEHANDLER_H
#define NCSAVEFILEHANDLER_H
#include <QFile>
#include <player.h>


class NCSaveFileHandler
{
public:
    NCSaveFileHandler();
    void saveNewGame(Player one, Player two);
    void writeTurn(Player p, int xCoord, int yCoord);
    void writeEvent(Player p, QString eventDefinition);
    ~NCSaveFileHandler();
private:
    QFile file;
    QFile highscores;
};

#endif // NCSAVEFILEHANDLER_H
