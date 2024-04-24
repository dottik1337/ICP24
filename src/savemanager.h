#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QString>


class SaveManager
{
public:
    SaveManager();
    void readJson(QString path);
};

#endif // SAVEMANAGER_H
