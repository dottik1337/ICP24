#include "savemanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

SaveManager::SaveManager()
{

}

void SaveManager::readJson(QString path){
    QString val;
    QFile file;
    QJsonDocument doc;

    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    doc = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject info = doc.object();

    if(info.isEmpty()){
        qWarning() << "Syntax Error";
        return;
    }

    QJsonArray robots = info.value(QString("robots")).toArray();
    QJsonArray obstacles = info.value(QString("obstacles")).toArray();


    qWarning() << "Robots";
    for (auto it = robots.begin(); it != robots.end();it++){
        QJsonObject robot = it->toObject();
        QJsonValue x = robot["x"];
        QJsonValue y =robot["y"];
        QJsonValue rotation = robot["rotation"];
        qWarning() << x.toInt() << y.toInt();
    }
    qWarning() << "Obstacles";
    for (auto it = obstacles.begin(); it != obstacles.end();it++){
        QJsonObject obstacle = it->toObject();
        QJsonValue x = obstacle["x"];
        QJsonValue y =obstacle["y"];
        QJsonValue size = obstacle["size"];
        qWarning() << x.toInt() << y.toInt() << size.toInt();
    }
}
