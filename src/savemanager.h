#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QString>
#include <QGraphicsScene>
#include <QJsonObject>
#include "robot.h"
#include "obstacle.h"

class SaveManager
{
private:
    static void AddRobotToScene(QGraphicsScene* scene, qreal x, qreal y, bool rot_dir,
                         qreal rot_angle, qreal det_range, qreal rotation, qreal speed);
    static void AddObstacleToScene(QGraphicsScene* scene, qreal x, qreal y, qreal size);

    static QJsonObject makeRobotJson(const Robot *robot);
    static QJsonObject makeObstacleJson(const Obstacle *obstacle);
public:
    static void readJson(QString path, QGraphicsScene* scene);
    static void saveJson(QString path, QGraphicsScene* scene);
};

#endif // SAVEMANAGER_H
