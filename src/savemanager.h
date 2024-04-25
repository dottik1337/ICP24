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
    void AddRobotToScene(QGraphicsScene* scene, qreal x, qreal y, bool rot_dir,
                         qreal rot_angle, qreal det_range, qreal rotation, qreal speed);
    void AddObstacleToScene(QGraphicsScene* scene, qreal x, qreal y, qreal size);

    QJsonObject makeRobotJson(const Robot *robot);
    QJsonObject makeObstacleJson(const Obstacle *obstacle);
public:
    SaveManager();
    void readJson(QString path, QGraphicsScene* scene);
    void saveJson(QString path, QGraphicsScene* scene);
};

#endif // SAVEMANAGER_H
